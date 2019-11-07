#include "mgos_gpio.h"
#include "mgos_sys_config.h"

#include "mgos_board_led.h"

bool mgos_board_led_init(void) {
  return true;
}

struct mgos_board_led *mgos_board_led_create(void *user_data) {
  /*struct mgos_board_led *led =
      (struct mgos_board_led *) calloc(1, sizeof(*led));
  led->user_data = user_data;

  led->led1 = mgos_sys_config_get_board_led1_pin();
  if (led->led1 > 0) {
    led->led1_active_high = mgos_sys_config_get_board_led1_active_high();
    mgos_gpio_setup_output(led->led1, !led->led1_active_high);
  }*/

  return mgos_board_led_create_full(mgos_sys_config_get_board_led1_pin(),
                               mgos_sys_config_get_board_led1_active_high(),
                               user_data);
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
