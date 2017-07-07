#ifndef REPLAYRECORDER_H
#define REPLAYRECORDER_H

#include "common.h"

class ReplayRecorder
{
public:
    enum ReplayMode
    {
        Disabled,
        Record,
        Replay
    };

    static void init(ReplayMode, std::string fileName);
    static ReplayMode replayMode();
    static void logData(char* data, int size);
    static void logBool(bool& value);
    template<typename T> static void logValue(T& value);

private:
    static void processBoolData();
    static ReplayMode _replayMode;
    static std::fstream _recordStream;
    static char _boolBuffer;
    static char _boolMask;
};

template<typename T>
void ReplayRecorder::logValue(T& value)
{
    logData(reinterpret_cast<char*>(&value), sizeof(T));
}

#endif // REPLAYRECORDER_H
