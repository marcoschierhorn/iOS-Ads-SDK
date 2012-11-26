//
//  SASBannerView.h
//  SmartAdServer
//
//  Created by Clémence Laurent on 09/03/12.
//  Copyright (c) 2012 Smart AdServer. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SmartAdServerView.h"
#import "SmartAdServerAd.h"
#import "SmartAdServerViewDelegate.h"

/** The SASBannerView class provides a wrapper view that displays an ad banner to the user.
 
 When the user taps a SASBannerView instance, the view triggers an action programmed into the advertisement.
 For example, an advertisement might, present a modal advertisement, show a movie, or launch a third party application (Safari, the App Store, YouTube...).
 Your application is notified by the **SmartAdServerViewDelegate protocol** methods which are called during the ad's lifecycle.
 You can interact with the view by 
 
 - refreshing it : refresh
 - displaying a local **SmartAdServerAd** created by your application : displayThisAd:
 
 The delegate of a SASBannerView object must adopt the SmartAdServerViewDelegate protocol.
 The protocol methods allow the delegate to be aware of the ad-related events.
 You can use it to handle your app's or the ad's (the SASBannerView instance) behavior like adapting your viewController's view size depending on the ad being displayed or not.
 
 */

@interface SASBannerView : SmartAdServerView


///-----------------------------------
/// @name Ad banner view properties
///-----------------------------------


/** The object that acts as the delegate of the receiving ad banner view.
 
 The delegate must adopt the SmartAdServerViewDelegate protocol.
 This must be the view controller actually controlling the view displaying the ad, not a view controller just designed to handle the ad logic.
 
 @bug *Important* : the delegate is not retained by the SASBannerView instance, so you need to set the ad's delegate to nil before the delegate is killed.
 
 */

@property (nonatomic, assign) UIViewController <SmartAdServerViewDelegate> *delegate;

/** Whether the ad banner should expand from the top to the bottom.
 
 On a banner placement, "expand" formats can be loaded. 
 This will cause the view to resize itself in an animated way. If you place your banner at the top of your view, set this property to YES, if you place it at the bottom, set it to NO.
 
 */

@property (assign) BOOL expandsFromTop;


///-----------------------------------
/// @name Creating an ad banner view
///-----------------------------------


/** Initializes and returns a SASBannerView object for the given frame
 
 @param frame A rectangle specifying the initial location and size of the ad banner view in its superview's coordinates. The frame of the table view changes when it loads an expand format. 
 
 */

- (id)initWithFrame:(CGRect)frame;

/** Initializes and returns a SASBannerView object for the given frame, and optionally sets a loader on it.
 
 @param frame A rectangle specifying the initial location and size of the ad banner view in its superview's coordinates. The frame of the table view changes when it loads an expand format. 
 @param loaderType A SmartAdServerViewLoader value that determines whether the view should display a loader or not while downloading the ad.
 
 */

- (id)initWithFrame:(CGRect)frame loader:(SmartAdServerViewLoader)loaderType;


///-----------------------------------
/// @name Loading a Banner
///-----------------------------------


/** Fetches a banner from Smart AdServer.
 
 Call this method after initializing your SASBannerView object to load the appropriate SmartAdServerAd object from the server.
 
 @param formatId The format ID in the Smart AdServer manage interface.
 @param pageId The page ID in the Smart AdServer manage interface.
 @param isMaster The master flag. If this is YES, the a Page view will be counted. This should have the YES value for the first ad on the page, and NO for the others (if you have more than one ad on the same page).
 @param target If you specified targets in the Smart AdServer manage interface, you can send it here to target your advertisement. 
 
 */

- (void)loadFormatId:(NSInteger)formatId
			  pageId:(NSString *)pageId
			  master:(BOOL)isMaster
			  target:(NSString *)target;

/** Fetches a banner from Smart AdServer with a specified timeout.
 
 Call this method after initializing your SASBannerView object with an initWithFrame: to load the appropriate SmartAdServerAd object from the server.
 If the timeout expires, the SASBannerView will fail to prefetch and notify the delegate. If an ad is available in the cache, it will display it even in offline mode.
 
 @param formatId The format ID in the Smart AdServer manage interface.
 @param pageId The page ID in the Smart AdServer manage interface.
 @param isMaster The master flag. If this is YES, the a Page view will be counted. This should have the YES value for the first ad on the page, and NO for the others (if you have more than one ad on the same page).
 @param target If you specified targets in the Smart AdServer manage interface, you can send it here to target your advertisement.
 @param timeout The time givent to the ad banner view to download the ad data. After this time, the ad download will fail,  call [SmartAdServerViewDelegate sasViewDidFailToLoadAd:], and be dismissed if not unlimited. A negative value will disable the timeout.
 
 */

- (void)loadFormatId:(NSInteger)formatId
			  pageId:(NSString *)pageId
			  master:(BOOL)isMaster
			  target:(NSString *)target 
			 timeout:(float)timeout;

/** Updates the banner data.
 
 Call this method to fetch a new banner from Smart AdServer with the same settings you provided with loadFormatId:pageId:master:target:
 This will set the master flag to NO, because you probably don't want to count a new page view.
 
 */

- (void)refresh;


///-------------------------------------------
/// @name Interacting with the ad banner view
///-------------------------------------------


/** Gives an ad for the banner view to display.
 
 Use this method if you want your application to provide a local SmartAdServerAd (usually in case of error).
 
 @param adBanner A SmartAdServerAd created by your application. This object is retained by the ad banner view.
 
 */

- (void)displayThisAd:(SmartAdServerAd *)adBanner;

@end
