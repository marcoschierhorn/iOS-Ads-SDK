//
//  DetailViewController.h
//  Sample
//
//  Created by Julien Stoeffler on 08/07/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SmartAdServerView.h"
#import "SmartAdServerViewDelegate.h"


@interface ToasterViewController : UIViewController <SmartAdServerViewDelegate>

@property (nonatomic, retain) SmartAdServerView *toasterBanner;

@end
