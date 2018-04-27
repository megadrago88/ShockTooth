#include <stdint.h>
#include <malloc.h>

static const struct {
    const char *name;
    uint16_t source;
    uint16_t vid;
    uint16_t pid;
    uint16_t version;
    uint16_t bt_pid;
} device = {

    "PLAYSTATION(R)3 Controller", //name
    0x0002, //source
    0x054c, //vid
    0x0268, //pid
    0x0000 //version
};

struct leds_data {
    char *syspath_prefix;
    uint8_t bitmap;
};

static void leds_data_destroy(struct leds_data *data) {
    free(data->syspath_prefix);
    free(data);
}
