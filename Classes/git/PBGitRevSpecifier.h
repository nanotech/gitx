//
//  PBGitRevSpecifier.h
//  GitX
//
//  Created by Pieter de Bie on 12-09-08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
@class PBGitRef;

NS_ASSUME_NONNULL_BEGIN

@interface PBGitRevSpecifier : NSObject  <NSCopying> {
	NSString *description;
	NSArray *parameters;
	NSURL *workingDirectory;
	BOOL isSimpleRef;
}

- (id) initWithParameters:(NSArray *)params description:(NSString * _Nullable)descrip;
- (id) initWithParameters:(NSArray*) params;
- (id) initWithRef: (PBGitRef*) ref;

- (NSString * _Nullable) simpleRef;
- (PBGitRef * _Nullable) ref;
- (BOOL) hasPathLimiter;
- (NSString *) title;

- (BOOL) isEqual: (PBGitRevSpecifier*) other;
- (BOOL) isAllBranchesRev;
- (BOOL) isLocalBranchesRev;

+ (PBGitRevSpecifier *)allBranchesRevSpec;
+ (PBGitRevSpecifier *)localBranchesRevSpec;

@property(retain)   NSString *description;
@property(readonly) NSArray *parameters;
@property(retain)   NSURL *workingDirectory;
@property(readonly) BOOL isSimpleRef;

@end

NS_ASSUME_NONNULL_END
