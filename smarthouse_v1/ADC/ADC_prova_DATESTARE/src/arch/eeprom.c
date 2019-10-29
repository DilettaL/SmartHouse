#include "eeprom.h"
#include "avr/eeprom.h"
void EEPROM_init(void){
}

void EEPROM_read(void* dest_, const uint16_t src, uint16_t size){
  uint8_t * dest=(uint8_t*)dest_;
  uint16_t s=src;;
  uint16_t s_end=src+size;
  while(s<s_end){
    eeprom_busy_wait();
    *dest=eeprom_read_byte((uint8_t*)s);
    ++s;
    ++dest;
  }
}

void EEPROM_write(uint16_t dest, const void* src_,  uint16_t size){
  const uint8_t * s=(uint8_t*)src_;
  const uint8_t * s_end=s+size;
  while(s<s_end){
    eeprom_busy_wait();
    eeprom_write_byte((uint8_t*)dest, *s);
    ++s;
    ++dest;
  }
}
