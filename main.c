#include <stdlib.h>
#include <stdio.h>
#include "lib.h"


typedef struct Context {
    int id;
} Context;

void callback(void* data) {
    Context* ctx = (Context*)data;

    printf("Context id=%d\n", ctx->id);
}

int main(){
    Context* ctx = malloc(sizeof(Context)); 
    ctx->id = 114514;

    // some operation

    register_callback(callback, ctx);

    // other operation

    free(ctx);
}