#include "Logger.hpp"

namespace my {

    Logger::Logger(const std::string& logFilePath) {
        m_logFile.open(logFilePath);
        m_logLevel = LogLevel::Info;    // default log level 
    }

    Logger::~Logger() {
        if (m_logFile.is_open()) {
            m_logFile.close();
        }
    }

    void Logger::setLogLevel(LogLevel level) {
        m_logLevel = level;
    }

    std::string Logger::getCurrentDateAndTime() const {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);

        char buffer[20];    // 19 + '/0'
        std::strftime(buffer, sizeof(buffer), "%d-%m-%Y %X", std::localtime(&time));        //%d-%m-%Y %X  -  day month year
        return buffer;
    }

    // time + log level
    std::string Logger::formatLogMessage(const std::string& message, LogLevel level) const {
        std::string formattedMessage = getCurrentDateAndTime() + " ";

        switch (level) {
        case LogLevel::Info:
            formattedMessage += "[INFO] ";
            break;
        case LogLevel::Debug:
            formattedMessage += "[DEBUG] ";
            break;
        case LogLevel::Error:
            formattedMessage += "[ERROR] ";
            break;
        default:
            break;
        }

        formattedMessage += message;
        return formattedMessage;
    }

    void Logger::logInfo(const std::string& message) {
        if (m_logLevel >= LogLevel::Info) {
            std::string formattedMessage = formatLogMessage(message, LogLevel::Info);
            std::cout << formattedMessage << "\n";
            if (m_logFile.is_open()) {
                m_logFile << formattedMessage << "\n";
            }
        }
    }

    void Logger::logDebug(const std::string& message) {
        if (m_logLevel >= LogLevel::Debug) {
            std::string formattedMessage = formatLogMessage(message, LogLevel::Debug);
            std::cout << formattedMessage << "\n";
            if (m_logFile.is_open()) {
                m_logFile << formattedMessage << "\n";
            }
        }
    }

    void Logger::logError(const std::string& message) {
        if (m_logLevel >= LogLevel::Error) {
            std::string formattedMessage = formatLogMessage(message, LogLevel::Error);
            std::cerr << formattedMessage << "\n";
            if (m_logFile.is_open()) {
                m_logFile << formattedMessage << "\n";
            }
        }
    }

}