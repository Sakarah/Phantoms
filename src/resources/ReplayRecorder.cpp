#include "ReplayRecorder.h"
#include <cstring>
#include <fstream>
#include <iostream>

const int RECORD_VERSION = 0;

ReplayRecorder::ReplayMode ReplayRecorder::_replayMode = ReplayRecorder::Disabled;
std::fstream ReplayRecorder::_recordStream;
char ReplayRecorder::_boolBuffer = 0;
char ReplayRecorder::_boolMask = 0x1;

void ReplayRecorder::init(ReplayRecorder::ReplayMode mode, std::string fileName)
{
    _replayMode = mode;
    if(mode == Disabled) return;

    _recordStream.open(fileName, std::ios::binary | (mode == Replay ? std::ios::in : std::ios::out | std::ios::trunc));

    char header[5] = "FRec";
    logData(header, 4);
    if(std::strcmp(header, "FRec"))
    {
        std::cerr << tr("Invalid record file") << std::endl;
        mode = Disabled;
    }

    int version = RECORD_VERSION;
    logValue(version);
    if(version != RECORD_VERSION)
    {
        std::cerr << tr("Wrong record file version") << std::endl;
        mode = Disabled;
    }
}

ReplayRecorder::ReplayMode ReplayRecorder::replayMode() { return _replayMode; }

void ReplayRecorder::logData(char* data, int size)
{
    processBoolData();
    if(_replayMode == Record) _recordStream.write(data, size);
    else if(_replayMode == Replay) _recordStream.read(data, size);
    if(_recordStream.fail()) _replayMode = Disabled;
}

void ReplayRecorder::logBool(bool& value)
{
    if(_replayMode == Record) _boolBuffer |= value*_boolMask;
    else if(_replayMode == Replay)
    {
        if(_boolMask == 0x1) logValue(_boolBuffer);
        value = _boolBuffer&_boolMask;
    }
    _boolMask <<= 1;

    if(_boolMask == 0x0) processBoolData();
}

void ReplayRecorder::processBoolData()
{
    if(_boolMask == 0x1) return;
    if(_replayMode == Record)
    {
        _boolMask = 0x1;
        logValue(_boolBuffer);
        _boolBuffer = 0;
    }
    else if(_replayMode == Replay)
    {
        _boolMask = 0x1;
    }
}
