#include "esp_log.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_tls.h"
#include "esp_eth.h"
#include "esp_netif.h"
#include "esp_http_server.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/param.h>
// #include <ctype.h>

#include "chip.h"
#include "spiffs_demo.h"
#include "wifi_sta_demo.h"
#include "ngx_code.h"
#include "main.h"

#define EXAMPLE_HTTP_QUERY_KEY_MAX_LEN  (64)

// 路由定义开始 ===============================================

void example_uri_decode(char *dest, const char *src, size_t len)
{
    if (!src || !dest) {
        return;
    }

    unsigned char *src_ptr = (unsigned char *)src;
    unsigned char *dst_ptr = (unsigned char *)dest;
    ngx_unescape_uri(&dst_ptr, &src_ptr, len, NGX_UNESCAPE_URI);
}

uint32_t example_uri_encode(char *dest, const char *src, size_t len)
{
    if (!src || !dest) {
        return 0;
    }

    uintptr_t ret = ngx_escape_uri((unsigned char *)dest, (unsigned char *)src, len, NGX_ESCAPE_URI_COMPONENT);
    return (uint32_t)(ret - (uintptr_t)dest);
}

static esp_err_t hello_get_handler(httpd_req_t *req)
{
    char*  buf;
    size_t buf_len;

    /* 获取头部字段值的长度 + 1, C 字符串结尾 */
    buf_len = httpd_req_get_hdr_value_len(req, "Host") + 1;
    if (buf_len > 1) {
        buf = malloc(buf_len);
        // ESP_RETURN_ON_FALSE(buf, ESP_ERR_NO_MEM, TAG, "buffer alloc failed");
        if (!buf) {
          printf("buffer alloc failed\n");
          return ESP_ERR_NO_MEM;
        }

        /* 复制头部字段到缓存 */
        if (httpd_req_get_hdr_value_str(req, "Host", buf, buf_len) == ESP_OK) {
            // ESP_LOGI(TAG, "Found header => Host: %s", buf);
            printf("Found header => Host: %s\n", buf);
        }
        free(buf);
    }

    buf_len = httpd_req_get_hdr_value_len(req, "Test-Header-2") + 1;
    if (buf_len > 1) {
        buf = malloc(buf_len);
        // ESP_RETURN_ON_FALSE(buf, ESP_ERR_NO_MEM, TAG, "buffer alloc failed");
        if (!buf) {
          printf("buffer alloc failed\n");
          return ESP_ERR_NO_MEM;
        }
        if (httpd_req_get_hdr_value_str(req, "Test-Header-2", buf, buf_len) == ESP_OK) {
            // ESP_LOGI(TAG, "Found header => Test-Header-2: %s", buf);
            printf("Found header => Test-Header-2: %s\n", buf);
        }
        free(buf);
    }

    buf_len = httpd_req_get_hdr_value_len(req, "Test-Header-1") + 1;
    if (buf_len > 1) {
        buf = malloc(buf_len);
        // ESP_RETURN_ON_FALSE(buf, ESP_ERR_NO_MEM, TAG, "buffer alloc failed");
        if (!buf) {
          printf("buffer alloc failed\n");
          return ESP_ERR_NO_MEM;
        }
        if (httpd_req_get_hdr_value_str(req, "Test-Header-1", buf, buf_len) == ESP_OK) {
            // ESP_LOGI(TAG, "Found header => Test-Header-1: %s", buf);
            printf("Found header => Test-Header-1: %s\n", buf);
        }
        free(buf);
    }

    /* 读取 URL 查询字符串长度 + 1, C 字符串结尾 */
    buf_len = httpd_req_get_url_query_len(req) + 1;
    if (buf_len > 1) {
        buf = malloc(buf_len);
        // ESP_RETURN_ON_FALSE(buf, ESP_ERR_NO_MEM, TAG, "buffer alloc failed");
        if (!buf) {
          printf("buffer alloc failed\n");
          return ESP_ERR_NO_MEM;
        }

        if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK) {
            // ESP_LOGI(TAG, "Found URL query => %s", buf);
            printf("Found URL query => %s\n", buf);
            char param[EXAMPLE_HTTP_QUERY_KEY_MAX_LEN], dec_param[EXAMPLE_HTTP_QUERY_KEY_MAX_LEN] = {0};
            /* 查询字符串的值分离 */
            if (httpd_query_key_value(buf, "query1", param, sizeof(param)) == ESP_OK) {
                // ESP_LOGI(TAG, "Found URL query parameter => query1=%s", param);
                printf("Found URL query parameter => query1=%s\n", param);
                example_uri_decode(dec_param, param, strnlen(param, EXAMPLE_HTTP_QUERY_KEY_MAX_LEN));
                // ESP_LOGI(TAG, "Decoded query parameter => %s", dec_param);
                printf("Decoded query parameter => %s\n", dec_param);
            }
            if (httpd_query_key_value(buf, "query3", param, sizeof(param)) == ESP_OK) {
                // ESP_LOGI(TAG, "Found URL query parameter => query3=%s", param);
                printf("Found URL query parameter => query3=%s\n", param);
                example_uri_decode(dec_param, param, strnlen(param, EXAMPLE_HTTP_QUERY_KEY_MAX_LEN));
                // ESP_LOGI(TAG, "Decoded query parameter => %s", dec_param);
                printf("Decoded query parameter => %s\n", dec_param);
            }
            if (httpd_query_key_value(buf, "query2", param, sizeof(param)) == ESP_OK) {
                // ESP_LOGI(TAG, "Found URL query parameter => query2=%s", param);
                printf("Found URL query parameter => query2=%s\n", param);
                example_uri_decode(dec_param, param, strnlen(param, EXAMPLE_HTTP_QUERY_KEY_MAX_LEN));
                // ESP_LOGI(TAG, "Decoded query parameter => %s", dec_param);
                printf("Decoded query parameter => %s\n", dec_param);
            }
        }
        free(buf);
    }

    /* 设置一些自定义响应的头部字段。 */
    httpd_resp_set_hdr(req, "Custom-Header-1", "Custom-Value-1");
    httpd_resp_set_hdr(req, "Custom-Header-2", "Custom-Value-2");

    /* Send response with custom headers and body set as the
     * string passed in user context*/
    const char* resp_str = (const char*) req->user_ctx;
    httpd_resp_send(req, resp_str, HTTPD_RESP_USE_STRLEN);

    /* 发送响应后旧的请求头就会丢失，读取响应头。 */
    if (httpd_req_get_hdr_value_len(req, "Host") == 0) {
        // ESP_LOGI(TAG, "Request headers lost");
        printf("Request headers lost\n");
    }
    return ESP_OK;
}

// 复读示例，把请求作为响应。
static esp_err_t echo_post_handler(httpd_req_t *req)
{
    char buf[100];
    int ret, remaining = req->content_len;

    while (remaining > 0) {
        /* 读取请求数据 */
        if ((ret = httpd_req_recv(req, buf,
                        MIN(remaining, sizeof(buf)))) <= 0) {
            if (ret == HTTPD_SOCK_ERR_TIMEOUT) {
                /* 超时重试 */
                continue;
            }
            return ESP_FAIL;
        }

        /* 发送相同的数据 */
        httpd_resp_send_chunk(req, buf, ret);
        remaining -= ret;

        /* Log data received */
        // ESP_LOGI(TAG, "=========== RECEIVED DATA ==========");
        // ESP_LOGI(TAG, "%.*s", ret, buf);
        // ESP_LOGI(TAG, "====================================");
        printf("=========== RECEIVED DATA ==========\n");
        printf("%.*s\n", ret, buf);
        printf("====================================\n");
    }

    // 结束响应
    httpd_resp_send_chunk(req, NULL, 0);
    return ESP_OK;
}

// 错误处理路由
esp_err_t http_404_error_handler(httpd_req_t *req, httpd_err_code_t err)
{
    if (strcmp("/hello", req->uri) == 0) {
        httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "/hello URI is not available");
        /* 返回 ESP_OK 保持底层 socket 打开 */
        return ESP_OK;
    } else if (strcmp("/echo", req->uri) == 0) {
        httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "/echo URI is not available");
        /* 返回 ESP_FAIL 关闭底层 socket */
        return ESP_FAIL;
    }
    /* 处理其他 URI 并关闭底层 socket */
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Some 404 error message");
    return ESP_FAIL;
}

static const httpd_uri_t hello = {
    .uri       = "/hello",
    .method    = HTTP_GET,
    .handler   = hello_get_handler,
    /* Let's pass response string in user
     * context to demonstrate it's usage */
    .user_ctx  = "Hello World!"
};

static const httpd_uri_t echo = {
    .uri       = "/echo",
    .method    = HTTP_POST,
    .handler   = echo_post_handler,
    .user_ctx  = NULL
};

// 控制示例 路由 动态修改路由。
static esp_err_t ctrl_put_handler(httpd_req_t *req)
{
    char buf;
    int ret;

    if ((ret = httpd_req_recv(req, &buf, 1)) <= 0) {
        if (ret == HTTPD_SOCK_ERR_TIMEOUT) {
            httpd_resp_send_408(req);
        }
        return ESP_FAIL;
    }

    if (buf == '0') {
        /* URI 路由的处理程序 可以被注销 */
        // ESP_LOGI(TAG, "Unregistering /hello and /echo URIs");
        printf("Unregistering /hello and /echo URIs\n");
        httpd_unregister_uri(req->handle, "/hello");
        httpd_unregister_uri(req->handle, "/echo");
        /* 注册自定义的错误处理程序 */
        httpd_register_err_handler(req->handle, HTTPD_404_NOT_FOUND, http_404_error_handler);
    }
    else {
        // ESP_LOGI(TAG, "Registering /hello and /echo URIs");
        printf("Registering /hello and /echo URIs\n");
        httpd_register_uri_handler(req->handle, &hello);
        httpd_register_uri_handler(req->handle, &echo);
        /* 注销自定义异常处理程序 */
        httpd_register_err_handler(req->handle, HTTPD_404_NOT_FOUND, NULL);
    }

    /* 响应空 body */
    httpd_resp_send(req, NULL, 0);
    return ESP_OK;
}

static const httpd_uri_t ctrl = {
    .uri       = "/ctrl",
    .method    = HTTP_PUT,
    .handler   = ctrl_put_handler,
    .user_ctx  = NULL
};
// 路由定义结束 ===============================================



static httpd_handle_t start_webserver(void)
{
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    config.server_port = 8001;
    config.lru_purge_enable = true;

    // Start the httpd server
    // ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
    printf("Starting server on port: '%d'\n", config.server_port);
    if (httpd_start(&server, &config) == ESP_OK) {
        // Set URI handlers
        // ESP_LOGI(TAG, "Registering URI handlers");
        printf("Registering URI handlers\n");
        httpd_register_uri_handler(server, &hello);
        httpd_register_uri_handler(server, &echo);
        httpd_register_uri_handler(server, &ctrl);
        #if CONFIG_EXAMPLE_BASIC_AUTH
        httpd_register_basic_auth(server);
        #endif
        return server;
    }

    // ESP_LOGI(TAG, "Error starting server!");
    printf("Error starting server!\n");
    return NULL;
}


void app_main(void) {
  static httpd_handle_t server = NULL;

  printf("http server example app_main start\n");
  init_nvc_demo();
  printf("NVS ok.\n");

  init_wifi_sta_demo();
  printf("Wifi Connect.\n");

  print_chip_info();
  spiffs_action();
  // wait_s_restart(10);

  printf("begin.\n");
  server = start_webserver();
  while (server) {
    sleep(4);
  }
}