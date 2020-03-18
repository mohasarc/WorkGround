// wgbgService.cpp : This is the background service for WG
// Author : Mohammed S. Yaseen
// Date   : 18/03/2020

#include <string>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "../WGs/src/header/workGround.h"
using namespace std;

// constantss
const int DELETE_WG = 0;
const int RETRIEVE_WG = 1;
const int STORE_WG = 2;
const int SEND_ID = 3;

int main()
{
    // Local Variables
    int opCode;
    vector<WorkGround> activeWGs;
    // Create named Pipe Variables
    HANDLE hNamedPipe;
    char* szInputBuffer;
    char* szOutputBuffer;
    DWORD dwszInputBuffer = sizeof(szInputBuffer);
    DWORD dwszOutputBuffer = sizeof(szOutputBuffer);
    // Read OPcode Local Variables
    bool bReadFile = false;
    bool bConnectNamedPipe = false;
    int* opBuffer = 0;
    DWORD dwNoBytesRead;
    // Read WorkGround Local Variables
    WorkGround* wgBuffer = 0;
    // Retrieve WorkGround Local Variables
    WorkGround* toRetrieveBuffer = 0;
    bool bWriteFile = false;
    bool bFlushFileBuffer = false;
    int* wgIDBuffer = 0;
    DWORD dwNoBytesWrite;


    while (1) {
        // Create wgbgservice named pipe - STEP 1
        hNamedPipe = CreateNamedPipe(
            TEXT("\\\\.\\pipe\\wgbgserviceTest11"),
            PIPE_ACCESS_DUPLEX,
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
            PIPE_UNLIMITED_INSTANCES,
            dwszOutputBuffer,
            dwszInputBuffer,
            0,
            NULL
        );

        if (hNamedPipe == INVALID_HANDLE_VALUE)
        {
            cout << "wgbgservice named pipe Creation Failed & Error No - " << GetLastError() << endl;
        }
        else
        {
            cout << "wgbgservice named pipe Creation Succeeded" << endl;
        }

        // Connect to wgbgservice named pipe - STEP 2
        bConnectNamedPipe = ConnectNamedPipe(
            hNamedPipe,
            NULL);

        if (!bConnectNamedPipe)
        {
            cout << "NamePipe Connection Failed & Error No - " << GetLastError() << endl;
        }
        else
        {
            cout << "Connected Successfuly" << endl;
            cout << "Waiting for opCode..." << endl;
        }

        // Read OPcode - STEP 3
        bReadFile = ReadFile(
            hNamedPipe,
            opBuffer,
            sizeof(int),
            &dwNoBytesRead,
            NULL
        );
        if (!bReadFile)
        {
            cout << "Reading OPcode Failed & Error No - " << GetLastError() << endl;
        }
        else
        {
            cout << "OPcode read successfuly" << endl;
            opCode = *opBuffer;
            switch (opCode)
            {
            case(STORE_WG):
                // Read WorkGround
                bReadFile = ReadFile(
                    hNamedPipe,
                    wgBuffer,
                    sizeof(WorkGround),
                    &dwNoBytesRead,
                    NULL
                );
                if (!bReadFile)
                {
                    cout << "Reading WG Failed & Error No - " << GetLastError() << endl;
                }
                else
                {
                    cout << "WG read successfuly" << endl;
                    activeWGs.push_back(*wgBuffer); // storing the workground in memory
                }
                break;
            
            case(DELETE_WG):
                // Find WorkGround & Remove it
                for (int i = 0; i < activeWGs.size(); i++) {
                    if (activeWGs[i].getID() == *wgIDBuffer)
                        activeWGs.erase(activeWGs.begin() + i);
                }
                break;

            case(RETRIEVE_WG):
                // Find WorkGround
                for (WorkGround i : activeWGs) {
                    if (i.getID() == *wgIDBuffer)
                        toRetrieveBuffer = &i;
                }
                // Write WorkGround
                bWriteFile = WriteFile(
                    hNamedPipe,
                    toRetrieveBuffer,
                    sizeof(toRetrieveBuffer),
                    &dwNoBytesWrite,
                    NULL
                );

                if (!bWriteFile) {
                    cout << "Writing WG Failed & Error No - " << GetLastError() << endl;
                } else {
                    cout << "Writing WG Succeeded" << endl;
                }

                // Flush FileBuffer
                bFlushFileBuffer = FlushFileBuffers(hNamedPipe);
                if (!bFlushFileBuffer) {
                    cout << "FlushFile Buffer Failed & Error No - " << GetLastError() << endl;
                } else {
                    cout << "FlushFile Buffer Succeeded" << endl;
                }
                break;

            case(SEND_ID):
                // Read WGID
                bReadFile = ReadFile(
                    hNamedPipe,
                    wgIDBuffer,
                    sizeof(int),
                    &dwNoBytesRead,
                    NULL);

                if (!bReadFile)
                    cout << "Reading WGID Failed & Error No - " << GetLastError() << endl;
                else
                    cout << "WG read successfuly" << endl;
                break;

            default:
                // Do Nothing
                break;
            }
        }
    }
    
    // disconnect Pipe - STEP 6
    DisconnectNamedPipe(hNamedPipe);

    // Close handle - STEP 7
    CloseHandle(hNamedPipe);

    //system("PAUSE");
    return 0;
}