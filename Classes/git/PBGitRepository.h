//
//  PBGitRepository.h
//  GitTest
//
//  Created by Pieter de Bie on 13-06-08.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class PBGitHistoryList;
@class PBGitRevSpecifier;
@protocol PBGitRefish;
@class PBGitRef;
@class PBGitStash;
@class GTRepository;
@class GTConfiguration;

extern NSString* PBGitRepositoryErrorDomain;
extern NSString *PBGitRepositoryDocumentType;

typedef enum branchFilterTypes {
	kGitXAllBranchesFilter = 0,
	kGitXLocalRemoteBranchesFilter,
	kGitXSelectedBranchFilter
} PBGitXBranchFilterType;

static NSString * PBStringFromBranchFilterType(PBGitXBranchFilterType type) {
    switch (type) {
        case kGitXAllBranchesFilter:
            return @"All";
            break;
        case kGitXLocalRemoteBranchesFilter:
            return @"Local";
            break;
        case kGitXSelectedBranchFilter:
            return @"Selected";
            break;
        default:
            break;
    }
    return @"Not a branch filter type";
}

@class PBGitWindowController;
@class PBGitCommit;
@class GTOID;
@class PBGitRepositoryWatcher;

@interface PBGitRepository : NSObject {
	__strong PBGitRepositoryWatcher *watcher;
	__strong PBGitRevSpecifier *_headRef; // Caching
	__strong GTOID* _headOID;
	__strong GTRepository* _gtRepo;
}


@property (assign) BOOL hasChanged;
@property (assign) NSInteger currentBranchFilter;

@property (readonly, strong) PBGitWindowController *windowController;
@property (readonly, getter = getIndexURL) NSURL* indexURL;

@property (nonatomic, strong) PBGitHistoryList *revisionList;
@property (nonatomic, readonly, strong) NSArray* stashes;
@property (nonatomic, readonly, strong) NSArray* branches;
@property (nonatomic, strong) NSMutableOrderedSet* branchesSet;
@property (nonatomic, strong) PBGitRevSpecifier* currentBranch;
@property (nonatomic, strong) NSMutableDictionary* refs;
@property (readonly, strong) GTRepository* gtRepo;

@property (nonatomic, strong) NSMutableArray* submodules;

// Designated initializer
- (id)initWithURL:(NSURL *)repositoryURL error:(NSError **)error;

- (void) cloneRepositoryToPath:(NSString *)path bare:(BOOL)isBare;
- (void) beginAddRemote:(NSString *)remoteName forURL:(NSString *)remoteURL;
- (void) beginFetchFromRemoteForRef:(PBGitRef *)ref;
- (void) beginPullFromRemote:(PBGitRef *)remoteRef forRef:(PBGitRef *)ref;
- (void) beginPushRef:(PBGitRef *)ref toRemote:(PBGitRef *)remoteRef;
- (BOOL) checkoutRefish:(id <PBGitRefish>)ref;
- (BOOL) checkoutFiles:(NSArray *)files fromRefish:(id <PBGitRefish>)ref;
- (BOOL) mergeWithRefish:(id <PBGitRefish>)ref;
- (BOOL) cherryPickRefish:(id <PBGitRefish>)ref;
- (BOOL) rebaseBranch:(id <PBGitRefish>)branch onRefish:(id <PBGitRefish>)upstream;
- (BOOL) createBranch:(NSString *)branchName atRefish:(id <PBGitRefish>)ref;
- (BOOL) createTag:(NSString *)tagName message:(NSString *)message atRefish:(id <PBGitRefish>)commitSHA;
- (BOOL) deleteRemote:(PBGitRef *)ref;
- (BOOL) deleteRef:(PBGitRef *)ref;
- (BOOL) stashPop:(PBGitStash *)stash;
- (BOOL) stashApply:(PBGitStash *)stash;
- (BOOL) stashDrop:(PBGitStash *)stash;
- (BOOL) stashSave;
- (BOOL) stashSaveWithKeepIndex:(BOOL)keepIndex;

- (NSURL *) gitURL ;

- (NSFileHandle*) handleForCommand:(NSString*) cmd GITX_DEPRECATED;
- (NSFileHandle*) handleForArguments:(NSArray*) args GITX_DEPRECATED;
- (NSFileHandle *) handleInWorkDirForArguments:(NSArray *)args GITX_DEPRECATED;
- (NSString*) outputForCommand:(NSString*) cmd GITX_DEPRECATED;
- (NSString *)outputForCommand:(NSString *)str retValue:(int *)ret GITX_DEPRECATED;
- (NSString *)outputForArguments:(NSArray *)arguments inputString:(NSString *)input retValue:(int *)ret GITX_DEPRECATED;
- (NSString *)outputForArguments:(NSArray *)arguments inputString:(NSString *)input byExtendingEnvironment:(NSDictionary *)dict retValue:(int *)ret GITX_DEPRECATED;


- (NSString*) outputForArguments:(NSArray*) args GITX_DEPRECATED;
- (NSString*) outputForArguments:(NSArray*) args retValue:(int *)ret GITX_DEPRECATED;
- (NSString *)outputInWorkdirForArguments:(NSArray*) arguments GITX_DEPRECATED;
- (NSString *)outputInWorkdirForArguments:(NSArray*) arguments retValue:(int *)ret GITX_DEPRECATED;
- (BOOL)executeHook:(NSString *)name output:(NSString **)output GITX_DEPRECATED;
- (BOOL)executeHook:(NSString *)name withArgs:(NSArray*) arguments output:(NSString **)output GITX_DEPRECATED;

- (NSString *)workingDirectory GITX_DEPRECATED;
- (NSURL *)workingDirectoryURL;
- (NSString *)projectName;
- (NSString *)gitIgnoreFilename;
- (BOOL)isBareRepository;

- (BOOL)hasSVNRemote;

- (void) reloadRefs;
- (void) lazyReload;
- (PBGitRevSpecifier*)headRef;
- (GTOID *)headOID;
- (PBGitCommit *)headCommit;
- (GTOID *)OIDForRef:(PBGitRef *)ref;
- (PBGitCommit *)commitForRef:(PBGitRef *)ref;
- (PBGitCommit *)commitForOID:(GTOID *)sha;
- (BOOL)isOIDOnSameBranch:(GTOID *)baseOID asOID:(GTOID *)testOID;
- (BOOL)isOIDOnHeadBranch:(GTOID *)testOID;
- (PBGitStash *)stashForRef:(PBGitRef *)ref;
- (BOOL)isRefOnHeadBranch:(PBGitRef *)testRef;
- (BOOL)checkRefFormat:(NSString *)refName;
- (BOOL)refExists:(PBGitRef *)ref;
- (PBGitRef *)refForName:(NSString *)name;

- (NSArray *) remotes;
- (BOOL) hasRemotes;
- (PBGitRef *) remoteRefForBranch:(PBGitRef *)branch error:(NSError **)error;
- (NSString *) infoForRemote:(NSString *)remoteName;

- (void) readCurrentBranch;
- (PBGitRevSpecifier*) addBranch: (PBGitRevSpecifier*) rev;
- (BOOL)removeBranch:(PBGitRevSpecifier *)rev;

- (NSString*) parseSymbolicReference:(NSString*) ref;
- (NSString*) parseReference:(NSString*) ref;

- (void) forceUpdateRevisions;
- (NSURL*) getIndexURL;

@end
