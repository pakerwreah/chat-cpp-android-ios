#include <thread>
#include "chatclient.h"

using namespace std;

void ChatClient::conectar() {
    new thread([this]{
        bool connected = false;
        do
        {
            server.create();
            connected = server.connect("192.168.1.120", port, timeout);
            if(!connected)
                sleep(1);
            
        } while(!connected);
        
        new thread(&ChatClient::run,this);
    });
}

void ChatClient::run() {
    onConnect();
    
    String str;
    
    while(server.recv(str))
        recvMsg(str);
    
    onDisconnect();
    
    conectar();
}

bool ChatClient::enviar(String nick, String str) {
    return server.send(nick+String(": ")+str);
}