#include <ESP8266WiFi.h>

const char* ssid     = "freifunk-rhein-neckar.de";  //Our Wifi SSID
const char* password = "";  //Our Wifi Password
const int buttonPin = 5;             // Pin that we want to monitor
const char* host = "maker.ifttt.com";     //IFTTT channel address
int buttonState = 0;

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(buttonPin, INPUT_PULLUP);
  }

int value = 1;
void loop() {
   buttonState = digitalRead(buttonPin);
    if (buttonState == LOW) {                     //normally the pin is pulled down to ground
       if (value == 1){
        Serial.println("Button pressed");
               Serial.println("We now connect to local WIFI");
       Serial.println(ssid);
       WiFi.begin(ssid, password);
         while (WiFi.status() != WL_CONNECTED) {
          Serial.print(".");
       delay(500);
       }
       Serial.println("Connected");
       WiFiClient client;
       const int httpPort = 80;
       if (!client.connect(host, httpPort)) {
       return;
       }
       // We now create a URI for the request
       String url = "/trigger/input1/with/key/bWpGdGEYBQ8YHPPY80miOx-dGkagvGTpjTfZn8_JGLt";   //our link to trigger the event with special key and event name 
  
       // This will send the request to the server
       client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
       value = 0;
       delay(5000);
       Serial.println("Connection closed");
       }
    }

    else{
    value = 1;
    delay(500);
    }
}

