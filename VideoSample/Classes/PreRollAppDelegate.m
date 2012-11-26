//
//  PreRollAppDelegate.m
//  PreRoll
//
//  Created by jstoeffler on 17/05/11.
//  Copyright 2011 Smart AdServer. All rights reserved.
//

#import "PreRollAppDelegate.h"


#import "RootViewController.h"
#import "DetailViewController.h"
#import "SmartAdServerView.h"
#import <AVFoundation/AVFoundation.h>

@implementation PreRollAppDelegate
@synthesize window, splitViewController, rootViewController, detailViewController;

#pragma mark - Application lifecycle

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    
    
	// 'setMode:error:' is available since iOS 5.0
    if ([[AVAudioSession sharedInstance] respondsToSelector:@selector(setMode:error:)])
        [[AVAudioSession sharedInstance] setMode:AVAudioSessionModeDefault error:NULL];
	[SmartAdServerView setSiteID:27893];
    [self.window addSubview:splitViewController.view];
    [self.window makeKeyAndVisible];
    return YES;
}


- (void)dealloc {
    [splitViewController release];
    [window release];
    [super dealloc];
}


@end

