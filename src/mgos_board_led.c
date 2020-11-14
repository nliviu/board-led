/*
 * Copyright 2019 Liviu Nicolescu <nliviu@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mgos_gpio.h"
#include "mgos_sys_config.h"
#include "mgos_timers.h"

#include "mgos_board_led.h"

bool mgos_board_led_init(void) {
  return true;
}

struct mgos_board_led *mgos_board_led_create(void *user_data) {
  return mgos_board_led_create_full(
      mgos_sys_config_get_board_led1_pin(),
      mgos_sys_config_get_board_led1_active_high(), user_data);
}

struct mgos_board_led *mgos_board_led_create_full(int pin, bool active_high,
                                                  void *user_data) {
  struct mgos_board_led *led =
      (struct mgos_board_led *) calloc(1, sizeof(*led));
  led->user_data = user_data;

  led->led1 = pin;
  if (led->led1 > 0) {
    led->led1_active_high = active_high;
    mgos_gpio_setup_output(led->led1, !led->led1_active_high);
  }

  return led;
}

void mgos_board_led_free(struct mgos_board_led **led) {
  if ((led == NULL) || (*led == NULL)) {
    return;
  }
  free(*led);
  *led = NULL;
}

void mgos_board_led_set(const struct mgos_board_led *led, const bool on) {
  if (led != NULL) {
    mgos_gpio_write(led->led1, led->led1_active_high ? on : !on);
  }
}

void mgos_board_led_toggle(const struct mgos_board_led *led) {
  if (led != NULL) {
    mgos_gpio_toggle(led->led1);
  }
}

static void blink_timer_cb(void *arg) {
  const struct mgos_board_led *led = (const struct mgos_board_led *) arg;
  mgos_gpio_blink(led->led1, 0, 0);
}

void mgos_board_led_blink(const struct mgos_board_led *led, int on_ms,
                          int off_ms, int timer_ms) {
  if (led != NULL) {
    mgos_gpio_blink(led->led1, on_ms, off_ms);
    if (timer_ms > 0) {
      mgos_set_timer(timer_ms, 0, blink_timer_cb, (void *) led);
    }
  }
}
