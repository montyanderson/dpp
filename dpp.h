#include <Arduino.h>

#ifndef DPP
#define DPP

#define DPP_DELAY 1000

struct dpp_header {
    uint32_t size;
    uint32_t hash;
};

uint32_t dpp_hash(char *data, uint32_t length) {
    uint32_t i;
    uint32_t hash = 5381;
    int c;

    for(i = 0; i < length; i++) {
        c = data[i];
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

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

void dpp_write(uint8_t s, uint8_t d, char *data, uint32_t size) {
    struct dpp_header header;
    char *header_b = (char *) &header;
    size_t i;

    header.size = size;
    header.hash = dpp_hash(data, size);

    pinMode(s, OUTPUT);
    pinMode(d, INPUT_PULLUP);

    while(digitalRead(d) != 0);

    pinMode(d, INPUT);

    while(digitalRead(d) != 1);
    digitalWrite(s, 1);
    delayMicroseconds(DPP_DELAY);
    digitalWrite(s, 0);

    pinMode(d, OUTPUT);

    for(i = 0; i < ; i++) {
        dpp_wb(s, d, header_b[i]);
    }

    for(i = 0; i < size; i++) {
        dpp_wb(s, d, data[i]);
    }
}

void dpp_read(uint8_t s, uint8_t d) {
    struct dpp_header header;
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

    for(i = 0; i < sizeof(struct dpp_header); i++) {
        ((char *) &header)[0] = dpp_rb(s, d);
    }

    //Serial.println(header.size);

    while(1) {
        Serial.print(dpp_rb(s, d));
    }
}

#endif
