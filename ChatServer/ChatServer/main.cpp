//
//  main.cpp
//  ChatServer
//
//  Created by Paker on 10/04/15.
//  Copyright (c) 2015 Paker. All rights reserved.
//

#include <iostream>
#include "Socket.h"
#include <string>
#include "ChatServerController.h"

using namespace std;

int main(int argc, const char * argv[])
{
    cout << "intializing...." << endl;
 
    ChatServerController controller;
    
    // Create the socket
    int port = 30000;
    Socket server;
    server.create();
    server.bind(port);
    server.listen();
    
    cout << "running...." << endl;
    
    int count = 0;
    
    while ( true )
    {
        Socket *new_sock = new Socket;
        if(server.accept ( *new_sock ))
            controller.addClient(new Client(++count, new_sock, &controller));
        else
            cout << "falha ao conectar" << endl;
    }
    
    return 0;
}
