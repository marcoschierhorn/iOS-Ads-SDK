//
//  RootViewController.h
//  Sample
//
//  Created by Julien Stoeffler on 07/07/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SmartAdServerViewDelegate.h"
#import "SASBannerView.h"
#import "SASInterstitialView.h"


@interface RootViewController : UITableViewController <SmartAdServerViewDelegate>

// We keep properties to have reference to our ad object
@property (nonatomic, retain) SASBannerView *topBanner;
@property (nonatomic, retain) SASInterstitialView *interstitial;

// Two methods to create the ad objects and display them
- (void)createTopBanner;
- (void)createInterstitial;

@end
