#include "switch_panel.h"
#include "hardware/pio.h"
#include "switch_panel.pio.h"
#include <hardware/gpio.h>
#include <pico/cyw43_arch.h>
#include <pico/time.h>
#include <pico/types.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define BIT(n) (1u << (n))

#define SWITCH_1 (BIT(0) | BIT(16))
#define SWITCH_2 (BIT(1) | BIT(17))
#define SWITCH_3 (BIT(2) | BIT(18))
#define SWITCH_4 (BIT(3) | BIT(19))
#define SWITCH_5 (BIT(4) | BIT(20))
#define SWITCH_6 (BIT(5) | BIT(21))
#define SWITCH_7 (BIT(6) | BIT(22))
#define SWITCH_8 (BIT(7) | BIT(23))
#define SWITCH_9 (BIT(8) | BIT(16))
#define SWITCH_10 (BIT(9) | BIT(17))
#define SWITCH_11 (BIT(10) | BIT(18))
#define SWITCH_12 (BIT(11) | BIT(19))

#define SWITCH_1_PIN 0
#define SWITCH_2_PIN 1
#define SWITCH_3_PIN 2
#define SWITCH_4_PIN 3
#define SWITCH_5_PIN 4
#define SWITCH_6_PIN 5
#define SWITCH_7_PIN 6
#define SWITCH_8_PIN 7
#define SWITCH_9_PIN 8
#define SWITCH_10_PIN 9
#define SWITCH_11_PIN 10
#define SWITCH_12_PIN 11

const int OUTPUT_PIN = 28;

static switch_panel_t panel_obj;
switch_panel_t *panel = &panel_obj;

int main() {
  PIO pio;
  uint sm;
  uint offset;

  cyw43_arch_init();

  gpio_init(SWITCH_1_PIN);
  gpio_init(SWITCH_2_PIN);
  gpio_init(SWITCH_3_PIN);
  gpio_init(SWITCH_4_PIN);
  gpio_init(SWITCH_5_PIN);
  gpio_init(SWITCH_6_PIN);
  gpio_init(SWITCH_7_PIN);
  gpio_init(SWITCH_8_PIN);
  gpio_init(SWITCH_9_PIN);
  gpio_init(SWITCH_10_PIN);
  gpio_init(SWITCH_11_PIN);
  gpio_init(SWITCH_12_PIN);

  gpio_set_dir(SWITCH_1_PIN, GPIO_IN);
  gpio_set_dir(SWITCH_2_PIN, GPIO_IN);
  gpio_set_dir(SWITCH_3_PIN, GPIO_IN);
  gpio_set_dir(SWITCH_4_PIN, GPIO_IN);
  gpio_set_dir(SWITCH_5_PIN, GPIO_IN);
  gpio_set_dir(SWITCH_6_PIN, GPIO_IN);
  gpio_set_dir(SWITCH_7_PIN, GPIO_IN);
  gpio_set_dir(SWITCH_8_PIN, GPIO_IN);
  gpio_set_dir(SWITCH_9_PIN, GPIO_IN);
  gpio_set_dir(SWITCH_10_PIN, GPIO_IN);
  gpio_set_dir(SWITCH_11_PIN, GPIO_IN);
  gpio_set_dir(SWITCH_12_PIN, GPIO_IN);

  gpio_pull_up(SWITCH_1_PIN);
  gpio_pull_up(SWITCH_2_PIN);
  gpio_pull_up(SWITCH_3_PIN);
  gpio_pull_up(SWITCH_4_PIN);
  gpio_pull_up(SWITCH_5_PIN);
  gpio_pull_up(SWITCH_6_PIN);
  gpio_pull_up(SWITCH_7_PIN);
  gpio_pull_up(SWITCH_8_PIN);
  gpio_pull_up(SWITCH_9_PIN);
  gpio_pull_up(SWITCH_10_PIN);
  gpio_pull_up(SWITCH_11_PIN);
  gpio_pull_up(SWITCH_12_PIN);

  bool success = pio_claim_free_sm_and_add_program_for_gpio_range(
      &switch_panel_program, &pio, &sm, &offset, OUTPUT_PIN, 1, true);

  switch_panel_program_init(pio, sm, offset, OUTPUT_PIN);

  while (true) {
    reset_switch_panel(panel);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, true);

    if (!gpio_get(SWITCH_1_PIN)) {
      panel->switch_1 = true;
    }
    if (!gpio_get(SWITCH_2_PIN)) {
      panel->switch_2 = true;
    }
    if (!gpio_get(SWITCH_3_PIN)) {
      panel->switch_3 = true;
    }
    if (!gpio_get(SWITCH_4_PIN)) {
      panel->switch_4 = true;
    }
    if (!gpio_get(SWITCH_5_PIN)) {
      panel->switch_5 = true;
    }
    if (!gpio_get(SWITCH_6_PIN)) {
      panel->switch_6 = true;
    }
    if (!gpio_get(SWITCH_7_PIN)) {
      panel->switch_7 = true;
    }
    if (!gpio_get(SWITCH_8_PIN)) {
      panel->switch_8 = true;
    }
    if (!gpio_get(SWITCH_9_PIN)) {
      panel->switch_9 = true;
    }
    if (!gpio_get(SWITCH_10_PIN)) {
      panel->switch_10 = true;
    }
    if (!gpio_get(SWITCH_11_PIN)) {
      panel->switch_11 = true;
    }
    if (!gpio_get(SWITCH_12_PIN)) {
      panel->switch_12 = true;
    }
    uint32_t compare = get_switch_bits(panel);
    pio_sm_put_blocking(pio, sm, compare << 8);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, false);
    sleep_ms(75);
  }

  pio_remove_program_and_unclaim_sm(&switch_panel_program, pio, sm, offset);
  return 0;
}

uint32_t get_switch_bits(switch_panel_t *panel) {
  uint32_t frame = 0;
  if (panel->switch_1)
    frame |= SWITCH_1;
  if (panel->switch_2)
    frame |= SWITCH_2;
  if (panel->switch_3)
    frame |= SWITCH_3;
  if (panel->switch_4)
    frame |= SWITCH_4;
  if (panel->switch_5)
    frame |= SWITCH_5;
  if (panel->switch_6)
    frame |= SWITCH_6;
  if (panel->switch_7)
    frame |= SWITCH_7;
  if (panel->switch_8)
    frame |= SWITCH_8;
  if (panel->switch_9)
    frame |= SWITCH_9;
  if (panel->switch_10)
    frame |= SWITCH_10;
  if (panel->switch_11)
    frame |= SWITCH_11;
  if (panel->switch_12)
    frame |= SWITCH_12;
  return frame & 0x00FFFFFF;
}
switch_panel_t *new_switch_panel() {
  switch_panel_t *panel = malloc(sizeof(switch_panel_t));
  if (panel == NULL) {
    return NULL;
  }

  panel->switch_1 = 0;
  panel->switch_2 = 0;
  panel->switch_3 = 0;
  panel->switch_4 = 0;
  panel->switch_5 = 0;
  panel->switch_6 = 0;
  panel->switch_7 = 0;
  panel->switch_8 = 0;
  panel->switch_9 = 0;
  panel->switch_10 = 0;
  panel->switch_11 = 0;
  panel->switch_12 = 0;
  return panel;
}

void reset_switch_panel(switch_panel_t *panel) {
  panel->switch_1 = 0;
  panel->switch_2 = 0;
  panel->switch_3 = 0;
  panel->switch_4 = 0;
  panel->switch_5 = 0;
  panel->switch_6 = 0;
  panel->switch_7 = 0;
  panel->switch_8 = 0;
  panel->switch_9 = 0;
  panel->switch_10 = 0;
  panel->switch_11 = 0;
  panel->switch_12 = 0;
}
