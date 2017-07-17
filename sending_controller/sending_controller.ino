/*
 * Sends a signal each time the bike completes one cycle using IR communication.
 * A complete cycle occurs each time the reed switch is activated.
 * Two possible approaches:
 *    1- Send a signal each time a cycle completes
 *    2- Send the total number of cycles each 1 second
 *    
 *    Connection:
 *    2- Reed Switch
 *    3- IR Led
 */

#include <IRremote.h>
#include <IRremoteInt.h>

#define REED_PIN 2

IRsend irsend;

volatile uint8_t cyclesCount;
uint64_t lastSendTime;

void setup() {
  // put your setup code here, to run once:
  cli();
//  TCCR1A = 0;// set entire TCCR1A register to 0
//  TCCR1B = 0;// same for TCCR1B
//  TCNT1  = 0;//initialize counter value to 0
//  OCR1A = 15624;
//  TCCR1B |= (1 << WGM12);  // turn on CTC mode
//  TCCR1B |= (1 << CS12) | (1 << CS10);  // Set prescaler to 1024
//  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  pinMode(REED_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(REED_PIN), incrementCycles, RISING);
  cyclesCount = 0;
  lastSendTime = millis();
  sei();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(millis() - lastSendTime >= 1000)
  {
    irsend.sendRC6(cyclesCount, 16);
    cyclesCount = 0;
    lastSendTime = millis();
  }
}

void incrementCycles(){
  cyclesCount++;
}

ISR(TIMER1_COMPA_vect){
  irsend.sendRC6(cyclesCount, 16);
  cyclesCount = 0;
}

