---
layout: post
title: "tiniBot: A Voice-Activated Drink Mixer"
date: 2014-06-04 19:34
comments: true
categories: [arduino, chrome, python, electrical engineering]
---

{% youtube "https://www.youtube.com/watch?v=xetTOXwaTmc" %}

This past semester, I took ES50, Harvard's introductory course in electrical
engineering. For our final project, my group decided to make a voice-activated
drink mixer! I was in charge of the coding component of the project.

![Omnibox GDrive Search](/images/tinibot-code.jpg)

The code is available on [github](https://github.com/kennyyu/tinibot).
To do the speech recognition, I
used the Chrome Speech API. Once I have the transcribed text, I send
the text to a local server, which figures out the drink that was ordered,
and then sends the appropriate times to open each of the bottles.
The server sends these times to the attached Arduino, which then
sends current to the appropriate solenoid valves for the designated times.
When activated, the solenoid valves allow liquid to flow through.