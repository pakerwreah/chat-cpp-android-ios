//
//  AppDelegate.m
//  ChatClientIOS
//
//  Created by Paker on 12/04/15.
//  Copyright (c) 2015 Paker. All rights reserved.
//

#import "AppDelegate.h"
#import "ChatViewController.h"

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    
    ChatViewController *login = [[ChatViewController alloc] init];
    self.window.rootViewController = login;
    [self.window makeKeyAndVisible];
    
    return YES;
}

@end
