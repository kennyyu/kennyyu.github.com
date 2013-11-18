---
layout: post
title: "Java Flag Command Line Library"
date: 2012-08-22 18:07
comments: true
author: Kenny Yu
categories: [java, flags]
---

Inspired by other commmand line libraries, I decided to make my own Java flag
command line library [here](https://github.com/kennyyu/flags). It makes use
of Java's Reflection capabilities to fill in the values of flags at runtime.
The library is fairly simple to use--it requires only declaring a static
field, and one invocation to `Flags.parse` in the `main` method of the
application. The library offers support for various wrapper types as well
as collection types.

In addition to learning how to use Java's Reflection capabilities, this
was also an exercise in learning how to use Maven to build and deploy my
project. I am using a [github project](https://github.com/kennyyu/maven-repos)
as a maven server.

See the `README.md` in the github directory for more information on how to
use it and install the library.