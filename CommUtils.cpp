
#include "pch.h"
#include "CommUtils.h"
#include "stdio.h"
const int READ_TIMEOUT = 500;

CommUtils::CommUtils()
{
    bOpenCom = false;
}

CommUtils::~CommUtils()
{
    this->CloseCom();
}

bool CommUtils::OpenCom(int port_idx, int rate_idx)
{
    if (bOpenCom)
    {
        this->CloseCom();
        bOpenCom = false;
    }
    //char szport[10];
    //if (Port >= 10)  sprintf_s(szport, "\\\\.\\COM%d", Port);
    //else sprintf_s(szport, "COM%d", Port);
    LPCSTR port_name = m_PortNameList[port_idx];
    hComm = CreateFile(port_name, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
    int error = GetLastError();

    if (hComm == INVALID_HANDLE_VALUE)        return false;
    if (!SetupComm(hComm, 1024, 512))        return false;

    COMMTIMEOUTS commtimeouts;
    commtimeouts.ReadIntervalTimeout = MAXDWORD;
    commtimeouts.ReadTotalTimeoutConstant = 0;
    commtimeouts.ReadTotalTimeoutMultiplier = 0;
    commtimeouts.WriteTotalTimeoutConstant = 0;
    commtimeouts.WriteTotalTimeoutMultiplier = 0;

    if (!SetCommTimeouts(hComm, &commtimeouts))        return false;

    memset(&ReadovReady, 0, sizeof(OVERLAPPED));
    memset(&WriteovReady, 0, sizeof(OVERLAPPED));
    ReadovReady.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    WriteovReady.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;

    DCB dcb;
    GetCommState(hComm, &dcb);
    dcb.fBinary = TRUE;
    dcb.fParity = FALSE;
    // 波特率  数据位  标志位 根据自己的设备在此做修改 
    dcb.BaudRate = m_PortRateList[rate_idx];        // baud rate 9600
    dcb.ByteSize = 8;
    dcb.Parity = NOPARITY;
    dcb.StopBits = ONESTOPBIT;

    if (!SetCommState(hComm, &dcb))        return false;
    
    PurgeComm(hComm, PURGE_TXCLEAR | PURGE_RXCLEAR);

    DWORD a = GetFileSize(hComm, NULL);
    bOpenCom = true;
    return bOpenCom;
}

bool CommUtils::WriteCom(unsigned char* sendchar, int sendsize)
{
    if (!bOpenCom)    return false;

    DWORD    BytesSent;
    DWORD    resD;

    PurgeComm(hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

    BytesSent = 0;
    BOOL hr = WriteFile(hComm,                            // Handle to COMM Port
        sendchar,                        // Pointer to message buffer in calling finction
        sendsize,                        // Length of message to send
        &BytesSent,                        // Where to store the number of bytes sent
        &WriteovReady);                    // Overlapped structure
    if (!hr)
    {
        if (GetLastError() != ERROR_IO_PENDING)
        {
            return false;
        }
        else
        {
            resD = WaitForSingleObject(WriteovReady.hEvent, INFINITE);
        }
        switch (resD)
        {
        case WAIT_OBJECT_0:
        {
            if (!GetOverlappedResult(hComm, &WriteovReady, &BytesSent, false))
                return false;
            else
                return true;

        }
        default:
            return false;
            break;
        }
    }
    return true;
}

void CommUtils::CloseCom()
{
    if (!bOpenCom)    return;

    CloseHandle(hComm);
    hComm = NULL;

    CloseHandle(ReadovReady.hEvent);
    CloseHandle(WriteovReady.hEvent);
    ReadovReady.hEvent = NULL;
    WriteovReady.hEvent = NULL;
}

bool CommUtils::ReadCom(unsigned char* ReceiveData, DWORD& ReceiveLength)
{
    if (!bOpenCom)    return false;
    if (ReadovReady.hEvent == NULL)    return false;

    ReceiveLength = 0;
    if (ReadFile(hComm, ReceiveData, 128, &ReceiveLength, &ReadovReady) == FALSE)
    {
        if (GetLastError() != ERROR_IO_PENDING)    return false;
    }
    /*
    bResult = ReadFile(port->m_hComm,  // Handle to COMM port
                &RXBuff,    // RX Buffer Pointer
                 1,     // Read one byte
                 &BytesRead,   // Stores number of bytes read
                 &port->m_ov);  // pointer to the m_ov structure
                 // deal with the error code */
    if (ReceiveLength == 0)    return false;
    ReceiveData[ReceiveLength] = 0;

    DWORD dwRead;
    DWORD dwRes = WaitForSingleObject(ReadovReady.hEvent, READ_TIMEOUT);
    switch (dwRes)
    {
    case WAIT_OBJECT_0:
        if (!GetOverlappedResult(hComm, &ReadovReady, &dwRead, FALSE))    return false;
        break;

    case WAIT_TIMEOUT:
        break;

    default:
        break;
    }
    return true;
}

bool CommUtils::ReadAngle(double* Angle)
{
    if (!bOpenCom)    return false;
    if (ReadovReady.hEvent == NULL)    return false;
    unsigned char buffer[100];
    DWORD ReceiveLength;
    COMSTAT ComStat;
    DWORD dwErrorFlags;
    ClearCommError(hComm, &dwErrorFlags, &ComStat);
    int cnt = 0;
    while (1)
    {
        if (cnt > 1e6) {
            return false;
        }
        if (ReadFile(hComm, buffer, 1, &ReceiveLength, &ReadovReady) == FALSE)
        {
            if (GetLastError() != ERROR_IO_PENDING)    return false;
        }
        if (buffer[0] != 85) {
            cnt++;
            continue;
        }
        if (ReadFile(hComm, buffer, 1, &ReceiveLength, &ReadovReady) == FALSE)
        {
            if (GetLastError() != ERROR_IO_PENDING)    return false;
        }
        if (buffer[0] != 83) {
            cnt++;
            continue;
        }
        if (ReadFile(hComm, buffer, 6, &ReceiveLength, &ReadovReady) == FALSE)
        {
            if (GetLastError() != ERROR_IO_PENDING)    return false;
        }
        INT16 x, y, z; // roll, pitch, yaw
        x = buffer[1];
        x = x << 8;
        x = x + buffer[0];
        Angle[0] = x / 32768.0 * 180;
        y = buffer[3];
        y = y << 8;
        y = y + buffer[2];
        Angle[1] = y / 32768.0 * 180;
        z = buffer[5];
        z = z << 8;
        z = z + buffer[4];
        Angle[2] = z / 32768.0 * 180;

        cnt = 0;
        PurgeComm(hComm, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
        return true;
    }

    return true;
}
