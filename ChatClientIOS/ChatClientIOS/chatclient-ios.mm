//
//  chatclient-ios.m
//  ChatClientIOS
//
//  Created by Paker on 12/04/15.
//  Copyright (c) 2015 Paker. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "chatclient-ios.h"
#import "chatclient-protocol.h"

ChatClientController::ChatClientController(void *delegate) {
    this->delegate = delegate;
}

void ChatClientController::onConnect(){
    NSLog(@"Conectado!");
    dispatch_async(dispatch_get_main_queue(), ^{
        [(__bridge id<ChatClientDelegate>)delegate onConnect];
    });
}

void ChatClientController::onDisconnect(){
    NSLog(@"Desconectado!");
    dispatch_async(dispatch_get_main_queue(), ^{
        [(__bridge id<ChatClientDelegate>)delegate onDisconnect];
    });
}

void ChatClientController::recvMsg(String str){
    NSString *msg = [NSString stringWithUTF8String:str.c_str()];
    NSLog(@"Msg recebida: %@",msg);
    dispatch_async(dispatch_get_main_queue(), ^{
        [(__bridge id<ChatClientDelegate>)delegate recvMsg:msg];
    });
}