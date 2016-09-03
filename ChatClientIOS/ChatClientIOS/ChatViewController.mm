//
//  ChatViewController.m
//  ChatClientIOS
//
//  Created by Paker on 12/04/15.
//  Copyright (c) 2015 Paker. All rights reserved.
//

#import "ChatViewController.h"
#import "chatclient-protocol.h"
#include "chatclient-ios.h"

@interface ChatViewController () <UITextFieldDelegate, ChatClientDelegate>
@property (weak, nonatomic) IBOutlet UITextField *textField;
@property (weak, nonatomic) IBOutlet UITextView *textView;
@property (weak, nonatomic) IBOutlet UIButton *enviarBtn;

@end

@implementation ChatViewController {
    ChatClientController *chat;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    _textView.text = @"";
    _enviarBtn.enabled = NO;
    
    chat = new ChatClientController((__bridge void*)self);
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        chat->conectar();
    });
}

- (IBAction)textViewTap:(id)sender {
    [self.view endEditing:YES];
}

- (IBAction)enviarBtnTap:(id)sender {
    NSString *str = _textField.text;
    _textField.text = @"";
    _enviarBtn.enabled = NO;
    chat->enviar("Lagartixa",str.UTF8String);
}

-(BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string {
    _enviarBtn.enabled = [textField.text stringByReplacingCharactersInRange:range withString:string].length > 0;
    
    return YES;
}

-(void)onConnect {
    [_textView insertText:@"Conectado!\n"];
}

-(void)onDisconnect {
    [_textView insertText:@"Desconectado!\n"];
}

-(void)recvMsg:(NSString *)str {
    [_textView insertText:[str stringByAppendingString:@"\n"]];
}

@end
