---
layout: post
title: "A Twist on Binary Search"
date: 2012-05-18 12:00
comments: true
categories: [binary search, c++, math, proofs]
author: Kenny Yu
---

This past semester, I took a graduate course, 
[CS 207](http://iacs.seas.harvard.edu/courses/cs207/) - Systems Development
in Computational Science. In the course, we talked about good software 
engineering practices in C++ (but the lessons span beyond C++), in particular
representation invariants, abstraction functions, and writing solid code
specifications so that one could even prove things about code. The professor made
a couple of [blog](http://read.seas.harvard.edu/cs207/2012/)
 entries for some of the lectures, explaining cool tricks with iterators and bits. 

Early in the semester, we discussed several implementations of binary search, starting
from a simplistic version and incrementally building up to a production-ready
version. I thought the binary search discussion was an extremely eye-opening
exercise; it was my first time seeing invariants being used in proofs to prove
properties about code.

Below is how I've written binary search since high school: 
{% highlight c++ %}
/** Returns the index of any occurrence of @a x in @a a
 * @pre @a a has length equal to n
 * @pre @a a is sorted in increasing order
 * @return -1 if not found 
 */
int binary_search(int *a, int n, int x) {
  int lo = 0;
  int hi = n - 1;
  while (lo <= hi) {
    int mid = (lo + hi) / 2;
    if (x == a[mid])
      return mid;
    if (x < a[mid])
      hi = mid - 1;
    else
      lo = mid + 1;
  }
  return -1;
}
{% endhighlight %}
Here, I am using [Doxygen](http://www.stack.nl/~dimitri/doxygen/) style comments
for my specifications. In this version of binary search, I return the index of 
*any* occurence of item `x` in array `a`, or return `-1` if there is no such
occurrence. While this implementation is acceptable for an array of ints, it
is not particularly useful for other data types. 

Using C++ templates, we can generalize this implementation to make it
polymorphic for any type `T`, provided we provide a suitable comparison function
`compare` where `compare(p,q)` returns true if and only if `p` is less than `q`
for some ordering of values of type `T`. Thus, here is our attempt #2 at binary
search:
{% highlight C++ %}
/** Returns the index of any occurrence of @a x in @a a
 * @param compare(p,q) returns true if p < q
 * @pre @a a has length equal to @a n
 * @pre @a a is sorted by @a compare
 * @return -1 if not found 
 */
template<typename T, typename CMP>
int binary_search2(T *a, int n, T x, CMP compare) {
  int l = 0;
  int r = n;
  while (l < r) {
    int m = l + (r - l) / 2; // fix overflow issues
    if (compare(a[m],x))
      l = m + 1;
    else if (compare(x,a[m]))
      r = m;
    else
      return l;
  }
  return - 1;
}
{% endhighlight %}
Now, in order to call binary search, we must provide a function object `compare`
that defines how we compare two elements of type `T`. Below is an example of how
we would invoke this version of binary search:
{% highlight c++ %}
struct IntComp {
  bool operator()(int x, int y) {
    return x < y;
  }
};

int main(void) {
  int arr[12] = {2,3,4,5,7,8,9,11,13,15,16,17};
  std::cout << binary_search2(arr, 12, 15, IntComp()) << std::endl;
  return 0;
}
{% endhighlight %}
We overload `operator()` to allow `IntComp` objects to be invoked like functions,
and we pass an instance of `IntComp` to `binary_search2` whenever we perform
a binary search on an array of ints. 

Note one other difference between the two versions of binary search: in 
attempt #1, we had the line:
{% highlight c++ %}
int mid = (lo + hi) / 2;
{% endhighlight %}
whereas in attempt #2, we replaced this line with:
{% highlight c++ %}
int m = l + (r - l) / 2;
{% endhighlight %}
For all these years, I've been writing binary search incorrectly! In the first
version, we may run into integer overflow if `lo + hi` happen to be greater
than the maximum integer value for `int`! In the second version, we fix this
subtle bug by first subtracting `r` and `l`, then halving the difference and
add the result to `l` to calculate the new middle index `m`. By subtracting
first, we are guaranteed that `r - l` will not overflow (by the implicit
precondition that `r` and `l` are valid indices into the array and `r > l`), 
and thus `m` will also be a valid index into the array. 

We have generalized our binary search to work on an array containing any type.
But, we have actually done more than this. In C++, iterators overload pointer
syntax to represent collections of items. Using iterators, we can represent
an entire range of items in a collection with only two iterators--one pointing
to the beginning of the collection, and one pointing to the "position" after
the last element in the collection. 
See the CS 207 blog entries [here](http://read.seas.harvard.edu/cs207/2012/) 
for more information on C++ iterators. In our example, however, we represent
the array collection with a pointer to the first position and the number
of items in the list. Because binary search requires random access into our 
collection, *any collection represented by a random access iterator* will be
able to use the second version of our binary search!

Can we still do better? In our specification for binary search, note that we 
allowed the index of *any* occurrence of our search item `x` to be returned. 
This ambiguity makes it difficult to make any real use of the return value of 
binary search  (except simply to check whether the item is in the collection).
Instead of returning any index, what if we returned a *lower bound* position
of the element `x` in our collection? By lower bound, we mean the first index
into the array at which we should insert `x` and still keep the elements
in sorted order. 

For example, with the array `{0, 1, 2, 5, 5, 5, 7, 9}`, the
lower bound of `0` would be `0`, because we can insert `0` into index `0` and
still keep our array sorted. The lower bound of `-1` is also `0` by a similar
reasoning. The lower bound of `5` is `3` because `3` is the smallest index that
we can insert `5` and keep the array sorted. Similarly, the lower bound of `6`
is `6`. Note that the lower bound of `10` is `8`, which is not a valid index
into the array. This is okay because the return value only indicates the index
that one *could* insert an item and maintain the sorted property of the array.

To implement this, we can think of the array as a collection of boolean values
where the entries are `{false, false, ..., false, true, true, ... true}` (all
the falses occur together at the beginning of the array). The boolean values
correspond to whether our target element `x` is less than or equal to the
value in that array position. Our goal, then, is to find the first `true` in
the array, or return the last position (indicating that placing `x` at the
end of the array would maintain the sorted property of our array). Building 
on the polymorphism we introduced in attempt #2, here is attempt #3 using 
the lower bound idea:
{% highlight c++ %}
/** Return the lower-bound position of @a x in @a a
 * @param compare(p,q) returns true if p < q
 * @pre @a a has length equal to @a n
 * @pre @a a is sorted by @a compare
 * @post return R where 0 <= R <= @a n and:
 *   For all 0 <= i < n, 
 *      i < R iff a[i] < x
 *      i >= R iff a[i] >= x 
 */
template<typename T, typename CMP>
int lower_bound(T *a, int n, T x, CMP compare) {
  int l = 0;
  int r = n;
  while (l < r) {
    int m = l + (r - l) / 2;
    if (compare(a[m],x))
      l = m + 1;
    else
      r = m;
  }
  return l;
}
{% endhighlight %}
Nice, clean, and simple! 

Note that this version uses only *one* comparison instead of two (as we did
in attempts #1 and #2)! This lower bound idea not only tells us whether our
element `x` is the array, but where we should place it to keep the list sorted!

This code looks simple enough to verify the correctness by eyeballing it; but
can we make this rigorous? Can we *prove* the correctness of this code? Yes!
Here is the same piece of code but commented heavily with the proof of its
own correctness. 
{% highlight c++ %}
/** Return the lower-bound position of @a x in @a a
 * @param compare(p,q) returns true if p < q
 * @pre @a a has length equal to @a n
 * @pre @a a is sorted by @a compare
 * @post return R where 0 <= R <= @a n and:
 *   For all 0 <= i < n, 
 *      i < R iff a[i] < x
 *      i >= R iff a[i] >= x 
 */
template<typename T, typename CMP>
int lower_bound_proof(T *a, int n, T x, CMP compare) {
  // pre: for all i,j with 0 <= i <= j < n, we have a[i] <= a[j]
  // post: let R be the return value. Then 0 <= R <= n, and
  //   for all 0 <= i < n,
  //     i < R iff a[i] < x    (1)
  //     i >= R iff a[i] >= x  (2) 

  int l = 0;
  int r = n;
  while (l < r) {
    // PRE LOOP
    // loop invariant: l <= R <= r (always true in the loop)
    // decrementing function: d = r - l

    int m = l + (r - l) / 2; // if r - l >= 2, then (r - l)/2 >= 1,
                             //                so l < m < r
                             // if r - l == 1, then l = m < r, 
                             //                so l <= m < r

    if (compare(a[m],x)) {
      // we have a[m] < x. Then by (1), a[m] < x ==> m < R
      // then for all 0 <= i <= m, a[i] < x (b/c sorted)
      l = m + 1; // so l < l_new == m + 1 <= R
                 // r_new == r >= R
                 // so l_new <= R <= r_new
                 // and r_new - l_new < r - l (d decrements)
    } else {
      // we have a[m] >= x. Then by (2), a[m] >= x ==> m >= R
      // then for all m <= i < n, a[i] >= x (b/c sorted)
      r = m; // so r > r_new == m >= R
             // l_new == l <= R
             // so l_new <= R <= r_new
             // and r_new - l_new < r - l (d decrements)
    }

    // POST LOOP
    // loop invariant: l_new <= R <= r_new
    // decrementing function: r_new - l_new < r - l
  }

  // by the decrementing function, d eventually reaches 0;
  //      thus the loop terminates
  // by the loop invariant, we have l <= R <= r
  return l;
}
{% endhighlight %}
To prove the correctness, we make heavy use of the post condition:
{% highlight c++ %}
/**
 * @post return R where 0 <= R <= @a n and:
 *   For all 0 <= i < n, 
 *      i < R iff a[i] < x
 *      i >= R iff a[i] >= x 
 */
{% endhighlight %}
Thus, all elements at indices less than the return value `R` are less
than `x`, and all other elements are greater than or equal to `x`. We use this
both of these if and only if conditions in the two branches of the `if`
conditional to guide us on how we should update `l` or `r`. 

In both of the branches of the conditional, we have that the new values of
`l` and `r` are maintained so that `l <= R <= r` and still satisfy the
post condition of the function. Thus, the statement `l <= R <= r` is a
**loop invariant** of the `while` loop: it is always true on entering and
leaving the loop. To ensure that the loop terminates, we require a
**decrementing function**, a function that decreases on each iteration of
the loop and is equal to zero when the loop terminates. In this case, the 
obvious choice for the decrementing function would be `d = r - l`. We show
in both branches that the new values of `l` and `r` are such that
`r_new - l_new < r - l`, and so `d` decreases on each iteration. When
`d = 0`, we have that `l = r`, which is indeed when the loop terminates. Thus,
our final line `return l;` is proven correct by the combination of our
post conditions, pre conditions (array is sorted), loop invariant, and 
decrementing function. By analyzing the invariants in the code, the code almost
writes itself! Cool!

To view the code in its entirety (along with a couple of simple test harnesses
for each version of binary search), check out the source 
[here](/downloads/code/search.cpp).