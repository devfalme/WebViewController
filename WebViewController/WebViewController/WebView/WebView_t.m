//
//  WebView_t.m
//  WebViewConterllor
//
//  Created by devfalme on 2019/2/26.
//  Copyright © 2019 devfalme. All rights reserved.
//

#import "WebView_t.h"

@implementation WebView_t


#pragma mark - Setters

- (void)setDelegate_t:(id<NavigationDelegate_t>)delegate_t {
    if (!delegate_t || (self.delegate_t && ![self.delegate_t isEqual:delegate_t])) {
        [self removeObserver:self forKeyPath:NSStringFromSelector(@selector(estimatedProgress))];
    }
    
    if (delegate_t) {
        [self addObserver:self forKeyPath:NSStringFromSelector(@selector(estimatedProgress)) options:NSKeyValueObservingOptionOld|NSKeyValueObservingOptionNew context:NULL];
    }
    
    _delegate_t = delegate_t;
    
    [super setNavigationDelegate:delegate_t];
}

#pragma mark - Key Value Observer

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context {
    if ([object isEqual:self] && [keyPath isEqualToString:NSStringFromSelector(@selector(estimatedProgress))]) {
        if (self.delegate_t && [self.delegate_t respondsToSelector:@selector(webView:didUpdateProgress:)]) {
            [self.delegate_t webView:self didUpdateProgress:self.estimatedProgress];
        }
    } else {
        [super observeValueForKeyPath:keyPath ofObject:object change:change context:context];
    }
}


@end
