//
//  MainTableViewController.m
//  casieDemoApp2
//
//  Created by orcam on 11/23/15.
//  Copyright © 2015 orcam. All rights reserved.
//

#import "MainTableViewController.h"

@interface MainTableViewController ()

@end

@implementation MainTableViewController

- (void)viewDidLoad {
    [super viewDidLoad];
        
    NSLog(@"loaded");
    
    CASIE_SDK.delegate = self;
    
    //[CASIE_SDK quickConnectionToDeviceWithBestSignal];
    
    
    
    
    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
    
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
}

-(void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    [CASIE_SDK scanToFindPeripherals];
}




-(void) CASIEConnectionStateUpdated:(DeviceState)state
{
    if (state == DeviceState_connected)
    {
        [CASIE_SDK stopScanForPeripherals];
    }
}


-(void)recievedPeripheralData:(NSDictionary *)peripheralData
{
    NSLog(@"recieved peripherial data");
    
    [CASIE_SDK pairPeripheralId:[peripheralData objectForKey:@"ID"]];
    
    NSString *periID = [CASIE_SDK getPairedPeripheralId];
    
    if (periID)
    {
        [self printToConsole:@"Starting connection..."];
        NSLog(@"connected");
        [CASIE_SDK connect];
    }
    else
    {
        NSLog(@"NOT connected");
        [self printToConsole:@"Paired ID doe's not exist"];
        //[self showAlertWithTitle:@"Paired ID doe's not exist" andMessage:@"You should pair a device first"];
    }
    
}



- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
#warning Incomplete implementation, return the number of sections
    return 0;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
#warning Incomplete implementation, return the number of rows
    return 0;
}

/*
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:<#@"reuseIdentifier"#> forIndexPath:indexPath];
    
    // Configure the cell...
    
    return cell;
}
*/

/*
// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the specified item to be editable.
    return YES;
}
*/

/*
// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
    } else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
    }   
}
*/

/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath {
}
*/

/*
// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}
*/

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/





-(void)printToConsole:(NSString*) str
{
    NSDate* date = [NSDate date];
    
    NSDateFormatter* formatter = [[NSDateFormatter alloc] init] ;
    
    [formatter setDateFormat:@"HH:mm:ss"];
    
    NSString* strTime = [formatter stringFromDate:date];
    
    NSString *strOutput = [NSString stringWithFormat:@"%@ %@",strTime,str];
    
    NSLog(@"%@ \n",strOutput);
}





@end
