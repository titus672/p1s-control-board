#include <stdbool.h>
#include <stdint.h>

typedef struct SwitchPanel {
  bool switch_1;
  bool switch_2;
  bool switch_3;
  bool switch_4;
  bool switch_5;
  bool switch_6;
  bool switch_7;
  bool switch_8;
  bool switch_9;
  bool switch_10;
  bool switch_11;
  bool switch_12;
} switch_panel_t;

switch_panel_t *new_switch_panel(void);
uint32_t get_switch_bits(switch_panel_t *panel);
void reset_switch_panel(switch_panel_t *panel);
