import gc
import esp
from socket import socket, AF_INET, SOCK_STREAM
from time import sleep
from network import WLAN, STA_IF

esp.osdebug(None)
gc.collect()

wlan = WLAN(STA_IF)
wlan.active(True)

while not wlan.isconnected():
    try:
        wlan.connect('ssid', 'password')
    except OSError as e:
        print(e)
    sleep(1)

print(wlan.ifconfig())

html = '''
<!DOCTYPE html>
<html>
    <head>
        <title>ESP32</title>
    </head>
    <body>
        <h1>ESP32</h1>
    </body>
</html>
'''

sock = socket(AF_INET, SOCK_STREAM)
sock.bind(('', 80))
sock.listen(14)

print('start')
while True:
    conn, addr = sock.accept()
    print(f'accept {addr}')
    request = conn.recv(1024)
    response = html
    conn.send('HTTP/1.1 200 OK\r\n')
    conn.send('Content-Type: text/html\r\n')
    conn.send('Connection: close\r\n\r\n')
    conn.sendall(response)
    conn.close()
