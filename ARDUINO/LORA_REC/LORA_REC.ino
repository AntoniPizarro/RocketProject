#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int recivedValue = 0;
int lastRecivedValue = 0;

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    //for(;;); // Don't proceed, loop forever
  }

  // Clear the OLED buffer
  display.clearDisplay();
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println("Ready!");
  display.display();

  delay(2000);
  
  // Digital pins
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  while (!Serial);

  Serial.println("LoRa Receiver");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet: ");

    // read packet
    while (LoRa.available()) {
      recivedValue = LoRa.read() - 48;
      lastRecivedValue = recivedValue;
      Serial.print(recivedValue);

      if (recivedValue == 1) {
        digitalWrite(6, HIGH);
      } else if (recivedValue == 2) {
        digitalWrite(7, HIGH);
      } else if (recivedValue == 3) {
        digitalWrite(8, HIGH);
      } else {
        lastRecivedValue = 0;
        digitalWrite(6, HIGH);
        digitalWrite(7, HIGH);
        digitalWrite(8, HIGH);
      }
      delay(10);

      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
      digitalWrite(8, LOW);
    }

    // print RSSI of packet
    Serial.print(" - RSSI: ");
    Serial.println(LoRa.packetRssi());
  } else {
    recivedValue = 0;
    display.clearDisplay();
    
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);

    if (lastRecivedValue == 0) {
      display.println("No data...");
    } else {
      display.print("Last data: ");
      display.println(lastRecivedValue);
    }
    
    display.println("");
    display.println("B LED: 1");
    display.println("G LED: 2");
    display.println("R LED: 3");

    display.display();
  }
}
