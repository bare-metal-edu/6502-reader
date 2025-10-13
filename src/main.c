#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"

#define CLOCK_PIN 28
#define RW_PIN 27

int ADDR_PINS[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
int DATA_PINS[] = {16, 17, 18, 19, 20, 21, 22, 26};

void gpio_callback(uint gpio, uint32_t events) {
    int address = 0;
    for(int n = 0; n < sizeof(ADDR_PINS) / 4; n++) {
        int bit = gpio_get(ADDR_PINS[n]);
        printf("%d", bit);
        address = (address << 1) + bit;
    }
    printf("    ");
    int data = 0;
    for(int n = 0; n < sizeof(DATA_PINS) / 4; n++) {
        int bit = gpio_get(DATA_PINS[n]);
        printf("%d", bit);
        data = (data << 1) + bit;
    }
    printf("    ");
    printf("%04x    %02x    %c", address, data, gpio_get(RW_PIN) ? 'r' : 'W');
    printf("\n");
}

int main(void) {
    // Open serial port
    stdio_init_all();
    // Set pins for input
    for (int n = 0; n < sizeof(ADDR_PINS)/4; n++) {
        gpio_init(ADDR_PINS[n]);
        gpio_set_dir(ADDR_PINS[n], GPIO_IN);
    }
    for (int n = 0; n < sizeof(DATA_PINS)/4; n++) {
        gpio_init(DATA_PINS[n]);
        gpio_set_dir(DATA_PINS[n], GPIO_IN);
    }
    // Set RW pin as reat
    gpio_init(RW_PIN);
    gpio_set_dir(RW_PIN, GPIO_IN);
    // Set up clock pin as process interrupt
    gpio_init(CLOCK_PIN);
    gpio_set_dir(CLOCK_PIN, GPIO_IN);
    gpio_pull_up(CLOCK_PIN);
    gpio_set_irq_enabled_with_callback(
        CLOCK_PIN,
        GPIO_IRQ_EDGE_RISE,
        true,
        &gpio_callback
    );
    while (1) {
        tight_loop_contents();
    }
    return 0;
}
