#pragma once
#ifndef DEFINES_HPP
#define DEFINES_HPP

#include "core/logger.hpp"
#include "handlers/data_handler.hpp"

// Macros for logging with specific log levels
#define CINFO(message)    Logger::getInstance().log(Logger::LogLevel::INFO, message)
#define CDEBUG(message)   Logger::getInstance().log(Logger::LogLevel::DEBUG, message)
#define CWARN(message) Logger::getInstance().log(Logger::LogLevel::WARNING, message)
#define CERROR(message)   Logger::getInstance().log(Logger::LogLevel::ERROR, message)

#endif // DEFINES_HPP

