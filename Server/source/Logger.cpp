#include "../include/logger.h"

void logMessage(const std::string& message) {
    std::ofstream logfile("../../../Resources/server.log", std::ios::app);
    if (logfile.is_open()) {
        std::time_t now = std::time(nullptr);
        std::string timestamp = std::ctime(&now);
        timestamp.pop_back();
        logfile << "[" << timestamp << "] " << message << std::endl;
        logfile.close();
    }
    else {
        std::cerr << "Error:log file is not open" << std::endl;
    }
}