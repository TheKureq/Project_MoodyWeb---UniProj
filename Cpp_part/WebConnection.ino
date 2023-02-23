/*
 * Title:         "MOODY" ESP8266 (WeMosD1) WiFi Controled Robotic Arm
 * Authors:       Michał Kurek & Samir Abu Safieh
 * Purpose:       University project - educational robot 
 * Desctiption:   Moody is a robotic 5-axis robotic arm toy, controled by website MoodyWeb.com
 * File Version:  1.01v
 * Date:          06.11.2022
*/

/* Microcontroler and web connection modeled with this youtube tutorial
 * ESP8266 (WeMosD1) WiFi Relay Control
 * 
 * learnelectronics
 * 05 JUN 2017
 * 
 * www.youtube.com/c/learnelectronics
 * arduino0169@gmail.com
*/

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <Arduino.h>

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif



#define USE_SERIAL Serial

const char* ssid = "kurek";
const char* password = "kurek678";
WiFiServer server(80);


void ConnectionSetup() {
  delay(10);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
 
  // Connect to WiFi network
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
 
  // Start the server
  server.begin();
  Serial.println("Server started");
  digitalWrite(LED_BUILTIN, LOW);
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont(u8g2_font_smart_patrol_nbp_tf);	// choose a suitable font
  u8g2.drawStr(0,10,"Local IP:");	// write something to the internal memory
  u8g2.setCursor(0,21); // set cursor position
  u8g2.print(WiFi.localIP());	// write something to the internal memory
  u8g2.drawStr(0,32,"Kurek & Samir");	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display
};

void ConnectionLoop() {
  while (true) {
    // Check if a client has connected
    WiFiClient client = server.available();
    if (!client) {
      return;
    }
  
    // Wait until the client sends some data
    Serial.println("new client");
    while(!client.available()){
      delay(1);
      Serial.println(".");
    }

    // Read the first line of the request
    String request = client.readStringUntil('\r');
    Serial.println(request); // GET /?selec=1009 HTTP/1.1

    // Read and substract value from string to read type of request
    ClientRequest.type = request.substring(6,11);
    Serial.println(ClientRequest.type);
    int firstSpace;

    if (ClientRequest.type == "selec") {
      // Read and substract value from string to read request code
        Serial.println("axis selection code request type.");
        request = request.substring(13);
        firstSpace = request.indexOf(" ");
        request = request.substring(0,firstSpace);
        ClientRequest.axis = request.toInt();

        // E-STOP!!!
        if (ClientRequest.axis == 1009) {
          estop = true;
        } else {
          estop = false;
        }
    }
    else if (ClientRequest.type == "axis1") { // ANGLE OF AXIS 1
        // Read and substract value from string to read request code
        Serial.println("Value of axis request type.");
        request = request.substring(12);
        firstSpace = request.indexOf(" ");
        request = request.substring(0,firstSpace);
        ClientRequest.requestInt[0] = request.toInt();
    }
    else if (ClientRequest.type == "axis2") { // ANGLE OF AXIS 2
        // Read and substract value from string to read request code
        Serial.println("Value of axis request type.");
        request = request.substring(12);
        firstSpace = request.indexOf(" ");
        request = request.substring(0,firstSpace);
        ClientRequest.requestInt[1] = request.toInt();
    }
    else if (ClientRequest.type == "axis3") { // ANGLE OF AXIS 3
        // Read and substract value from string to read request code
        Serial.println("Value of axis request type.");
        request = request.substring(12);
        firstSpace = request.indexOf(" ");
        request = request.substring(0,firstSpace);
        ClientRequest.requestInt[2] = request.toInt();
    }
    else if (ClientRequest.type == "axis4") { // ANGLE OF AXIS 4
        // Read and substract value from string to read request code
        Serial.println("Value of axis request type.");
        request = request.substring(12);
        firstSpace = request.indexOf(" ");
        request = request.substring(0,firstSpace);
        ClientRequest.requestInt[3] = request.toInt();
    }
    else if (ClientRequest.type == "axis5") { // ANGLE OF AXIS 5
        // Read and substract value from string to read request code
        Serial.println("Value of axis request type.");
        request = request.substring(12);
        firstSpace = request.indexOf(" ");
        request = request.substring(0,firstSpace);
        ClientRequest.requestInt[4] = request.toInt();
    }
    else if (ClientRequest.type == "axis6") { // ANGLE OF AXIS 6
        // Read and substract value from string to read request code
        Serial.println("Value of axis request type.");
        request = request.substring(12);
        firstSpace = request.indexOf(" ");
        request = request.substring(0,firstSpace);
        ClientRequest.requestInt[5] = request.toInt();
    }

    // .........
    // SEQUENCES
    // .........
    else if (ClientRequest.type == "seqon") {
      ClientRequest.axis = 1200; // SEQUENCE CODE FOR STATE MACHINE
      Serial.println("Sequence request type.");
      Sequence.estop = false;
      estop = false;
      request = request.substring(12);
      firstSpace = request.indexOf(" ");
      request = request.substring(0,firstSpace);

      if (request.substring(0,3) == "lon") {
        Sequence.loop = true;
        Serial.println("Loop on");
      } else {
        Sequence.loop = false;
        Serial.println("Loop off");
      }

      request = request.substring(3,firstSpace);
      Serial.println(request);

      // request clearance every web submit
      for(int i=0; i<99; i++) {
        Sequence.Task[i].taskRequest.clear();
      }

      int j = 0;
      for (int i = 0; ;i++) {
        // "+" in decimal
        if (request[i] == 43) {
          Serial.println(Sequence.Task[j].taskRequest); // print request
          j++; 
          i++;
        }

        // "\n" in decimal
        if (request[i] == 0) {
          break;
        }

        Sequence.Task[j].taskRequest += request[i];
      }

      for (int i=0;;i++) {
        Serial.println("---\n");
        Sequence.Task[i].taskType = Sequence.Task[i].taskRequest[0];
        Serial.println(Sequence.Task[i].taskType);
        
        // TASK 1
        if (Sequence.Task[i].taskRequest[0] == 65) { // A in decimal
          //axis 1
          int temp = Sequence.Task[i].taskRequest.indexOf("x");
          int temp2 = Sequence.Task[i].taskRequest.indexOf("v");
          int temp3 = Sequence.Task[i].taskRequest.indexOf(" ");
          Sequence.Task[i].axisStr = Sequence.Task[i].taskRequest[temp+1];
          Sequence.Task[i].angleStr = Sequence.Task[i].taskRequest.substring(temp2+1,temp3);
          // conversion from web js string parameter to int value for motors
          String s = Sequence.Task[i].axisStr;
          
          Sequence.Task[i].axisInt = atoi(Sequence.Task[i].axisStr.c_str());
          Sequence.Task[i].angleInt = atoi(Sequence.Task[i].angleStr.c_str());
          Serial.println("A Task " + Sequence.Task[i].taskRequest);
          Serial.print("A ax1 ");
          Serial.println(Sequence.Task[i].axisStr);
          Serial.println(Sequence.Task[i].axisInt);
          Serial.print("A ag1 ");
          Serial.println(Sequence.Task[i].angleStr);
          Serial.println(Sequence.Task[i].angleInt);
        }

        // TASK 2
        else if (Sequence.Task[i].taskRequest[0] == 66) {
          //axis 1
          int temp = Sequence.Task[i].taskRequest.indexOf("x");
          int temp2 = Sequence.Task[i].taskRequest.indexOf("v");
          int temp3 = Sequence.Task[i].taskRequest.indexOf("y");
          Sequence.Task[i].axisStr = Sequence.Task[i].taskRequest[temp+1];
          Sequence.Task[i].angleStr = Sequence.Task[i].taskRequest.substring(temp2+1,temp3);
          // conversion from web js string parameter to int value for motors
          Sequence.Task[i].axisInt = atoi(Sequence.Task[i].axisStr.c_str());
          Sequence.Task[i].angleInt = atoi(Sequence.Task[i].angleStr.c_str());
          Serial.println("B Task " + Sequence.Task[i].taskRequest);
          Serial.print("B ax1 ");
          Serial.println(Sequence.Task[i].axisStr);
          Serial.print("B ag1 ");
          Serial.println(Sequence.Task[i].angleStr);

          //axis 2
          temp = Sequence.Task[i].taskRequest.indexOf("y");
          temp2 = Sequence.Task[i].taskRequest.indexOf("z");
          temp3 = Sequence.Task[i].taskRequest.indexOf(" ");
          Sequence.Task[i].axis2Str = Sequence.Task[i].taskRequest.substring(temp+1,temp2);
          Sequence.Task[i].angle2Str = Sequence.Task[i].taskRequest.substring(temp2+1,temp3);
          // conversion from web js string parameter to int value for motors
          Sequence.Task[i].axis2Int = atoi(Sequence.Task[i].axis2Str.c_str());
          Sequence.Task[i].angle2Int = atoi(Sequence.Task[i].angle2Str.c_str());
          Serial.print("B ax2 ");
          Serial.println(Sequence.Task[i].axis2Str);
          Serial.print("B ag2 ");
          Serial.println(Sequence.Task[i].angle2Str);
        }

        else if (Sequence.Task[i].taskRequest[0] == 67) { Serial.println(Sequence.Task[i].taskRequest); }
        else if (Sequence.Task[i].taskRequest[0] == 68) { Serial.println(Sequence.Task[i].taskRequest); }
        else if (Sequence.Task[i].taskRequest[0] == 69) { Serial.println(Sequence.Task[i].taskRequest); }
        
        else if (Sequence.Task[i].taskRequest[0] == 70) { 
          Serial.println(Sequence.Task[i].taskRequest); 
          int temp = Sequence.Task[i].taskRequest.indexOf("d");
          int temp3 = Sequence.Task[i].taskRequest.indexOf(" ");
          Sequence.Task[i].delayStr = Sequence.Task[i].taskRequest.substring(temp+1,temp3);
          Sequence.Task[i].delayInt = atoi(Sequence.Task[i].delayStr.c_str());
          Serial.println(Sequence.Task[i].delayStr);
          Serial.print("delay!!! ");
          Serial.println(Sequence.Task[i].delayInt);
          }
        else {break;}
      }
    }

    else if (ClientRequest.type == "seqof") {   
      Sequence.estop = true;

      for(int i=0; i<99; i++) {
        Sequence.Task[i].taskRequest.clear();
        Sequence.Task[i].axisStr.clear();
        Sequence.Task[i].axis2Str.clear();
        Sequence.Task[i].angleStr.clear();
        Sequence.Task[i].angleStr.clear();
        Sequence.Task[i].delayStr.clear();
        Sequence.Task[i].angleInt = 0;
        Sequence.Task[i].angle2Int = 0;
        Sequence.Task[i].axisInt = 0;
        Sequence.Task[i].axis2Int = 0;
        Sequence.Task[i].taskType = 0;
        Sequence.Task[i].delayInt = 0;
      }
    }   

    else {
        Serial.println("unrecognized request type");
    }

    // say what you got:
    Serial.print("\t I received: ");
    Serial.print(request + "\n\n");
    

    client.flush();
    delay(1);
    Serial.println("Client disconnected");
    Serial.println("");
  }
};
  

