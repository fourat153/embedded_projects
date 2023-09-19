/* 
 * File:   temp.h
 * Author: mm77
 *
 * Created on September 5, 2023, 7:09 PM
 */

#ifndef TEMP_H
#define	TEMP_H

#include "../../mcc_generated_files/mcc.h"
#include "../../mcc_generated_files/examples/i2c_master_example.h"
uint8_t TempSensorRead(i2c_address_t TC_addr);
#endif	/* TEMP_H */

