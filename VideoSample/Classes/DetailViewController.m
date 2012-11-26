//
//  DetailViewController.m
//  PreRoll
//
//  Created by jstoeffler on 17/05/11.
//  Copyright 2011 Smart AdServer. All rights reserved.
//

//***********************************************************************
//                                                                     //                  
//                          !!! WARNING !!!                            //
//                                                                     // 
//  This code sample assumes that particular choices have been made.   //
//  Those choices may not suit your requirements (you don't always     //
//  want a loader, for example), o please make sure you understand     //
//  the parameters you use, test the ad display, with good, bad,       //
//  and no connection, and no ad to deliver, before submitting your    //
//  application to the App Store.                                      //
//                                                                     //                  
//***********************************************************************


#import "DetailViewController.h"
#import "RootViewController.h"

#define kFormatID 12202
#define kPageID @"185846"


@implementation DetailViewController

@synthesize toolbar = _toolbar, containerView = _containerView, preRollInterstitial = _preRollInterstitial, popoverController;

- (void)dealloc {
    self.preRollInterstitial.delegate = nil;
    self.preRollInterstitial = nil;
    
    [popoverController release];
    [super dealloc];
}

#pragma mark - SmartAdServerViewIntegration

// This method is called by the RootViewController when the user taps an item in the menu (Sports/News/Movies)
- (void)selectIndex:(NSInteger)index {
	
    // We remove the ad, in case it was already there.
    self.preRollInterstitial.delegate = nil;
    [self.preRollInterstitial dismiss];
    self.preRollInterstitial = nil;
    
    // We remove the movie, in case it was playing.
    [_theMovie pause];
    [_theMovie.view removeFromSuperview];

    // We keep the selected choice in memory, to launch it when the ad will be dismissed
	_index = index;

    // iOS can't handle more than one instance of MPMoviePlayerController, so we have to "wait" (0.1s) before we add the ad, to avoid conflicts
	[NSTimer scheduledTimerWithTimeInterval:0.1 target:self selector:@selector(addPreRoll) userInfo:nil repeats:NO];
    
    if (self.popoverController != nil) {
        [self.popoverController dismissPopoverAnimated:YES];
    }
}


- (void)addPreRoll {   
    // We create the view with the same frame and auto-resizing mask as the "Container" view created in the nib
    // This container is not necessary, it's just to have a reference view that will have the same size and behavior as the Pre-Roll and the video player.
	_preRollInterstitial = [[SASInterstitialView alloc] initWithFrame:self.containerView.frame loader:SmartAdServerViewLoaderActivityIndicatorStyleBlack];
    
    // We load the ad with a 5 seconds timeout
	[self.preRollInterstitial loadFormatId:kFormatID pageId:kPageID master:YES target:@"" timeout:5.0];
    
	self.preRollInterstitial.delegate = self;			
	self.preRollInterstitial.autoresizingMask = self.containerView.autoresizingMask;
	[self.view addSubview:self.preRollInterstitial];
    
    // The user didn't click on the ad at this moment, so we set the value to NO
    _adHasModalView = NO;
}

#pragma mark - SmartAdServerView Delegate callbacks

- (void)sasViewWillPresentModalView:(SmartAdServerView *)adView {
	
    // The user clicked on the ad, and the post-click modal view will be displayed
    // We remember this, because we will wait until this modal view is dismissed before launching the movie.
    _adHasModalView = YES;
}


- (void)sasViewDidDisappear:(SmartAdServerView *)adView {
	
    if (!_adHasModalView) {
        // Get rid of the ad
        self.preRollInterstitial.delegate = nil;
        self.preRollInterstitial = nil;
        
        // iOS can't handle more than one instance of MPMoviePlayerController, so we have to "wait" (0.1s) before we add the ad, to avoid conflicts
        [NSTimer scheduledTimerWithTimeInterval:0.1 target:self selector:@selector(playMovie) userInfo:nil repeats:NO];
    }
}


- (void)sasViewWillDismissModalView:(SmartAdServerView *)adView {
	
    self.preRollInterstitial.delegate = nil;
    self.preRollInterstitial = nil;
    
    // iOS can't handle more than one instance of MPMoviePlayerController, so we have to "wait" (0.1s) before we add the ad, to avoid conflicts
    [NSTimer scheduledTimerWithTimeInterval:0.1 target:self selector:@selector(playMovie) userInfo:nil repeats:NO];
}

#pragma mark - Managing the detail item

- (void)playMovie {
	
	NSString *path = [[NSBundle mainBundle] pathForResource:[NSString stringWithFormat:@"%d",_index] ofType:@"mp4"];
	NSURL *url = [NSURL fileURLWithPath:path isDirectory:NO];

	if (!_theMovie) {        
        _theMovie = [[MPMoviePlayerController alloc] initWithContentURL:url];
        
        // ==============================================================================================================================
        // = IMPORTANT : The useAudioApplicationAudioSession property must be set to "NO" for ALL the video players in your application =
        // ==============================================================================================================================
        // = If you don't do this, there is a rare, but critical bug that will prevent ALL THE VIDEO PLAYERS ON THE DEVICE              =
        // = (including YouTube and other applications)                                                                                 =
        // = For more information on this iOS bug, please check this topic on StackOverflow :                                           =
        // = http://stackoverflow.com/questions/3000969/ipad-mpmovieplayercontroller-video-loads-but-automatically-pauses-when-played   =
        // ==============================================================================================================================
        _theMovie.useApplicationAudioSession = NO;
	}
	else {
		[_theMovie setContentURL:url];
	}

	[_theMovie.view setFrame:self.containerView.frame];
	_theMovie.view.autoresizingMask = self.containerView.autoresizingMask;

	[self.view addSubview:_theMovie.view];
	[_theMovie play];
}

#pragma mark - Split view support

- (void)splitViewController: (UISplitViewController *)svc willHideViewController:(UIViewController *)aViewController withBarButtonItem:(UIBarButtonItem *)barButtonItem forPopoverController: (UIPopoverController*)pc {
    
    barButtonItem.title = @"Menu";
    NSMutableArray *items = [[self.toolbar items] mutableCopy];
    [items insertObject:barButtonItem atIndex:0];
    [self.toolbar setItems:items animated:YES];
    [items release];
    self.popoverController = pc;
}


- (void)splitViewController: (UISplitViewController *)svc willShowViewController:(UIViewController *)aViewController invalidatingBarButtonItem:(UIBarButtonItem *)barButtonItem {
    
    NSMutableArray *items = [[self.toolbar items] mutableCopy];
    [items removeObjectAtIndex:0];
    [self.toolbar setItems:items animated:YES];
    [items release];
    self.popoverController = nil;
}

#pragma mark - Rotation support

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return YES;
}

@end
