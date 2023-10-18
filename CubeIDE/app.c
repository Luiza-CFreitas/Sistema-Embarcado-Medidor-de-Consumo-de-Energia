/*
 * app.c
 *
 *
 *      Authors: Leonardo Vecchi Meirelles, Luiza Custódio Freitas
 */

#include <stdint.h>
#include <stdio.h>
#include "app.h"
#include "hw.h"

// Define the register, according to the datasheet.
#define Voltage_RMS_Register 0x00D9
#define Current_RMS_Register 0x00DD
#define Active_Power_Register 0x00D0
#define Phase_Angle_Register 0x00F9
#define SwitchDisplayedInfoDelay_ms 10000

void app_init(void)
{

}

void app_loop(void)
{
	// Keeps displaying the information with a 10s interval between them. (using pooling)
	displayRMSVoltage();
	hw_delay_ms(SwitchDisplayedInfoDelay_ms);

	displayRMSCurrent();
	hw_delay_ms(SwitchDisplayedInfoDelay_ms);

	displayActivePower();
	hw_delay_ms(SwitchDisplayedInfoDelay_ms);

	displayPhaseAngle();
	hw_delay_ms(SwitchDisplayedInfoDelay_ms);
}

void displayRMSVoltage()
	{
	  // Read the RMS Voltage register value
	  uint16_t rawValue = hw_spi_read_register(Voltage_RMS_Register);

	  // Convert the raw value to voltage (multiply with LSB factor)
	  // Assuming 0.01 V per LSB, as datasheet indicates.
	  float voltage = rawValue * 0.01f;

	  // Format the voltage value into a string
	  char voltageString[21];
	  snprintf(voltageString, sizeof(voltageString), "RMS Voltage = %.2f V", voltage);

	  // Display the voltage string on the OLED display
	  hw_OLED_WriteString(voltageString);
	}

void displayRMSCurrent()
	{
	  // Read the RMS Current register value
	  uint16_t rawValue = hw_spi_read_register(Current_RMS_Register);

	  // Convert the raw value to current (multiply with LSB factor)
	  // Assuming 0.001 A per LSB, as datasheet indicates.
	  float current = rawValue * 0.001f;

	  // Format the current value into a string
	  char currentString[22];
	  snprintf(currentString, sizeof(currentString), "RMS Current = %.3f V", current);

	  // Display the current string on the OLED display
	  hw_OLED_WriteString(currentString);
	}

void displayActivePower()
{
  // Read the total active fundamental power register value
  uint16_t rawValue = hw_spi_read_register(Active_Power_Register);

  // Convert the raw value to power (multiply with LSB factor)
  // Assuming 4 Watts per LSB, as indicated in the datasheet.
  int16_t power = (int16_t)rawValue * 4;

  // Format the power value into a string
  char powerString[22];
  snprintf(powerString, sizeof(powerString), "Active Power = %d W", power);

  // Display the power string on the OLED display
  hw_OLED_WriteString(powerString);
}

void displayPhaseAngle()
{
  // Read the phase angle register value
  uint16_t rawValue = hw_spi_read_register(Phase_Angle_Register);

  // Convert the raw value to phase angle (multiply with LSB factor)
  // Assuming 0.1 degree per LSB, as indicated in the datasheet.
  int16_t angle = (int16_t)rawValue * 0.1;

  // Format the angle value into a string
  char angleString[22];
  snprintf(angleString, sizeof(angleString), "Phase Angle = %d.%01d°", angle / 10, angle % 10);

  // Display the angle string on the OLED display
  hw_OLED_WriteString(angleString);
}



