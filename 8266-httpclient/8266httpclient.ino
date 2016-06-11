/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>

const char* ssid     = "mxedu";
const char* password = "swjtumaker";

const char* host = "10.201.10.251";
const char* doorid   = "m";


void setup() {
  Serial.begin(4800);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Read,Waiting for input.y is open");
}

int value = 0;

void loop() {
  String rfid = "0";
  // if we get a valid byte, read analog ins:
  if (Serial.available() > 0) {
    // get incoming rfid id:
    String rfid = Serial.readString();
 
    //Serial.print(rfid);
    if(rfid != "0"){

          //Serial.print("connecting to ");
          //Serial.println(host);
       // Use WiFiClient class to create TCP connections
          WiFiClient client;
          const int httpPort = 1234;
          if (!client.connect(host, httpPort)) {
            Serial.print("E");
            return;
          }
          
          // We now create a URI for the request
          String url = "/users/opendoor/";
          url += doorid;
          url += "?rfid=";
          url += rfid;
          //url += "&value=";
          //url += value;
          
          //Serial.print("Requesting URL: ");
          //Serial.println(url);
          
          // This will send the request to the server
          client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                       "Host: " + host + "\r\n" + 
                       "Connection: close\r\n\r\n");
          delay(10);
          
          // Read all the lines of the reply from server and print them to Serial
          while(client.available()){
            String line = client.readStringUntil('\r');
            //Serial.print(line);
            if(line.substring(1)  == "YES"){
                Serial.print('Y');
              }
            if(line.substring(1)  == "NO"){
                Serial.print('N');
              }
              //if (line.substring(1) == "YES") {
             //     Serial.println("Got an OK from the server"); 
             // } 
          }
          //Serial.println();
          //Serial.println("closing connection");

      }

  }


}

