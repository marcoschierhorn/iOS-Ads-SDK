//
//  SampleAppDelegate.h
//  Sample
//
//  Created by Julien Stoeffler on 07/07/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SASInterstitialView.h"


@interface SampleAppDelegate : UIResponder <UIApplicationDelegate>

@property (retain, nonatomic) UIWindow *window;
@property (retain, nonatomic) UINavigationController *navigationController;
@property (retain) SASInterstitialView *startupAdView;

@end
