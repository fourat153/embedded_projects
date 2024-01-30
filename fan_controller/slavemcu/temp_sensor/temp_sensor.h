/* 
 * File:   temp_sensor.h
 * Author: ahmed
 *
 * Created on January 28, 2024, 12:33 PM
 */

#ifndef TEMP_SENSOR_H
#define	TEMP_SENSOR_H
#include "../../mini_project smart home .X/mcc_generated_files/mcc.h"
#include "../../mini_project smart home .X/mcc_generated_files/examples/i2c_master_example.h"


uint8_t Sensor_ReadTemp(i2c_address_t address_sensors ) ; 

#endif	/* TEMP_SENSOR_H */

