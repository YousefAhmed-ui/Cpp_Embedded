



#include "CppLogger.hpp"

int main()
{
    CppLogger cpp("yousef APP", lDebug, mFile, "Log.txt");
    cpp << "Hellllllo my friend?";
    cpp << "I'm good what about you?";
    cpp.setLogLevel("joe APP", lOff);
    cpp << "Log level is off";
    cpp.setLogMode("joe APP", mConsole);
    cpp.setLogLevel("joe APP", lInfo);
    cpp << "i'm Writing to console";
    //std::thread
    return 0;
}



