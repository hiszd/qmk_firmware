#include "raw_hid.h"
#include "hiszd.h"

void raw_hid_receive(uint8_t *data, uint8_t length) {
    uint8_t *command_id = &(data[0]);
    switch (*command_id) {
        case 0:
          layer_off(_RSTLNE);
          break;
        case 1:
          layer_on(_RSTLNE);
          break;
    }
}
