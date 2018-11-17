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

/* project includes */
#include "project_includes/enc.h"

void heartBeat_TASK(void)
{

    while (1)
    {
        Task_sleep(100);
        GPIO_toggle(Board_LED0);
    }
}

uint32_t enc0_pos, enc1_pos;
float enc0_vel, enc1_vel;
void speedLoop_TASK(void)
{

    // initialize encoder modules
    encInit();
    while(1)
    {
        // encoder 0 data
        enc0_pos = encGetPosition(ENC_CHANNEL_0);
        enc0_vel = encGetVelocity(ENC_CHANNEL_0);

        //encoder 1 data
        enc1_pos = encGetPosition(ENC_CHANNEL_1);
        enc1_vel = encGetVelocity(ENC_CHANNEL_1);

        // sleep for some time
        Task_sleep(100);
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
