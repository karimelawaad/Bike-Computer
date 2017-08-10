#include <IRremote.h>
#include <IRremoteInt.h>
#include <U8glib.h>
#include <stdlib.h>
<<<<<<< 24421c16034d77a71ea5f58d523eae3c8960ad3c

#define RECV_PIN 2
=======
#include <LowPower.h>

#define RECV_PIN 2
#define WAKE_UP_PIN 3
>>>>>>> added stand-by power saving mode
#define WHEEL_RADIUS 0.29f
#define NUMBER_OF_MAGNETS 1

#define DIN_PIN 4
#define DC_PIN 5
#define RST_PIN 6
#define CE_PIN 7
#define CLK_PIN 8
#define BACKLIGHT_PIN 11

IRrecv irrecv(RECV_PIN);
decode_results results;

U8GLIB_PCD8544 disp(CLK_PIN, DIN_PIN, CE_PIN, DC_PIN, RST_PIN);

uint8_t currentCyclesCount;
uint32_t cyclesCount;
float currentSpeed;
uint64_t lastUpdateTime;

void setup() {
  // put your setup code here, to run once:
  currentCyclesCount = 0;
  cyclesCount = 0;
  currentSpeed = 0;
<<<<<<< 24421c16034d77a71ea5f58d523eae3c8960ad3c

=======
  
  pinMode(WAKE_UP_PIN, INPUT);
  attachInterrupt(1, wakeUp, LOW);
  
>>>>>>> added stand-by power saving mode
  analogWrite(BACKLIGHT_PIN, 255);
  
  Serial.begin(9600);
  Serial.println("Starting..");

  irrecv.enableIRIn();  

  updateDisplay();
  lastUpdateTime = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(irrecv.decode(&results))
  {
    currentCyclesCount = results.value;
    cyclesCount += currentCyclesCount;
    currentSpeed = currentCyclesCount * WHEEL_RADIUS * 6.28318530716f * 3.6f / (NUMBER_OF_MAGNETS * 2);
    disp.firstPage();
    do {
    updateDisplay();
    }while(disp.nextPage());
    Serial.print("Current Cycles Count: ");
    Serial.print(currentCyclesCount);
    Serial.print("\tTotal Cycles Count: ");
    Serial.println(cyclesCount);
    Serial.print(currentSpeed);
    Serial.println(" KM/H");

    lastUpdateTime = millis();
    irrecv.resume();
  }
<<<<<<< 24421c16034d77a71ea5f58d523eae3c8960ad3c
=======

  if(millis() - lastUpdateTime > 5 * 1000 * 60){
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  }
}

void wakeUp()
{
  
>>>>>>> added stand-by power saving mode
}

void updateDisplay()
{
//  disp.firstPage();
//  disp.setFont(u8g_font_freedoomr25n);  // select font
//  disp.setPrintPos(15, 30);  // set position
//  
//  //FloatToStringNew(currentSpeed, currentVelocity, 10);
//  snprintf(currentSpeedStr, 10, "%f", currentSpeed);
//  disp.drawStr(0, 25, dtostrf(currentSpeed, 5, 2, currentSpeedStr));
//  disp.drawStr(50, 15, "km/hr ");
  char currentSpeedStr[10];
  disp.firstPage();
  do{
  disp.setFont(u8g_font_fur25);  // select font
  snprintf(currentSpeedStr, 10, "%.1f", currentSpeed);
  disp.drawStr(0, 35, dtostrf(currentSpeed, 5, 2, currentSpeedStr));
  //disp.setPrintPos(15, 15);  // set position
  }while(disp.nextPage());
}
<<<<<<< 24421c16034d77a71ea5f58d523eae3c8960ad3c

=======

>>>>>>> added stand-by power saving mode
