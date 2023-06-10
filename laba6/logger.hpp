﻿#pragma once
#pragma warning(disable : 4996) //to allow use of the deprecated functions

#include <fstream>
#include <iostream>
#include <string>
#include <chrono>

namespace my {

    enum class LogLevel {
        None,
        Info,
        Debug,
        Error
    };

    class Logger {
    private:
        std::ofstream m_logFile;
        LogLevel m_logLevel;    // current log level

        std::string getCurrentDateAndTime() const;
        std::string formatLogMessage(const std::string& message, LogLevel level) const;

    public:
        Logger(const std::string& logFilePath);

        ~Logger();

        void setLogLevel(LogLevel level);
        void logInfo(const std::string& message);
        void logDebug(const std::string& message);
        void logError(const std::string& message);
    };

}