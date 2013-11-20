---
layout: post
title: "Learning Through Bootcamps"
date: 2013-11-18 11:25
comments: true
categories: [teaching, unix, git, python]
---

This semester, I've been writing and leading [bootcamps](https://github.com/hcs/bootcamp-main/) as the
[Harvard Computer Society](http://www.hcs.harvard.edu/) Bootcamp Manager. In the past, HCS has
had bootcamps on various topics including python, javascript, and git. Bootcamps are typically
targetted for students just starting computer science (fresh{wo}men, sophomores).

My goal this smester was to restart the bootcamps and to revamp the curriculum. In this post, I'll talk about:

1.  The **bootcamp curriculum** I designed
2.  The typical **workflow** for a bootcamp
3.  The **design decisions** that went into writing these bootcamps
4.  Some high level **results** (pull request numbers and summary of testimonials)
5.  **Unedited testimonials** from students in the bootcamps

<!-- more -->

## Bootcamp Curriculum

1.  [Bootcamp Setup](https://github.com/hcs/bootcamp-setup/wiki) and [slides](http://goo.gl/jk45W1).
    From my experience leading bootcamps
    last semester, I realized it is really hard to cater to so many different programming
    backgrounds and machine setups. As a result, I chose to standardize and require students
    to install a UNIX system with a package manager:

    *   OSX with [homebrew](http://brew.sh/)
    *   [CS50 Appliance](https://manual.cs50.net/appliance/), since most students are either taking
        or have taken [CS50](https://cs50.harvard.edu/), Harvard's Intro to Computer Science course.
    *   Ubuntu virtual machine with VirtualBox or VMWare

2.  [Intro to UNIX Part 1: Command Line](https://github.com/hcs/bootcamp-unix/wiki) and [slides](http://goo.gl/5NJyWw).
    This bootcamp presents the UNIX command line and the stdin, stdout, stderr, and pipe abstractions.
    [Exercises](https://github.com/hcs/bootcamp-unix/wiki/Exercise:-Scavenger-hunt)
    include scavenger hunts through a code base using `find`, `grep`, and piping
    a sequence of commands together transform and analyze files.

3.  [Intro to UNIX Part 2: Shell Scripting](https://github.com/hcs/bootcamp-unix/wiki/Shell-scripts) and [slides](http://goo.gl/kRpD4y).
    This continues the introduction to UNIX with shell scripts. Exercises include:

    *   Writing a [web scraper to scrape images from Amazon](https://github.com/hcs/bootcamp-unix/wiki/Exercise:-Shell-scripts)
        using only basic UNIX commands, and writing
    *   A [mail merge script](https://github.com/hcs/bootcamp-unix/wiki/Exercise:-Mail-Merge-Shell-Script).

4.  [Git and Github](https://github.com/hcs/bootcamp-git/wiki) and [slides](http://goo.gl/siE4CQ).
    This bootcamp introduces students to version control and using git with Github. Exercises include

    *   [Scavenger Hunt](https://github.com/hcs/bootcamp-git/wiki/Exercise-Scavenger-Hunt)
        through a repository's history (e.g. which commit introduced a change, who did it, checking out an old revision)
    *   [Committing and Pushing](https://github.com/hcs/bootcamp-git/wiki/Exercise-Committing-and-Pushing). Have students
        attempt to replicate a git history tree.
    *   [Resolving Merge Conflicts](https://github.com/hcs/bootcamp-git/wiki/Exercise-Resolving-Merge-Conflicts).
        I made a branch that would purposely cause a merge conflict when students attempt to merge the branch
        into their master branch.
    *   [Reverting a Commit](https://github.com/hcs/bootcamp-git/wiki/Exercise-Reverting-a-commit).
    *   [Making a Pull Request](https://github.com/hcs/bootcamp-git/wiki/Exercise-Making-a-Pull-Request). Students
        create a pull request on github. This exercise allows students to make pull requests in the future
        and to give me and the HCS board the opportunity to give them feedback on their work.

5.  [Intro to Python](https://github.com/hcs/bootcamp-python/wiki) and [slides](http://goo.gl/9ID3ad).
    This bootcamp introduces students to basic feature of Python, including control flow and data structures
    (lists, sets, dictionaries, tuples, strings). Exercises include:

    *   [Hello World!](https://github.com/hcs/bootcamp-python/wiki/Exercise-Hello-World).
        This also sets up a pull request to keep track of their work.
    *   [Spell Checker](https://github.com/hcs/bootcamp-python/wiki/Exercise-Spell-Checker). Inspired by CS50's
        [Spell Checker](http://cdn.cs50.net/2013/fall/psets/6/pset6/pset6.html) problem set, I wanted to
        show students how much Python abstracts many things away and makes programming in Python extremely
        simple and easy.
    *   [Python Exercises](https://github.com/hcs/bootcamp-python/wiki/Exercise-Programming). This is an example
        of test-driven development: we give students failing unit tests, and their job is to make
        all the unit tests pass.

## Workflow

I designed the workflow centered around github wiki pages and pull requests. Here's the workflow for a typical bootcamp:

1.  Start reading the github wiki page for the bootcamp repository.
2.  Fork the bootcamp repository and clone it to their local machines.
3.  Do some of the exercises.
4.  Setup a pull request using the original bootcamp respository as the base of the pull request,
    and their master branch as the head of the pull request
5.  Do some more exercises and push commits to their master branch, which will update their pull request.
6.  Wait for feedback on the pull request.

## Design Goals

I designed the curriculum and workflow with multiple goals in mind:

*   **Flipped Classroom.** From my experience in classes with
    [flipped classrooms](http://www.eecs.harvard.edu/~margo/cs161/),
    students learn (at least with programing exercises) much better when they have hands-on
    exercises with guidance from the instructor. With this in mind, I wrote all the bootcamps
    to minimize the amount of lecturing I give and to maximize the amount of time students
    would be programming and asking questions.

*   **Useful Software Engineering Skills.** With these bootcamps, I wanted to provide
    others with the exercises and support that I wish I had had as a freshmen--exercises
    to teach some basic skills that would be useful not only in industry, but also
    useful in an academic setting. From my experiences in internships and classes,
    some of the most useful skills that have learned are

    1.  using the command line effectively
    2.  scripting repetitive tasks (e.g. test harnesses, moving/editing files)
    3.  using version control
    4.  having a go-to language for quick prototyping and tasks

*   **Start from Zero.** Because HCS's target audience is students with very
    little programming experience, I wrote the bootcamps so that anyone starting
    from zero programming experience could quickly get their environment setup
    and start using the command line. Naturally, there will be students that
    already have programming experience, and I supplemented the basic exercises
    in bootcamps with more involved exercises that students can do on their
    own pace.

*   **Feedback System.** I believe it's very important to get feedback
    on your work, especially when programming for the first time. Therefore, I
    designed the bootcamps to use github's pull request feature for comments
    and feedback. Pull requests allow us to leave in-line comments on code,
    and to provide a comment-discussion feature for general feedback. I also
    encouraged students to install the [GH Diff Highlight Chrome Extension](https://chrome.google.com/webstore/detail/gh-diff-highlight/gjljgldconccfbldbnnpbgahpckhjcfj)
    to colorize pull request diffs.

    [Here](https://github.com/hcs/bootcamp-python/pulls) are examples of the
    feedback we provided on the Intro to Python bootcamp.

*   **Reusable.** I am a senior and will be graduating soon; as a result, I
    want the bootcamps to be reusable after I leave. Because of this,
    I made all the bootcamps open source github repositories
    so that they may be reused, updated, and forked as necessary in the future.

## Results

Overall, attendance was generally higher than I expected. The attendance for
the setup and first two UNIX bootcamps were roughly 30-40 people, which
is one of the highest attendance rates HCS has had in a while for a bootcamp.
Naturally, as the semester progresses, students get more busy with midterms and assignments,
and so attendance dropped to about 20 for git, and a dozen or so for the Python
bootcamp. After each bootcamp, I posted a survey asking for feedback. I asked
the question:

> What did you think of the bootcamp? (What you liked, didn't like, what was useful, wasn't useful. What would you have done differently? etc.)

The feedback was generally positive. The types of feedback were generally along one or
more of these categories (see the Testimonial section at the end for real responses):

1.  Hands-on flipped classroom sessions were helpful in helping students digest the material.
2.  More advanced students wanted more challenging exercises.
3.  Too fast/too slow.
4.  Requests for review of material from previous sessions.

In terms of numbers, the [Git and Github Bootcamp](https://github.com/hcs/bootcamp-git/pulls) had 28 forks, with 16
students successfully submitting a pull request. The [Python Bootcamp](https://github.com/hcs/bootcamp-git/pulls) had 16 forks,
with 10 students sucessfully submitting a pull request, and 4 students finishing all the python exercises.

From these numbers and testimonials, it seems that the flipped classroom model worked very well,
and the various levels of exercises and walkthroughs catered to both advanced and beginner students.

## Testimonials

Below are the unedited and anonymized testimonials from students:

### UNIX Part 1: Command Line

> This seems well done, albeit rather basic. Maybe mentioning "do one thing well" to explain why UNIX works the way it does.

> I thought it was good since it taught me all the basics in one sitting

> Like it.

> I think this was great although taught a little quickly

> Useful, but went a little slowly; Overall was run very well, learned some useful UNIX commands.

> Very useful! I learned a lot about some of the basic commands available to us. I wish we'd dived into the scavenger hunt sooner so we could've had more time for it and the shell script exercise.

> I liked how many functions could be linked to each other. That was really cool. Also how there are functions that allow tons of flexibility with the -char ability.

> Very helpful especially one-on-one. Went through the slides a bit too fast

> Awesome! While I've done a good amount of programming before, I haven't had a chance to learn many of the covered UNIX commands... until now.

> Thanks for an awesome class, Kenny!"

> smaller room preferably

> Scavenger hunt was fun. I'm glad I sat next to people who were more familiar with this material.

> Ir was really useful.  I got a better sense of how to use the command line than ever before!  Thanks.

> It got a little hectic at the end...

> I thought it went a little too fast for me. But I enjoy the premises of the program. I just wish it was not so much like a class, but a collaboration so that everyone feels involved.

> I thought it was a really good topic, but it moved to quickly for me. It also would have been nice if there were more people to answer questions, because that was really helpful. Along with piazza, it would be nice to have a small recap session to go over the topics and solidify them.

> This was a good set of exercises.  I got distracted with unrelated things (c/p, sending the answers directly to answers.txt), so I lagged behind.

> I liked it! I thought I knew shell scripting before, but now I feel more comfortable with channeling and piping and whatnot. :)

> It was very informative!

> I've learned a lot. It was very informative.

> Great tutorial. Learned a lot about UNIX, especially piping.

### UNIX Part 2: Shell Scripting

> could have been a little more organized.  But people were very helpful.

> Useful bootcamp, I didn't know how to write shell scripts...

> I liked having the recap of last week and generally enjoyed this exercise.  I like the presence of a second exercise for those who finish early.

> Could've used more instruction on the scraper parts - using man over and over again got annoying

### Git and Github

> Awesome overview of git. I knew a bit coming in, but setting up the alias for my "lg" command was great, so that I can see my requests in a more aesthetically pleasing fashion. Maybe a bit more on creating branches to make temporary changes and then merging your own branch back.

> github is harder than i expected–it's like a whole new world of stuff! so it was largely a struggle but i think i learned a lot

> Liked how straightforward it was. I would maybe have thrown in a challenge exercise

> It was very fun and easy to understand. Plus, I learned a whole bunch of stuff I never knew before (and a lot of things unrelated to git, but useful as a whole, like how to use vim). :)

> It was fantastic! I don't think I would have done anything differently.

> Useful, already knew a decent amount about git. The pace was good, wouldn't have changed anything.

> It is difficult but manageable

> Exercises are nice.

> It was great! And useful!

> I thought the bootcamp was useful. Github is a lot more manageable and less confusing after today's bootcamp. I'm glad I came.

> This one was really good and understandable!

> I wasn't able to come to the bootcamp on Wednesday, but I just completed it on my own - the slides and online directions were really helpful, and I could pretty much figure most things out on my own.

> On a side note, I also completed the mail merger exercise from last week's bootcamp, and the solution didn't follow the instructions that we were given, so that confused me a little.

### Intro to Python

> Pretty cool.  Exercises were nice, good practice.  I was already pretty familiar with Python, though, so not representative.

> It was useful, especially the talk about CS classes and coursework!

> This was a great lesson. The only problems I had were setting up git stuff, but that is mostly due to the fact that this was the first time I came up. There is not much to change other than perhaps moving a bit slower.

> It was great! Learnt a lot about python. Especially liked the exercises that helped me get a little more used to python syntax.

> I love to code and I love the exercises, as well as the debugger tests that let me see what I was doing wrong and which lines. Python is so applicable. To improve, I think we could get thai(Spice?) for the food next time to add variety.

> I liked that it had fewer directed parts and relied more on us learning some of python's capabilities on our own





