# pip install -i https://mirrors.aliyun.com/pypi/simple/ httpx

import httpx

# 这个 IP 随单片机比分配而定，看串口返回的 IP
TARGET_IP = '192.168.1.216'

r1 = httpx.get(f'http://{TARGET_IP}:8001/hello?query3=3&query2=2')
print(r1)

r2 = httpx.post(f'http://{TARGET_IP}:8001/echo', data='aaaaa=123')
print(r2)

r3 = httpx.put(f'http://{TARGET_IP}:8001/ctrl', data='0')
print(r3)

r4 = httpx.put(f'http://{TARGET_IP}:8001/ctrl', data='1')
print(r4)
