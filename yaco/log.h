#ifndef __YACO_LOG_H__
#define __YACO_LOG_H__

#include <string>
#include <stdint.h>
#include <memory>
#include <stringstream>
#include <fstream>

namespace yaco
{

class LogLevel;
class Logger;
class LogEvent;
class LogAppender;
class LogFormatter;

// 日志等级
class LogLevel
{
public:
    enum Level
    {
        DEBUG = 1,
        INFO ,
        WARN ,
        ERROR ,
        FATAL
    }
}


// 日志器
class Logger
{
public:
    using ptr = std::shared_ptr<Logger>;
   
    Logger(const std::string& name = "root");
    void log(LogLevel::Level level,LogEvent::ptr event);

    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addAppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);


    LogEvent::level getLevel() const { return m_level };
    void setLevel(LogLevel::Level level) { m_level = level };
private:
    // 日志器名称
    std::string m_name;
    // Appender集合   
    std::list<LogAppender::ptr> m_appenders;
    // 日志级别
    LogLevel::Level m_level;
}


// 日志事件
class LogEvent
{
public:
    using ptr = std::shared_ptr<LogEvent>;
    LogEvent();
private:
    // 文件名
    const char* m_file = nullptr;
    // 行号
    int32_t m_line = 0;
    // 线程Id
    uint32_t m_threadId = 0;
    // 协程Id
    uint32_t m_fiberId = 0;
    // 程序启动到现在的毫秒数
    uint32_t m_elapse = 0;
    // 时间戳
    uint64_t m_time;
    // 消息
    std::string m_connect;
}



// 日志输出地
class LogAppender
{
public:
    using ptr =  std::shared_ptr<LogAppender>;

    virtual ~LogAppender();
    virtual void log(LogLevel::Level level,LogEvent::ptr event) = 0;

    

    void setFormatter(LogFormatter::ptr formatter){ m_formatter = formatter; }
    LogFormatter::ptr getFormatter(){return m_formatter;}
protected:
    LogLevel::Level level;
    LogFormatter::ptr m_formatter;
}


// 日志格式化
class LogFormatter
{
public:
    using ptr = std::shared_ptr<LogFormatter>;
    std::string format(LogEvent::ptr event);
private:
}

// 输出到控制台的 Appender
class StdoutLogAppender : public LogAppender
{
public:
    using ptr = std::shared_ptr<StdoutLogAppender>;
    void log(LogLevel::Level level,LogEvent::ptr event) override;
}
// 输出到文件的 Appender
class FileLogAppender : public LogAppender
{
public:
    using ptr = std::shared_ptr<StdoutLogAppender>;
    FileLogAppender(const std::string& fileName)
    bool log(LogLevel::Level level,LogEvent::ptr event) override;

    // 重新打开文件
    void reopen();
private:
    std::string m_fileName;
    std::ofstream m_filestream;
}

}



#endif // !__YACO_LOG_H__