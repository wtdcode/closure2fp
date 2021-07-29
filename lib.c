#include "lib.h"

void register_callback(callback_t callback, void* data) {
    callback(data);
}

void register_callback_bad(callback_bad_t callback) {
    callback();
}