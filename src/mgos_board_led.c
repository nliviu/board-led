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

#include "mgos_board_led.h"

bool mgos_board_led_init(void) {
  return true;
}

struct mgos_board_led *mgos_board_led_create(void *user_data) {
  struct mgos_board_led *led =
      (struct mgos_board_led *) calloc(1, sizeof(*led));
  led->user_data = user_data;

  led->led1 = mgos_sys_config_get_board_led1_pin();
  if (led->led1 > 0) {
    led->led1_active_high = mgos_sys_config_get_board_led1_active_high();
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