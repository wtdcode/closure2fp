#include <stdlib.h>
#include <stdio.h>
#include "lib.h"
#include "closure.h"

typedef struct Context {
    int id;
} Context;

void callback(void* data) {
    Context* ctx = (Context*)data;

    printf("Context id=%d\n", ctx->id);
}

int main(){
    Context* ctx = malloc(sizeof(Context));
    Closure* closure;
    ctx->id = 114514;

    // Generate a closure.
    tramp_table_init();
    closure = closure_alloc();
    closure_prepare(closure, callback, ctx);

    // some operation

    // NOTE: We are passing a closure to a raw function pointer.
    register_callback_bad(closure_to_pointer(closure));

    // other operation

    closure_dealloc(closure);
    free(ctx);
}