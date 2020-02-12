---
layout: post
title: "Omnibox GDrive Search"
date: 2013-10-20 22:11
comments: true
categories: [chrome extension, javascript]
---

![Omnibox GDrive Search](/images/omnibox-gdrive-search.png)

I published my first Chrome Extension: [Omnibox GDrive Search](https://chrome.google.com/webstore/detail/omnibox-gdrive-search/faadbnlolclhboooficaklnhnkdjmdnb)!
The extension allows you to search your google drive for documents and then jump directly to them from the omnibox! See the [code on github](https://github.com/kennyyu/omnibox-gdrive-search).

In the omnibox, type `gd` and press `TAB`. Now you can enter your queries and jump directly to the file from the omnibox suggestions!

To use it, you must first authorize Google Drive metadata read-only access to the extension by following these instructions (see screenshots in extension link):

1.  Go to `chrome://extensions`
2.  Find this extension, and click "Options"
3.  Click "Authorize", and then click "Accept" to grant the extension access. This will redirect to a blank page. Close it, and refresh the options page.
4.  If you see "You have already authorized this extension!", then you can now search!

By far, the most difficult part of the extension was understanding authorization with Google Drive. The extension is a bit
buggy and lags a little because the extension must renew the authorization with Google Drive every 15 minutes or so.
To get around this, the extension only requests authorization on the first use after the expiration and will
redirect the user to the options page.
Thus, if you're using the extension for the first time in a while, it may take ~3 seconds before search results come back.