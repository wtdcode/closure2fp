#define _GNU_SOURCE 1
#include <stdint.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include "closure.h"

typedef struct Closure {
    unsigned index; // Fast to dealloc.
    int is_free; // Whether in use.
    callback_bad_t code; // Actual code entry point.
    callback_t callback; // User supplied callback.
    void* data; // User supplied data.
} Closure;

// ['mov rsi, qword ptr [rip + 0xff9] size=7', # 0xff9 + 7 = 0x1000 (tramp_len)
//  'mov r10, qword ptr [rip + 0xffa] size=7', # 0xffa + 7 + 7 = 0x1004 (tramp_len + 8)
//  'jmp r10 size=3']
#define TRAMP_CODE "\x48\x8b\x3d\xf9\x0f\x00\x00\x4c\x8b\x15\xfa\x0f\x00\x00\x41\xff\xe2"
#define TRAMP_CODE_ALIGNED_LEN ((sizeof(TRAMP_CODE) - 1 + 0x10 - 1) & ( ~(0x10 - 1) )) 
#define TRAMP_LEN (0x1000)
#define TRAMP_COUNT (TRAMP_LEN / TRAMP_CODE_ALIGNED_LEN)
static Closure closures[TRAMP_COUNT];

static void internal_closure_callback(Closure* closure) {
    closure->callback(closure->data);
}

void tramp_table_init() {
    void* addr;
    uint64_t tramp_addr;

    // No error handling for simplicity.

    // Map TRAMP_LEN * 2 memory, a half for code and the other half for data.
    addr = mmap(NULL, TRAMP_LEN * 2, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1 ,0);
    // Replace the half of the tramp memory with our code.
    addr = mmap(addr, TRAMP_LEN, PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0);

    tramp_addr = (uint64_t)addr;
    for (int i = 0;i < TRAMP_COUNT; i++) {
        // Initialize closures.
        closures[i].is_free = 1;
        closures[i].code = (void*)tramp_addr;
        closures[i].index = i;
        closures[i].callback = NULL;
        closures[i].data = NULL;

        // Setup tramp code.
        memcpy((void*)tramp_addr, TRAMP_CODE, sizeof(TRAMP_CODE) - 1);

        // The parameter of the internal_closure_callback.
        *(Closure**)(tramp_addr + TRAMP_LEN) = &closures[i];
        // The target of jmp r10.
        *(uint64_t*)(tramp_addr + TRAMP_LEN + 8) = (uint64_t)internal_closure_callback;

        // Next closure.
        tramp_addr = tramp_addr + TRAMP_CODE_ALIGNED_LEN;
    }

}

Closure* closure_alloc() {
    // Find the first free closure.
    for (int i = 0;i < TRAMP_COUNT; i++) {
        if (closures[i].is_free) {
            closures[i].is_free = 0;
            return &closures[i];
        }
    }

    return NULL;
}

void closure_prepare(Closure* closure, callback_t callback, void* data) {
    closure->callback = callback;
    closure->data = data;
}

Closure* closure_dealloc(Closure* closure) {
    closure->callback = NULL;
    closure->data = NULL;
    closures[closure->index].is_free = 1;
}

callback_bad_t closure_to_pointer(Closure* closure) {
    return closure->code;
}
