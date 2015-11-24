//
//  Casie.h
//  CasieSDK
//
//  Created by Quickode on 10/19/15.
//  Copyright © 2015 Quickode. All rights reserved.
//
/*
 To make bluetooth work add:
 <key>UIBackgroundModes</key>
	<array><string>bluetooth-central</string></array>
 to your apps info.plist
 
 */


#import <Foundation/Foundation.h>
#import "CasieFace.h"
#import "CasiePerson.h"

@import UIKit;


typedef enum DeviceState{
    DeviceState_disconnected,
    DeviceState_detected,
    DeviceState_connecting,
    DeviceState_connected,
    DeviceState_sendingData
} DeviceState;

typedef enum WifiState{
    WifiState_NotReachable,
    WifiState_ReachableViaWiFi,
    WifiState_ReachableViaWWAN,
    WifiState_RequestFailed //in case some thing went wrong
} WifiState;



/*****************************************************--Casie-Delegate--***************************************************************************************/
 
@protocol CasieDelegate <NSObject>
@optional
-(void) CASIEConnectionStateUpdated:(DeviceState)state;
-(void) FaceDetected:(CasieFace*)face atTimestamp:(NSDate*)time;
-(void) QRCodeDetected:(NSArray*)code atTimestamp:(NSDate*)time; //not implemented
-(void) barcodeDetected:(NSArray*)code atTimestamp:(NSDate*)time;//not implemented
-(void) wordHasRecieved:(NSString*)word atTime:(NSDate*)time;// not finished yet

-(void)recievedPeripheralData:(NSDictionary*)peripheralData;

-(void)printTextToConsole:(NSString*)txt; //used in quick connect to print to console
@end

/**************************************************************************************************************************************************************/



@interface Casie : NSObject 

@property (nonatomic, weak) id <CasieDelegate> delegate;

+ (instancetype)sharedInstance;


#pragma mark - communication

/**************************************** Methods to Connect your phone to the device *************************************************************************/
/* 
    1)scanToFindPeripherals;
    2)pairPeripheralId:(NSString*)peripheralId;
    3)getPairedPeripheralId
    4)connect
*/

-(void) connect;

-(void)disconnect;

/** Get the current devices state **/
-(DeviceState) state; //(disconnected, detected, connecting, connected, sendingData)
-(void) getBatteryPercentageWithBlock:(void (^)(UInt8 batteryLevel)) batteryBlock;


-(void) scanToFindPeripherals;
-(void) stopScanForPeripherals;


-(void)pairPeripheralId:(NSString*)peripheralId;
-(void)removePeripheralId;
-(NSString*)getPairedPeripheralId;

/**************************************************************************************************************************************************************/


/**
 This block requests the image from the device that is associated to this face. If face arrived it will be added automatically to the face in the DB
 @param face The face that you want it's image
 @return image and error - one of them will always be nil
 **/
-(void) requestImageForFace:(CasieFace*)face  WithBlock:(void (^)(UIImage *image, NSError *error)) block;
//-(NSArray*) requestCASIEMotionsForTime:(NSDate*)time1 toTime:(NSDate*)time2;




#pragma mark - Firmware update

-(void)getCurrentHardwareVersionWithBlock:(void(^)(NSString* version))version;
-(void)getCurrentSoftwareVersionWithBlock:(void(^)(NSString* version))version;

//-(NSString*) getCurrentVersion;
-(NSDictionary*) getWifiData;
//-(void) setWifiPassword:(NSString*)password forNetwork:(WifiNetwork*)network
-(WifiState) getWifiState;
//-(BOOL) upgradeFirmware;



#pragma mark - Person/ Faces methods
/**
 Returns an array with all the people that exist in the DB
 @return Array with all the people
 **/
-(NSArray*) getAllPeople;
/**
 Creates a new person and adds him to the DB
 @return copy of the person with the new personID
 **/
-(CasiePerson*) createNewPerson;
/**
 Removes the person from the DB, all of the person faces will be deleted as well
 @return YES if delete succeeded, NO if not
 **/
-(BOOL) removePersonByPersonID:(NSString*)personID;

-(NSArray*) getAllFacesOfPersonByPersonID:(NSString*)personID;
/**
 Adds a face to the specified person
 @param face casieFace that was received from calling the method: "-(CasieFace*) generateFaceFromImage:(UIImage*)image"
 @param person The person you want to add the face to
 @return YES if face was added to person
 **/
-(BOOL) associateFace:(CasieFace*)face ToPerson:(CasiePerson*)person;
/**
 Removes the face from the DB and.
 @return YES if delete succeeded, NO if not
 **/
-(BOOL)deleteFaceWithFaceId:(NSString*)faceId;

-(BOOL)removeFaceWithFaceId:(NSString*)faceId fromPersonWithPersonID:(NSString*)personId;
/**
 Returns the person that has the best match to the specified face
 @param face The CasieFace that will be used to find the best match
 @return The best matched CasiePerson, returns nil if no such person exists
 **/
-(CasiePerson*) bestPersonMatchForFace:(CasieFace*)face; //(return nil if no person exists)
-(NSDictionary*) detectPossibleMatchesFrom:(CasieFace*)face underScore:(double)underScore; //dictionary will contains an array of possible “person” and an array of “confidante scores"
-(double) similarityOf:(CasieFace*)face1 and:(CasieFace*)face2;

-(CasieFace*) generateFaceFromImage:(UIImage*)image; //calling REST server api







-(void)quickConnectionToDeviceWithBestSignal;

#pragma mark - other methods
-(NSArray*) getAllFacesFromTime:(NSDate*)from toTime:(NSDate*)to;
-(NSArray*) getAllDeviceFaces;
-(NSArray*) getAllAppFaces;
-(NSArray*) getAllFaces;




#pragma mark - debug methods

-(void)mockImageReceivedFromDeviceWithImage:(UIImage*)image andVector:(NSArray*)arrVector;
-(CasieFace*) generateDeviceFaceFromImage:(UIImage*)image andFeatures:(NSArray*)arrFeatures;

@end
