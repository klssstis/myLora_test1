#include <SPI.h>
#include <LoRa.h>
#include <Adafruit_GFX.h>               // Подключение библиотеки Adafruit_GFX
#include <Adafruit_SSD1306.h>           // Подключение библиотеки Adafruit_SSD1306
#define OLED_RESET                      0
Adafruit_SSD1306 display(OLED_RESET);
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

#if (SSD1306_LCDHEIGHT != 48)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
void show_display(String pText){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(pText);
  display.display();                       
}
void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); // Указываем адрес дисплея

  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Receiver");
  show_display("LoRa Receiver");
  LoRa.setPins(ss, rst, dio0);

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
    Serial.print("Received packet '");
    String pckt;
    // read packet
    while (LoRa.available()) {
      pckt += (char)LoRa.read();
//      Serial.print((char)LoRa.read());
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    pckt +=" "+String(LoRa.packetRssi());
    Serial.println(LoRa.packetRssi());
    show_display(pckt);
  }
}
