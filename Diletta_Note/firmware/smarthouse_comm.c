#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "uart.h"
//librerie dell'handler common 
//libreria pacchetti
#include "smarthouse_comm.h"
#include "smarthouse_packets.h"
//2f)/*PROVA*/
#include "packet_avr_comm.h"  
/*********************In realtà tutta la roba con packet_handler andrebbe gestita con i deffered******************/

static struct UART* uart;
static uint16_t global_seq;
static PacketHandler packet_handler; //Dovrebbe essere deferred

//2a)
void Smarthouse_commInit(void)
{
	uart=UART_init("uart_0", system_params.comm_speed);
	global_seq=0;
	PacketHandler_initialize(&packet_handler); //dovrebbe essere deferred
	//Installa tutti i pacchetti:Smarthouse_initializePackets();
	//Prima di utilizzarla bisogna definire i pacchetti
	//2f)/*PROVA*/
	PacketHandler_initialize(&packet_handler);
	Smarthouse_initializePackets();
}

//2g/*PROVA*/
void Smarthouse_initializePackets()
{
	//x5 pacchetti in totale
	PacketHandler_installPacket(&packet_handler, ANALOG_STATUS_PACKET_ID, sizeof(AnalogStatus), PACKETS_PER_TYPE_MAX, funzione da richiamare, argomenti);
	PacketHandler_installPacket(&packet_handler, ANALOG_CONFIG_PACKET_ID, sizeof(AnalogConfig), PACKETS_PER_TYPE_MAX, funzione da richiamare, argomenti);
	PacketHandler_installPacket(&packet_handler, DIGITAL_STATUS_PACKET_ID, sizeof(DigitalStatus), PACKETS_PER_TYPE_MAX, funzione da richiamare, argomenti);
	PacketHandler_installPacket(&packet_handler, DIGITAL_CONFIG_PACKET_ID, sizeof(DigitalConfig), PACKETS_PER_TYPE_MAX, funzione da richiamare, argomenti);
	PacketHandler_installPacket(&packet_handler, SISTEM_PARAM_PACKET_ID, sizeof(SystemParamPacket), PACKETS_PER_TYPE_MAX, funzione da richiamare, argomenti);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Smarthouse_commHandle(void)
{
	//Arduino riceve da uart con Smarthouse_flushInputBuffers();
	//Si deve in qualche modo elaborare il pacchetto
	//A questo punto si rinvia al pc il pacchetto con Smarthouse_flushOutputBuffers();
}
/*void Orazio_commHandle(void){
  Orazio_flushInputBuffers();
  ++global_seq;
  system_status.rx_packet_queue=packet_handler.pending_packets_size;
  DeferredPacketHandler_processPendingPackets(&packet_handler);
  if (system_params.periodic_packet_mask & PSystemStatusFlag) 
    Orazio_sendPacket((PacketHeader*)&system_status);
  if (system_params.periodic_packet_mask & PJointStatusFlag) {
    for (uint8_t i=0; i<NUM_JOINTS; ++i)
      Orazio_sendPacket((PacketHeader*)&joint_status[i]);
  }
  if (system_params.periodic_packet_mask & PDriveStatusFlag)
    Orazio_sendPacket((PacketHeader*)&drive_status);
  
#ifdef _ORAZIO_USE_SONAR_
  if ((system_params.periodic_packet_mask & PSonarStatusFlag) && Orazio_sonarReady()) 
    Orazio_sendPacket((PacketHeader*)&sonar_status);
#endif

  // if we have a string message to send to the host, we send it
  if(string_message.header.seq>0 && string_message.message[0]){
    Orazio_sendPacket((PacketHeader*)&string_message);
    string_message.header.seq=0;
  }
  Orazio_sendPacket((PacketHeader*)&end_epoch);
  Orazio_flushOutputBuffers();
}*/
