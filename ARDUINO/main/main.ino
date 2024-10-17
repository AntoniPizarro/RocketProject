#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 9
#define CSN_PIN 10

//creamos el objeto radio (NRF24L01)
RF24 radio(CE_PIN, CSN_PIN);

byte direccion[5] = { 'c', 'a', 'n', 'a', 'l' };

int data = 69;

void setup(void) {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(direccion);
}

void loop(void) {
  bool ok = radio.write(&data, sizeof(data));
  if (ok) {
    Serial.println("Datos enviados");
  } else {
    Serial.println("Datos NO enviados");
  }
}