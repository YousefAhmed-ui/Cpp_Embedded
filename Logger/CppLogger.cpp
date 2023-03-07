

#include "CppLogger.hpp"
#include <ctime>
#include <mutex>

#define START_TIMESTAMP_INDEX   11

#define END_TIMESTAMP_INDEX     18

static std::mutex log_mutex;


CppLogger::CppLogger(std::string appId, LogLevel logLevel, LogMode logMode, std::string fileName = "")
{
    
    this->appId = appId;
    this->logLevel = logLevel;
    this->logMode = logMode;
    this->fileName = fileName;
    if(this->fileName != "")
    {
        fileStream = std::ofstream(fileName);
    }
    this->logNum = 0;
}

std::string CppLogger::getTimestamp()
{
    std::time_t localDateTime = std::time(nullptr);
    std::string dateAndTime = std::asctime(std::localtime(&localDateTime));
    std::string timestamp;
    for(uint8_t iterator = START_TIMESTAMP_INDEX; iterator <= END_TIMESTAMP_INDEX; iterator++)
    {
        timestamp += dateAndTime[iterator];
    }
    return timestamp;
}

std::ostream& operator << (CppLogger& logger, const char* logMsg)
{
    std::scoped_lock lock(log_mutex);
    if (logger.logLevel == lOff)
    {
        if(logger.logMode == mFile)
        {
            logger.fileStream << "| " << logger.getTimestamp() << " | " << logger.appId << " | "
                << logger.logNum << " | " << "lOff" << " | " << std::endl;
            return logger.fileStream;
        }
        if (logger.logMode == mConsole)
        {
            std::cout << "| " << logger.getTimestamp() << " | " << logger.appId << " | "
                << logger.logNum << " | " << "lOff" << " | " << std::endl;
            return std::cout;
        }
    }
    else
    {
        std::string lLevel;
        switch (logger.logLevel)
        {
            case lError:
                lLevel = "lError";
                break;
            case lWarn:
                lLevel = "lWarn";
                break;
            case lInfo:
                lLevel = "lInfo";
                break;
            case lDebug:
                lLevel = "lDebug";
                break;
        }
        if (logger.logMode == mFile)
        {
            logger.fileStream << "| " << logger.getTimestamp() << " | " << logger.appId << " | "
                << logger.logNum << " | " << lLevel << " | " << logMsg << std::endl;
            logger.logNum++;
            return logger.fileStream;
        }
        if (logger.logMode == mConsole)
        {
            std::cout << "| " << logger.getTimestamp() << " | " << logger.appId << " | "
                << logger.logNum << " | " << lLevel << " | " << logMsg << std::endl;
            logger.logNum++;
            return std::cout;
        }
    }
}

void CppLogger::setLogLevel(std::string appId, LogLevel logLevel)
{
    if (appId != "")
    {
        this->appId = appId;
    }
    this->logLevel = logLevel;
}

void CppLogger::setLogMode(std::string appId, LogMode logMode)
{
    if (appId != "")
    {
        this->appId = appId;
    }
    this->logMode = logMode;
}

CppLogger::~CppLogger()
{
    if(fileStream)
    {
        fileStream.close();
    }
}

