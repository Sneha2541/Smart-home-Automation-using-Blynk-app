//#define BLYNK_TEMPLATE_ID "TMPL3NozHvQS3"
//#define BLYNK_TEMPLATE_NAME "blynk home"
//#define BLYNK_AUTH_TOKEN "ImGf305pjcLJJprn3Kr3QV-zKgmMIEK8"

#define BLYNK_TEMPLATE_ID "TMPL3Zv6995cE"
#define BLYNK_TEMPLATE_NAME "Sneha home"
#define BLYNK_AUTH_TOKEN "VmKbT-w7NPZdjLEgSPlzdrGJrRqRPOvm"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = "VmKbT-w7NPZdjLEgSPlzdrGJrRqRPOvm"; 
char ssid[] = "Redmi 9 Prime"; 
char pass[] = "25418125"; // 

DHT dht(D3, DHT11); // 
BlynkTimer timer;
bool buzzer = 0;

// Define component pins
#define Buzzer D0
#define led1 D1
#define led2 D2
#define trig D4
#define echo D5


// Button handler for PIR sensor activation
BLYNK_WRITE(V0) {
 buzzer = param.asInt();
}

void setup() {
  Serial.begin(9600);
  pinMode(Buzzer, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  dht.begin();

  // Call the functions periodically
  timer.setInterval(100L, DHT11sensor);
  timer.setInterval(100L, ultrasonic);
}

// Function to get the DHT11 sensor values
void DHT11sensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V1, t);
  Blynk.virtualWrite(V2, h);
}


// Function to get the ultrasonic sensor values
void ultrasonic() {
  digitalWrite(trig, LOW);
  delayMicroseconds(4);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long t = pulseIn(echo, HIGH);
  long cm = t / 29 / 2;
  Blynk.virtualWrite(V3, cm);
}



// Function to on led1
BLYNK_WRITE(V4){
  int value = param.asInt();
  value ? digitalWrite(led1, HIGH) : digitalWrite(led1, LOW);
  }

// Function to on led2
BLYNK_WRITE(V5){
  int value = param.asInt();
  value ? digitalWrite(led2, HIGH) : digitalWrite(led2, LOW);
  }
  
void loop() {
  Blynk.run(); // Run the Blynk library
  timer.run(); // Run the Blynk timer
}
