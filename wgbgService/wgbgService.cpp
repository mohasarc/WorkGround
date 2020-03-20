// wgbgService.cpp : This is the background service for WG
// Author : Mohammed S. Yaseen
// Date   : 18/03/2020

#include <string>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "../WGs/src/header/workGround.h"
#define BUFSIZE 4096

using namespace std;

// constantss
const int DELETE_WG = 100;
const int SEND_WG_TO_CLIENT = 101;
const int STORE_WG = 102;
const int RECIEVE_ID = 103;
const int TERMINATE_SERVICE = 200;

int main()
{
    // Local Variables
    int opCode;
    vector<WorkGround> activeWGs;
    // Create named Pipe Variables
    HANDLE hNamedPipe = 0;
    char* szInputBuffer;
    char* szOutputBuffer;
    DWORD dwszInputBuffer = sizeof(szInputBuffer);
    DWORD dwszOutputBuffer = sizeof(szOutputBuffer);
    // Read OPcode Local Variables
    bool bReadFile = false;
    bool bConnectNamedPipe = false;
    int requestBuffer = -1;
    DWORD dwNoBytesRead;
    // Read WorkGround Local Variables
    string serializedWG;
    char* serializedWGBuffer;
    WorkGround* readWG;
    // Retrieve WorkGround Local Variables
    char* serializedWGBuff = new char[BUFSIZE];
    DWORD serializedWGBuffSize = BUFSIZE;
    WorkGround wgToRetrieve;
    bool bWriteFile = false;
    bool bFlushFileBuffer = false;
    int wgIDBuffer = 0;
    DWORD dwNoBytesWrite;
    // wgbgService Local Variables
    bool exit = false;

    while (!exit) {
        // Create wgbgservice named pipe - STEP 1
        hNamedPipe = CreateNamedPipe(
            TEXT("\\\\.\\pipe\\wgbgservice"),
            PIPE_ACCESS_DUPLEX,
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
            PIPE_UNLIMITED_INSTANCES,
            BUFSIZE * sizeof(TCHAR),
            BUFSIZE * sizeof(TCHAR),
            0,
            NULL
        );

        if (hNamedPipe == INVALID_HANDLE_VALUE) {
            cout << "wgbgservice named pipe Creation Failed & Error No - " << GetLastError() << endl;
        }
        else {
            cout << "wgbgservice named pipe Creation Succeeded" << endl;
        }

        // Connect to wgbgservice named pipe - STEP 2
        bConnectNamedPipe = ConnectNamedPipe(
            hNamedPipe,
            NULL);

        if (!bConnectNamedPipe) {
            cout << "NamePipe Connection Failed & Error No - " << GetLastError() << endl;
        }
        else {
            cout << "Connected Successfuly" << endl;
        }

        // Read OPcode - STEP 3
        bReadFile = ReadFile(
            hNamedPipe,
            &requestBuffer,
            sizeof(int),
            &dwNoBytesRead,
            NULL
        );
        if (!bReadFile)
        {
            cout << "Reading request Failed & Error No - " << GetLastError() << endl;
        }
        else
        {
            cout << "Request read successfuly, OPcode : " << requestBuffer << endl;
            switch (requestBuffer)
            {
            //************************
            //       STORE_WG
            //************************
            case(STORE_WG):
                // Read WorkGround
                serializedWGBuffer = new char[BUFSIZE];
                bReadFile = ReadFile(
                    hNamedPipe,
                    serializedWGBuffer,
                    BUFSIZE,
                    &dwNoBytesRead,
                    NULL
                );

                if (!bReadFile)
                {
                    cout << "Reading WG Failed & Error No - " << GetLastError() << endl;
                }
                else
                {
                    serializedWG = "";
                    readWG = new WorkGround;
                    for (int i = 0; i < BUFSIZE - 1; i++) {
                        if (serializedWGBuffer[i] == '\n' && serializedWGBuffer[i + 1] == '\n')
                            break;
                        serializedWG += serializedWGBuffer[i];
                    }
                    cout << "the string \n" << serializedWG;
                    stringstream serializedWGStream(serializedWG);
                    WorkGround::deserialize(serializedWGStream, readWG);
                    cout << "WG read successfully " << endl;
                    cout << readWG->wgView();
                    activeWGs.insert(activeWGs.begin() ,*readWG); // storing the workground in memory
                }

                requestBuffer = -1;
                break;
            
            //************************
            //       DELETE_WG
            //************************
            case(DELETE_WG):
                // Find WorkGround & Remove it
                for (int i = 0; i < activeWGs.size(); i++) {
                    if (activeWGs[i].getID() == wgIDBuffer)
                        activeWGs.erase(activeWGs.begin() + i);
                }

                requestBuffer = -1;
                break;
            //*****************************
            //      SEND_WG_TO_CLIENT
            //*****************************
            case(SEND_WG_TO_CLIENT):
                // Find WorkGround
                for (WorkGround i : activeWGs) {
                    if (i.getID() == wgIDBuffer)
                        wgToRetrieve = i;
                }

                serializedWG = "";
                cout << "retrieving " << endl << wgToRetrieve.wgView();
                WorkGround::serialize(wgToRetrieve, serializedWG);

                // Initialize the buffer
                for (int i = 0; i < BUFSIZE; i++) {
                    if (i < serializedWG.size())
                        serializedWGBuff[i] = serializedWG.at(i);
                    else
                        serializedWGBuff[i] = '\n';
                }

                // Write WorkGround
                bWriteFile = WriteFile(
                    hNamedPipe,
                    serializedWGBuff,
                    serializedWGBuffSize,
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

                requestBuffer = -1;
                break;

            //************************
            //       RECIEVE_ID
            //************************
            case(RECIEVE_ID):
                // Read WGID
                bReadFile = ReadFile(
                    hNamedPipe,
                    &wgIDBuffer,
                    sizeof(int),
                    &dwNoBytesRead,
                    NULL);

                if (!bReadFile)
                    cout << "Reading WGID Failed & Error No - " << GetLastError() << endl;
                else
                    cout << "WGID read successfuly, WGID : " << wgIDBuffer << endl;
                
                requestBuffer = -1;
                break;

            //*************************
            //    TERMINATE_SERVICE
            //*************************
            case (TERMINATE_SERVICE):
                exit = true;
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