//
//  chatclient-protocol.h
//  ChatClientIOS
//
//  Created by Paker on 12/04/15.
//  Copyright (c) 2015 Paker. All rights reserved.
//

#ifndef ChatClientIOS_chatclient_protocol_h
#define ChatClientIOS_chatclient_protocol_h

#import <Foundation/Foundation.h>

@protocol ChatClientDelegate

- (void) onConnect;
- (void) onDisconnect;
- (void) recvMsg: (NSString *) str;

@end

#endif
