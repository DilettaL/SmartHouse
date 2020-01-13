# SmartHouse
5. SmartHouse [2-3 w/BT]
   Arduino: Build a smart switch/dimmer/controller that can be controlled
            by bluetooth. We don't use bluetooth, we use a serial first. 

            The arduino should support:
            8 switches/dimmers (simulate tghem with LEDS).
            8 ADC channels
            8 Digital inputs
            
            Give name to the device:
            es. $>Smarthouse
            
            To use the device:
            "to choice operation insert one of this commands(then choice the pin and other settings):
            $>Smarthouse	ledOn
            $>Smarthouse	dimmer
            $>Smarthouse	digital_input
            $>Smarthouse	ledOff
            $>Smarthouse	adc
            to request a status packet insert(then choice packet type):
            $>Smarthouse	request
            to access to eeprom insert(then choice pin and packet type):
            $>Smarthouse	save  
            or
            $>Smarthouse	load
            to exit insert:   
            $>Smarthouse	quit"
