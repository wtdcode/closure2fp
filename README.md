# closure2fp

An example to illustrate how libffi cast a closure to a pointer to function.

Blog post link:

- [Pass a Closure to a Function Pointer -- How libffi closure works](https://blog.lazym.io/2021/07/29/Pass-a-Closure-to-a-Function-Pointer-How-libffi-closure-works/)
- [把闭包变成函数指针 ——libffi 闭包原理解析](https://blog.ihomura.cn/2021/07/30/%E6%8A%8A%E9%97%AD%E5%8C%85%E5%8F%98%E6%88%90%E5%87%BD%E6%95%B0%E6%8C%87%E9%92%88%E2%80%94%E2%80%94libffi-%E9%97%AD%E5%8C%85%E5%8E%9F%E7%90%86%E8%A7%A3%E6%9E%90/)

# Sources

- closure.c closure.h: The closure lib to cast a closure to a raw function pointer.
- lib.c lib.h: The lib that provides API to register callback.
- main.c: The example that uses lib.h well-designed callback API.
- main.cpp: The example that uses lib.c well-designed callback API with a cpp wrapper.
- main_bad.c: The example that uses lib.h bad-designed callback API.
- main_bad.cpp: The example that uses lib.c bad-designed callback API with a cpp wrapper.