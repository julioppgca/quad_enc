/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/System.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>

/* TI-RTOS Header files */
#include <ti/drivers/GPIO.h>
// #include <ti/drivers/I2C.h>
// #include <ti/drivers/SDSPI.h>
// #include <ti/drivers/SPI.h>
// #include <ti/drivers/UART.h>
// #include <ti/drivers/Watchdog.h>
// #include <ti/drivers/WiFi.h>

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

/* Board Header file */
#include "project_includes/Board.h"

uint32_t pos;

void heartBeat_TASK(void)
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
    // 1000 line encoder at four edges per line, there are 4000 pulses per
    // revolution; therefore set the maximum position to 3999 as the count
    // is zero based.
    //
    QEIConfigure(QEI0_BASE, (QEI_CONFIG_CAPTURE_A_B |
    QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP),
                 129);

    //
    // Enable the quadrature encoder.
    //
    QEIEnable(QEI0_BASE);

    QEIVelocityConfigure(QEI0_BASE, QEI_VELDIV_1, 1000);

    QEIVelocityEnable(QEI0_BASE);

    while (1)
    {
        Task_sleep(100);
        GPIO_toggle(Board_LED0);
        //
        // Read the encoder position.
        //
        pos = QEIPositionGet(QEI0_BASE);
    }
}

/*
 *  ======== main ========
 */
int main(void)
{

    /* Call board init functions */
    Board_initGeneral();
    Board_initGPIO();
    // Board_initI2C();
    // Board_initSDSPI();
    // Board_initSPI();
    // Board_initUART();
    // Board_initUSB(Board_USBDEVICE);
    // Board_initWatchdog();
    // Board_initWiFi();

    /* Turn on user LED */
    GPIO_write(Board_LED0, Board_LED_ON);

    System_printf("Starting the example\nSystem provider is set to SysMin. "
                  "Halt the target to view any SysMin contents in ROV.\n");
    /* SysMin will only print to the console when you call flush or exit */
    System_flush();

    /* Start BIOS */
    BIOS_start();

    return (0);
}
