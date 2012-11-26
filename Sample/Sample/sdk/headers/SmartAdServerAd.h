//
//  SmartAdServerAd.h
//  SmartAdServer
//
//  Created by Julien Stoeffler on 06/01/10.
//  Copyright 2010 Smart AdServer. All rights reserved.
//


/** 
A SmartAdServerAd object represent the ad data, as it has been programmed in the Smart AdServer interface
You can create one of those objects, if you need to display an offline ad : 
 
	SmartAdServerAd * ad = [[SmartAdServerAd alloc] init];
    ad.creativeURL = portraitUrl;
	ad.creativeLandscapeUrl = landscapeUrl;
	[banner displayThisAd:ad];
 */


#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>



typedef enum {
	SkipTopLeft,
	SkipTopRight,
	SkipBottomLeft,
	SkipBottomRight,
} SkipPosisiton;

typedef enum {
	CreativeTypeImage,
	CreativeTypeAudio,
	CreativeTypeVideo,
	CreativeTypeHtml,
} CreativeType;




@interface SmartAdServerAd : NSObject <NSCopying, NSCoding>

///--------------------
/// @name Ad properties 
///--------------------



/** The time during which your ad will stay in place
 
 The timer starts when the creative is loaded
 This value is not used for with a SmartAdServerView set to unlimited (banners, toasters,...)
 
 */

@property float duration;

/** The ad's background color
  
 */

@property (nonatomic, retain) UIColor *backgroundColor;

/** The creative displayed in portrait mode
 
 */

@property (nonatomic, retain) NSURL *creativeURL;

/** The creative displayed in portrait mode
 
 */

@property (nonatomic, retain) NSURL *creativeLandscapeUrl;

/** The URL called when the ad is clicked, for the ad action
 
 */

@property (nonatomic, retain) NSURL *redirectURL;

/** The URL called when the ad (landscape creative if exists) is clicked, for the ad action
 
 */
@property (nonatomic, retain) NSURL *redirectLandscapeURL;

/** The URL called when the ad is clicked, for statistics
 
 */

@property (nonatomic, retain) NSURL *countURL;

/** The URL called when the ad (landscape creative if exists) is clicked, for statistics
 
 */

@property (nonatomic, retain) NSURL *countLandscapeURL;

/** The impression pixel to count the number of impressions
 
 */

@property (nonatomic, retain) NSURL *impPixel;

/** The impression pixel in landscape mode, to count the number of impressions
 
 */

@property (nonatomic, retain) NSURL *impLandscapePixel;



/** The impression pixel to count the number of impressions
 
 */

@property (nonatomic, retain) NSArray *agencyPortraitPixels;

/** The impression pixel in landscape mode, to count the number of impressions
 
 */
@property (nonatomic, retain) NSArray *agencyLandscapePixels;

/** The text displayed on the "trigger" button of an expand ad
 
 */
@property (nonatomic, retain) NSString *text;

/** The color of the text displayed on the "trigger" button of an expand ad
 
 */

@property (nonatomic, retain) UIColor *textColor;
/** A boolean value which specifies whether it should be expanded when loaded 
 
 Only used if the ad is in expand format
 */
@property BOOL expandedAtInit;

/** A boolean value which specifies whether the ad is in expand format 
 
 Only used if the ad is in expand format (it's height changes with animated effect)
 
 */

@property BOOL expand;

/** A boolean value which specifies if the WebView displaying the ad's redirect URL has controls.   
 
 Those controls are "Previous/Next", "Safari" and "Back"

 */

@property BOOL navigationHasControls;

/** A boolean value which specifies whether the ad should expand from top 
 
 Only used if the ad is in expand format
 
 */
@property BOOL fromTop;

/** A boolean value which specifies whether the ad has a transparent background
 
 */

@property BOOL transparentBackground;

/** A boolean value which specifies whether the ad asks the user if he wants to quit the app when a third party app is called
 
 */

@property BOOL askConfirmationBeforeClosingApp;


/** A boolean value which specifies whether the video ad should auto-play 
 
 */

@property BOOL videoAutoPlay;

/** A boolean value which specifies whether the ad has a skip button 
 
 */

@property BOOL skip;

/** A boolean value which specifies whether the ad's will redirect to the App Store/YouTube/.. 
 
 */


@property BOOL redirectsToThirdParty;

/** The button's Skip Position
 
 */


@property SkipPosisiton skipPosition;


/** An integer specifying the ad's creative type (image, HTML) 
 
 */
@property CreativeType creativeType;

/** An HTML script to load in case of an HTML creative type
 
 */

@property (nonatomic, retain) NSString *creativeScript;


/** The URL to the HTML script to load in case of an HTML creative type
 
 */

@property (nonatomic, retain) NSURL *creativeScriptURL;


/** An HTML script to load in case of an HTML creative type
 
 */

@property (nonatomic, assign) BOOL isOffline;

/** The desired expanded height, in protrait orientation, for a toaster
 
  */

@property CGFloat expandedHeight;

/** The desired expanded height, in landscape orientation, for a toaster
  
 */

@property CGFloat expandedLandscapeHeight;


/** whether the standard trigger should be added at the bottom
 
 */


@property BOOL addStandardTrigger;


/** The desired height of the trigger zone, for a toaster
 
 */

@property CGFloat triggerHeight;

/** The desired height of the trigger zone, in landscape orientation, for a toaster
 
 */
@property CGFloat triggerLandscapeHeight;


/** The original portrait image size
 
 */
@property  CGSize imageSize;

/** The original landscape image size
 
 */
@property CGSize landscapeImageSize;


/** The original video size
 
 */
@property  CGSize videoSize;

/** The expiration date for offline ads
 
 */
@property (nonatomic, retain) NSDate *expirationDate;

/** The insertion ID
 
 */
@property (assign) NSInteger insertionId;


@end
