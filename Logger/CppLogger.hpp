#ifndef CPPLOGGER_H
#define CPPLOGGER_H

#include <iostream>
#include <string>
#include <fstream>
#include <mutex>

enum LogLevel
{
    lOff,
    lError,
    lWarn,
    lInfo,
    lDebug,
};

enum LogMode
{
    mFile,
    mConsole,
    mRemote,
};

class CppLogger
{
    private:
        std::string appId;

        LogLevel logLevel;

        LogMode logMode;

        std::string getTimestamp();

        std::string fileName;

        int logNum;

        std::ofstream fileStream;
        
    public:
        CppLogger(std::string appId, LogLevel logLevel, LogMode logMode, std::string fileName);

        void setLogLevel(std::string appId, LogLevel logLevel);

        void setLogMode(std::string appId, LogMode logMode);

        friend std::ostream& operator << (CppLogger& logger, const char* logMsg);

        ~CppLogger();
};



#endif