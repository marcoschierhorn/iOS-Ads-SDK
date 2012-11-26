//
//  DetailViewController.h
//  PreRoll
//
//  Created by jstoeffler on 17/05/11.
//  Copyright 2011 Smart AdServer. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MediaPlayer/MediaPlayer.h>
#import "SASInterstitialView.h"
#import "SmartAdServerViewDelegate.h"


@interface DetailViewController : UIViewController <SmartAdServerViewDelegate, UIPopoverControllerDelegate, UISplitViewControllerDelegate> {
	MPMoviePlayerController *_theMovie;
	NSInteger _index;
    // To launch the video, we wait until the ad is dismissed
    // But if the user clicked on the ad, we want to wait until the post-click modal view is dismissed instead.
    BOOL _adHasModalView;
}

@property (nonatomic, retain) IBOutlet UIToolbar *toolbar;
@property (nonatomic, retain) IBOutlet UIView *containerView;
@property (nonatomic, retain) SASInterstitialView *preRollInterstitial;
@property (nonatomic, retain) UIPopoverController *popoverController;

- (void)playMovie;
- (void)selectIndex:(NSInteger)index;
- (void)addPreRoll;

@end
