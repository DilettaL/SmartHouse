/*
Lui utilizza funzioni di libreria: https://www.nongnu.org/avr-libc/user-manual/group__avr__eeprom.html#ga44c64ebb425fcb34b8d4dc19c4079869

4k di EEPROM
//EEPROM-CPU: three registers 
	//EEPROM Address Registers: 	EEARH=da 11 a 8
					EEARL=da 7 a 0
					0 and 4096
//EEPROM Data Register
	//EEDR – The EEPROM Data Register 7MSB 0LSB
//EEPROM Control Register
	//EECR – The EEPROM Control Register
	EEPM1 EEPM0 EERIE EEMPE EEPE EERE
	//n order to prevent unintentional EEPROM writes, a specific write procedure must be followed
	//PROBLEMI DI CORRUZIONE !
	ATTENZIONE: durante l'utilizzo della eeprom può accadere che la Vcc non sia sufficiente per la frequenza utilizzata, quindi necessario
	prendere delle precauzioni= altrimenti corruzione dei dati
	PER EVITARE LA CORRUZIONE DEL DATO:
	AVR RESET active (low)->enabling the internal Brown-out Detector (BOD)
	Scrittura: CPU interrotta per 4 cicli di ck
	Lettura: CPU interrotta per 2 cicli di ck


Interrupt: durante la lettura / scrttura della EEPROM si disabilitano

CodeExample:
void EEPROM_write(unsigned int uiAddress, unsigned char ucData)
{
/* Wait for completion of previous write 
while(EECR & (1<<EEPE))
;
/* Set up address and Data Registers 
EEAR = uiAddress;
EEDR = ucData;
/* Write logical one to EEMPE 
EECR |= (1<<EEMPE);
/* Start eeprom write by setting EEPE
EECR |= (1<<EEPE);
}

unsigned char EEPROM_read(unsigned int uiAddress)
{
/* Wait for completion of previous write 
while(EECR & (1<<EEPE))
;
/* Set up address register 
EEAR = uiAddress;
/* Start eeprom read by writing EERE 
EECR |= (1<<EERE);
/* Return data from Data Register
return EEDR;
}

*/
