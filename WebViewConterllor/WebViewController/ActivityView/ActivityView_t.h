//
//  ActivityView_t.h
//  WebViewConterllor
//
//  Created by devfalme on 2019/2/26.
//  Copyright © 2019 devfalme. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_OPTIONS(NSUInteger, ActivityType) {
    ActivityTypeLink,
    ActivityTypeSafari,
    ActivityTypeCleanCache,
};


#ifndef ActivityView
#define ActivityView ActivityView_t
#endif

@interface ActivityView_t : UIActivity

@property (nonatomic, readonly) ActivityType type;
@property (nonatomic, readonly) NSURL *URL;

- (instancetype)initWithActivityType:(ActivityType)type;
+ (instancetype)activityWithType:(ActivityType)type;

@end

NS_ASSUME_NONNULL_END
