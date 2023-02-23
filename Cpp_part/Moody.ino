/*
 * Title:         "MOODY" ESP8266 (WeMosD1) WiFi Controled Robotic Arm
 * Authors:       Michał Kurek & Samir Abu Safieh
 * Purpose:       University project - educational robot 
 * Desctiption:   Moody is a robotic 5-axis robotic arm toy, controled by website MoodyWeb.com
 * File Version:  1.01v
 * Date:          06.11.2022
*/

#include <Servo.h>
#include <stdio.h>
#include <SoftwareSerial.h>

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define OLED_RESET -1 
#define OLED_ADDR 0x3C // here address is 0x3C for 128x32 display

// OLED DISPLAY DECLARATION
U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED


Servo servo[6];  
int servo__position[6] = {0};
int servo__actual_position[6] = {0};

int potentiometer = analogRead(A0);
int axis_button__state = 0;
int axis_button__lastState = 1;
int g_machine__state = 0;

const int AXIS_BUTTON = 15;
const int MODE_TOGGLE = 14;
const int AXIS_NUMBER = 6; /// You can change parameter depends of axis you want to use
const int MAX_TASKS = 99;

bool manual_mode;
bool estop = false;

struct ClientRequest {
  int axis;
  int requestInt[6];
  String type;
} ClientRequest;

struct Sequence {
  bool loop = false;
  bool estop = false;
  int iterator = 0;
  struct Task {
    int taskType;
    String axisStr;
    String axis2Str;
    String angleStr;
    String angle2Str;
    String delayStr;
    byte axisInt;
    byte axis2Int;
    byte angleInt;
    byte angle2Int;
    int delayInt;
    String taskRequest = {};
  } Task[MAX_TASKS]; 
} Sequence;

// FUNCTION DECLARATION
void moveSequence(int requestInt,int i);
void moveZero();

void setup() {
  pinMode(3, FUNCTION_3); 
  pinMode(1, FUNCTION_3); 
  pinMode(2, FUNCTION_3); 
  pinMode(AXIS_BUTTON, INPUT); 
  pinMode(MODE_TOGGLE, INPUT);

  // DEFINE SERVOS PINS
  servo[0].attach(3,500,2400); 
  servo[1].attach(2,500,2400);  
  servo[2].attach(12, 500,2400);  
  servo[3].attach(13,1100,3600);  
  servo[4].attach(0,1100,3600);  
  servo[5].attach(16,1100,3600);  
  
  OledControlSetup();
  // Serial.begin(9600);

  if (digitalRead(MODE_TOGGLE) == LOW) {
    // WIFI SERVER CONNECTION SETUP
    manual_mode = false;
    u8g2.clearBuffer();
    u8g2.drawStr(0,10,"MOODY V2");
    u8g2.drawStr(0,21,"Mode: Remote");
    u8g2.drawStr(0,32,"Con. setup begin");
    u8g2.sendBuffer();	
    Serial.println("connection setup begin:");
    ConnectionSetup();
  } 
  else {
    manual_mode = true;
    u8g2.clearBuffer();			
    u8g2.drawStr(0,10,"MOODY V2");	
    u8g2.drawStr(0,21,"Mode: Manual");	
    u8g2.drawStr(0,32,"Wait...");	
    u8g2.sendBuffer();					
  }

 
  g_machine__state = 1;

  


  // // RESTARTING SERVOS
  for (int i = 0; i < AXIS_NUMBER; i++) {
    servo[i].write(90);  
    servo__position[i] = 90; 
    ClientRequest.requestInt[i] = 90;           
  }

  Serial.println("Setup finished, ready to control");
  delay(100);
}

void loop() { 
  if (manual_mode == false) {  // ===== WEBSITE CONTROL MODE ======
    // WIFI CLIENT LISTENER LOOP
    ConnectionLoop();

    // MATCH THE REQUEST
    if (estop != false) {
      u8g2.clearBuffer();					
      u8g2.drawStr(0,10,"MOODY V2");	
      u8g2.drawStr(0,32,"State: Stop!");	
      u8g2.sendBuffer();
    } else {
      switch (ClientRequest.axis) {
        case 1001: // AXIS 1
          moveSequence(ClientRequest.requestInt[0],0);
          u8g2.clearBuffer();
          u8g2.drawStr(0,10,"MOODY V2");
          u8g2.drawStr(0,32,"State: Axis 1");	
          u8g2.sendBuffer();
          break;
        case 1002: // AXIS 2
          moveSequence(ClientRequest.requestInt[1],1);
          u8g2.clearBuffer();
          u8g2.drawStr(0,10,"MOODY V2");
          u8g2.drawStr(0,32,"State: Axis 2");	
          u8g2.sendBuffer();
          break;
        case 1003: // AXIS 3
          moveSequence(ClientRequest.requestInt[2],2);
          u8g2.clearBuffer();
          u8g2.drawStr(0,10,"MOODY V2");
          u8g2.drawStr(0,32,"State: Axis 3");	
          u8g2.sendBuffer();
          break;
        case 1004: // AXIS 4
          moveSequence(ClientRequest.requestInt[3],3);
          u8g2.clearBuffer();
          u8g2.drawStr(0,10,"MOODY V2");
          u8g2.drawStr(0,32,"State: Axis 4");	
          u8g2.sendBuffer();
          break;
        case 1005: // AXIS 5
          moveSequence(ClientRequest.requestInt[4],4);
          u8g2.clearBuffer();
          u8g2.drawStr(0,10,"MOODY V2");
          u8g2.drawStr(0,32,"State: Axis 5");	
          u8g2.sendBuffer();
          break;
        case 1006: // GRIPPER
          moveSequence(ClientRequest.requestInt[5],5);
          u8g2.clearBuffer();
          u8g2.drawStr(0,10,"MOODY V2");
          u8g2.drawStr(0,32,"State: Gripper");	
          u8g2.sendBuffer();					
          break;
        case 1007: // DEMO MODE - based on sweep example
          u8g2.clearBuffer();
          u8g2.drawStr(0,10,"MOODY V2");
          u8g2.drawStr(0,32,"State: Demo");	
          u8g2.sendBuffer();	
          for (int pos = 90; pos >= 20; pos -= 1) { 
            servo[0].write(pos);              
            servo[1].write(pos);              
            servo[2].write(pos);              
            servo[3].write(pos);              
            servo[4].write(pos); 
            delay(2);                      
          }			
          for (int pos = 20; pos <= 145; pos += 1) { 
            servo[0].write(pos);              
            servo[1].write(pos);              
            servo[2].write(pos);              
            servo[3].write(pos);              
            servo[4].write(pos); 
            
            delay(2);                      
          }
          for (int pos = 145; pos >= 20; pos -= 1) { 
            servo[0].write(pos);              
            servo[1].write(pos);              
            servo[2].write(pos);              
            servo[3].write(pos);              
            servo[4].write(pos);                                
            delay(2);                       
          }
          for (int pos = 20; pos <= 90; pos += 1) { 
            servo[0].write(pos);              
            servo[1].write(pos);              
            servo[2].write(pos);              
            servo[3].write(pos);              
            servo[4].write(pos);                               
            delay(2);                       
          }
          break;

        case 1008: // SEQUENCE 1        
          u8g2.clearBuffer();					
          u8g2.drawStr(0,10,"MOODY V2");	
          u8g2.drawStr(0,32,"State: Seq1");	
          u8g2.sendBuffer();					
          delay(500);
          moveSequence(50,0);
          moveSequence(50,1);
          moveSequence(20,2);   
          moveSequence(20,3);
          moveSequence(140,4);
          moveSequence(90,5);       
          delay(500); 
          moveSequence(30,5);
          moveSequence(75,4);
          moveSequence(75,3);
          moveSequence(90,2);      
          moveSequence(90,1);
          moveSequence(90,0);
          delay(500); 
          break;
        case 1009: // E-STOP
          break;
          
        case 1010: // POSITION ZERO SEQUENCE
          u8g2.clearBuffer();					
          u8g2.drawStr(0,10,"MOODY V2");	
          u8g2.drawStr(0,32,"State: Pos-Zero");	
          u8g2.sendBuffer();
          moveZero();
          break;

        case 1011: // Presentation mode
          u8g2.clearBuffer();					
          u8g2.drawStr(0,10,"MOODY V2");	
          u8g2.drawStr(0,32,"St: Presentation");	
          u8g2.sendBuffer();

          // pick first object from pos1 and place it to pos2
          moveSequence(30,5); 
          moveSequence(96,0); 
          moveSequence(1,4); 
          moveSequence(79,3); 
          moveSequence(51,1); 
          moveSequence(90,2); 
          moveSequence(90,5); 
          moveSequence(100,1); 
          moveSequence(60,0); 
          moveSequence(67,1); 
          moveSequence(122,2); 
          moveSequence(30,5); 
          moveSequence(90,1); 


          // return to zero position
          moveZero();
          delay(2000);

          // pick first object from pos2 and place it to pos1
          moveSequence(1,4); 
          moveSequence(79,3); 
          moveSequence(79,3); 
          moveSequence(60,0); 
          moveSequence(67,1); 
          moveSequence(122,2); 
          moveSequence(90,5); 
          moveSequence(100,1); 
          moveSequence(96,0); 
          moveSequence(94,2); 
          moveSequence(55,1); 
          moveSequence(30,5); 
          moveSequence(90,1); 

          // return to zero position
          moveZero();
          delay(2000);
          break;
        
        case 1200:
          if(Sequence.estop != false) {
            u8g2.clearBuffer();					
            u8g2.drawStr(0,10,"MOODY V2");	
            u8g2.drawStr(0,21,"Task: Stoped");	
            u8g2.drawStr(0,32,"State: Stop!");	
            u8g2.sendBuffer();
          } else {     
            switch(Sequence.Task[Sequence.iterator].taskType) {
              case 65:
                Serial.println("Main A");
                u8g2.clearBuffer();					
                u8g2.drawStr(0,21,"Task type: A");
                u8g2.drawStr(0,10,"MOODY V2");	
                u8g2.drawStr(0,32,"State: Sequence");	
                u8g2.sendBuffer();
                moveSequence(Sequence.Task[Sequence.iterator].angleInt,
                              Sequence.Task[Sequence.iterator].axisInt);
                Sequence.iterator++;
                break;
              case 66:
                Serial.println("Main B");
                u8g2.clearBuffer();					
                u8g2.drawStr(0,21,"Task type: B");
                u8g2.drawStr(0,10,"MOODY V2");	
                u8g2.drawStr(0,32,"State: Sequence");	
                u8g2.sendBuffer();
                moveSequence(Sequence.Task[Sequence.iterator].angleInt,
                              Sequence.Task[Sequence.iterator].axisInt);
                moveSequence(Sequence.Task[Sequence.iterator].angle2Int,
                            Sequence.Task[Sequence.iterator].axis2Int);
                Sequence.iterator++;
                break;
              case 67:
                Serial.println("Main C");
                u8g2.clearBuffer();					
                u8g2.drawStr(0,21,"Task type: C");
                u8g2.drawStr(0,10,"MOODY V2");	
                u8g2.drawStr(0,32,"State: Sequence");	
                u8g2.sendBuffer();
                moveSequence(90,5); 
                Sequence.iterator++;
                break;
              case 68:
                Serial.println("Main D");
                u8g2.clearBuffer();					
                u8g2.drawStr(0,21,"Task type: D");
                u8g2.drawStr(0,10,"MOODY V2");	
                u8g2.drawStr(0,32,"State: Sequence");	
                u8g2.sendBuffer();
                moveSequence(30,5);
                Sequence.iterator++;
                break;
              case 69:
                Serial.println("Main E");
                u8g2.clearBuffer();					
                u8g2.drawStr(0,21,"Task type: E");
                u8g2.drawStr(0,10,"MOODY V2");	
                u8g2.drawStr(0,32,"State: Sequence");	
                u8g2.sendBuffer();
                moveZero();
                Sequence.iterator++;
                break;
              case 70:
                Serial.println("Main F");
                u8g2.clearBuffer();					
                u8g2.drawStr(0,21,"Task type: F");
                u8g2.drawStr(0,10,"MOODY V2");	
                u8g2.drawStr(0,32,"State: Sequence");	
                u8g2.sendBuffer();
                delay(Sequence.Task[Sequence.iterator].delayInt);
                Sequence.iterator++;
                break;

              default: 
                Sequence.iterator = 0;
                u8g2.clearBuffer();					
                u8g2.drawStr(0,10,"MOODY V2");	
                u8g2.drawStr(0,32,"State: Sequence");	
                u8g2.drawStr(0,21,"Task type: IDLE");
                u8g2.sendBuffer();
                if (Sequence.loop == false) {

                  // request clearance every web submit
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
                break;
            }
          }      
        default:
          // Serial.println("- IDLE - Choose axis! ");
          // OledControlLoop();
          break;
      }
    }
  }
  else {  // ========== MANUAL MODE ==========
    // POTENTIOMETER READ
    potentiometer = analogRead(A0);
    delay(5);
    potentiometer = potentiometer * 180 / 1024;
    Serial.println(potentiometer);
    axis_button__state = digitalRead(AXIS_BUTTON);


    // BUTTON RISIN EDGE DETECTION
    if (axis_button__state != axis_button__lastState){
      if (axis_button__state == HIGH) {
        Serial.println("BUTTON!!!");
        g_machine__state =  g_machine__state + 1;

        if (g_machine__state > AXIS_NUMBER) {
          g_machine__state = 1;
        }

        delay(5);
      }
    }
    axis_button__lastState = axis_button__state; // DO NOT DELETE!

    // AXIS MACHINE STATE
    switch  (g_machine__state) {

      // axis_1__state
      case 1:
        Serial.println("STAN 1");
        moveSequence(potentiometer,0);
        u8g2.clearBuffer();				
        u8g2.drawStr(0,10,"MOODY V2");	
        u8g2.drawStr(0,21,"Mode: Manual");	
        u8g2.drawStr(0,32,"State: Axis 1");	
        u8g2.sendBuffer();				
        break;

      // axis_2__state
      case 2:
        Serial.println("STAN 2");
        moveSequence(potentiometer,1);
        u8g2.clearBuffer();					// clear the internal memory
        u8g2.drawStr(0,10,"MOODY V2");	// write something to the internal memory
        u8g2.drawStr(0,21,"Mode: Manual");	// write something to the internal memory
        u8g2.drawStr(0,32,"State: Axis 2");	// write something to the internal memory
        u8g2.sendBuffer();					// transfer internal memory to the display
        break;

      // axis_3__state
      case 3:
        Serial.println("STAN 3");
        moveSequence(potentiometer,2);
        u8g2.clearBuffer();					// clear the internal memory
        u8g2.drawStr(0,10,"MOODY V2");	// write something to the internal memory
        u8g2.drawStr(0,21,"Mode: Manual");	// write something to the internal memory
        u8g2.drawStr(0,32,"State: Axis 3");	// write something to the internal memory
        u8g2.sendBuffer();					// transfer internal memory to the display
        break;

      // axis_4__state
      case 4:
        Serial.println("STAN 4");
        if (potentiometer >= 150) {
          potentiometer = 150;
        }
        moveSequence(potentiometer,3);        
        u8g2.clearBuffer();					// clear the internal memory
        u8g2.drawStr(0,10,"MOODY V2");	// write something to the internal memory
        u8g2.drawStr(0,21,"Mode: Manual");	// write something to the internal memory
        u8g2.drawStr(0,32,"State: Axis 4");	// write something to the internal memory
        u8g2.sendBuffer();					// transfer internal memory to the display
        break;

      // axis_5__state
      case 5:
        Serial.println("STAN 5");
        if (potentiometer >= 150) {
          potentiometer = 150;
        }
        moveSequence(potentiometer,4);
        u8g2.clearBuffer();					// clear the internal memory
        u8g2.drawStr(0,10,"MOODY V2");	// write something to the internal memory
        u8g2.drawStr(0,21,"Mode: Manual");	// write something to the internal memory
        u8g2.drawStr(0,32,"State: Axis 5");	// write something to the internal memory
        u8g2.sendBuffer();					// transfer internal memory to the display
        break;

      // Gripper  
      case 6:
        Serial.println("STAN 6");
        potentiometer = potentiometer/2;
        moveSequence(potentiometer,5);
        u8g2.clearBuffer();					// clear the internal memory
        u8g2.drawStr(0,10,"MOODY V2");	// write something to the internal memory
        u8g2.drawStr(0,21,"Mode: Manual");	// write something to the internal memory
        u8g2.drawStr(0,32,"State: Gripper");	// write something to the internal memory
        u8g2.sendBuffer();					// transfer internal memory to the display
        break;

      // default
      default:
        Serial.println("STAN DEFAULT");
        u8g2.clearBuffer();					// clear the internal memory
        u8g2.drawStr(0,10,"MOODY V2");	// write something to the internal memory
        u8g2.drawStr(0,21,"Mode: Manual");	// write something to the internal memory
        u8g2.drawStr(0,32,"State: Default");	// write something to the internal memory
        u8g2.sendBuffer();					// transfer internal memory to the display
        break;
    }
  }
}

// FUNCTIONS
void moveSequence(int requestInt, int i) {
  if (manual_mode == false) {
    if (requestInt > servo__position[i]) {
      for (int pos = servo__position[i]; pos <= requestInt; pos += 1) { 
        servo[i].write(servo__position[i]);    
        servo__position[i] = pos;                   
        delay(15);  
      }                   
    }
    else if (requestInt < servo__position[i]) {
      for (int pos = servo__position[i]; pos >= requestInt; pos -= 1) { 
        servo[i].write(servo__position[i]);    
        servo__position[i] = pos;                 
        delay(15);  
      }                   
    }
  }
  else {                                                                                                                                      
  servo[i].write(requestInt);
  delay(5);
  }
}

void moveZero() {
        moveSequence(90,0);
        ClientRequest.requestInt[0] = 90; 
        moveSequence(90,1);
        ClientRequest.requestInt[1] = 90; 
        moveSequence(90,2);   
        ClientRequest.requestInt[2] = 90; 
        moveSequence(75,3);
        ClientRequest.requestInt[3] = 75; 
        moveSequence(75,4);
        ClientRequest.requestInt[4] = 75; 
        moveSequence(60,5);
        ClientRequest.requestInt[5] = 90; 
}





