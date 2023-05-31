#include <LoRa.h>
#include <SPI.h>
#include <LoRa.h>                           
#define led 15                                 
void setup() {
  Serial.begin(115200);
  Serial.println("LORA recibido");
  LoRa.setPins(17,16,22);                       // NSS, RESET y DIO0.
  if (!LoRa.begin(915E6)) {                     // Frecuencia de la banda libre ISM en Europa. (868MHz) Si hay algun fallo de conexiones muestra el error.
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  pinMode(led,OUTPUT);
}
void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {                             // Se ha recibido un paquete.
    Serial.print(" Recibio mensaje '");
    digitalWrite(led,HIGH);                     // Parpadear LED al recibir el mensaje.
    delay(100);
    digitalWrite(led,LOW);
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }
    Serial.print(" A traves de LORA ");
    Serial.println(LoRa.packetRssi());
  }
}
