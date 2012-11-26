//
//  RootViewController.m
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
//  want a loader, for example), so please make sure you understand    //
//  the parameters you use, test the ad display, with good, bad,       //
//  and no connection, and no ad to deliver, before submitting your    //
//  application to the App Store.                                      //
//                                                                     //                  
//***********************************************************************

#import "RootViewController.h"
#import "DetailViewController.h"


@implementation RootViewController
@synthesize detailViewController;

#pragma mark - View lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];
    self.clearsSelectionOnViewWillAppear = NO;
    self.contentSizeForViewInPopover = CGSizeMake(320.0, 600.0);
}


- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return YES;
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)aTableView {
    return 1;
}


- (NSInteger)tableView:(UITableView *)aTableView numberOfRowsInSection:(NSInteger)section {
    return 1;
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    static NSString *CellIdentifier = @"CellIdentifier";
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
        cell.accessoryType = UITableViewCellAccessoryNone;
    }
    
	switch (indexPath.row) {
		case 0:
			cell.textLabel.text = @"Timelapse";
			break;
		
		default:
			break;
	}
    return cell;
}

#pragma mark - Table view delegate

- (void)tableView:(UITableView *)aTableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    
    [detailViewController selectIndex:indexPath.row];
	[self.tableView deselectRowAtIndexPath:indexPath animated:YES];
}

#pragma mark - Memory management

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}


- (void)dealloc {
    [detailViewController release];
    [super dealloc];
}

@end

