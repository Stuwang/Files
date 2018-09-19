#include <cstdio>
#include <string>
#include <iostream>

class Logger{
public:
    Logger(const char* file,int line);
    ~Logger();

#define DEFINE_TYPE(type) \
    friend Logger& operator<<(Logger & out,type value)

    DEFINE_TYPE(int);
    DEFINE_TYPE(long);
    DEFINE_TYPE(char);
    DEFINE_TYPE(const char*);
    DEFINE_TYPE(const std::string&);

#undef DEFINE_TYPE
private:
    const char* file_;
    int line_;
    std::string data_;
};

struct helper{
    helper(const char* file,int line)
        :log_(file,line){}

    Logger& Log(){
        return log_;
    }
// private:
    Logger log_;
};

inline helper CreateLogger(const char* file,int line){
    helper h{file,line};
    return h;
}

#define LOG() CreateLogger(__FILE__,__LINE__).Log()
