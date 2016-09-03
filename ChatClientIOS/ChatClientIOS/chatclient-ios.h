//
//  chatclient-ios.h
//  ChatClientIOS
//
//  Created by Paker on 12/04/15.
//  Copyright (c) 2015 Paker. All rights reserved.
//

#ifndef ChatClientIOS_chatclient_ios_h
#define ChatClientIOS_chatclient_ios_h

#include "chatclient.h"

class ChatClientController : public ChatClient
{
    void *delegate;
public:
    ChatClientController(void *delegate);
    void onConnect();
    void onDisconnect();
    void recvMsg(String str);
};

#endif
