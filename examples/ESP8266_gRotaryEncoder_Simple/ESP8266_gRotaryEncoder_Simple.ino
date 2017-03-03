/*
    Rotary Encoder Example
    
    Encoder is connected to +3.3V in to the common
        Encoder has 3 pins, A is bit 1, B is bit 2 and C is input
            
                             _____
              (D5 - 14)  A -|     |
              (D6 - 12)  B -|  O  |
                  (VCC)  C -|_____|
                
        A connects to ESP8266 pin D5
        B connects to ESP8266 pin D6

*/
#include <gRotaryEncoder.h>

gRotaryEncoder encoder_1 = gRotaryEncoder(); // Uses default pins

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial){}
  Serial.println(" gRotaryEncoder Example for ESP8266 ");
}

void loop() {
  // put your main code here, to run repeatedly:
  while (encoder_1.readPins())
  {
    // Something has changed, check the properties for step count and direction
    Serial.println(String(encoder_1.steps) + " - " + String(encoder_1.spinDirection));
  }

}
