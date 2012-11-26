//
//  PreRollAppDelegate.h
//  PreRoll
//
//  Created by jstoeffler on 17/05/11.
//  Copyright 2011 Smart AdServer. All rights reserved.
//

#import <UIKit/UIKit.h>


@class RootViewController;
@class DetailViewController;

@interface PreRollAppDelegate : NSObject <UIApplicationDelegate> {
    
    UIWindow *window;
    UISplitViewController *splitViewController;
    
    RootViewController *rootViewController;
    DetailViewController *detailViewController;
}

@property (nonatomic, retain) IBOutlet UIWindow *window;
@property (nonatomic, retain) IBOutlet UISplitViewController *splitViewController;

@property (nonatomic, retain) IBOutlet RootViewController *rootViewController;
@property (nonatomic, retain) IBOutlet DetailViewController *detailViewController;

@end
