//
//  MainTableViewController.h
//  casieDemoApp2
//
//  Created by orcam on 11/23/15.
//  Copyright © 2015 orcam. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CasieSDK/CasieSDK.h>

#define CASIE_SDK [Casie sharedInstance]


@interface MainTableViewController : UITableViewController<CasieDelegate>

@end
