#include <SPI.h>
#include <RH_RF95.h>

const int LDR_PIN = A0; // Analog pin connected to LDR

// Singleton instance of the radio driver
RH_RF95 rf95;
float frequency = 868.0;

void setup() 
{
  Serial.begin(9600);
  
  Serial.println("Start LoRa Client 2 with LDR");
  if (!rf95.init())
    Serial.println("RFM95 init failed");
  
  // Setup ISM frequency
  rf95.setFrequency(frequency);
  // Setup Power, dBm
  rf95.setTxPower(13);

  // Setup Spreading Factor (6 ~ 12)
  rf95.setSpreadingFactor(7);
  
  // Setup BandWidth, option: 7800,10400,15600,20800,31200,41700,62500,125000,250000,500000
  // Lower BandWidth for longer distance.
  rf95.setSignalBandwidth(125000);
  
  // Setup Coding Rate:5(4/5),6(4/6),7(4/7),8(4/8) 
  rf95.setCodingRate4(5);
}

void loop()
{
  // Read value from LDR
  int ldrValue = analogRead(LDR_PIN);

  // Prepare the message
  String message = "LDR Value: " + String(ldrValue);

  // Convert message to uint8_t array
  uint8_t data[message.length() + 1];
  message.toCharArray((char*)data, message.length() + 1);

  // Send data to LoRa Server
  rf95.send(data, sizeof(data));
  rf95.waitPacketSent();
  
  Serial.println("Data sent to LoRa Server from client 2");
  delay(5000);
}
