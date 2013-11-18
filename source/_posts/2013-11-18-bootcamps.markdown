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

My goal this smester was to restart the bootcamps and to revamp the curriculum. Below is the
curriculum I designed for this semester and links to the appropriate respositories and wikis.

## Bootcamp Curriculum

TODO: include link to bootcamp-main

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

TODO: wiki, pull requests, github

## Design Goals

TODO: TALK ABOUT GOALS

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
    encouraged students to install the [GH Diff Highligh Chrome Extension](https://chrome.google.com/webstore/detail/gh-diff-highlight/gjljgldconccfbldbnnpbgahpckhjcfj)
    to colorize pull request diffs. Workflow for bootcamps:

    1.  students would fork our main bootcamp repository
    2.  setup a pull request from their master branch
    3.  do exercises and push commits to their master branch, which will update their pull request

    [Here](https://github.com/hcs/bootcamp-python/pulls) are examples of the
    feedback we provided on the Intro to Python bootcamp.

*   **Reusable.** I am a senior and will be graduating soon; as a result, I
    want the bootcamps to be reusable after I leave. Because of this,
    I placed made all the bootcamps as open source github repositories
    so that they may be reused, updated, and forked as necessary in the future.

## Results

TODO: attendance, gender ratio, feedback, demographics from spreadsheet



