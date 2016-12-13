#include "dpp.h"
#define S 8
#define D 9

void setup() {
  Serial.begin(9600);
  dpp_read(8, 9);
}

void loop() {

}
