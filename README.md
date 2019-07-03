# SmartHouse
5. SmartHouse [2-3 w/BT]
   Arduino: Build a smart switch/dimmer/controller that can be controlled
            by bluetooth. We don't use bluetooth, we use a serial first. 

            The arduino should support:
            8 switches/dimmers (simulate tghem with LEDS).
            8 ADC channels
            8 Digital inputs

            Define a protocol to
            - Configure the device (give it a "name"),
              set which channels are used, and what is the name of each channel
              
            - Send commands to the device (based on the "name");
              Upon correct execution of a command, the device should send back
              an "ack" message.
              
            - receive readings from the device (based on the "name");
            
            
   From PC: Implement a "controller" program that can baptize the device,
            and interact with it, from command line

            eg

            $> smart_house_host set_name kitchen_controller
            $> smart_house set_channel_name kitchen_controller switch_0 "top_fridge"
            $> smart_house set_channel_value "top_fridge" 1
            $> smart_house kitchen_controller query_channels
