#include "retval.h"

template <typename Func>
RetVal timed(Func&& func) {
    auto start = std::chrono::high_resolution_clock::now();
    RetVal ret = func();
    auto end = std::chrono::high_resolution_clock::now();

    ret.timing = end - start;
    return ret;
}
