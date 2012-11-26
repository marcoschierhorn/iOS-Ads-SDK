//
//  ViewController.m
//  SampleOffline
//
//  Created by Julien Stoeffler on 14/03/12.
//  Copyright (c) 2012 Smart AdServer. All rights reserved.
//

#import "ViewController.h"

@implementation ViewController
@synthesize offlineStartupInterstitial = _offlineStartupInterstitial;
@synthesize banner = _banner;


// The banner can not prefecth ads for offline delivery.
- (void)loadBanner {
    if (_banner) {
        [self.banner removeFromSuperview];
        self.banner = nil;
    }
    [self.banner loadFormatId:12161  pageId:@"240851" master:NO target:nil];
    [self.view sendSubviewToBack:self.banner];
}

- (void)loadInterstitial {
    if (_offlineStartupInterstitial) {
        [self.offlineStartupInterstitial dismiss];
        self.offlineStartupInterstitial= nil;
    }
    // We use the dedicated offline loading method. This will
    // - Check if an ad is already on the disk
    // - Display it if yes, fail if not
    // - Download an ad from the server and store it on the disk
    
    [self.offlineStartupInterstitial prefetchFormatId:12160 pageId:@"240851" master:YES target:nil];
    
}

- (SASBannerView *)banner {
    if(!_banner) {
        CGFloat height = 50.0;
        CGFloat width = UIInterfaceOrientationIsPortrait([[UIApplication sharedApplication]statusBarOrientation]) ?  320.0 : 480.0;
        
        _banner = [[SASBannerView alloc] initWithFrame:CGRectMake(.0, .0, width, height) loader:SmartAdServerViewLoaderActivityIndicatorStyleBlack];
        _banner.unlimited = YES;
        _banner.autoresizingMask = UIViewAutoresizingFlexibleWidth;
        _banner.delegate = self;
        [self.view addSubview:_banner];
    }
    
    return _banner;
}


- (SASInterstitialView *)offlineStartupInterstitial {
    if (!_offlineStartupInterstitial) {
        CGFloat width = UIInterfaceOrientationIsPortrait([[UIApplication sharedApplication]statusBarOrientation]) ?  320.0 : 480.0;
        CGFloat height = UIInterfaceOrientationIsPortrait([[UIApplication sharedApplication]statusBarOrientation]) ?  460.0 : 300.0;
        
        
        _offlineStartupInterstitial = [[SASInterstitialView alloc] initWithFrame:CGRectMake(.0, .0, width, height) loader:SmartAdServerViewLoaderLaunchImage];
        _offlineStartupInterstitial.unlimited = NO;
        _offlineStartupInterstitial.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
        _offlineStartupInterstitial.delegate = self;
        [self.view addSubview:_offlineStartupInterstitial];
    }
    
    return _offlineStartupInterstitial;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self loadBanner];
	// Do any additional setup after loading the view, typically from a nib.
}


- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return YES;
}



@end
