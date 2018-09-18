#include <cstdio>

#include "rpc/base/log.h"

Logger::Logger(const char* file, int line)
 : file_(file)
 , line_(line) {
    data_.reserve(1024);
}

Logger::~Logger() { std::cout << data_ << std::endl; }

#define DEFINE_FMT(fmt, type)                     \
    Logger& operator<<(Logger& out, type value) { \
        char buf[64] = { 0 };                     \
        sprintf(buf, fmt, value);                 \
        out.data_.append(buf);                    \
        return out;                               \
    }

DEFINE_FMT("%d", int)
DEFINE_FMT("%l", long)
DEFINE_FMT("%c", char)

Logger& operator<<(Logger& out, const char* value) {
    out.data_.append(value);
    return out;
}

Logger& operator<<(Logger& out, const std::string& value) {
    out.data_.append(value);
    return out;
}
