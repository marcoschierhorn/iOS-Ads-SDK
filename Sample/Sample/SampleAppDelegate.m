//
//  SampleAppDelegate.m
//  Sample
//
//  Created by Julien Stoeffler on 07/07/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "SampleAppDelegate.h"
#import "SmartAdServerView.h"
#import "RootViewController.h"

#define kSiteID 27893
#define kFormatID 12160
#define kPageID @"185330"


@implementation SampleAppDelegate

@synthesize window = _window;
@synthesize navigationController = _navigationController;
@synthesize startupAdView = _startupAdView;


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
	
	_window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    RootViewController *controller = [[RootViewController alloc] initWithNibName:@"RootViewController" bundle:nil];
    _navigationController = [[UINavigationController alloc] initWithRootViewController:controller];

    self.window.rootViewController = self.navigationController;
    
    // Set the Site ID of your application.
    [SmartAdServerView setSiteID:kSiteID];

    // Create the interstitial with the Launch Image (Default.png) as the loader, for a smooth transition
    _startupAdView = [[SASInterstitialView alloc] initWithFrame:self.navigationController.view.bounds loader:SmartAdServerViewLoaderLaunchImage hideStatusBar:YES];
    
    // We set the RootViewController instance as the delegate, so that it will notify this instance when the interstitial is dismissed.
    self.startupAdView.delegate = controller;
    
    //We load the ad for the given tags
    [self.startupAdView loadFormatId:kFormatID pageId:kPageID master:YES target:nil timeout:30];
    
    //Add the view to the navigationController, so it stays fulscreen.
    [self.navigationController.view addSubview:self.startupAdView];
    
    [self.window makeKeyAndVisible];
    return YES;
}


- (void)dealloc {
    self.window = nil;
    self.navigationController = nil;
}

@end
