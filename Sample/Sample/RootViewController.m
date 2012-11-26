//
//  RootViewController.m
//  Sample
//
//  Created by Julien Stoeffler on 07/07/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "RootViewController.h"
#import "ToasterViewController.h"
#import "TravelViewController.h"

#define kBannerFormatID 12161
#define	kInterstitialFormatID 12167
#define kPageID @"185330"


@implementation RootViewController
@synthesize topBanner = _topBanner;
@synthesize interstitial = _interstitial;

#pragma mark - Object lifecycle

- (void)dealloc {
    // We clean everything
    // Setting the delegate to nil is very important, because if you don't do it, the ad can still call your delegate, even if it's been deallocated (the delegate is not retained by the ad).
    self.topBanner.delegate = nil;
    
    // Free the memory
    self.topBanner = nil;
    self.interstitial.delegate = nil;
    self.interstitial = nil;
    
    [super dealloc];
}


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
	
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        self.title = @"Banner + Interstitial";
    }
    return self;
}

#pragma mark - View lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // We create the banner immediately after the view did load
    [self createTopBanner];
}


- (void)createTopBanner {
    // We check if the banner exists

    if (!_topBanner) {
        // We create the banner with a white activity indicator as the loader. This loader is usually not visible if the user has a wifi connection because the ad loading is too fast.
        // The standard recommended size for a banner is 53 pixels high, and full-width.
        _topBanner = [[SASBannerView alloc] initWithFrame:CGRectMake(0, 0, self.view.frame.size.width, 53) loader:SmartAdServerViewLoaderActivityIndicatorStyleWhite];
    }
	
    // In this example, we just display a simple banner. However, a trafic manager can program an expandable format on this placement.
    // In order to anticipate this, we specify that we want the expand ads to expand from the top.
    self.topBanner.expandsFromTop = YES;
    
    // We set ourself as the delegate, to support clicks, and to be warned by the different events such as if the ad download fails,...
    self.topBanner.delegate = self;
    
    // We ask the view to call an ad, without any timeout. We don't want a timeout in this case because the banner doesn't block the application, so it's not necessary to remove it when the conneciton is bad, we can wait.
    [self.topBanner loadFormatId:kBannerFormatID pageId:kPageID master:NO target:nil];
    
    // We could add the view to "self.view", but this would hide part of the content. If you work with tableview, it's an interesting option to set the banner as the tableview's  header view. If you work with a regular view, or if you want to have the ad always visible, you need prepare some place for it.
    self.tableView.tableHeaderView = self.topBanner;
}


- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
	
    // Many people get confused by this method. It is NOT called when the device is rotated. It can be called at unexpected time, and it's purpose is just to check wether rotations are allowed, not to let you know that something is happening.
    // Check the UIViewController Class Reference for more information.

    return YES;
}

#pragma mark - SmartAdServerView delegate methods

- (void)sasView:(SmartAdServerView *)adView didDownloadAdInfo:(SmartAdServerAd *)adInfo {
    NSLog(@"Did download ad info");
}


- (void)sasViewDidLoadAd:(SmartAdServerView *)adView {
    NSLog(@"Ad is loaded and will display");
}


- (void)sasViewDidDisappear:(SmartAdServerView *)adView {
	
	if(adView == self.interstitial) {
        [self.navigationController setNavigationBarHidden:NO animated:YES];
        
        //We don't need to keep the reference to the ad anymore
        self.interstitial = nil;
    }
    else if(adView != self.topBanner) {
        // If the ad isn't the top banner or the interstitial, then it is the startup interstitial that disappeared (see App Delegate to see how it is created).
        // We use this moment to create the interstitial.
        [self createInterstitial];
    }
}


- (void)createInterstitial {
    // We remove the navigation bar, to display a big interstitial
    [self.navigationController setNavigationBarHidden:YES animated:YES];
    
    // We check if the interstitial exists
    if (!_interstitial) {
        float height = .0;
        
        // We can't get directly the available height on our view because it's a UITableView, but we know it's height depending on the orientation. The status bar's orientation is a good way to figure out the real device orientation.
        if (UIInterfaceOrientationIsPortrait([UIApplication sharedApplication].statusBarOrientation))
            height = 460.0;
        else
            height = 300.0;
        
        // We create the interstitial with a black activity indicator as the loader. This loader is usually not displayed if the user has a wifi connection because the ad loading is too fast.
        _interstitial = [[SASInterstitialView alloc] initWithFrame:CGRectMake(0, 0, self.view.frame.size.width, height) loader:SmartAdServerViewLoaderActivityIndicatorStyleBlack];
    }
	
    // We set ourself as the delegate, to support clicks, and to be warned by the different events such as when it disappears, if it fails,... The delegate is not retained
    self.interstitial.delegate = self;
    
    // We ask the view to call an ad, we set a 2 seconds timeout, in case the user has a bad connection.
    [self.interstitial loadFormatId:kInterstitialFormatID pageId:kPageID master:YES target:nil timeout:2.0];
    
    // We add the view to the view hierarchy.
    [self.view addSubview:self.interstitial];
}


- (void)sasViewDidFailToLoadAd:(SmartAdServerView *)adView {
	
    if(adView == self.topBanner) {
        // Here you can customize what you want to happen in case of failure.
        // In this case, we simply remove the view.
        [self.topBanner removeFromSuperview]; 
    }
    // We don't need to do this for the interstitial, because if "unlimited" is set to "NO", it will be automatically removed.
}

#pragma mark - UITableView related Methods

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [self.navigationController setNavigationBarHidden:NO animated:YES];
    
	if(0 == indexPath.row) {
        ToasterViewController *detailViewController = [[ToasterViewController alloc] initWithNibName:@"ToasterViewController" bundle:nil];
        [self.navigationController pushViewController:detailViewController animated:YES];
    }
    else {
        TravelViewController *detailViewController = [[TravelViewController alloc] initWithNibName:@"TravelViewController" bundle:nil];
        [self.navigationController pushViewController:detailViewController animated:YES];
    }
}


- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}


- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return 2;
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *CellIdentifier = @"Cell";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
        [cell autorelease];
    }
    if(indexPath.row == 0)
        cell.textLabel.text = @"Toaster";
    else
        cell.textLabel.text = @"Travel";
	
    return cell;
}

@end
