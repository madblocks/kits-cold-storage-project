/***********************************************************
 * Input: DHT11, Flame
 * Output: 2-channel Relay (Siren,Sprinkler), AWS IoT Core, madBlocks DB
 * Programmer: Madhu Parvathaneni (linkedin.com/in/MadhuPIoT)
 * Hardware Engineer: Madhu Parvathaneni (linkedin.com/in/MadhuPIoT)
 * Client: KITS Guntur
 * Date: 23rd Feb 2021
 ***********************************************************/

#include "AWS_IOT.h"
#include "DHT.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include "cert.c"

AWS_IOT madblocks;

char host[]="a366shaagepcsd-ats.iot.us-east-1.amazonaws.com";
char topic_name[]="iotkits/box1";
char client_id[]="ESP32";
char payload[512];

const char* ssid = "Madhu P";
const char* password = "madhu2022";

String serverName1 = "http://madblocks.tech/coldstorage/drivers/temp_api.php";
String serverName2 = "http://madblocks.tech/coldstorage/drivers/hum_api.php";

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

DHT dht(23,DHT11);

// Function Declarations
void bsp_init(void);

void setup() {
 bsp_init();
}

void loop() {
 int temp=dht.readTemperature();
 int hum=dht.readHumidity();

 Serial.print("Temp: ");
 Serial.print(temp);
 Serial.print(", Hum: ");
 Serial.println(hum);
 delay(1000);
 upload_temp_to_madblocksdb(temp);
 delay(1000);
 upload_hum_to_madblocksdb(hum);

  sprintf(payload,"{temperature:%d,humidity:%d}",temp,hum);
  if(madblocks.publish(topic_name,payload)==0)
  {
    Serial.println("Data Sent Successfully");
    Serial.println(payload);
  }
  else
  {
    Serial.println("Failed to Publish");
  }
  delay(5000);
}

// Board Support Package Initalisation
void bsp_init(void) {
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  if(madblocks.connect(host,client_id)==0)
  {
    Serial.println("Connected to AWS IOT Core");
    delay(1000);
  }
  else
  {
    Serial.println("Error , Kindly Check Your Host Address");
    while(1);
  }
}

void upload_temp_to_madblocksdb(int t) {
  
   if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      String serverPath = serverName1 + "?temp=" + String(t)+"&box=1&floor=1";
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverPath.c_str());
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

void upload_hum_to_madblocksdb(int t) {
  
   if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      String serverPath = serverName2 + "?hum=" + String(t)+"&box=1&floor=1";
      
      // Your Domain name with URL path or IP address with path
      http.begin(serverPath.c_str());
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
