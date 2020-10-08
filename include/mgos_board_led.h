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

#pragma once
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct mgos_board_led {
  int led1;
  bool led1_active_high;

  void *user_data;
};

struct mgos_board_led *mgos_board_led_create(void *user_data);
struct mgos_board_led *mgos_board_led_create_full(int pin, bool active_high,
                                                  void *user_data);

void mgos_board_led_free(struct mgos_board_led **led);

void mgos_board_led_set(const struct mgos_board_led *led, const bool on);

void mgos_board_led_toggle(const struct mgos_board_led *led);

#ifdef __cplusplus
}
#endif
