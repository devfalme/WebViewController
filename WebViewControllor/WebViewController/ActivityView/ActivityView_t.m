//
//  ActivityView_t.m
//  WebViewConterllor
//
//  Created by devfalme on 2019/2/26.
//  Copyright © 2019 devfalme. All rights reserved.
//

#import "ActivityView_t.h"
#import <WebKit/WebKit.h>
#import <Foundation/Foundation.h>

@implementation ActivityView_t

+ (instancetype)activityWithType:(ActivityType)type {
    return [[ActivityView alloc] initWithActivityType:type];
}

- (instancetype)initWithActivityType:(ActivityType)type {
    if (self = [super init]) {
        _type = type;
    }
    return self;
}


#pragma mark - Getter methods

+ (UIActivityCategory)activityCategory {
    return UIActivityCategoryAction;
}

- (NSString *)activityType {
    switch (self.type) {
        case ActivityTypeLink:
            return @"com.WebViewController.activity.CopyLink";
        case ActivityTypeSafari:
            return @"com.WebViewController.activity.OpenInSafari";
        case ActivityTypeCleanCache:
            return @"com.WebViewController.activity.CleanCache";
    }
}

- (NSString *)activityTitle {
    switch (self.type) {
        case ActivityTypeLink:
            return NSLocalizedStringFromTable(@"Copy Link", @"WebViewLocalized", nil);
        case ActivityTypeSafari:
            return NSLocalizedStringFromTable(@"Open in Safari", @"WebViewLocalized", nil);
        case ActivityTypeCleanCache:
            return NSLocalizedStringFromTable(@"Clean Cache", @"WebViewLocalized", nil);
    }
}

- (UIImage *)activityImage {
    switch (self.type) {
        case ActivityTypeLink:
            return [UIImage imageNamed:@"Link_t" inBundle:[NSBundle bundleForClass:[ActivityView class]] compatibleWithTraitCollection:nil];
        case ActivityTypeSafari:
            return [UIImage imageNamed:@"Safari_t" inBundle:[NSBundle bundleForClass:[ActivityView class]] compatibleWithTraitCollection:nil];
        case ActivityTypeCleanCache:
            return [UIImage imageNamed:@"Clean_t" inBundle:[NSBundle bundleForClass:[ActivityView class]] compatibleWithTraitCollection:nil];
        
        default:
            return nil;
    }
}

- (BOOL)canPerformWithActivityItems:(NSArray *)activityItems {
    for (UIActivity *item in activityItems) {
        
        if ([item isKindOfClass:[NSString class]]) {
            
            NSURL *URL = [NSURL URLWithString:(NSString *)item];
            if (!URL) continue;
            
            if (self.type == ActivityTypeLink) {
                return URL ? YES : NO;
            }
            if (self.type == ActivityTypeSafari) {
                return [[UIApplication sharedApplication] canOpenURL:URL];
            }
            if (self.type == ActivityTypeCleanCache) {
                return YES;
            }
            
            
            break;
        }
    }
    
    return NO;
}

- (void)prepareWithActivityItems:(NSArray *)activityItems {
    for (id item in activityItems) {
        if ([item isKindOfClass:[NSString class]]) {
            _URL = [NSURL URLWithString:(NSString *)item];
            if (!self.URL) continue;
            else break;
        }
    }
}

- (void)performActivity {
    if (!self.URL) {
        [self activityDidFinish:NO];
        return;
    }
    
    switch (self.type) {
        case ActivityTypeLink:
            [[UIPasteboard generalPasteboard] setURL:self.URL];
            [self activityDidFinish:YES];
            break;
        case ActivityTypeSafari: {
            [[UIApplication sharedApplication] openURL:self.URL options:@{} completionHandler:^(BOOL success) {
                [self activityDidFinish:success];
            }];
            break;
        }
        case ActivityTypeCleanCache: {
            NSSet *websiteDataTypes = [WKWebsiteDataStore allWebsiteDataTypes];
            NSDate *dateFrom = [NSDate dateWithTimeIntervalSince1970:0];
            [[WKWebsiteDataStore defaultDataStore] removeDataOfTypes:websiteDataTypes modifiedSince:dateFrom completionHandler:^{
                [self activityDidFinish:YES];
            }];
        }
            break;
    }
    
    
}

@end
