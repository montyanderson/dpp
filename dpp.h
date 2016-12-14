#include <Arduino.h>

#ifndef DPP
#define DPP

#define DPP_DELAY 500

char dpp_rb(uint8_t s, uint8_t d) {
  uint8_t j;
  char c;

  for(j = 0; j < 8; j++) {
    while(digitalRead(s) == 0);
    c |= digitalRead(d) << j;
    while(digitalRead(s) == 1);
  }

  return c;
}

void dpp_wb(uint8_t s, uint8_t d, char c) {
    uint8_t j;

    for(j = 0; j < 8; j++) {
        digitalWrite(d, (c & (1 << j)) >> j);
        digitalWrite(s, 1);
        delayMicroseconds(DPP_DELAY);
        digitalWrite(s, 0);
        delayMicroseconds(DPP_DELAY);
    }
}

void dpp_write(uint8_t s, uint8_t d, char *data, size_t length) {
    size_t i;

    pinMode(s, OUTPUT);
    pinMode(d, INPUT_PULLUP);

    while(digitalRead(d) != 0);

    pinMode(d, INPUT);

    while(digitalRead(d) != 1);
    digitalWrite(s, 1);
    delayMicroseconds(DPP_DELAY);
    digitalWrite(s, 0);

    pinMode(d, OUTPUT);

    for(i = 0; i < length; i++) {
        dpp_wb(s, d, data[i]);
    }
}

void dpp_read(uint8_t s, uint8_t d) {
    size_t i;

    delay(1000);

    pinMode(s, INPUT_PULLUP);
    pinMode(d, OUTPUT);

    while(digitalRead(s) != 0);

    pinMode(s, INPUT);

    digitalWrite(d, 1);
    while(digitalRead(s) != 1);
    while(digitalRead(s) == 1);

    pinMode(s, INPUT);
    pinMode(d, INPUT);

    while(1) {
        Serial.print(dpp_rb(s, d));
    }
}

#endif
