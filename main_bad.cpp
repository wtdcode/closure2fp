#include <functional>
#include <memory>
#include <cstdio>
#include "lib.h"
#include "closure.h"

typedef std::function<void()> callback_fn;

class CallbackManager {
public:
    static CallbackManager* New(callback_fn fn, Closure* closure) {
        return new CallbackManager(fn, closure);
    }

    void operator()() {
        return this->_fn();
    }

    ~CallbackManager(){
        closure_dealloc(this->_closure);
        delete this;
    }
private:
    callback_fn _fn;
    Closure* _closure;
    CallbackManager(callback_fn fn, Closure* closure) : _fn(fn), _closure(closure) {}
};

void register_callback_wrapper(callback_fn callback) {
    Closure* closure = closure_alloc();
    CallbackManager* mgr = CallbackManager::New(callback, closure);

    closure_prepare(closure, [](void* data){ (*(CallbackManager*)data)();}, mgr);
    // NOTE: We are passing a closure to a raw function pointer.
    register_callback_bad(closure_to_pointer(closure));
}

typedef struct Context {
    int id;
} Context;

int main(){
    std::shared_ptr<Context> ctx = std::make_shared<Context>();
    ctx->id = 114514;

    // Initialize the trampoline table.
    tramp_table_init();

    register_callback_wrapper([ctx](){
        // play with Context without any concern.
        printf("Context id=%d\n", ctx->id);
    });

    // no need to free context.
}
