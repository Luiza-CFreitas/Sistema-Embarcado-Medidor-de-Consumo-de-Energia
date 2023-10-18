/*
 * hw.h
 *
 *
 *      Authors: Leonardo Vecchi Meirelles, Luiza Custódio Freitas
 */

#ifndef HW_H_
#define HW_H_
#include "main.h"
extern I2C_HandleTypeDef hi2c1;
extern SPI_HandleTypeDef hspi3;

uint16_t hw_spi_read_register(uint16_t register_address);
void hw_spi_write_register(uint16_t register_address, uint16_t data);
void hw_spi_select_device(void);
void hw_spi_deselect_device(void);
void hw_OLED_WriteData(uint16_t data);
void hw_OLED_WriteString(const char* str);
void hw_delay_ms(uint32_t time_ms);

#endif /* HW_H_ */
