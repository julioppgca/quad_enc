
#define MCU_CLOCK           80000000    // MCU main clock, 80MHz *change to match your MCU clock
#define ENC_PPR             60          // encoder pulses per revolution
#define SPEED_COUNT_WINDOW  8000000     // time window to count encoder velocity pulses 80MHz/8MHZ = 10Hz > T=100ms
#define ENC_CHANNEL_0       QEI0_BASE
#define ENC_CHANNEL_1       QEI1_BASE

// rmp constant definition
// datasheet: tm4c123gh6pm.pdf pg.1309
#define K_RPM   ((MCU_CLOCK * 1 * 60.0)/(SPEED_COUNT_WINDOW*ENC_PPR*4.0))  // rpm = (clock * (2 ^ VELDIV) * SPEED * 60) ÷ (LOAD * ppr * edges)

void encInit(void);
float encGetVelocity(uint32_t encChannel);
uint32_t encGetPosition(uint32_t encChannel);
