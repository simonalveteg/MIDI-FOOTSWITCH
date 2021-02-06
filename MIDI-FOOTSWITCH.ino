
#include "MIDIUSB.h"
#include "OneButton.h"

const int channel = 12;                                           // midi channel (12 is 13)
const int Pins[9] = {6, 8, A0, A5, 9, 4, A2, A1, A3} ;            // PINS THAT BUTTONS ARE CONNECTED TO in order: 
const int togglePin = 12;                                         // PIN THAT TOGGLEBUTTON IS CONNECTED TO
const int longPressTime = 500;                                    // NUMBER OF MS NEEDED TO TRIGGER LONG PRESS
const int ledPin = 11;                                             // PIN THAT LED IS CONNECTED TO
const int velocity = 120;
int baseNote = 0;

OneButton button1(Pins[0], true, true);
OneButton button2(Pins[1], true, true);
OneButton button3(Pins[2], true, true);
OneButton button4(Pins[3], true, true);
OneButton button5(Pins[4], true, true);
OneButton button6(Pins[5], true, true);
OneButton button7(Pins[6], true, true);
OneButton button8(Pins[7], true, true);
OneButton button9(Pins[8], true, true);
OneButton toggleButton(togglePin, true, true);

void setup() {
  Serial.begin(31250);

  // led pin
  pinMode(ledPin, OUTPUT);

  // toggle button
  toggleButton.attachClick([]() {
    layerToggle();
  });


  // regular buttons
  button1.setPressTicks(longPressTime);
  button1.attachLongPressStop([]() {
    longpress(1);
  });
  button1.attachClick([]() {
    singleclick(2);
  });
  button2.setPressTicks(longPressTime);
  button2.attachLongPressStop([]() {
    longpress(3);
  });
  button2.attachClick([]() {
    singleclick(4);
  });
  button3.setPressTicks(longPressTime);
  button3.attachLongPressStop([]() {
    longpress(5);
  });;
  button3.attachClick([]() {
    singleclick(6);
  });
  button4.setPressTicks(longPressTime);
  button4.attachLongPressStop([]() {
    longpress(7);
  });
  button4.attachClick([]() {
    singleclick(8);
  });
  button5.setPressTicks(longPressTime);
  button5.attachLongPressStop([]() {
    longpress(9);
  });
  button5.attachClick([]() {
    singleclick(10);
  });
  button6.setPressTicks(longPressTime);
  button6.attachLongPressStop([]() {
    longpress(11);
  });
  button6.attachClick([]() {
    singleclick(12);
  });
  button7.setPressTicks(longPressTime);
  button7.attachLongPressStop([]() {
    longpress(13);
  });
  button7.attachClick([]() {
    singleclick(14);
  });
  button8.setPressTicks(longPressTime);
  button8.attachLongPressStop([]() {
    longpress(15);
  });
  button8.attachClick([]() {
    singleclick(16);
  });
  button9.setPressTicks(longPressTime);
  button9.attachLongPressStop([]() {
    longpress(17);
  });
  button9.attachClick([]() {
    singleclick(18);
  });


}


void loop() {
  button1.tick();
  button2.tick();
  button3.tick();
  button4.tick();
  button5.tick();
  button6.tick();
  button7.tick();
  button8.tick();
  button9.tick();
  toggleButton.tick();
}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void ledFlicker() {
    if (baseNote == 0) {
    digitalWrite(ledPin, HIGH);
    delay(200);
    digitalWrite(ledPin, LOW);
  } else {
    digitalWrite(ledPin, LOW);
    delay(200);
    digitalWrite(ledPin, HIGH);
  }
}

void longpress(byte pitch) {
  Serial.println("LONGPRESS");
  noteOn(channel, baseNote + pitch, velocity);
  delay(15);
  noteOff(channel, baseNote + pitch, velocity);
  MidiUSB.flush();
  ledFlicker();
}
void singleclick(byte pitch) {
  Serial.println("SINGLE CLICK");
  noteOn(channel, baseNote + pitch, velocity);
  MidiUSB.flush();
  delay(15);
  noteOff(channel, baseNote + pitch, velocity);
  MidiUSB.flush();
  ledFlicker();
}

void layerToggle() {
  if (baseNote == 0) {
    baseNote = 48;
    digitalWrite(ledPin, HIGH);
  } else {
    baseNote = 0;
    digitalWrite(ledPin, LOW);
  }
  Serial.print("Base Note is:  ");
  Serial.println(baseNote);
}
