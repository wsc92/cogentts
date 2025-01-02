#include "logger.hpp"

Logger::Logger() : currentLogLevel(LogLevel::INFO) {
    logLevelNames = {
        {LogLevel::INFO, "INFO"},
        {LogLevel::WARNING, "WARNING"},
        {LogLevel::ERROR, "ERROR"},
        {LogLevel::DEBUG, "DEBUG"}
    };

    logLevelColors = {
        {LogLevel::INFO, "\033[36m"},    // Cyan
        {LogLevel::WARNING, "\033[33m"}, // Yellow
        {LogLevel::ERROR, "\033[31m"},   // Red
        {LogLevel::DEBUG, "\033[32m"}    // Green 
    };
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::setLogFile(const std::string& filename) {
    std::lock_guard<std::mutex> lock(logMutex);
    if (logFile.is_open()) {
        logFile.close();
    }
    logFile.open(filename, std::ios::out | std::ios::app);
    if (!logFile) {
        throw std::runtime_error("Failed to open log file: " + filename);
    }
}

void Logger::setLogLevel(LogLevel level) {
    std::lock_guard<std::mutex> lock(logMutex);
    currentLogLevel = level;
}

void Logger::log(LogLevel level, const std::string& message) {
    if (!shouldLog(level)) {
        return;
    }

    std::lock_guard<std::mutex> lock(logMutex);

    std::ostringstream logMessage;
    logMessage << "[" << getCurrentTime() << "] "
               << "[" << logLevelNames[level] << "] "
               << message;

    // Log to console with color
    std::cout << colorize(level, logMessage.str()) << std::endl;

    // Log to file without color
    if (logFile.is_open()) {
        logFile << logMessage.str() << std::endl;
    }
}

std::string Logger::getCurrentTime() const {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::ostringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

bool Logger::shouldLog(LogLevel level) const {
    return static_cast<int>(level) >= static_cast<int>(currentLogLevel);
}


std::string Logger::colorize(LogLevel level, const std::string& message) const {
    auto it = logLevelColors.find(level);
    if (it != logLevelColors.end()) {
        return it->second + message + "\033[0m"; // Reset color after message
    }
    return message;
}

