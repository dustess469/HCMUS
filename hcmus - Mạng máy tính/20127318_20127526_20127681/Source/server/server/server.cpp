#include <iostream>
#include <WS2tcpip.h>
#include "DiaDiem.h"
#include <vector>
#include <fstream>
#include <string>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

int main()
{
    WSADATA data;
    WORD version = MAKEWORD(2, 2);
    int wsOK = WSAStartup(version, &data);
    if (wsOK != 0)
    {
        cout << "can't start Winsock! " << wsOK;
        return 0;
    }

    SOCKET in = socket(AF_INET, SOCK_DGRAM, 0);
    sockaddr_in serverHint;
    serverHint.sin_addr.S_un.S_addr = ADDR_ANY;
    serverHint.sin_family = AF_INET;
    serverHint.sin_port = htons(540000);

    if (bind(in, (sockaddr*)&serverHint, sizeof(serverHint)) == SOCKET_ERROR)
    {
        cout << "Can't bind socket " << WSAGetLastError() << endl;
    }

    sockaddr_in client;
    int clientLength = sizeof(client);
    ZeroMemory(&client, clientLength);
    char buf[1024];
    string str, str1, str2;
    vector<DiaDiem> vec;
    ifstream file;

    file.open("sampledata.txt");
    while (!file.eof())
    {
        getline(file, str, '\n');
        getline(file, str1, '\n');
        getline(file, str2, '\n');

        DiaDiem dd(str, str1, str2);
        vec.push_back(dd);
        getline(file, str, '\n');
    }
    file.close();
    
    ZeroMemory(buf, 1024);
    recvfrom(in, buf, 1024, 0, (sockaddr*)&client, &clientLength);
    
    char clientIp[256];
    ZeroMemory(clientIp, 256);
    inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);

    cout << "Message receive from " << clientIp << " : " << buf << endl;
    str = "Xin chao  client " + (string)clientIp;
    cout << "Server: " << str << endl;
    sendto(in, str.c_str(), str.size() + 1, 0, (sockaddr*)&client, sizeof(client));

    str = "1. Xuat tat ca cac dia diem ";
    cout << "Server: " << str << endl;
    sendto(in, str.c_str(), str.size() + 1, 0, (sockaddr*)&client, sizeof(client));  
    str = "2. Truy xuat dia diem ";
    cout << "Server: " << str << endl;
    sendto(in, str.c_str(), str.size() + 1, 0, (sockaddr*)&client, sizeof(client));

    recvfrom(in, buf, 1024, 0, (sockaddr*)&client, &clientLength);
    cout << "Client: " << buf << endl;

    if ((string)buf == "1")
    {
        for (int i = 0; i < vec.size(); i++)
        {
            str = vec[i].ten;
            cout << "Server: " << str << endl;
            sendto(in, str.c_str(), str.size() + 1, 0, (sockaddr*)&client, sizeof(client));

            str = vec[i].toado;
            cout << "Server: " << str << endl;
            sendto(in, str.c_str(), str.size() + 1, 0, (sockaddr*)&client, sizeof(client));

            str = vec[i].mota;
            cout << "Server: " << str << endl;
            sendto(in, str.c_str(), str.size() + 1, 0, (sockaddr*)&client, sizeof(client));
        }
        str = "end";
        sendto(in, str.c_str(), str.size() + 1, 0, (sockaddr*)&client, sizeof(client));
    }
    else if ((string)buf == "2")
    {
        DiaDiem x;
        str = "Nhap ten dia diem";
        cout << "Server: " << str << endl;
        sendto(in, str.c_str(), str.size() + 1, 0, (sockaddr*)&client, sizeof(client));

        recvfrom(in, buf, 1024, 0, (sockaddr*)&client, &clientLength);
        cout << "Client: " << buf << endl;

        for (int i = 0; i < vec.size(); i++)
            if ((string)buf == vec[i].ten)
                x = vec[i];
        
        str = x.ten;
        cout << "Server: " << str << endl;
        sendto(in, str.c_str(), str.size() + 1, 0, (sockaddr*)&client, sizeof(client));

        str = x.toado;
        cout << "Server: " << str << endl;
        sendto(in, str.c_str(), str.size() + 1, 0, (sockaddr*)&client, sizeof(client));

        str = x.mota;
        cout << "Server: " << str << endl;
        sendto(in, str.c_str(), str.size() + 1, 0, (sockaddr*)&client, sizeof(client));
    }


    closesocket(in);
    WSACleanup();
    return 0;
}
