#ifndef LIB_H
#define LIB_H

typedef void (*callback_t)(void* data);

typedef void (*callback_t2)();

#ifdef __cplusplus
extern "C" {
#endif

void register_callback(callback_t callback, void* data);

void register_callback2(callback_t2 callback);

#ifdef __cplusplus
}
#endif

#endif