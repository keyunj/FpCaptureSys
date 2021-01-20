#pragma once
#ifndef _CommUtils_H__
#define _CommUtils_H__

#include <vector>
#include "Timer.hpp"

using namespace std;

class CommUtils
{
public:
    bool ReadCom(unsigned char* ReceiveData, DWORD& ReceiveLength);
    bool ReadAngle(double* Angle);
    void StartListen(int interval);
    void StopListen();
    void CloseCom();
    bool WriteCom(unsigned char* sendchar, int sendsize);
    bool OpenCom(int port_idx, int rate_idx);

    CommUtils();
    virtual ~CommUtils();
    int m_Port;
    char szCurPath[256];

    Timer rec_timer;
    double Angle[3];
    double Acc[3];
    double Mag[3];
    
    vector<CString> m_PortNameList;
    vector<int> m_PortRateList = {2400, 4800, 9600, 19200, 38400, 57600, 115200};

private:
    OVERLAPPED ReadovReady, WriteovReady;
    HANDLE hComm;
    bool bOpenCom;

    bool ReadData();
    void DecodeData(unsigned char* buffer);
};

#endif


