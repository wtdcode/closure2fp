#ifndef CLOSURE_H
#define CLOSURE_H

#include "lib.h"

struct Closure;
typedef struct Closure Closure;

#ifdef __cplusplus
extern "C" {
#endif
/*
    Initialize the trampoline table. Must be called before other APIs.
*/
void tramp_table_init();

/*
    Allocate a free closure.
*/
Closure* closure_alloc();

/*
    Prepare for the closure.
*/
void closure_prepare(Closure* closure, callback_t callback, void* data);

/*
    Deallocate a free closure.
*/
Closure* closure_dealloc(Closure*);

/*
    Cast a closure to a raw pointer to function.
*/
callback_t2 closure_to_pointer(Closure*);

#ifdef __cplusplus
}
#endif

#endif