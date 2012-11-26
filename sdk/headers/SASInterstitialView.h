//
//  SASInterstitialView.h
//  SmartAdServer
//
//  Created by Clémence Laurent on 09/03/12.
//  Copyright (c) 2012 Smart AdServer. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SmartAdServerView.h"
#import "SmartAdServerAd.h"
#import "SmartAdServerViewDelegate.h"

/** The SASInterstitialView class provides a wrapper view that displays an ad interstitial to the user.
 
 When the user taps a SASInterstitialView instance, the view triggers an action programmed into the advertisement.
 For example, an advertisement might, present a modal advertisement, show a movie, or launch a third party application (Safari, the App Store, YouTube...).
 Your application is notified by the **SmartAdServerViewDelegate protocol** methods which are called during the ad's lifecycle.
 You can interact with the view by 
 
 - displaying a local **SmartAdServerAd** created by your application : displayThisAd:
 - removing it : dismiss
 
 The delegate of a SASInterstitialView object must adopt the SmartAdServerViewDelegate protocol.
 The protocol methods allow the delegate to be aware of the ad-related events.
 You can use it to handle your app's or the ad's (the SASInterstitialView instance) behavior like adapting your viewController's view size depending on the ad being displayed or not.
 
 */

@interface SASInterstitialView : SmartAdServerView

///---------------------------------------
/// @name Ad interstitial view properties
///---------------------------------------


/**  The object that acts as the delegate of the receiving ad interstitial view.
 
 The delegate must adopt the SmartAdServerViewDelegate protocol.
 This must be the view controller actually controlling the view displaying the ad, not a view controller just designed to handle the ad logic.
 
 @bug *Important* : the delegate is not retained by the SASInterstitialView instance, so you need to set the ad's delegate to nil before the delegate is killed.
 
 */

@property (nonatomic, assign) UIViewController <SmartAdServerViewDelegate> *delegate;


///-----------------------------------------
/// @name Creating an ad insterstitial view
///-----------------------------------------


/** Initializes and returns a SASInterstitialView object for the given frame.
 
 @param frame A rectangle specifying the initial location and size of the ad interstitial view in its superview's coordinates. The frame of the table view changes when it loads an expand format. 
 
 */

- (id)initWithFrame:(CGRect)frame;

/** Initializes and returns a SASInterstitialView object for the given frame, and optionally sets a loader on it.
 
 @param frame A rectangle specifying the initial location and size of the ad interstitial view in its superview's coordinates. The frame of the table view changes when it loads an expand format. 
 @param loaderType A SmartAdServerViewLoader value that determines whether the view should display a loader or not while downloading the ad.
 
 */

- (id)initWithFrame:(CGRect)frame loader:(SmartAdServerViewLoader)loaderType;

/** Initializes and returns a SASInterstitialView object for the given frame, and optionally sets a loader on it and hides the status bar.
 
 You can use this method to display an interstitial in full screen mode, even if you have a status bar. The ad interstitial view will remove the status bar, and replace it when the ad duration is over, or when the user dimisses the ad by taping on it, or on the skip button.
 
 @param frame A rectangle specifying the initial location and size of the ad interstitial in its superview's coordinates. The frame of the table view changes when it loads an expand format. 
 @param loaderType A SmartAdServerViewLoader value that determines whether the view should display a loader or not while downloading the ad.
 @param hideStatusBar A boolean value indicating the SASInterstitialView object to auto hide the status bar if needed when the ad is displayed.
 @warning Your application should support auto-resizing without the status bar. Some ads can have a transparent background, and if your application doesn't resize, the user will see a blank 20px frame on top of your app. 
 
 */

- (id)initWithFrame:(CGRect)frame loader:(SmartAdServerViewLoader)loaderType hideStatusBar:(BOOL)hideStatusBar;


///-----------------------------------
/// @name Loading an Interstitial
///-----------------------------------


/** Fetches an interstitial from Smart AdServer.
 
 Call this method after initializing your SASInterstitialView object to load the appropriate SmartAdServerAd object from the server.
 
 @param formatId The format ID in the Smart AdServer manage interface.
 @param pageId The page ID in the Smart AdServer manage interface.
 @param isMaster The master flag. If this is YES, the a Page view will be counted. This should have the YES value for the first ad on the page, and NO for the others (if you have more than one ad on the same page).
 @param target If you specified targets in the Smart AdServer manage interface, you can send it here to target your advertisement. 
 
 */

- (void)loadFormatId:(NSInteger)formatId
			  pageId:(NSString *)pageId
			  master:(BOOL)isMaster
			  target:(NSString *)target;

/** Fetches an interstitial from Smart AdServer with a specified timeout.
 
 Call this method after initializing your SASInterstitialView object with an initWithFrame: to load the appropriate SmartAdServerAd object from the server.
 If the timeout expires, the SASInterstitialView will fail to prefetch and notify the delegate. If an ad is available in the cache, it will display it even in offline mode.
 
 @param formatId The format ID in the Smart AdServer manage interface.
 @param pageId The page ID in the Smart AdServer manage interface.
 @param isMaster The master flag. If this is YES, the a Page view will be counted. This should have the YES value for the first ad on the page, and NO for the others (if you have more than one ad on the same page).
 @param target If you specified targets in the Smart AdServer manage interface, you can send it here to target your advertisement.
 @param timeout The time givent to the ad interstitial view to download the ad data. After this time, the ad download will fail,  call [SmartAdServerViewDelegate sasViewDidFailToLoadAd:], and be dismissed if not unlimited. A negative value will disable the timeout.
 
 */

- (void)loadFormatId:(NSInteger)formatId
			  pageId:(NSString *)pageId
			  master:(BOOL)isMaster
			  target:(NSString *)target 
			 timeout:(float)timeout;

/** Prefetches an interstitial from Smart AdServer cache in offline or online mode.
 
 Call this method after initializing your SASInterstitialView object with an initWithFrame: to load the appropriate SmartAdServerAd object from the server and display the previously prefetched ad.
 The SASInterstitialView will fail, and notify the delegate if the timeout expires.
 
 @param formatId The format ID in the Smart AdServer manage interface.
 @param pageId The page ID in the Smart AdServer manage interface.
 @param isMaster The master flag. If this is YES, the a Page view will be counted. This should have the YES value for the first ad on the page, and NO for the others (if you have more than one ad on the same page).
 @param target If you specified targets in the Smart AdServer manage interface, you can send it here to target your advertisement.
 
 */

- (void)prefetchFormatId:(NSInteger)formatId pageId:(NSString *)pageId master:(BOOL)isMaster target:(NSString *)target;


///-------------------------------------------------
/// @name Interacting with the ad interstitial view
///-------------------------------------------------


/** Gives an ad for the interstitial view to display.
 
 Use this method if you want your application to provide a local SmartAdServerAd (usually in case of error).
 
 @param adInterstitial A SmartAdServerAd created by your application. This object is retained by the ad interstitial view.
 
 */

- (void)displayThisAd:(SmartAdServerAd *)adInterstitial;

/** Removes the ad interstitial view.
 
 Call this method to remove the advertisement from its subview.
 The view's disparition will be animated according to the advertiser's settings.
 
 @warning This method doesn't remove ads having their unlimited attribute set to YES. 
 
 */

- (void)dismiss;

@end
