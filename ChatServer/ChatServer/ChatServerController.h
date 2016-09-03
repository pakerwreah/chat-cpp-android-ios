//
//  ChatController.h
//  ChatServer
//
//  Created by Paker on 10/04/15.
//  Copyright (c) 2015 Paker. All rights reserved.
//

#ifndef __ChatServer__ChatServerController__
#define __ChatServer__ChatServerController__

#include "util.h"
#include "Socket.h"
#include <thread>

class ChatServerController;

class Client {
    
    Socket *socket;
    ChatServerController *delegate;
    
public:
    String ident;
    
    Client(String ident, Socket *socket, ChatServerController *delegate);
    void run();
    bool send(String str);
};

class ChatServerController {
    
    std::mutex m;
    List<Client*> clients;
    
public:
    
    void addClient(Client *client);
    void remClient(Client *client);
    void sendAll(String str);
};

#endif /* defined(__ChatServer__ChatServerController__) */
