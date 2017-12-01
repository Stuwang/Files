#include <iostream>

#include "Logger.h"


Logger::Logger(ILogger * logger, int LogLevel)
  : log_(logger)
  , loglevel_(LogLevel)
{
}


Logger::~Logger()
{
  log_->log(loglevel_, str.GetString().c_str());
}

// std logger, in console

class StdLogger : public ILogger {
public:
	StdLogger() {};
	virtual ~StdLogger() {};
	virtual void log(int leval, const char* str) {
		if (leval >= ILogger::LOG_ERROR) {
			std::cerr << str << std::endl;
		} else {
			std::cout << str << std::endl;
		}
		if (leval == ILogger::LOG_FATAL) {
			exit(-1);
		}
	};
};

ILogger* GetStdLogger() {
	static StdLogger logger_;
	return &logger_;
};


#define DECLARE_OPERATOR(type,fmt)                        \
  StrStream& operator << (StrStream& self, type value){   \
  char buf[128];                                          \
  _snprintf_s(buf, sizeof(buf), fmt, value);              \
  self.data_ += buf;                                      \
  return self;                                            \
  };

namespace internal{

  DECLARE_OPERATOR(char, "%c")
  DECLARE_OPERATOR(int, "%d")
  DECLARE_OPERATOR(unsigned int, "%u")
  DECLARE_OPERATOR(long, "%ld")
  DECLARE_OPERATOR(unsigned long, "%lu")
  DECLARE_OPERATOR(long long, "%lld")
  DECLARE_OPERATOR(unsigned long long, "%llu")
  DECLARE_OPERATOR(float, "%f")
  DECLARE_OPERATOR(double, "%g")
#undef DECLARE_OPERATOR

  StrStream& operator << (StrStream& self, const char* value){
    self.data_ += value;
    return self;
  };
  StrStream& operator << (StrStream& self, const std::string& value){
    self.data_ += value;
    return self;
  };

  StrStream::StrStream(size_t size){
    data_.reserve(size);
  }
}