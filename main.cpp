#include <functional>
#include <memory>
#include <cstdio>
#include "lib.h"

typedef std::function<void()> callback_fn;

class CallbackManager {
public:
    static CallbackManager* New(callback_fn fn) {
        return new CallbackManager(fn);
    }

    void operator()() {
        return this->_fn();
    }

    ~CallbackManager(){
        delete this;
    }
private:
    callback_fn _fn;
    CallbackManager(callback_fn fn) : _fn(fn) {}
};

void register_callback_wrapper(callback_fn callback) {
    CallbackManager* mgr = CallbackManager::New(callback);
    register_callback([](void* data){ (*(CallbackManager*)data)(); }, mgr);
}

typedef struct Context {
    int id;
} Context;

int main(){
    std::shared_ptr<Context> ctx = std::make_shared<Context>();
    ctx->id = 114514;

    register_callback_wrapper([ctx](){
        // play with Context without any concern.
        printf("Context id=%d\n", ctx->id);
    });

    // no need to free context.
}
