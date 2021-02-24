/***********************************************************
 * Input: DHT11 Sensor
 * Output: Serial Monitor
 * Programmer: Madhu Parvathaneni (linkedin.com/in/MadhuPIoT)
 * Hardware Engineer: Madhu Parvathaneni (linkedin.com/in/MadhuPIoT)
 * Client: KITS Guntur
 * Date: 23rd Feb 2021
 ***********************************************************/

#include "DHT.h"

DHT dht(23,DHT11);

void setup() {
 Serial.begin(115200);
 dht.begin();
}

void loop() {
  int temp=dht.readTemperature();
  int hum=dht.readHumidity();
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(", Hum: ");
  Serial.println(hum);
  delay(1000);

}
