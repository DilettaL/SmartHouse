#include <stdio.h>
#include <string.h>
#include "smarthouse_firmware_globals.h"
#include "smarthouse_functions.h"
#include "packet_handler.h"
#include "smarthouse_packets.h"
#include "adc.h"
#include "digio.h"
#include "pwm.h"
#include "uart.h"
#include "delay.h"

uint8_t sync;
static struct UART* uart;
static PacketHandler packet_handler;
PacketHeader *pointer_firmware=(PacketHeader*)&test_config;

void flushInputBuffers(void) {
	while (UART_rxBufferFull(uart))
	{
		uint8_t c=UART_getChar(uart);
		PacketHandler_rxByte(&packet_handler, c);
	}
}

int flushOutputBuffers(void)
{
	while (packet_handler.tx_size)
		UART_putChar(uart, PacketHandler_txByte(&packet_handler));
	return packet_handler.tx_size;
}

//variables for initializeBuffer
TestStatusPacket test_config_buffer;
TestStatusPacket test_status_buffer;
DigitalConfigPacket digital_config_buffer;
DigitalStatusPacket digital_status_buffer;
AnalogConfigPacket analog_config_buffer;
AnalogStatusPacket analog_status_buffer;
EepromWritePacket eeprom_write_buffer;
EepromReadPacket eeprom_read_buffer;

PacketHeader* firmware_initializeBuffer(PacketType type, PacketSize size, void* args __attribute__((unused))) 
{
	if (type==TEST_CONFIG_PACKET_ID && size==sizeof(TestConfigPacket))
	{	return (PacketHeader*) &test_config_buffer;	}
	else if(type==TEST_STATUS_PACKET_ID && size==sizeof(TestStatusPacket))
	{	return (PacketHeader*) &test_status_buffer;	}
	else if (type==DIGITAL_CONFIG_PACKET_ID && size==sizeof(DigitalConfigPacket))
	{	return (PacketHeader*) &digital_config_buffer;}
	else if (type== DIGITAL_STATUS_PACKET_ID && size==sizeof(DigitalStatusPacket))
	{	return (PacketHeader*) &digital_status_buffer;}
	else if (type== ANALOG_CONFIG_PACKET_ID && size==sizeof(AnalogConfigPacket))
	{	return (PacketHeader*) &analog_config_buffer;}
	else if (type== ANALOG_STATUS_PACKET_ID && size==sizeof(AnalogStatusPacket))
	{	return (PacketHeader*) &analog_status_buffer;}	
	else if (type== EEPROM_WRITE_PACKET_ID && size==sizeof(EepromWritePacket))
	{	return (PacketHeader*) &eeprom_write_buffer;}	
	else if (type== EEPROM_READ_PACKET_ID && size==sizeof(EepromReadPacket))
	{	return (PacketHeader*) &eeprom_read_buffer;}	
	else
	{	return 0; }
}

PacketStatus firmware_onReceive(PacketHeader* header, void* args __attribute__((unused))) 
{
	++header->seq;
	PacketIndexed *idx_p=(PacketHeader*)header;
	switch (header->type)
	{
		case TEST_CONFIG_PACKET_ID:
			break;
		case TEST_STATUS_PACKET_ID:
			break;
		case DIGITAL_CONFIG_PACKET_ID:
			memcpy(&digital_config, header, header->size);
			Smarthouse_digital();
			//pointer_firmware=(PacketHeader*)&digital_status
/*DEBUG*/PacketHandler_sendPacket(&packet_handler, (PacketHeader*) &digital_status[idx_p->index]);
			break;
		case DIGITAL_STATUS_PACKET_ID:
			PacketHandler_sendPacket(&packet_handler, (PacketHeader*) &digital_status[idx_p->index]);
			break;
		case ANALOG_CONFIG_PACKET_ID:
			memcpy(&analog_config, header, header->size);
			Smarthouse_analog();
			//pointer_firmware=(PacketHeader*)&analog_status;
/*DEBUG*/PacketHandler_sendPacket(&packet_handler, (PacketHeader*) &analog_status[idx_p->index]);
			break;
		case ANALOG_STATUS_PACKET_ID:
			PacketHandler_sendPacket(&packet_handler, (PacketHeader*) &analog_status[idx_p->index]);
			break;
		case EEPROM_WRITE_PACKET_ID:
			memcpy(&eeprom_write, header, header->size);
			Smarthouse_paramSave();
//PacketHandler_sendPacket(&packet_handler, (PacketHeader*) &digital_status[eeprom_write.pin]);
			break;
		case EEPROM_READ_PACKET_ID:
/*DEBUG*/
DigIO_setDirection(pin, Output);
DigIO_setValue(pin, 1);
			memcpy(&eeprom_read, header, header->size);
			Smarthouse_paramLoad();
			if(eeprom_read.type==digital)
			{
				PacketHandler_sendPacket(&packet_handler, (PacketHeader*) &digital_status[eeprom_read.pin]);
			}
			else if(eeprom_read.type==analog)
			{
				PacketHandler_sendPacket(&packet_handler, (PacketHeader*) &analog_status[eeprom_read.pin]);
			}
			break;
		default:
			break;
	}
	return Success;
}

PacketOperations test_config_ops = {
	TEST_CONFIG_PACKET_ID,
	sizeof(TestConfigPacket),
	firmware_initializeBuffer,
	0,
	firmware_onReceive,
	0
};

PacketOperations test_status_ops = {
	TEST_STATUS_PACKET_ID,
	sizeof(TestStatusPacket),
	firmware_initializeBuffer,
	0,
	firmware_onReceive,
	0
};	

PacketOperations digital_config_ops = {
	DIGITAL_CONFIG_PACKET_ID,
	sizeof(DigitalConfigPacket),
	firmware_initializeBuffer,
	0,
	firmware_onReceive,
	0
};

PacketOperations digital_status_ops = {
	DIGITAL_STATUS_PACKET_ID,
	sizeof(DigitalStatusPacket),
	firmware_initializeBuffer,
	0,
	firmware_onReceive,
	0
};

PacketOperations analog_config_ops = {
	ANALOG_CONFIG_PACKET_ID,
	sizeof(AnalogConfigPacket),
	firmware_initializeBuffer,
	0,
	firmware_onReceive,
	0
};

PacketOperations analog_status_ops = {
	ANALOG_STATUS_PACKET_ID,
	sizeof(AnalogStatusPacket),
	firmware_initializeBuffer,
	0,
	firmware_onReceive,
	0
};

PacketOperations eeprom_write_ops = {
	EEPROM_WRITE_PACKET_ID,
	sizeof(EepromWritePacket),
	firmware_initializeBuffer,
	0,
	firmware_onReceive,
	0

};

PacketOperations eeprom_read_ops = {
	EEPROM_READ_PACKET_ID,
	sizeof(EepromReadPacket),
	firmware_initializeBuffer,
	0,
	firmware_onReceive,
	0

};

int main (int argc, char** argv)
{
	DigIO_init();
	PWM_init();
	Adc_init();
	uart = UART_init(0,115200);
	PacketHandler_initialize(&packet_handler);
	PacketHandler_installPacket(&packet_handler, &test_config_ops);
	PacketHandler_installPacket(&packet_handler, &test_status_ops);
	PacketHandler_installPacket(&packet_handler, &digital_config_ops);
	PacketHandler_installPacket(&packet_handler, &digital_status_ops);
	PacketHandler_installPacket(&packet_handler, &analog_config_ops);
	PacketHandler_installPacket(&packet_handler, &analog_status_ops);	
	PacketHandler_installPacket(&packet_handler, &eeprom_write_ops);	
	PacketHandler_installPacket(&packet_handler, &eeprom_read_ops);	
	int global_seq = 0;
	while (1)
	{
		flushInputBuffers();
		test_config.header.seq = global_seq;
		++global_seq;
		PacketHandler_sendPacket(&packet_handler, (PacketHeader*)&test_status);
		delayMs(10);
		flushOutputBuffers();
	}	
}
