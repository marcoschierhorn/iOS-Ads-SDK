//
//  TravelViewController.h
//  Sample
//
//  Created by Julien Stoeffler on 11/07/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SmartAdServerView.h"


@interface TravelViewController : UIViewController <SmartAdServerViewDelegate>

@property (nonatomic, retain) SmartAdServerView *travel;

@end
