#include <SPI.h>
#include <LoRa.h>

int btn_1 = A3;
int btn_2 = A4;
int btn_3 = A5;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  LoRa.setTxPower(20);
  
}

void loop() {
  if (digitalRead(btn_1) == HIGH) {
    sendData(1);
    delay(100);
  } else if (digitalRead(btn_2) == HIGH) {
    sendData(2);
    delay(100);
  } else if (digitalRead(btn_3) == HIGH) {
    sendData(3);
    delay(100);
  } else {
    Serial.println("===============");
    Serial.println(digitalRead(btn_1));
    Serial.println(digitalRead(btn_2));
    Serial.println(digitalRead(btn_3));
    delay(500);
  }
}

void sendData(int value) {
  Serial.print("Sending data: ");
  Serial.println(value);
  
  LoRa.beginPacket();
  LoRa.print(value);
  LoRa.endPacket();
}
