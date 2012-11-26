//
//  TravelViewController.m
//  Sample
//
//  Created by Julien Stoeffler on 11/07/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "TravelViewController.h"


@implementation TravelViewController
@synthesize travel = _travel;

- (void)dealloc {
    // IMPORTANT : Not setting the delegate to nil can cause your app to crash, because the Ad View can call your object, for example if the ad fails to download after your object is released.
    self.travel.delegate = nil;
    self.travel = nil;
}


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
	
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.title = @"Travel";
    }
    return self;
}

#pragma mark - View lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // We remove the navigation bar, to display a big ad
    [self.navigationController setNavigationBarHidden:YES animated:YES];
    
    // We check if the interstitial exists
    if (!_travel) {
        float height = .0;
        
        // We can't get directly the available height on our view because it's a UITableView, but we know it's height depending on the orientation. The status bar's orientation is a good way to figure out the real device orientation.
        if (UIInterfaceOrientationIsPortrait([UIApplication sharedApplication].statusBarOrientation ))
            height = 460.0;
        else
            height = 300.0;
        
        // We create the fullscreen ad view with a white activity indicator as the loader. This loader is usually not displayed if the user has a wifi connection because the ad loading is too fast.
        _travel = [[SmartAdServerView alloc] initWithFrame:CGRectMake(0, 0, self.view.frame.size.width, height) loader:SmartAdServerViewLoaderActivityIndicatorStyleWhite];
    }
    
    // Important : a fullscreen ad view should'nt be unlimited, because it is removed after a defined duration, a tap on the skip button, or at the end of a video. We don't want to have it stay in place forever and to block the application.
    self.travel.unlimited = NO;
    
    // We want the interstitial to stay full screen on the device rotation, or on the superview resizing.
    self.travel.autoresizingMask = UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleWidth;
    
    // We set ourself as the delegate, to support clicks, and to be warned by the different events such as when it disappears, if it fails,... The delegate is not retained
    self.travel.delegate = self;
    
    // We ask the view to call an ad, we set a 2 seconds timeout, in case the user has a bad connection.
    [self.travel loadFormatId:12192 pageId:@"185330" master:YES target:nil timeout:2.0];
    
    // We add the view to the view hierarchy.
    [self.view addSubview:self.travel];
}


- (void)sasViewDidDisappear:(SmartAdServerView *)adView {
	
    if(adView == self.travel) {
        [self.navigationController setNavigationBarHidden:NO animated:YES];
        
        //We don't need to keep the reference to the ad anymore
        self.travel = nil;
    }
}


- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return YES;
}

@end