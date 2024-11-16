#include <SPI.h>
#include <LoRa.h>

/*
 * MOSI -> D11
 * MISO -> D12
 * SCK  -> D13
 * NSS  -> D10
 * NRST -> D9
 * DIO0 -> D2
 */

#define ss 10
#define rst 9
#define dio0 2
int counter = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");
  LoRa.setPins(ss, rst, dio0);
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;

  delay(5000);
}
