//
//  CasieFace.h
//  CasieSDK
//
//  Created by Quickode on 10/19/15.
//  Copyright © 2015 Quickode. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum SourceType{
    SourceType_casieDevice, // For image arrived from device
    SourceType_app // For image arrived from app
} SourceType;

@interface CasieFace : NSObject

+(CasieFace*) casieFaceWithImageId:(NSString*)imageId
                         imageData:(NSData*)imageData
                   andDetectedTime:(NSDate*)time;

@property (strong,nonatomic) NSString* casieImageID;
@property (strong,nonatomic) NSData* casieImageData;
@property (strong,nonatomic) NSDate* detectedTime;

@end
