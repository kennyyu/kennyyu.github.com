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

As an example of using the library, you declare a flag using the
annotation `@FlagInfo` with the desired flag names and values.

{% highlight java %}
import me.kennyyu.flags.Flag;
import me.kennyyu.flags.Flags;

import java.util.List;

public class MyApp {
  @FlagInfo(help = "maximum number of threads to use", altName = "n")
  private static final Flag<Integer> maxNumThreads = Flags.valueOf(3);

  @FlagInfo(help = "use real logger", altName = "r")
  private static final Flag<Boolean> useRealLogger = Flags.valueOf(false);

  @FlagInfo(help = "input list", altName = "l")
  private static final Flag<List<String>> inputList =
      Flags.valueOf(new ArrayList<String>());

  public static void main(String[] args) {
    Flags.parse(args);
    System.out.println(maxNumThreads.get());
    System.out.println(useRealLogger.get());
    System.out.println(inputList.get());
  }
}
{% endhighlight %}

Then you provide flag values at the command line like so:

{% highlight sh %}
java MyApp --maxNumThreads=5 --useRealLogger -l=foo,bar,baz
{% endhighlight %}

All classes referenced from the main class with flags will be available as options.

In addition to learning how to use Java's Reflection capabilities, this
was also an exercise in learning how to use Maven to build and deploy my
project. I am using a [github project](https://github.com/kennyyu/maven-repos)
as a maven server.

See the `README.md` in the github directory for more information on how to
use it and install the library.