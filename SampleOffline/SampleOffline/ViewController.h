//
//  ViewController.h
//  SampleOffline
//
//  Created by Julien Stoeffler on 14/03/12.
//  Copyright (c) 2012 Smart AdServer. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SASBannerView.h"
#import "SASInterstitialView.h"

@interface ViewController : UIViewController <SmartAdServerViewDelegate> {
    SASBannerView *_banner;
    SASInterstitialView *_offlineStartupInterstitial;
}
@property (nonatomic, retain) SASInterstitialView *offlineStartupInterstitial;
@property (nonatomic, retain) SASBannerView *banner;

- (void)loadBanner;
- (void)loadInterstitial;
@end
