//
//  CasiePerson.h
//  CasieSDK
//
//  Created by Quickode on 10/19/15.
//  Copyright © 2015 Quickode. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CasiePerson : NSObject

+(CasiePerson*) casiePersonWithId:(NSString*)personId;

@property (strong,nonatomic) NSString* personID;

@end
