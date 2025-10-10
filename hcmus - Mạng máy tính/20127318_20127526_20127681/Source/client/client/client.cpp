#include <iostream>
#include <WS2tcpip.h>
#include <string>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

int main(int argc, char* argv[])
{
    WSADATA data;
    WORD version = MAKEWORD(2, 2);
    int wsOK = WSAStartup(version, &data);
    if (wsOK != 0)
    {
        cout << "can't start Winsock! " << wsOK;
        return 0;
    }
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(540000);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);
    string s;
    char buf[1024];
    int serverLength = sizeof(server);
    s = "Da ket noi duoc voi client ";
    cout << "Client: " << s << endl;
    sendto(out, s.c_str(), s.size() + 1, 0, (sockaddr*) & server, sizeof(server));
   
    recvfrom(out, buf, 1024, 0, (sockaddr*)&server, &serverLength);
    cout << "Server: " << buf << endl;
    recvfrom(out, buf, 1024, 0, (sockaddr*)&server, &serverLength);
    cout << "Server: " << buf << endl;
    recvfrom(out, buf, 1024, 0, (sockaddr*)&server, &serverLength);
    cout << "Server: " << buf << endl;

    cout << "Client: ";
    getline(cin, s);
    sendto(out, s.c_str(), s.size() + 1, 0, (sockaddr*)&server, sizeof(server));

    if(s == "1")
    {
        while ((string)buf != "end")
        {
            recvfrom(out, buf, 1024, 0, (sockaddr*)&server, &serverLength);
            cout << "Server: " << buf << endl;
        }
    }
    else if(s == "2")
    {
        recvfrom(out, buf, 1024, 0, (sockaddr*)&server, &serverLength);
        cout << "Server: " << buf << endl;

        cout << "Client: ";
        getline(cin, s);
        sendto(out, s.c_str(), s.size() + 1, 0, (sockaddr*)&server, sizeof(server));
        
        for (int i = 0; i < 3; i++)
        {
            recvfrom(out, buf, 1024, 0, (sockaddr*)&server, &serverLength);
            cout << "Server: " << buf << endl;
        }
    }

    closesocket(out);
    WSACleanup();
    return 0;
}