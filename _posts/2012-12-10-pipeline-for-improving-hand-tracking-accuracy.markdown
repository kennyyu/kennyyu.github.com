---
layout: post
title: "Pipeline for Improving Hand Tracking Accuracy"
date: 2012-12-10 21:48
comments: true
categories: [computer vision, opencv, python, javascript]
---
{% youtube "https://www.youtube.com/watch?v=DFPg-9D46kE" %}

For my CS283: Computer Vision Final Project, I created an application to control Google Maps
using your hand and a webcam.

It uses the Chrome API to access the webcam, and frames are sent to a Tornado server that
runs the hand tracking pipeline, annotates the frame, and sends back the displacement
vector to update the view of the map. I am using OpenCV for it's Haar Cascade libraries.

You can [view the code on github](https://github.com/kennyyu/cs283-project)
and setup an instance of the server locally!

You can also [view the paper](https://www.dropbox.com/s/tnyzr1qt8fmnscp/hand-tracking-pipeline.pdf)
I wrote to describe the process I used in the pipeline. Below is a summary of the problem
statement and the stages in the pipeline.

# Problem Statement

Given a poorly trained Haar Cascade Classifier (250 positive samples and 100 negative samples) to recognize hands,
this project assembles a pipeline to improve the quality of the tracking. These steps include:

1.  Face detection and removal of faces.
2.  Background subtraction.
3.  Use a simplified Kalman-Filter-esque technique to estimate the bounding box of the hand. This assumes that a hand moves in a smooth manner.
4.  Use our hand classifier to detect the largest hand within the bounding box.
5.  Compute the optical flow of points within the bounding box using Lucas-Kanade.
6.  Use the optical flow and the measured position of the hand to correct our Kalman-Filter estimate.
