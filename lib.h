#ifndef LIB_H
#define LIB_H

typedef void (*callback_t)(void* data);

typedef void (*callback_bad_t)();

#ifdef __cplusplus
extern "C" {
#endif

/*
    Well-designed callback API.
*/
void register_callback(callback_t callback, void* data);

/*
    Bad-designed callback API.
*/
void register_callback_bad(callback_bad_t callback);

#ifdef __cplusplus
}
#endif

#endif