//
//  SmartAdServerView.h
//  SmartAdServer
//
//  Created by Julien Stoeffler on 17/02/11.
//  Copyright 2010 Smart AdServer. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>
#import "SmartAdServerViewDelegate.h"

#define SASV_DEFAULT_DURATION						10
#define SASV_MAX_EXPAND_HEIGHT						600
#define SASV_ENDTRANSITION_DURATION					0.5
#define SAS_SDK_VERSION	 @"3.2.2"

typedef enum {
	SmartAdServerViewFormatIntersticielStart,
	SmartAdServerViewFormatIntersticiel,				//	320x460	Full screen ad for a screen with statusbar without navBar either tabBar
	SmartAdServerViewFormatIntersticielNavBar,			//	320x416	Full screen ad for a screen with statusbar with navBar and without tabBar
	SmartAdServerViewFormatIntersticielTabBar,			//	320x411	Full screen ad for a screen with statusbar without navBar and with tabBar
	SmartAdServerViewFormatIntersticielNavBarTabBar,	//	320x367	Full screen ad for a screen with statusbar with navBar and tabBar
	SmartAdServerViewFormatBanner,						//	320x50/20	Banner ad. This type of ad will not
	
	// iPad
	SmartAdServerViewFormatIntersticieliPadStart,			//	768x1024	Full screen ad for a screen with statusbar without navBar either tabBar and Default.png during the downloadind delay
	SmartAdServerViewFormatIntersticieliPad,				//	768x1024	Full screen ad for a screen with statusbar without navBar either tabBar
	SmartAdServerViewFormatIntersticielNavBariPad,			//	768x960	Full screen ad for a screen with statusbar with navBar and without tabBar
	SmartAdServerViewFormatIntersticielTabBariPad,			//	768x955	Full screen ad for a screen with statusbar without navBar and with tabBar
	SmartAdServerViewFormatIntersticielNavBarTabBariPad,	//	768x911	Full screen ad for a screen with statusbar with navBar and tabBar
	SmartAdServerViewFormatBanneriPad,						//	768x90/20	Banner ad. This type of ad will not
} SmartAdServerViewFormat;

typedef enum {
    SmartAdServerViewLoaderNone,
    SmartAdServerViewLoaderLaunchImage,
    SmartAdServerViewLoaderActivityIndicatorStyleBlack,
    SmartAdServerViewLoaderActivityIndicatorStyleWhite,
    SmartAdServerViewLoaderActivityIndicatorStyleTransparent
} SmartAdServerViewLoader;

@protocol SASAdDownloaderDelegate
@required
- (void)SASAdDownloaderDelegateDidFinish:(SmartAdServerAd *)ad;
- (void)SASAdDownloaderDelegateDidFailedWithError:(NSError *)er;
@end

@protocol SASMoviePlayerManagerDelegate <NSObject>
- (void)videoReadyToDisplay;
- (void)videoClicked;
@end

@class SASApi, ORMMAController, SASLoaderView, SASMoviePlayerManager, SASMRAIDBridge, SASAdViewController;

/** The SmartAdServerView class provides a wrapper view that displays advertisements to the user.
 
 When the user taps a SmartAdServerView, the view triggers an action programmed into the advertisement.
 For example, an advertisement might, present a modal advertisement, show a movie, or launch a third party application (Safari, the App Store, YouTube...).
 Your application is notified by the **SmartAdServerViewDelegate protocol** methods which are called during the ad's lifecycle.
 You can interact with the view by 
 
 - refreshing it : refresh 
 - displaying a local **SmartAdServerAd** created by your application : displayThisAd:
 - removing it : dismiss
 
 
 The delegate of a SmartAdServerView object must adopt the SmartAdServerViewDelegate protocol.
 The protocol methods allow the delegate to be aware of the ad-related events.
 You can use it to handle your app's or the ad's (the SmartAdServerView instance) behavior like adapting your viewController's view size depending on the ad being displayed or not.
 
 */

@interface SmartAdServerView : UIView <SASAdDownloaderDelegate, UIWebViewDelegate, SASMoviePlayerManagerDelegate> {
        SASLoaderView *_loaderView;
        BOOL _unlimited;
        BOOL _portraitCreativeLoaded;
        BOOL _landscapeCreativeLoaded;
        BOOL _statusBarWasHidden;
        BOOL _expandsFromTop;
        
        UIViewController <SmartAdServerViewDelegate> *_delegate;
        
        NSInteger _formatId;
        NSString *_pageId;
        NSString *_target;
        CGFloat _expandedHeight;
        CGFloat _userHeight;
        
        //UIButton *_clickUrlButton;
        SmartAdServerAd *ad;
        UIWebView *_webView;
        SASMRAIDBridge *_mraidBridge;
        SASAdViewController *_adViewController;
        NSTimer *durationTimer;
        NSTimer *progressTimer;
        ORMMAController *ormma;
        UILabel *progressLabel;
    UIInterfaceOrientation _loadedOrientation;
    BOOL _durationTimerFired;
    BOOL _isPlayingFullscreen;
}

///-----------------------------------
/// @name Global Settings
///-----------------------------------


/** Sets your app's Site ID.
 
 This method should be called before initializing any SmartAdServerView object.
 It's only necessary to call it once in your App's life cycle.
 
 @param siteId Your Site ID in the Smart AdServer manage interface
 
 */

+ (void)setSiteID:(NSInteger)siteId;
 
/** Set the base URL for the ad call
 
If you need the call to be done on a different domain than ours, use this method to specify it (if you use a CNAME for example).
 
    [SmartAdServerView setBaseUrl:@"http://smartadserver.example.com"];
 
@param theBaseUrl The base url of the website redirecting to the ad server (without the ending slash).
 
 */

+ (void)setBaseUrl:(NSString *)theBaseUrl;


/** Specify the user's coordinate
 
 Use this method if you want to provide geo-targeted advertisement.
 For example in your CLLoationManagerDelegate :
 
 
    -(void)locationManager:(CLLocationManager *)m didUpdateToLocation:(CLLocation *)newLocation fromLocation:(CLLocation *)old
    {
        [SmartAdServerView setCoordinate:newLocation.coordinate];
    }
 
 If used, this method should be called as often as possible in order to provide up to date geo-targeting.
 
 @warning *Important:* your application can be rejected by Apple if you use user&rsquo;s location *only* for advertising.
 Your application needs to have a feature (other than advertising) using geo-location in order to be allowed to ask for user&rsquo;s position.
 
 @param coordinate The user's position
 */



+ (void)setCoordinate:(CLLocationCoordinate2D)coordinate;

/** Enable test mode
 
 Calling this method will enable the test mode that displays a default ad that always deliver.
 This allow easier development, as the ad provided by 
 
 - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    
 [SmartAdServerView enableLogging];
 }
 
 
 */

+ (void)enableTestMode;


/** Enable logging mode
 
 Calling this method will enable warning and error logs in your console.
 You may want to do this if you have problems in the integration, to see where the issue is.
 Letting this in production is not optimal, as logging consumes resources.
 
    - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    
        [SmartAdServerView enableLogging];
    }
 
 
 */

+ (void)enableLogging;



/** Enable the hashed mode for the UDID in the ad requests
 
 Calling this method will cause the UDID to be hashed by the SDK when requesting an advertisement.
 
 @bug By hashing the UDID, Smart AdServer will not get the original value, so it can prevent from interfacing with other partners and applications. 
 
 */

+ (void)enableIdentifierHashing;



///-----------------------------------
/// @name Creating ad views
///-----------------------------------

/** Initializes and returns a SmartAdServerView object for the given frame
 
 @param fr A rectangle specifying the initial location and size of the ad view in its superview's coordinates. The frame of the table view changes when it loads an expand format. 
 
 */


- (id)initWithFrame:(CGRect)frame;

/** Initializes and returns a SmartAdServerView object for the given frame, and optionally sets a loader on it.
 
 @param fr A rectangle specifying the initial location and size of the ad view in its superview's coordinates. The frame of the table view changes when it loads an expand format. 
 @param loaderType A SmartAdServerViewLoader value that determines whether the view should display a loader or not while downloading the ad.
 
 */


- (id)initWithFrame:(CGRect)frame loader:(SmartAdServerViewLoader)loaderType;

/** Initializes and returns a SmartAdServerView object for the given frame, and optionally sets a loader on it and hides the status bar.
 
 You can use this method to display interstitials in full screen mode, even if you have a status bar. The ad view will remove the status bar, and replace it when the ad duration is over, or when the user dimisses the ad by taping on it, or on the skip button.
 
 @param fr A rectangle specifying the initial location and size of the ad view in its superview's coordinates. The frame of the table view changes when it loads an expand format. 
 @param loaderType A SmartAdServerViewLoader value that determines whether the view should display a loader or not while downloading the ad.
 @param hideStatusBar A boolean value indicating the SmartAdServerView object to auto hide the status bar if needed when the ad is displayed
 @warning Your application should support auto-resizing without the status bar. Some ads can have a transparent background, and if your application doesn't resize, the user will see a blank 20px frame on top of your app. 
 
 */

- (id)initWithFrame:(CGRect)frame loader:(SmartAdServerViewLoader)loaderType hideStatusBar:(BOOL)hideStatusBar;


//-----------------------------------
// @name Ad view properties
//-----------------------------------


/*  The object that acts as the delegate of the receiving ad view
 
 The delegate must adopt the SmartAdServerViewDelegate protocol.
 This must be the view controller actually controlling the view displaying the ad, not a view controller just designed to handle the ad logic.

 @bug *Important* : the delegate is not retained by the SmartAdServerView, so you need to set the ad's delegate to nil before the delegate is killed
 
 */
@property (nonatomic, assign) UIViewController <SmartAdServerViewDelegate> *delegate;

/*  whether the ad should stay in place (typically a banner) or be removed after a certain duration (typically an interstitial).
  
 */

@property (assign) BOOL unlimited;

/* whether the ad should expand from the top to bottom.
 
 On a banner placement, "expand" formats can be loaded. 
 This will cause the view to resize itself in an animated way. If you place your banner at the top of your view, set this property to YES, if you place it at the bottom, set it to NO.
 
 */

@property (assign) BOOL expandsFromTop;

/* the reference to the SASMediaPlayerManager when a native video layer is displayed
 
 This reference is nil when the currently displayed ad is not a video layer.
 */
@property (nonatomic, retain) SASMoviePlayerManager *moviePlayerManager;

///-----------------------------------
/// @name Loading ad data
///-----------------------------------


/* Fetches an ad from Smart AdServer
 
 Call this method after initializing your SmartAdServerView object to load the appropriate SmartAdServerAd object from the server.
 
 @param formatId The format ID in the Smart AdServer manage interface
 @param pageId The page ID in the Smart AdServer manage interface
 @param isMaster The master flag. If this is YES, the a Page view will be counted. This should have the YES value for the first ad on the page, and NO for the others (if you have more than one ad on the same page)
 @param target If you specified targets in the Smart AdServer manage interface, you can send it here to target your advertisement. 
 
 */

- (void)loadFormatId:(NSInteger)formatId
			  pageId:(NSString *)pageId
			  master:(BOOL)isMaster
			  target:(NSString *)target;

/* Fetches an ad from Smart AdServer with a specified timeout
 
 Call this method after initializing your SmartAdServerView object with an initWithFrame: to load the appropriate SmartAdServerAd object from the server.
 If the timeout expires, the SmartAdServerView will fail to prefetch and notify the delegate. If an ad is available in the cache, it will display it even in offline mode.
 
 @param formatId The format ID in the Smart AdServer manage interface
 @param pageId The page ID in the Smart AdServer manage interface
 @param isMaster The master flag. If this is YES, the a Page view will be counted. This should have the YES value for the first ad on the page, and NO for the others (if you have more than one ad on the same page)
 @param target If you specified targets in the Smart AdServer manage interface, you can send it here to target your advertisement.
 @param timeout The time givent to the ad view to download the ad data. After this time, the ad download will fail,  call [SmartAdServerViewDelegate sasViewDidFailToLoadAd:], and be dismissed if not unlimited. A negative value will disable the timeout.

 */

- (void)loadFormatId:(NSInteger)formatId
			  pageId:(NSString *)pageId
			  master:(BOOL)isMaster
			  target:(NSString *)target 
			 timeout:(float)timeout;

/* Fetches an ad from Smart AdServer cache in offline or online mode
 
 Call this method after initializing your SmartAdServerView object with an initWithFrame: to load the appropriate SmartAdServerAd object from the server and display the previously prefetched ad.
 The SmartAdServerView will fail, and notify the delegate if the timeout expires.
 
 @param formatId The format ID in the Smart AdServer manage interface
 @param pageId The page ID in the Smart AdServer manage interface
 @param isMaster The master flag. If this is YES, the a Page view will be counted. This should have the YES value for the first ad on the page, and NO for the others (if you have more than one ad on the same page)
 @param target If you specified targets in the Smart AdServer manage interface, you can send it here to target your advertisement.
 @param prefetch whether the format should prefetch an ad before displaying it. This means that the display will fail until an ad has been stored on the disk.
 
 */

- (void)loadFormatId:(NSInteger)formatId
			  pageId:(NSString *)pageId
			  master:(BOOL)isMaster
			  target:(NSString *)target 
			prefetch:(BOOL)shouldPrefetch;


/* Updates the ad data
 
 Call this method to fetch a new ad from Smart AdServer with the same settings you provided with loadFormatId:pageId:master:target:
 This will set the master flag to NO, because you probably don't want to count a new page view.
 
 */

- (void)refresh;

/* Initialise the view, and load the ad
 
 Initializes and returns a SmartAdServerView object withe one of the pre-defined SmartAdServerViewFormat, and loads the appropriate ad. 
 
 
 @param form One of the predefined SmartAdServerViewFormat
 @param formatId The Format ID in the Smart AdServer manage interface
 @param pageId The Page ID in the Smart AdServer manage interface
 @param isMaster The master flag. If this is YES, the a Page view will be counted. This should have the YES value for the first ad on the page, and NO for the others (if you have more than one ad on the same page)
 @param target If you specified targets in the Smart AdServer manage interface, you can send it here to target your advertisement. 
 */
/*
- (id)initWithFormat:(SmartAdServerViewFormat)form 
			formatId:(NSInteger)formatId 
              pageId:(NSString *)pageId 
              master:(BOOL)isMaster 
              target:(NSString *)target;

*/


//-----------------------------------
// @name Interacting with the ad view
//-----------------------------------

- (void)displayThisAd:(SmartAdServerAd *)adv;
- (void)dismiss;


/** Remove the video layer
 
 Call this method to remove the video layer from its subview
 */
- (void)dismissVideoLayer;



@end
