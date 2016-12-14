#include "dpp.h"

char str[100];

void setup() {
    strcpy(str, "Welcome, dear Rosencrantz and Guildenstern.");

  delay(100);
  dpp_write(8, 9, str, strlen(str));

  
} 

void loop() {
}
