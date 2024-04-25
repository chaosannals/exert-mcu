#include <Adafruit_NeoPixel.h>
#include <rp2040_pio.h>

// arduino 定式，入口函数。
void setup() {
    Serial.begin(115200);
    while(!Serial);
}

// arduino 定式，循环体函数。
void loop() {
    if (Serial.available()) {
        String inputString = Serial.readString();
        Serial.println(inputString);
    }
}