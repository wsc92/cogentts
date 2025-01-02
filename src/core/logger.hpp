#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <sstream>
#include <map>
#include <chrono>
#include <ctime>
#include <iomanip>

class Logger {
public:
    enum class LogLevel {
        DEBUG = 0,    // Lowest priority
        INFO = 1,
        WARNING = 2,
        ERROR = 3     // Highest priority
    };


    static Logger& getInstance();

    void setLogFile(const std::string& filename);
    void setLogLevel(LogLevel level);
    void log(LogLevel level, const std::string& message);

private:
    Logger();
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::ofstream logFile;
    std::mutex logMutex;
    LogLevel currentLogLevel;
    std::map<LogLevel, std::string> logLevelNames;
    std::map<LogLevel, std::string> logLevelColors;

    std::string getCurrentTime() const;
    bool shouldLog(LogLevel level) const;
    std::string colorize(LogLevel level, const std::string& message) const;
};

#endif // LOGGER_HPP

