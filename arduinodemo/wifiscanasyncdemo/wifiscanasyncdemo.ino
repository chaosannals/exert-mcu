#include <WiFi.h>
#include <Ticker.h>

Ticker t1;

void scanWifiAsync() {
    if (!WiFi.isConnected()) {
        int n = WiFi.scanComplete();
        switch (n) {
        case -1:
            Serial.println("扫描中...");
            break;
        case -2:
            Serial.println("未进入扫描...");
            break;
        default:
            Serial.println("扫描完成");
            Serial.print("扫描到");
            Serial.print(n);
            Serial.println("个 Wifi");
            for (size_t i = 0; i < n; i++) {
                Serial.print("Wifi名SSID：");
                Serial.println(WiFi.SSID(i));
                Serial.print("Wifi强度：");
                Serial.println(WiFi.RSSI(i));
                Serial.print("Wifi加密类型：");
                auto et = WiFi.encryptionType(i);
                Serial.print(et);
                Serial.print(" 是否加密：");
                Serial.println(et == WIFI_AUTH_OPEN ? "否": "是");
            }
            WiFi.scanDelete(); // 清除扫描结果。
            t1.detach();
            break;
        }
    }
}

void setup() {
    Serial.begin(115200);
    while(!Serial);
    WiFi.mode(WIFI_MODE_STA);
    WiFi.disconnect();
    delay(100);
    Serial.println("开始扫描 Wifi:");
    int n = WiFi.scanNetworks();

    t1.attach(0.5, scanWifiAsync);
}

void loop() {

}