/* Tivaware Library */
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/qei.h" // QEI module

#include "enc.h"

void encInit(void)
{
    /* pin config */
    //
    // Enable Peripheral Clocks
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    //
    // Configure the GPIO Pin Mux for PD6
    // for PHA0
    //
    MAP_GPIOPinConfigure(GPIO_PD6_PHA0);
    MAP_GPIOPinTypeQEI(GPIO_PORTD_BASE, GPIO_PIN_6);

    //
    // Unlock the Port Pin and Set the Commit Bit
    //
    HWREG(GPIO_PORTD_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTD_BASE+GPIO_O_CR) |= GPIO_PIN_7;
    HWREG(GPIO_PORTD_BASE+GPIO_O_LOCK) = 0x0;

    //
    // Configure the GPIO Pin Mux for PD7
    // for PHB0
    //
    MAP_GPIOPinConfigure(GPIO_PD7_PHB0);
    MAP_GPIOPinTypeQEI(GPIO_PORTD_BASE, GPIO_PIN_7);

    //
    // Configure the GPIO Pin Mux for PC5
    // for PHA1
    //
    MAP_GPIOPinConfigure(GPIO_PC5_PHA1);
    MAP_GPIOPinTypeQEI(GPIO_PORTC_BASE, GPIO_PIN_5);

    //
    // Configure the GPIO Pin Mux for PC6
    // for PHB1
    //
    MAP_GPIOPinConfigure(GPIO_PC6_PHB1);
    MAP_GPIOPinTypeQEI(GPIO_PORTC_BASE, GPIO_PIN_6);

    /* qei config */

    //
    // Enable the QEI0 peripheral
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI0);
    //
    // Wait for the QEI0 module to be ready.
    //
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_QEI0))
    {
    }
    //
    // Configure the quadrature encoder to capture edges on both signals and
    // maintain an absolute position by resetting on index pulses. Using a
    // 60 line encoder at four edges per line, there are 240 pulses per
    // revolution; therefore set the maximum position to 239 as the count
    // is zero based.
    //
    QEIConfigure(QEI0_BASE, (QEI_CONFIG_CAPTURE_A_B |
    QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP),
                 (ENC_PPR * 4) - 1);

    //
    // Enable the quadrature encoder.
    //
    QEIEnable(QEI0_BASE);

    QEIVelocityConfigure(QEI0_BASE, QEI_VELDIV_1, SPEED_COUNT_WINDOW);

    QEIVelocityEnable(QEI0_BASE);

    /* qei config */

    //
    // Enable the QEI0 peripheral
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI1);
    //
    // Wait for the QEI0 module to be ready.
    //
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_QEI1))
    {
    }
    //
    // Configure the quadrature encoder to capture edges on both signals and
    // maintain an absolute position by resetting on index pulses. Using a
    // 60 line encoder at four edges per line, there are 240 pulses per
    // revolution; therefore set the maximum position to 239 as the count
    // is zero based.
    //
    QEIConfigure(QEI1_BASE, (QEI_CONFIG_CAPTURE_A_B |
    QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP),
                 (ENC_PPR * 4) - 1);

    //
    // Enable the quadrature encoder.
    //
    QEIEnable(QEI1_BASE);

    QEIVelocityConfigure(QEI1_BASE, QEI_VELDIV_1, SPEED_COUNT_WINDOW);

    QEIVelocityEnable(QEI1_BASE);
}

float encGetVelocity(uint32_t encChannel)
{
    return QEIVelocityGet(encChannel)*K_RPM;
}

uint32_t encGetPosition(uint32_t encChannel)
{
    return QEIPositionGet(encChannel);
}
