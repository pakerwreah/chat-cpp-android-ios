//
//  android.h
//  ChatClient
//
//  Created by Paker on 12/04/15.
//  Copyright (c) 2015 Paker. All rights reserved.
//

#ifndef __ChatClientJNI_chatclient_android_h
#define __ChatClientJNI_chatclient_android_h

#include <jni.h>

#include "android/log.h"
#include "chatclient.h"

#define LOG_TAG "JNILog"

#define LOGI(fmt, args...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, fmt, ##args)
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, fmt, ##args)
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, fmt, ##args)

class ChatClientController : public ChatClient {
public:
    void onConnect();
    void onDisconnect();
    void recvMsg(String str);
};

extern "C" {
    jboolean sendMsg(JNIEnv *_env, jobject thiz, jstring nick, jstring msg);
    jint JNI_OnLoad(JavaVM* vm, void* reserved);
    void conectar(JNIEnv *_env, jobject obj);
}

#endif
