
sensors_mdriver.c /переделал функцию

void Sensor_ReadAll(Sensor_HandleTypeDef *sensors, uint32_t (*data)[4], int num_sensors) {
    cmd_t command = {.flag = 0, .count = 4, .address = 4}; 
    
    for (int i = 0; i < num_sensors; i++) {           
        sensor_send_cmd(&sensors[i], &command);         
    }

    for (uint32_t i = 0; i < 11000; i++) {
        asm("nop");
    }

    for (int i = 0; i < num_sensors; i++) {
        LL_GPIO_ResetOutputPin(sensors[i].cs_port, sensors[i].cs_pin);
        
    
        spi_receive(sensors[i].SPIx, (uint16_t*)data[i], 8);
        
        LL_GPIO_SetOutputPin(sensors[i].cs_port, sensors[i].cs_pin);
    }
}

main.c \переделал функцию

void updateTimer3() {
    static uint32_t code[256][4];
    static uint32_t cnt = 0;
    uint32_t data[4]; 
    Sensor_ReadAll(sensors, code, MAX_SENSORS);

    
    for (int i = 0; i < 4; i++) {
        code[cnt][i] = data[i]; 
    }

    if (++cnt == 256) {
        cnt = 0;
    }
}

