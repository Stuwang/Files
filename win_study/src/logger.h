#pragma once

#ifndef _LOGGER_H__
#define _LOGGER_H__

#include <string>

class ILogger {
public:

	static const int LOG_FATAL = 5;
	static const int LOG_ERROR = 4;
	static const int LOG_WARN = 3;
	static const int LOG_INFO = 2;
	static const int LOG_DEBUG = 1;

	virtual ~ILogger() {};
	virtual void log(int leval, const char* str) = 0;
};

template<class T>
inline std::string Fmt(const char* f, const T data){
  char buf[256] = { 0 };
  _snprintf(buf, sizeof(buf), f, data);
  return buf;
}

namespace internal{

class StrStream{
public:

  StrStream(){};
  explicit StrStream(size_t size);

  friend StrStream& operator << (StrStream& log, char value);
  friend StrStream& operator << (StrStream& log, int value);
  friend StrStream& operator << (StrStream& log, unsigned int value);
  friend StrStream& operator << (StrStream& log, long value);
  friend StrStream& operator << (StrStream& log, unsigned long value);
  friend StrStream& operator << (StrStream& log, long long value);
  friend StrStream& operator << (StrStream& log, unsigned long long value);
  friend StrStream& operator << (StrStream& log, float value);
  friend StrStream& operator << (StrStream& log, double value);

  friend StrStream& operator << (StrStream& log, const char* value);
  friend StrStream& operator << (StrStream& log, const std::string& value);

  const std::string& GetString() const {
    return data_;
  };

  const char* c_str() const {
    return data_.c_str();
  };

private:
  std::string data_;
};

}; // internal

class Logger
{
public:
  Logger(ILogger * logger,int LogLevel);
  ~Logger();
  internal::StrStream& GetStream(){
    return str;
  }
private:
  internal::StrStream str;
  int loglevel_;
	ILogger *log_;
};

ILogger* GetStdLogger();

#define _UTIL_LOGGER(log,level)\
  Logger(log, level).GetStream() << __FILE__ << ':' << __LINE__ << ' '

#define LOG_FATAL(logger) _UTIL_LOGGER(logger,ILogger::LOG_FATAL)
#define LOG_ERROR(logger) _UTIL_LOGGER(logger,ILogger::LOG_ERROR)
#define LOG_WARN(logger) _UTIL_LOGGER(logger,ILogger::LOG_WARN)
#define LOG_INFO(logger) _UTIL_LOGGER(logger,ILogger::LOG_INFO)
#define LOG_DEBUG(logger) _UTIL_LOGGER(logger,ILogger::LOG_DEBUG)


#endif