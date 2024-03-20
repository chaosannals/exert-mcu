#include "main.h"
#include "w5500.h"
#include "usart_print.h"
#include <socket.h>
#include <stdbool.h>
#include <wizchip_conf.h>
#include <DHCP/dhcp.h>
#include <DNS/dns.h>

extern SPI_HandleTypeDef hspi1;

uint8_t dhcp_buffer[1024];
uint8_t dns_buffer[1024];

#define MY_DHCP_SOCKET     0
#define MY_DNS_SOCKET      1
#define MY_HTTP_SOCKET     2

volatile bool ip_assigned = false;

void Callback_IPAssigned(void) {
    UART_Printf("Callback: IP assigned! Leased time: %d sec\r\n", getDHCPLeasetime());
    ip_assigned = true;
}

void Callback_IPConflict(void) {
    UART_Printf("Callback: IP conflict!\r\n");
}

void W5500_Select(void) {
    HAL_GPIO_WritePin(W5500_CSN_GPIO_Port, W5500_CSN_Pin, GPIO_PIN_RESET);
}

void W5500_Unselect(void) {
    HAL_GPIO_WritePin(W5500_CSN_GPIO_Port, W5500_CSN_Pin, GPIO_PIN_SET);
}

void W5500_ReadBuff(uint8_t* buff, uint16_t len) {
    HAL_SPI_Receive(&hspi1, buff, len, HAL_MAX_DELAY);
}

void W5500_WriteBuff(uint8_t* buff, uint16_t len) {
    HAL_SPI_Transmit(&hspi1, buff, len, HAL_MAX_DELAY);
}

uint8_t W5500_ReadByte(void) {
    uint8_t byte;
    W5500_ReadBuff(&byte, sizeof(byte));
    return byte;
}

void W5500_WriteByte(uint8_t byte) {
    W5500_WriteBuff(&byte, sizeof(byte));
}

void W5500_Init(void) {
	reg_wizchip_cs_cbfunc(W5500_Select, W5500_Unselect);
	reg_wizchip_spi_cbfunc(W5500_ReadByte, W5500_WriteByte);
	reg_wizchip_spiburst_cbfunc(W5500_ReadBuff, W5500_WriteBuff);


	uint8_t rx_tx_buff_sizes[] = {2, 2, 2, 2, 2, 2, 2, 2};
	int8_t r1 = wizchip_init(rx_tx_buff_sizes, rx_tx_buff_sizes);
	UART_Printf("wizchip_init %d\r\n", r1);


	// DHCP client 初始化
	UART_Printf("Calling DHCP_init()...\r\n");
	wiz_NetInfo net_info = {
		.mac  = { 0xEA, 0x11, 0x22, 0x33, 0x44, 0xEA },
		.dhcp = NETINFO_DHCP
	};
	// set MAC address before using DHCP
	setSHAR(net_info.mac);
	DHCP_init(MY_DHCP_SOCKET, dhcp_buffer);

	UART_Printf("Registering DHCP callbacks...\r\n");
	reg_dhcp_cbfunc(
		Callback_IPAssigned,
		Callback_IPAssigned,
		Callback_IPConflict
	);

	UART_Printf("Calling DHCP_run()...\r\n");
	// actually should be called in a loop, e.g. by timer
	uint32_t ctr = 10000;
	while((!ip_assigned) && (ctr > 0)) {
		uint8_t r2 = DHCP_run();
		ctr--;
		UART_Printf("try DHCP %d  %d\r\n", ctr, r2);
	}
	if(!ip_assigned) {
		UART_Printf("\r\nIP was not assigned :(\r\n");
		return;
	}

	getIPfromDHCP(net_info.ip);
	getGWfromDHCP(net_info.gw);
	getSNfromDHCP(net_info.sn);

	// DNS
	uint8_t dns[4];
	getDNSfromDHCP(dns);

	UART_Printf("IP:  %d.%d.%d.%d\r\nGW:  %d.%d.%d.%d\r\nNet: %d.%d.%d.%d\r\nDNS: %d.%d.%d.%d\r\n",
		net_info.ip[0], net_info.ip[1], net_info.ip[2], net_info.ip[3],
		net_info.gw[0], net_info.gw[1], net_info.gw[2], net_info.gw[3],
		net_info.sn[0], net_info.sn[1], net_info.sn[2], net_info.sn[3],
		dns[0], dns[1], dns[2], dns[3]
	);

	UART_Printf("Calling wizchip_setnetinfo()...\r\n");
	wizchip_setnetinfo(&net_info);

	UART_Printf("Calling DNS_init()...\r\n");
	DNS_init(MY_DNS_SOCKET, dns_buffer);

	uint8_t addr[4];
	{
		char domain_name[] = "baidu.com";
		UART_Printf("Resolving domain name \"%s\"...\r\n", domain_name);
		int8_t res = DNS_run(dns, (uint8_t*)&domain_name, addr);
		if(res != 1) {
			UART_Printf("DNS_run() failed, res = %d", res);
			return;
		}
		UART_Printf("Result: %d.%d.%d.%d\r\n", addr[0], addr[1], addr[2], addr[3]);
	}


	// HTTP
	UART_Printf("Creating socket...\r\n");
	uint8_t http_socket = MY_HTTP_SOCKET;
	uint8_t code = socket(http_socket, Sn_MR_TCP, 10888, 0);
	if(code != http_socket) {
		UART_Printf("socket() failed, code = %d\r\n", code);
		return;
	}

	UART_Printf("Socket created, connecting...\r\n");
	code = connect(http_socket, addr, 80);
	if(code != SOCK_OK) {
		UART_Printf("connect() failed, code = %d\r\n", code);
		close(http_socket);
		return;
	}

	UART_Printf("Connected, sending HTTP request...\r\n");
	{
		char req[] = "GET / HTTP/1.0\r\nHost: baidu.com\r\n\r\n";
		uint16_t len = sizeof(req) - 1;
		uint8_t* buff = (uint8_t*)&req;
		while(len > 0) {
			UART_Printf("Sending %d bytes...\r\n", len);
			int32_t nbytes = send(http_socket, buff, len);
			if(nbytes <= 0) {
				UART_Printf("send() failed, %d returned\r\n", nbytes);
				close(http_socket);
				return;
			}
			UART_Printf("%d bytes sent!\r\n", nbytes);
			len -= nbytes;
		}
	}

	UART_Printf("Request sent. Reading response...\r\n");
	{
		char buff[32];
		for(;;) {
			int32_t nbytes = recv(http_socket, (uint8_t*)&buff, sizeof(buff)-1);
			if(nbytes == SOCKERR_SOCKSTATUS) {
				UART_Printf("\r\nConnection closed.\r\n");
				break;
			}

			if(nbytes <= 0) {
				UART_Printf("\r\n recv() failed, %d returned\r\n", nbytes);
				break;
			}

			buff[nbytes] = '\0';
			UART_Printf("%s", buff);
		}
	}

	UART_Printf("Closing socket.\r\n");
	close(http_socket);
}
