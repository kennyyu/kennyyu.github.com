---
layout: post
title: "Reflecting on 3 Years of Teaching"
date: 2014-04-29 16:30
comments: true
categories: [teaching, school]
excerpt_separator: <!-- more -->
---

I taught my last section as an undergraduate today.
I've been a teaching fellow for a computer science class
every semester for the past three years, teaching:

* CS50 (Intro to Computer Science), Fall 2011
* CS51 (Abstraction and Design), Spring 2012 and Spring 2013
* CS61 (Systems Programming and Machine Organization), Fall 2012 and Fall 2013
* CS161 (Operating Systems), Spring 2014

At Harvard, a "Teaching Fellow" is the equivalent of
teaching assistants at most other universities.
Technically, I'm a "Course Assistant" as the title
"Teaching Fellow" is reserved for graduate students, but in
many of the classes that I've taught, the undergraduates have
the same (if not more) responsibilities than the graduate
students. These typically include teaching section, holding
office hours, and grading.

Over the past three years, I've attempted to have an impact in
all of the classes I've taught, and hopefully that impact will
last after I graduate. Also, I've learned several lessons about teaching
computer science classes, and I have advice for current
or future undergraduates considering teaching.

<!-- more -->

## Contributions

Below is a list of some of the ways I've contributed to the courses
that I've taught:

* **[CS50 Section Notes](https://github.com/kennyyu/cs50section)** -
  Before CS50 standardized the section notes
  for each section, many of the teaching fellows often prepared
  their own material for section (based on a set of example material
  from previous years). I took this as an opportunity to create
  material that I wish there were more of when I took the class:
  more interactive coding labs, and fun technical interview-esque
  problems for students with the extra time and interest. The end
  result of this include coding labs teaching students file IO
  (reading/writing pokemon structs from/to disk), implementing
  essential data structures, building a pokedex (end-to-end web
  application with a mysql backend), autocompletion (how to
  perform asynchronous http requests), and many brainteaser
  coding questions.

* **CS51 Moogle: 2-3 Trees** - CS51 is one of the few courses at Harvard
  that uses OCaml as the core programming language for the course. The
  class is famous for it's moogle problem set: at the end of the assignment,
  students will have a working web crawler that can index a graph of web pages
  and then rank them with different ranking algorithms (e.g., PageRank).
  The goal of this assignment is to teach students abstraction and modularization
  while implementing sets, maps, and rankers in different ways. In my first
  time teaching the class, I was tasked to write a new portion of the assignment:
  have students implement balanced trees with 2-3 trees. Implementing the 2-3 trees
  was definitely a non-trivial task, but what made it more difficult was structuring
  the code so that (1) it would be instructive for students who would need to understand
  and modify the code to implement the 2-3 trees, and (2) the code would allow
  for proper unit testing when the course staff later grades the student submissions.
  Two years later, the course is still using my code in that assignment!

* **CS51 Object Oriented Programming Notes** - When I took CS51, the course was still taught
  in both OCaml and Java. In my first year teaching the class, the professor
  decided to axe the Java portion of the class because it was too difficult to
  introduce object oriented programming concepts while having the students pick up
  and entirely new programming language in only a few weeks. As a result,
  the course staff decided to teach OO using the OO side of ocaml. I was tasked
  with writing the section notes for this material. It was a learning experience to
  figure out how to introduce so many new terms
  (objects, classes, subclassing, inheritance, interfaces,
  methods, overriding, polymorphism, subtyping, ...) in one section and not overwhelm
  the students. Two years later, the course is still using these section notes!

* **CS61** - When I taught CS61 for the first time, it was also
  Eddie Kohler's first time as the instructor for the course. He taught the course
  differently from previous years and emphasized different concepts and as a result,
  the course required a whole new set of section notes. Furthermore, the
  course had a much smaller staff than the previous classes I had taught. As a result,
  I ended contributing to and writing many of the
  [section notes](http://cs61.seas.harvard.edu/wiki/2012/Section) for that year. I took
  that as an opportunity to present the course material in a different light
  from the way material was presented in lecture, hopefully providing confused students a
  clearer picture of course concepts. In my second time teaching the class, I was one of
  the few returning course staff from the previous year, and I felt honored
  that Eddie valued my opinion
  on what I thought were the good and bad parts from the previous year.

* **[CS161 Synchronization Problems](/blog/2014/03/20/writing-synchronization-problems-for-os161/)** - At the beginning of this semester, I was tasked
  with writing the sychronization problems for the synchronization problem set. I
  tried to phrase the problem in an amusing and instructive way, and hopefully
  these problems will be used again in future offerings of the class.

In summary, an undergraduate teaching fellow can have a **huge and lasting impact**
on a course, including coming up with new assignments, writing new section notes, or
directing the overall direction of a course.

## Lessons Learned

After teaching in so many different classes and so many different
students over the past three years, I've learned a few lessons:

* **Students can achieve more than they think they can.** I remember before teaching my very
  first section for CS50, I was told that my section was a "More Comfortable" section. In CS50,
  students are placed into sections based on how they self-identify themselves into the buckets
  "Less Comfortable", "More Comfortable", and "Somwhere In Between." As a result, I spent that
  week preparing material I thought would be appropriate for more advanced students (material
  including code labs and fun brain teaser technical interview questions). When I stepped
  into the very first section and double checked with students that this was a more comfortable
  section, they all gave me grim stares of horror and told me that the section was actually
  "Somewhere in Between." It turns out that the head TFs for the class had accidentally
  informed incorrectly about my section. However, I still taught the section as if it were
  more comfortable: I still prepared for the code labs and brain teaser coding questions,
  and I tried to be as clear and instructive as I could in my slides and explanations
  of course concepts. At the end of the semester, many of the students did very well
  in the class and thought section was taught at an appropriate, if not slow, pace.
  As a result, I learned that students can undervalue their abilities: the
  students regarded themselves as "somewhere in between" when they achieved just as well
  as the "more comfortable" students.

* **Make section relevent and useful for the students who attend.**
  In all of the courses that I've
  taught, section was always optional but highly encouraged. I've been in many classes
  were I had required section that I thought was pointless, or I've attended optional sections
  only to find them unhelpful, discouraging me from attending future sections. As a result,
  I highly value the students' opinion when I do have the privilege of them
  attending my section, I want to make all of my sections helpful and useful for
  the students that choose to attend. To do this, for CS50,
  CS51, and CS61, I would always email a short anonymous feedback survey to students in
  my section
  to see what they thought was good and bad, and what they wanted to cover the following
  week. I took this feedback to heart when planning material for sectiones, and as a result,
  my sections always had a consistently near 100% (and for CS61 my first time, > 100%)
  attendance, when many other sectiones taught by other course staff had lower a lower
  attendance rate.

* **Effective teaching requires planning, planning, planning.** Before every section,
  I would always plan out the agenda for the section, making sure every concept transitioned
  smoothly to the next, and I had clear explanations and guiding questions to motivate
  the material. Often, planning took longer than the actual length of time of section.
  I learned very quickly that I was better and more comfortable teaching
  using the white board/chalk board than using a slideshow. Using the board allowed
  for more interactivity with students, and it made it easier to draw diagrams. Also,
  writing things down on the board give time for students to pause and think, whereas
  it is often difficult for students to read the text on slides while at the same time
  having to listen to what the instructor has to say. As a result, I filled notebooks
  with notes on how I would present the material in section, carefully planning out
  my boardwork, how to make the most effective use of the board, and planning
  diagrams I would use to explain the concepts. From this experience,
  I learned to appreciate and admire the planning teachers have to do in preparation for
  classes, and I also learned that I greatly enjoy the lesson planning part
  of teaching.

* **The most valuable thing you can do for students at office hours is to teach
  students how to discover the answers themselves.** One of the things I've
  learned in my four years as an undergraduate is how to go about searching for
  an answer to a question--often involving googling, experimenting at the command line,
  and code reading. As I've moved on to higher level and more difficult courses,
  the thing that I notice more about the more advanced students is their ability
  to independently acknowledge what they don't know, and then take the initiative to
  go about searching for the answer themselves. My experience with CS50 office hours
  typically involved conversations of the form: "Student: Things don't work,
  can you fix it? Me: what have you tried? Student: not much." and the student
  would then sit with me until the problem was resolved. At office hours for CS161,
  the conversations are typically of the form: "Student: Things don't work,
  do you have any ideas why? Me: what have you tried? Student: gdb, grep, find,
  binary searching the problem..." As a result, I realize that what makes students
  more "advanced" is their ability to self-diagnose their own problems and take
  the initiative to resolve them. Thus, my philosophy for office hours is to emphasize
  teaching students the tools to go about solving a problem instead of telling
  them the answer directly. One of my students
  remarked on this philosophy in a comment in the Q guide,
  stating "Kenny has tough love at office hours."

* **Grading is very difficult.** For me, grading is typically the most difficult
  and time consuming part of being a TF. Automated testing for correctness is
  not enough, as students typically (and rightfully) want in-depth feedback on how
  they can improve. As a result, much of my experience grading as a TF has been
  learning how to give appropriate and useful feedback, and I still have much to learn
  in this area.

* **Professors are people too.** When you're taking a class and spending many
  all-nighters on a problem set, it's easy to assume the professors are monsters
  and forget
  that professors are people too with their own lives, families, and goals.
  After working with four different instructors on their course staff, I see
  the course from the course staff point of view and I begin to understand
  why professors structure the courses the way they do, and how much they do
  in fact care about their courses and students, despite them not seeming to do
  so when you're up coding late into the early morning.


## Advice for Current and Future Undergraduates

After all the lessons I've learned and work I've put into teaching, I highly
encourage other undergraduates to consider teaching as well for the following
reasons:

* **Teaching is a great opportunity to get to know professors.** For large
  lecture classes (typically the intro courses), it can be very difficult
  to get an opportunity to talk one-on-one with professors and have them
  know who you are. When you are on the course staff, the instructor personally
  relies on you and the other course staff to run the course.
  You get the rare opportunity to work with them and get to know them
  on a more personal level.

* **You don't really understand the material until you have to teach it to someone else.**
  Teaching is great opportunity to review and solidify your understanding of
  the course material, and in my experience when I teach, I always learn something
  that I didn't know when I first learned the material.

* **You get to see how a course is run and control the direction of a course.**
  When you're on the course staff, you see and run everything: the infrastructure
  for distributing and receiving student submissions, the scripts and tools
  used for grading, the discussions for deciding what to cover in the next lecture, section
  or assignment, and more. As a result, course staff can typically have a large
  impact on a course, including coming up with new assignments, section material, or
  guiding the direction of the course material.

* **You become a mentor figure for underclassmen.** I still remember the legendary
  TFs I've had and how I admire them want to emulate them. When you teach,
  you often become a mentor for students entering the concentration, and you can
  have a large influence on the courses they choose and how they progress
  through their time at Harvard within the concentration.

Of course, there are downsides as well for being a teaching fellow:

* **Office hours is 24/7, even for classes you're not teaching.** For large classes,
  you often have many friends in the class. As a result, friends will direct
  their questions to you in-person, through instant message, and through many other
  means even when you're not having office hours. You'll also get questions for
  classes that you're not teaching. It can be difficult to draw the boundary
  between being a helpful friend and being a teaching fellow.

* **It is time consuming.** This semester, I've probably spent more time working on
  CS161-related work than any of my actual courses. Office hours, teaching, preparing
  for section, grading, attending lecture (for the hybrid classroom) can really add up.
  In my opinion, it's like taking a fifth class.


## Three Years Later

After three years of teaching, 4 different classes,
3 [Certificates of Excellence in Teaching](http://bokcenter.harvard.edu/icb/icb.do?keyword=k1985&pageid=icb.page29684), over 40 sections taught, and nearly 100 students I've
had the privilege of teaching, I've seen some of my own students become
teaching fellows for the same classes or other classes (I'm a grand-TF, haha),
and I like to think
I influenced their decision in some way. I've also had many underclassmen
in my section ask for computer science advice, and I've now seen them advanced
through multiple classes within the concentration.


I want to personally thank David, Greg, Eddie, and Margo for giving me the
opportunity to work with them and teach: teaching has definitely influenced
my undergraduate experiece in a significant and positive way, and college
would not have been the same without it.

Being a teaching fellow has been an important experience for me in
terms of self-discovery: I learned that I really like to teach and plan lessons,
and this makes me want to pursue some teaching-related work in my future.

