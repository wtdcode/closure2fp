#include "lib.h"

void register_callback(callback_t callback, void* data) {
    callback(data);
}

void register_callback2(callback_t2 callback) {
    callback();
}