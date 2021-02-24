/***********************************************************
 * Input: Serial Monitor 
 * Output: Relay Board
 * Programmer: Madhu Parvathaneni (linkedin.com/in/MadhuPIoT)
 * Hardware Engineer: Madhu Parvathaneni (linkedin.com/in/MadhuPIoT)
 * Client: KITS Guntur
 * Date: 23rd Feb 2021
 ***********************************************************/
#define siren 23
#define co2 22

// Function Declarations
int sirenControl(int);
int sprinklerControl(int);

void setup() {
  pinMode(siren,OUTPUT);
  pinMode(co2,OUTPUT);
  digitalWrite(siren,1);
  digitalWrite(co2,1);

  Serial.begin(115200);
}

void loop() {
  while(Serial.available()) {
    char ch=Serial.read();
    if(ch=='A' || ch=='a') {
      sirenControl(0);
    }
    else if(ch=='B' || ch=='b') {
      sirenControl(1);
    }
  }
}

int sirenControl(int m) {
  if(m==0)  {
    digitalWrite(siren,1);
  } else if(m==1)  {
    digitalWrite(siren,0);
  }
}

int sprinklerControl(int s) {
  if(s==0)  {
    digitalWrite(co2,1);
  } else if(s==1)  {
    digitalWrite(co2,0);
  }
}
