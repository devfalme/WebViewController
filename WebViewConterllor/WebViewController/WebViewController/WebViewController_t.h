//
//  WebViewController_t.h
//  WebViewConterllor
//
//  Created by devfalme on 2019/2/26.
//  Copyright © 2019 devfalme. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <WebKit/WebKit.h>

#import "WebView_t.h"

#ifndef WebViewController
#define WebViewController WebViewController_t
#endif

/**
 Types of supported navigation tools.
 */
typedef NS_OPTIONS(NSUInteger, WebNavigationTools) {
    WebNavigationToolAll = -1,
    WebNavigationToolNone = 0,
    WebNavigationToolBackward = (1 << 0),
    WebNavigationToolForward = (1 << 1),
    WebNavigationToolHome = (1 << 3),
    WebNavigationToolStopReload = (1 << 2)
};

/**
 Types of supported actions (i.e. Share & Copy link, Add to Reading List, Open in Safari/Chrome/Opera/Dolphin).
 */
typedef NS_OPTIONS(NSUInteger, SupportedWebActions) {
    SupportedWebActionAll = -1,
    SupportedWebActionNone = 0,
    SupportedWebActionshareLink = (1 << 0),
    SupportedWebActionCopyLink = (1 << 1),
    SupportedWebActionReadLater = (1 << 2),
    SupportedWebActionOpenSafari = (1 << 3),
    SupportedWebActionCleanCache = (1 << 4),
};

/**
 Types of information to be shown on navigation bar. Default is DZNWebNavigationPromptAll.
 */
typedef NS_OPTIONS(NSUInteger, WebNavigationPrompt) {
    WebNavigationPromptNone = 0,
    WebNavigationPromptTitle = (1 << 0),
    WebNavigationPromptURL = (1 << 1),
    WebNavigationPromptAll = WebNavigationPromptTitle | WebNavigationPromptURL,
};
NS_ASSUME_NONNULL_BEGIN

@interface WebViewController_t : UIViewController <NavigationDelegate_t, WKUIDelegate, UITableViewDataSource, UITableViewDelegate>

/** The web view that the controller manages. */
@property (nonatomic, retain) WebView *webView;
/** The URL identifying the location of the content to load. */
@property (nonatomic, retain) NSURL *URL;
/** The supported navigation tool bar items. Default is All. */
@property (nonatomic) WebNavigationTools supportedWebNavigationTools;
/** The supported actions like sharing and copy link, add to reading list, open in Safari, etc. Default is All. */
@property (nonatomic) SupportedWebActions supportedWebActions;
/** The information to be shown on navigation bar. Default is DZNWebNavigationPromptAll. */
@property (nonatomic) WebNavigationPrompt webNavigationPrompt;
/** Yes if a progress bar indicates the . Default is YES. */
@property (nonatomic) BOOL showLoadingProgress;
/** YES if long pressing the backward and forward buttons the navigation history is displayed. Default is YES. */
@property (nonatomic) BOOL allowHistory;
/** YES if both, the navigation and tool bars should hide when panning vertically. Default is YES. */
@property (nonatomic) BOOL hideBarsWithGestures;


///------------------------------------------------
/// @name Initialization
///------------------------------------------------

/**
 Initializes and returns a newly created webview controller with an initial HTTP URL to be requested as soon as the view appears.
 
 @param URL The HTTP URL to be requested.
 @returns The initialized webview controller.
 */
- (instancetype)initWithURL:(NSURL *)URL;

/**
 Initializes and returns a newly created webview controller for local HTML navigation.
 
 @param URL The file URL of the main html.
 @returns The initialized webview controller.
 */
- (instancetype)initWithFileURL:(NSURL *)URL;

/**
 Starts loading a new request. Useful to programatically update the web content.
 
 @param URL The HTTP or file URL to be requested.
 */
- (void)loadURL:(NSURL *)URL NS_REQUIRES_SUPER;

/**
 Starts loading a new request. Useful to programatically update the web content.
 
 @param URL The HTTP or file URL to be requested.
 @param baseURL A URL that is used to resolve relative URLs within the document.
 */
- (void)loadURL:(NSURL *)URL baseURL:(NSURL *)baseURL;

///------------------------------------------------
/// @name Appearance customisation
///------------------------------------------------

// The back button displayed on the tool bar (requieres DZNWebNavigationToolBackward)
@property (nonatomic, strong) UIImage *backwardButtonImage;
// The forward button displayed on the tool bar (requieres DZNWebNavigationToolForward)
@property (nonatomic, strong) UIImage *forwardButtonImage;
@property (nonatomic, strong) UIImage *homeButtonImage;
// The stop button displayed on the tool bar (requieres DZNWebNavigationToolStopReload)
@property (nonatomic, strong) UIImage *stopButtonImage;
// The reload button displayed on the tool bar (requieres DZNWebNavigationToolStopReload)
@property (nonatomic, strong) UIImage *reloadButtonImage;
// The action button displayed on the navigation bar (requieres at least 1 DZNsupportedWebActions value)
@property (nonatomic, strong) UIImage *actionButtonImage;


///------------------------------------------------
/// @name Delegate Methods Requiring Super
///------------------------------------------------

// NavigationDelegate
- (void)webView:(WebView *)webView didStartProvisionalNavigation:(WKNavigation *)navigation NS_REQUIRES_SUPER;
- (void)webView:(WebView *)webView didCommitNavigation:(WKNavigation *)navigation NS_REQUIRES_SUPER;
- (void)webView:(WebView *)webView didUpdateProgress:(CGFloat)progress NS_REQUIRES_SUPER;
- (void)webView:(WebView *)webView didFinishNavigation:(WKNavigation *)navigation NS_REQUIRES_SUPER;
- (void)webView:(WebView *)webView didFailNavigation:(WKNavigation *)navigation withError:(NSError *)error NS_REQUIRES_SUPER;

// WKUIDelegate
- (WebView *)webView:(WebView *)webView createWebViewWithConfiguration:(WKWebViewConfiguration *)configuration forNavigationAction:(WKNavigationAction *)navigationAction windowFeatures:(WKWindowFeatures *)windowFeatures NS_REQUIRES_SUPER;

// UITableViewDataSource
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView NS_REQUIRES_SUPER;
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section NS_REQUIRES_SUPER;
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath NS_REQUIRES_SUPER;
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath NS_REQUIRES_SUPER;

// UITableViewDelegate
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath NS_REQUIRES_SUPER;
@end

NS_ASSUME_NONNULL_END
