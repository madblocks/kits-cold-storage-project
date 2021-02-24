/***********************************************************
 * Input: Flame Sensor
 * Output: Serial Monitor
 * Programmer: Madhu Parvathaneni (linkedin.com/in/MadhuPIoT)
 * Hardware Engineer: Madhu Parvathaneni (linkedin.com/in/MadhuPIoT)
 * Client: KITS Guntur
 * Date: 23rd Feb 2021
 ***********************************************************/
int flame=21;

void setup() {
 pinMode(flame,INPUT);
 Serial.begin(115200);
}

void loop() {
  if(digitalRead(flame)==0) {
    Serial.println("Detected");
  } else {
    Serial.println("Not Detected");
  }
  delay(1000);
}
