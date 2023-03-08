import gc
import esp
from time import sleep
from network import WLAN, STA_IF

def esp_clean():
    esp.osdebug(None)
    gc.collect()


def open_wifi(ssid, password, retry_time=4):
    wlan = WLAN(STA_IF)
    wlan.active(True)

    while not wlan.isconnected() and retry_time > 0:
        retry_time -= 1
        try:
            wlan.connect(ssid, password)
        except OSError as e:
            print(e)
        sleep(1)
    return wlan if retry_time > 0 else None
