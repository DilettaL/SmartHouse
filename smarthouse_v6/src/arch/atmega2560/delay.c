#include "delay.h"
#include <util/delay.h>

void delayMs(uint16_t ms){
  while(ms){
    _delay_ms(1);
    --ms;
  }
}
