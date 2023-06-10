#include "Logger.hpp"

int main() {
    my::Logger logger("logger.txt");
    logger.setLogLevel(my::LogLevel::Error);

    logger.logInfo("INFO!!!");
    logger.logDebug("DEBUG!!!");
    logger.logError("ERROR!!!");

    return 0;
}