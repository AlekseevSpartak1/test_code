void Sensor_ReadAll(Sensor_HandleTypeDef *sensors, uint32_t data[][4], int num_sensors) {
   
    cmd_t command_time = {.flag = 0, .count = 2, .address = 4}; 
    cmd_t command_data = {.flag = 0, .count = 2, .address = 5}; 


    for (uint32_t i = 0; i < 10000; i++) {
        asm("nop");
    }
    
    for (int i = 0; i < num_sensors; i++) {
        sensor_send_cmd(&sensors[i], &command_time); 
    }

 
   
    for (int i = 0; i < num_sensors; i++) {
        LL_GPIO_ResetOutputPin(sensors[i].cs_port, sensors[i].cs_pin);
        spi_receive(sensors[i].SPIx, (uint16_t*)data[i], 4); 
        LL_GPIO_SetOutputPin(sensors[i].cs_port, sensors[i].cs_pin);
    }

    for (int i = 0; i < num_sensors; i++) {
        sensor_send_cmd(&sensors[i], &command_data); 

 
    for (uint32_t i = 0; i <10000; i++) {
        asm("nop");
    }

    for (int i = 0; i < num_sensors; i++) {
        LL_GPIO_ResetOutputPin(sensors[i].cs_port, sensors[i].cs_pin);
        spi_receive(sensors[i].SPIx, (uint16_t*)(data[i] + 2), 4);
        LL_GPIO_SetOutputPin(sensors[i].cs_port, sensors[i].cs_pin);
    }
}
}


void updateTimer3() {
    static uint32_t code[256][4];
    static uint32_t cnt = 0;

    Sensor_ReadAll(sensors, code, MAX_SENSORS); 


    if (++cnt == 256) {
        cnt = 0;
    }
    
   
}
