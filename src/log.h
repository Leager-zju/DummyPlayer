#pragma once

#include <fstream>

class LogManager {
public:
    LogManager() : logWrite("./dummyPlayer.log", std::ios::app) {}
    ~LogManager() {
        if (logWrite.is_open()) {
            logWrite.close();
        }
    }

    template<class T, class ...Args>
    void log(T&& first, Args&& ...args) {
        logWrite << first << " ";
        log(args...);
    }

    template<class T>
    void log(T&& arg) {
        logWrite << arg << std::endl;
    }
private:
    std::ofstream logWrite;
};

inline std::string extractFileName(const std::string& filePath) {
    return filePath.substr(filePath.find_last_of("/\\") + 1);  
}

inline std::string header(const std::string& filename, int line) {
    return "[" + extractFileName(filename) + ":" + std::to_string(line) + "]";
}