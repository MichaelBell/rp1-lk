#include <platform/time.h>
#include <stdbool.h>
#include <lk/reg.h>
#include <arch/arm/cm.h>

int platform_dgetc(char *c, bool wait) {
  return -1;
}

void platform_dputc(char c) {
  while (*REG32(0x40034000 + 0x18) & (1<<5));
  *REG32(0x40034000) = c; // uart1
}
void platform_early_init(void) {
    // start the systick timer
    arm_cm_systick_init(200 * 1000 * 1000);

    // Setup UART1, 115200, 8 bits, 1 stop, no parity
    *REG32(0x40034024) = 0x1b;
    *REG32(0x40034028) = 0x8;
    *REG32(0x4003402c) = 0x70;

    // Enable UART1
    *REG32(0x40034030) = 0x301;

    // Select the UART on GPIO 0 and 1 and enable them
    *REG32(0x400d0004) = 0x82;  // Function 2 = UART1
    *REG32(0x400d000c) = 0x82;
    *REG32(0x400f0004) = 0x10;  // Output enable, 4mA, no pull
    *REG32(0x400f0008) = 0xca;  // Input enable, pull up, schmitt
}
