//
//  chatclient.h
//  ChatClient
//
//  Created by Paker on 12/04/15.
//  Copyright (c) 2015 Paker. All rights reserved.
//

#ifndef ChatClient_chatclient_h
#define ChatClient_chatclient_h

#include "Socket.h"
#include "util.h"

class ChatClient {
    static const int port = 30000;
    static const int timeout = 5;
    Socket server;
    void run();
public:
    void conectar();
    bool enviar(String nick, String str);
    void virtual onConnect() = 0;
    void virtual onDisconnect() = 0;
    void virtual recvMsg(String str) = 0;
};

#endif
