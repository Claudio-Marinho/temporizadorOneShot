#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "pico/bootrom.h"

#define LED_RED 13
#define LED_GREEN 11
#define LED_BLUE 12
#define BTN_A 5
#define DEBOUNCE_TIME 200000  // 200ms de debounce

volatile int led_atual = 1;
volatile uint32_t last_time = 0;
volatile bool alarme_ativado = false;

int64_t alarm_callback(alarm_id_t id, void *user_data) {
    if (led_atual == 1) {
        gpio_put(LED_RED, false);
        add_alarm_in_ms(3000, alarm_callback, NULL, false);
    } else if (led_atual == 2) {
        gpio_put(LED_BLUE, false);
        add_alarm_in_ms(3000, alarm_callback, NULL, false);
    } else if (led_atual == 3) {
        gpio_put(LED_GREEN, false);
        led_atual = 1;
        alarme_ativado = false;
        return 0;
    }
    led_atual++;
    return 0;
}

// Função de interrupção com debounce para o botão
void gpio_irq_handler(uint gpio, uint32_t events) {
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    if (current_time - last_time > DEBOUNCE_TIME) {
        if (gpio == BTN_A && !alarme_ativado) {
            gpio_put(LED_RED, true);
            gpio_put(LED_BLUE, true);
            gpio_put(LED_GREEN, true);
            alarme_ativado = true;
            add_alarm_in_ms(3000, alarm_callback, NULL, false);
        }
        last_time = current_time;
    }
}

int main() {
    stdio_init_all();

    // Inicializa LEDs
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);

    // Inicializa botão
    gpio_init(BTN_A);
    gpio_set_dir(BTN_A, GPIO_IN);
    gpio_pull_up(BTN_A);

    // Configuração da interrupção do botão
    gpio_set_irq_enabled_with_callback(BTN_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    while (true) {
        tight_loop_contents(); // Mantém o loop principal rodando
    }
}
