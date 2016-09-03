//
//  ChatServerController.cpp
//  ChatServer
//
//  Created by Paker on 10/04/15.
//  Copyright (c) 2015 Paker. All rights reserved.
//

#include "ChatServerController.h"

using namespace std;

Client::Client(String ident, Socket *socket, ChatServerController *delegate) {
    this->ident = ident;
    this->socket = socket;
    this->delegate = delegate;
    
    new thread(&Client::run, this);
}

void ChatServerController::addClient(Client *client) {
    clients << client;
    cout << clients.size() << " clientes conectados." << endl;
}

void ChatServerController::remClient(Client *client) {
    m.lock();
    clients.erase(find(clients.begin(), clients.end(), client));
    cout << "Cliente \"" << client->ident << "\" foi desconectado!" << endl;
    cout << clients.size() << " clientes conectados." << endl;
    m.unlock();
}

void ChatServerController::sendAll(String str) {
    for (Client *c : clients)
        c->send(str);
}

bool Client::send(String str) {
    return socket->send(str);
}

void Client::run() {
    
    cout << "Cliente \"" << ident << "\" running... " << endl;
    
    String str;
    
    while(socket->recv(str))
    {
        cout << "Cliente \"" << ident << "\" disse: " << str << endl;
        
        delegate->sendAll(str);
    }
    
    delegate->remClient(this);
}