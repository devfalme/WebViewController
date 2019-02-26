//
//  WebView_t.h
//  WebViewConterllor
//
//  Created by devfalme on 2019/2/26.
//  Copyright © 2019 devfalme. All rights reserved.
//


#import <WebKit/WebKit.h>

NS_ASSUME_NONNULL_BEGIN

#ifndef WebView
#define WebView WebView_t
#endif


@protocol NavigationDelegate_t;

@interface WebView_t : WKWebView

@property (nonatomic, weak) id <NavigationDelegate_t> delegate_t;

@end

@protocol NavigationDelegate_t <WKNavigationDelegate>

- (void)webView:(WebView_t *)webView didUpdateProgress:(CGFloat)progress;

@end

NS_ASSUME_NONNULL_END
