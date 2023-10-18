/*
 * hw.c
 *
 *      Authors: Leonardo Vecchi Meirelles, Luiza Custódio Freitas
 */

#include "main.h"
#include "hw.h"
#include "stm32f4xx_hal_spi.h"

// In the display datasheet, it says that to write something using the I2C, it first has to write the slave address with a '0' after.
// The datasheet that it is: '01111000', then 0x78 in hexa, so that is its address.
// It will always be a write operation, so this will be always its address.
#define OLED_I2C_ADDRESS 0x78

uint16_t hw_spi_read_register(uint16_t register_address)
{
	// Set the read instruction (1XXXXXAAAAAAAAAA), as the datasheet says.
	// The first bit on SDI defines the access type (1 = read; 0 = write).
	// The address is as follows:
	// Fixed 15-bit, following the access type bits. The lower 10-bit is decoded as address; the higher 5 bits are ‘Don't Care’
	uint16_t command_word = (1 << 15) | (register_address);
	uint16_t data_word;

	// CS = 0
	hw_spi_select_device();

	// The read operation first transmits the command with the address, and then receive the data from said address.
	HAL_SPI_Transmit(&hspi3, (uint8_t*)&command_word, sizeof(command_word), HAL_MAX_DELAY);
	HAL_SPI_Receive(&hspi3, (uint8_t*)&data_word, sizeof(data_word), HAL_MAX_DELAY);

	// CS = 1
	hw_spi_deselect_device();

	return data_word;

}

void hw_spi_write_register(uint16_t register_address, uint16_t data)
{
	// Set access type as write, address bits [14:0]
    uint16_t command_word = (register_address);

    // CS = 0
    hw_spi_select_device();

    // The write operation first transmits the command with the address, then the data to be written.
    HAL_SPI_Transmit(&hspi3, (uint8_t*)&command_word, sizeof(command_word), HAL_MAX_DELAY);
    HAL_SPI_Transmit(&hspi3, (uint8_t*)&data, sizeof(data), HAL_MAX_DELAY);

    // CS = 1
    hw_spi_deselect_device();
}

void hw_spi_select_device(void)
{
	// Set the CS pin low to select the ATM90E36A
    HAL_GPIO_WritePin(GPIO_Out_CS_GPIO_Port, GPIO_Out_CS_Pin, GPIO_PIN_RESET);
}

void hw_spi_deselect_device(void)
{
	// Set the CS pin high to deselect the ATM90E36A
    HAL_GPIO_WritePin(GPIO_Out_CS_GPIO_Port, GPIO_Out_CS_Pin, GPIO_PIN_SET);
}

void hw_OLED_WriteData(uint16_t data)
{
  // Generate Start condition and wait until I2C is ready for transmission
  // The following command already make the start and stop conditions, so it does not need to be implemented.
  HAL_I2C_Master_Transmit(&hi2c1, OLED_I2C_ADDRESS, (uint8_t*)&data, 1, HAL_MAX_DELAY);
  // The datasheet of the display says that "The Acknowledge bit will be generated after receiving each control byte or data byte".
}

// The function takes a pointer to a string str as an input parameter.
// The string is expected to be a null-terminated string, where the end of the string is marked by a null character ('\0').
void hw_OLED_WriteString(const char* str)
{
	// The function uses a while loop to iterate over each character in the string.
	// The loop continues until it reaches the null character, indicating the end of the string.
	while (*str)
	{
		// Inside the loop, the function calls hw_OLED_WriteData function with the current character pointed to by str. The *str++ syntax is a shorthand way to access the current character and then advance the pointer to the next character in the string.
		hw_OLED_WriteData(*str++);
	}
}

void hw_delay_ms(uint32_t time_ms)
{
	// Use the HAL_Delay function to delay the specified number of milliseconds
	HAL_Delay(time_ms);
}


