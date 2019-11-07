#include "smarthouse_globals.h"

SystemParamPacket system_params = 
{
	{
		.type=SYSTEM_PARAM_PACKET_ID,
		.size=sizeof(SystemParamPacket),
		.seq=0
	},
	.protocol_version= SMARTHOUSE_PROTOCOL_VERSION,
	.firmware_version= SMARTHOUSE_FIRMWARE_VERSION,
//  .timer_period_ms=10,
	.comm_speed=19200
//  .comm_cycles=2,
//  .periodic_packet_mask=(PSystemStatusFlag|PJointStatusFlag|PDriveStatusFlag|PSonarStatusFlag),
//  .watchdog_cycles=0,
//  .num_joints=NUM_JOINTS
};

SystemStatusPacket system_status = 
{
	{
		.type=SYSTEM_STATUS_PACKET_ID,
		.size=sizeof(SystemStatusPacket),
		.seq=0
  	},
	.rx_buffer_size=0,
	.rx_packets=0,
	.rx_packet_errors=0
	.rx_seq=0,
//	.rx_packet_queue=0,
//	.idle_cycles=0
};

PacketTest test=
{
	{
		.type=TEST_PACKET_ID,
		.size=sizeof(PacketTest),
		.seq=0
	},
	.type=Null,
	.pintest=0
}

DigitalParamPacket digital_control[DIGITAL_MAX] = {
{//pinDig 0
	//PacketIndex
	{
		//Packetheader inside PacketIndex
		{
        		.type=DIGITAL_PARAM_PACKET_ID,
        		.size=sizeof(DigitalParamPacket),
        		.seq=0
        	},
	.index=0
	},
	//DigitalParam
	{
		.type=Null,
		.ledOn=0,
		.ledOff=0,
		.dimmer=0,
		.input=0,
		.intensity=0
	}
},
{//pinDig 1
	//PacketIndex
	{
		//Packetheader inside PacketIndex
		{
        		.type=DIGITAL_PARAM_PACKET_ID,
        		.size=sizeof(DigitalParamPacket),
        		.seq=0
        	},
	.index=1
	},
	//DigitalParam
	{
		.type=Null,
		.ledOn=0,
		.ledOff=0,
		.dimmer=0,
		.input=0,
		.intensity=0
	}
},
{//pinDig 2
	//PacketIndex
	{
		//Packetheader inside PacketIndex
		{
        		.type=DIGITAL_PARAM_PACKET_ID,
        		.size=sizeof(DigitalParamPacket),
        		.seq=0
        	},
	.index=2
	},
	//DigitalParam
	{
		.type=Null,
		.ledOn=0,
		.ledOff=0,
		.dimmer=0,
		.input=0,
		.intensity=0
	}
},
{//pinDig 3
	//PacketIndex
	{
		//Packetheader inside PacketIndex
		{
        		.type=DIGITAL_PARAM_PACKET_ID,
        		.size=sizeof(DigitalParamPacket),
        		.seq=0
        	},
	.index=3
	},
	//DigitalParam
	{
		.type=Null,
		.ledOn=0,
		.ledOff=0,
		.dimmer=0,
		.input=0,
		.intensity=0
	}
},
{//pinDig 4
	//PacketIndex
	{
		//Packetheader inside PacketIndex
		{
        		.type=DIGITAL_PARAM_PACKET_ID,
        		.size=sizeof(DigitalParamPacket),
        		.seq=0
        	},
	.index=4
	},
	//DigitalParam
	{
		.type=Null,
		.ledOn=0,
		.ledOff=0,
		.dimmer=0,
		.input=0,
		.intensity=0
	}
},
{//pinDig 5
	//PacketIndex
	{
		//Packetheader inside PacketIndex
		{
        		.type=DIGITAL_PARAM_PACKET_ID,
        		.size=sizeof(DigitalParamPacket),
        		.seq=0
        	},
	.index=5
	},
	//DigitalParam
	{
		.type=Null,
		.ledOn=0,
		.ledOff=0,
		.dimmer=0,
		.input=0,
		.intensity=0
	}
},
{//pinDig 6
	//PacketIndex
	{
		//Packetheader inside PacketIndex
		{
        		.type=DIGITAL_PARAM_PACKET_ID,
        		.size=sizeof(DigitalParamPacket),
        		.seq=0
        	},
	.index=6
	},
	//DigitalParam
	{
		.type=Null,
		.ledOn=0,
		.ledOff=0,
		.dimmer=0,
		.input=0,
		.intensity=0
	}
},
{//pinDig 7
	//PacketIndex
	{
		//Packetheader inside PacketIndex
		{
        		.type=DIGITAL_PARAM_PACKET_ID,
        		.size=sizeof(DigitalParamPacket),
        		.seq=0
        	},
	.index=7
	},
	//DigitalParam
	{
		.type=Null,
		.ledOn=0,
		.ledOff=0,
		.dimmer=0,
		.input=0,
		.intensity=0
	}
}
};

AnalogParamPacket analog_control[ANALOG_MAX] = {
{//Pin0
	//PacketIndex
	{
		//Packetheader inside PacketIndex
		{
        		.type=ANALOG_PARAM_PACKET_ID,
        		.size=sizeof(AnalogParamPacket),
        		.seq=0
        	},
	.index=0
	},
	//AnalogParam
	{
		.Adc=0,
		.samples=0
	}
},
{//Pin1
	//PacketIndex
	{
		//Packetheader inside PacketIndex
		{
        		.type=ANALOG_PARAM_PACKET_ID,
        		.size=sizeof(AnalogParamPacket),
        		.seq=0
        	},
	.index=1
	},
	//AnalogParam
	{
		.Adc=0,
		.samples=0
	}
},
{//Pin2
	//PacketIndex
	{
		//Packetheader inside PacketIndex
		{
        		.type=ANALOG_PARAM_PACKET_ID,
        		.size=sizeof(AnalogParamPacket),
        		.seq=0
        	},
	.index=2
	},
	//AnalogParam
	{
		.Adc=0,
		.samples=0
	}
},
{//Pin3
	//PacketIndex
	{
		//Packetheader inside PacketIndex
		{
        		.type=ANALOG_PARAM_PACKET_ID,
        		.size=sizeof(AnalogParamPacket),
        		.seq=0
        	},
	.index=3
	},
	//AnalogParam
	{
		.Adc=0,
		.samples=0
	}
},
{//Pin4
	//PacketIndex
	{
		//Packetheader inside PacketIndex
		{
        		.type=ANALOG_PARAM_PACKET_ID,
        		.size=sizeof(AnalogParamPacket),
        		.seq=0
        	},
	.index=4
	},
	//AnalogParam
	{
		.Adc=0,
		.samples=0
	}
},
{//Pin5
	//PacketIndex
	{
		//Packetheader inside PacketIndex
		{
        		.type=ANALOG_PARAM_PACKET_ID,
        		.size=sizeof(AnalogParamPacket),
        		.seq=0
        	},
	.index=5
	},
	//AnalogParam
	{
		.Adc=0,
		.samples=0
	}
},
{//Pin6
	//PacketIndex
	{
		//Packetheader inside PacketIndex
		{
        		.type=ANALOG_PARAM_PACKET_ID,
        		.size=sizeof(AnalogParamPacket),
        		.seq=0
        	},
	.index=6
	},
	//AnalogParam
	{
		.Adc=0,
		.samples=0
	}
},
{//Pin7
	//PacketIndex
	{
		//Packetheader inside PacketIndex
		{
        		.type=ANALOG_PARAM_PACKET_ID,
        		.size=sizeof(AnalogParamPacket),
        		.seq=0
        	},
	.index=7
	},
	//AnalogParam
	{
		.Adc=0,
		.samples=0
	}
}
};
