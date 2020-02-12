---
layout: post
title: "Coupling and the Coupon Collector"
date: 2012-06-24 21:43
author: Kenny Yu
comments: true
categories: [math, statistics, probability, markov chains, coupling]
---

In the fall semester last year, I took [Stat 110](http://blog.bokcenter.harvard.edu/2012/01/23/stat-110-lectures-are-now-available-on-itunesu/),
an introductory
statistics course focusing on probability. I had done probability in contest
math from high school, but this course was my first real rigorous treatment
of probability.

One of the most interesting problems I saw in the course involves Markov chains
and a simple and elegant solution using another interesting problem we saw
earlier in the course--[the coupon collector's problem](http://en.wikipedia.org/wiki/Coupon_collector%27s_problem).

## Random-to-Top Shuffling Problem

Suppose $n$ cards are placed in order on a table. Consider the following shuffling
procedure: Pick a card at random from the deck and place it on top of the deck.
What is the expected number of times we need to repeat the process to arrive
at a "random" deck, for some suitable definition of "random"?

To solve this question, we'll need to answer a seemingly unrelated question first.

## Coupon Collector's Problem (aka. The Toy Collector's Problem)

A certain brand of cereal always distributes a toy in every cereal box. The toy
chosen for each box is chosen randomly from a set of $n$ distinct toys. A toy
collector wishes to collect all $n$ distinct toys. What is the expected number
of cereal boxes must the toy collector buy so that the toy collector collects
all $n$ distinct toys?

## Solution to the Toy Collector's Problem

The key to understanding this problem is to break the task of collecting all
$n$ distinct toys into different stages: what is the expected number of cereal
boxes that the toy collector has to buy to get the $i$-th new toy?

Let random variable $X_i$ be the number of boxes it takes for the toy collector
to collect the $i$-th new toy after the $i-1$-th toy has already been collected.
(Note: this does NOT mean assign numbers to toys
and then collect the $i$-th toy. Instead, this means that after $X_i$ boxes,
the toy collector would have collected $i$ distinct toys, but with only $X_i - 1$
boxes, the toy collector would have only collected $i-1$ distinct toys.)

Clearly $E(X_1) = 1$, because the toy collector starts off with no toys. Now
consider the $i$-th toy. After the $i-1$-th toy has been collected, then there
are $n - (i-1)$ possible toys that could be the new $i$-th toy. We can interpret
the process of waiting for the $i$-th new toy as a [geometric distribution](http://en.wikipedia.org/wiki/Geometric_distribution), where
each trial is buying another cereal box, "success" is getting any of the
$n - (i-1)$ uncollected toys, and
"failure" is getting any of the already collected $i - 1$ toys. From this point
of view, we see that

$$X_i - 1 \sim \textrm{Geom}(p)$$

where the probability of success $p$ is

$$p = \frac{n - (i-1)}{n}.$$

Here, our definition of the geometric distribution does NOT include the success.
Using the expectation of a geometric distribution, we have that the expected number
of cereal boxes the toy collector must collect to get the $i$-th new toy after
collecting $i-1$ toys is

$$E(X_i - 1) = \frac{1 - p}{p}$$

$$E(X_i) = \frac{1}{p} = \frac{n}{n - (i - 1)}.$$

Now let random variable $X$ to be the number of cereal boxes the toy collector
needs to buy to collect all $n$ distinct toys. Since we have separated the
process into collecting the $i$-th new toy, then

$$X = X_1 + X_2 + \cdots + X_n.$$

Using linearity of expectation, we can compute the expected value of $X$
by summing the individual expectations of $X_i$. Thus, we obtain the following
result:

$$E(X) = E(X_1 + X_2 + X_3 + \cdots + X_n)$$

$$E(X) = E(X_1) + E(X_2) + E(X_3) + \cdots + E(X_n)$$

$$E(X) = n\left( 1 + \frac{1}{2} + \frac{1}{3} + \cdots + \frac{1}{n} \right).$$

This is the harmonic series! The harmonic series diverges to infinity and
grows approximately as $\gamma + \log n$ where $\gamma \approx 0.57722$ is
Euler's constant. Thus, we can approximate the expected number of cereal boxes with:

$$E(X) \approx n (\gamma + \log n).$$

## Solution to the Random-to-Top Shuffling Problem

### Markov Chains and Stationary Distrubutions

Coming back to the random-to-top shuffling problem, we first need to define
our notion of "random" for our deck. In order to do this, we use Markov chains.

For our Markov chain, let our states be all $n!$ permutations of $n$-card deck,
and two states are adjacent if and only if it is possible to reach one of the
states from the other through one step of this shuffle. For any state, we move to
one of its $n-1$ neighbors with probability $\frac{1}{n}$, or stay at the same
state with probability $\frac{1}{n}$. Since all of our $n!$ states has degree
$n$ (including loops), then by symmetry, the probability of having any
permutation is equally likely. Thus, the stationary distribution for our
random-to-top shuffling Markov process is the uniform vector

$$\vec{s} = \left(\frac{1}{n!}, ..., \frac{1}{n!}\right).$$

Thus, to define our notion of a "random" deck, we would like that after
implementing our shuffling algorithm, the resulting deck is sampled from our
stationary distribution: that is, our resulting deck is equally likely
to be any of the $n!$ permutations.

### Coupling

Now that we have established that our shuffling process can be modeled with
a Markov chain that has a stationary distribution, we use the idea of "coupling"
to arrive at our solution.

Let deck $A$ be our original deck, and let deck $B$ be uniformly randomly sampled
from all $n!$ permutations. Since the stationary distribution for our shuffling
process is the uniform distribution, then deck $B$ is sampled from the
stationary distribution.

We use the fact that if we start our Markov process from a state sampled
from the stationary distribution, then the resulting state will also be
sampled from the stationary distribution. More formally:

**Lemma.** *Let $\vec{s}$
be the stationary distribution of our Markov chain.
Let $X_0$ be our starting state, and let it
be sampled from the stationary distribution (i.e. $P(X_0 = i) = s_i$). Then
the resulting state $X_1$ after running the Markov chain for one step
will also be sampled from $\vec{s}$*.

Now consider our "coupling" strategy: every time we move a card $C$ to the top
of deck $A$, we locate card $C$ in deck $B$ and place it on top of the deck.
Note that the physical process of how we chose card $C$ in the two decks is
different: we choose a random position in deck $A$, whereas we located card
$C$ in deck $B$. Although the process of how we chose card $C$ is different,
from deck $B$'s perspective, $C$ is simply a card selected at random. Using
our lemma, we have that deck $B$ still remains sampled from the stationary
distribution after moving card $C$ to the top of deck $B$.

We note that after $t$ steps, all the cards that have been touched
up to time $t$ will be in the same order on top of both decks.
When all the cards of deck A and deck B are in the same order
after some time $T$ steps, we will have that deck A and deck B are both
sampled from the stationary distribution (because B always stays
stationary through our coupling strategy). Thus, after $T$ steps,
deck A will satisfy our notion of a "random" deck. We wish to compute $E(T)$.

How do we compute $E(T)$? We note that both decks will be the same once we have
touched all the cards. Therefore, we wish to compute the expected number
of random-to-top shuffles needed to touch all the cards.
This is an instance of the coupon collector's problem! Instead of
touching all $n$ cards, we wish the collect all $n$ coupons. Thus,
after approximately $n (\gamma + \log n)$
random-to-top shuffles, our original deck $A$
will be a "random" deck. For $n = 52$, we require $E(T) \approx 236$ shuffles
to randomize our deck.
