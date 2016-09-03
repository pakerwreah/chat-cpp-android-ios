//
//  android.cpp
//  ChatClient
//
//  Created by Paker on 12/04/15.
//  Copyright (c) 2015 Paker. All rights reserved.
//

#include "chatclient-android.h"

const char* ChatFragmentID = "com/paker/androidchatclient/ChatFragment";
JNIEnv *env;
jclass ChatFragment;
jobject classObj;
JavaVM* jvm;
ChatClientController chat;

#define AttachThread \
JNIEnv *env; \
jvm->AttachCurrentThreadAsDaemon(&env, NULL);

#define DetachThread \
jvm->DetachCurrentThread();

void ChatClientController::onConnect() {
    LOGI("Conectado!");
    
    AttachThread
    
    jmethodID methodID = env->GetMethodID(ChatFragment, "onConnect", "()V");
    env->CallVoidMethod(classObj, methodID);
    
    DetachThread
}

void ChatClientController::onDisconnect() {
    
    AttachThread
    
    jmethodID methodID = env->GetMethodID(ChatFragment, "onDisconnect", "()V");
    env->CallVoidMethod(classObj, methodID);
    
    LOGI("Desconectado!");
    
    DetachThread
}

void ChatClientController::recvMsg(String str) {
    
    AttachThread
    
    jmethodID methodID = env->GetMethodID(ChatFragment, "recvMsg", "(Ljava/lang/String;)V");
    env->CallVoidMethod(classObj, methodID, env->NewStringUTF(str.c_str()));
    
    DetachThread
}

static JNINativeMethod CFMethods[] = {
    {"conectar", "()V",(void*)conectar},
    {"sendMsg", "(Ljava/lang/String;Ljava/lang/String;)Z",(void*)sendMsg},
};

void conectar(JNIEnv *_env, jobject obj) {
    env = _env;
    classObj = env->NewGlobalRef(obj);
    
    LOGI("Conectando...");
    chat.conectar();
}

jboolean sendMsg(JNIEnv *_env, jobject thiz, jstring _nick, jstring _msg) {
    const char *nick = env->GetStringUTFChars(_nick, NULL);
    const char *msg = env->GetStringUTFChars(_msg, NULL);
    bool ok = chat.enviar(nick, msg);
    env->ReleaseStringUTFChars(_nick, nick);
    env->ReleaseStringUTFChars(_msg, msg);
    
    return ok;
}

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }
    
    jvm = vm;
    
    ChatFragment = env->FindClass(ChatFragmentID);
    if (ChatFragment == NULL)
        return JNI_ERR;
    
    ChatFragment = (jclass)env->NewGlobalRef(ChatFragment);
    
    env->RegisterNatives(ChatFragment, CFMethods, sizeof(CFMethods)/sizeof(CFMethods[0]));
    
    return JNI_VERSION_1_6;
}
