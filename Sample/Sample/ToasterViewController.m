//
//  DetailViewController.m
//  Sample
//
//  Created by Julien Stoeffler on 08/07/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "ToasterViewController.h"


@implementation ToasterViewController
@synthesize toasterBanner = _toasterBanner;

#pragma mark - Object lifecycle

- (void)dealloc {
    // IMPORTANT : Not setting the delegate to nil can cause your app to crash, because the Ad View can call your object, for example if the ad fails to download after your object is released.
    self.toasterBanner.delegate = nil;
    self.toasterBanner = nil;
}


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
	
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.title = @"Toaster";
    }
    return self;
}

#pragma mark - View lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];
    
    if (!_toasterBanner) {
        // We create a banner with the frame going to the bottom of the view 
        
        /* bottom toaster sample */
        
        _toasterBanner = [[SmartAdServerView alloc] initWithFrame:CGRectMake(0, self.view.frame.size.height - 53.0, self.view.frame.size.width, 53)];
        // Since the toaster is at the bottom of the view, we specify that we want it to expand from the bottom.
        self.toasterBanner.expandsFromTop = NO;
        
        /* end of bottom toaster sample */
        
        /* top toaster sample, comment bottom toaster sample to test this config */
        
        // _toasterBanner = [[SmartAdServerView alloc] initWithFrame:CGRectMake(0, 0,self.view.frame.size.width, 53)];
        // self.toasterBanner.expandsFromTop = YES;
        
        /* end of top toaster sample */
    }
    
    // Set an autoresizing mask to support rotation. A banner wants to fill the width of the screen. Since this one is at the bottom, we want to have a flexible top margin.
	self.toasterBanner.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleTopMargin;
	// self.toasterBanner.
	
    // Load the ad format, Master is YES, because it's the only ad on the page.
    [self.toasterBanner loadFormatId:12175 pageId:@"185330" master:YES target:nil];
    
    [self.view addSubview:self.toasterBanner];
    
    //Set self as the delegate, to handle clicks and to be notified of the events.
    self.toasterBanner.delegate = self;
}

- (void)sasViewDidFailToLoadAd:(SmartAdServerView *)adView {
	
    if (adView == self.toasterBanner) {
        //Kill the ad
        [adView removeFromSuperview];
        adView.delegate = nil;
        self.toasterBanner = nil;
    }
}


- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return YES;
}

@end
