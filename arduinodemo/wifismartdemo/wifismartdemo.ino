#include <WiFi.h>

// void confSmartWifi() {
//     WiFi.mode(WIFI_MODE_STA);
//     Serial.println("开启智能配网：");
//     WiFi.beginSmartConfig();
//     while (1) {
//         Serial.print(".");
//         delay(500);
//         if (WiFi.smartConfigDone()) {
//             Serial.println("配网成功");
//             Serial.printf("SSID: %s", WiFi.SSID().c_str());
//             Serial.printf("PSK: %s", WiFi.psk().c_str());
//             break;
//         }
//     }
// }

// int confAuto() {
//     WiFi.disconnect(true);
//     WiFi.begin();
//     for (size_t i = 0; i < 20; i++) {
//         int wifiStatus = WiFi.status();
//         if (wifiStatus == WL_CONNECTED) {
//             Serial.println("自动连接成功");
//             return 1;
//         } else {
//             delay(1000);
//             Serial.println("等待自动自动配网中...");
//         }
//     }
//     Serial.println("自动配网尝试失败...");
//     return 0;
// }

// 直接的方式。
void confiSimple() {
    WiFi.mode(WIFI_MODE_STA);
    Serial.println("开启智能配网：");
    WiFi.beginSmartConfig();

    while(!WiFi.smartConfigDone()) {
        delay(400);
        Serial.print(".");
    }

    Serial.println("配网成功");
    Serial.printf("SSID: %s", WiFi.SSID().c_str());
    Serial.printf("PSK: %s", WiFi.psk().c_str());
    Serial.println("=====");
}

void setup() {
    Serial.begin(115200);
    while(!Serial);

// 这种亲测可刑。
    confSimple();

    // 网络代码，有问题。
//     if (!confAuto()) {
//         confSmartWifi();
//     }
// }

void loop() {
    if (WiFi.isConnected()) {
        Serial.println("配网完成");
    } else {
        Serial.println("未连接");
    }
    delay(1000);
}