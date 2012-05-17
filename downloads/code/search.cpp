#include <cstdio>
#include <cstdlib>
#include <assert.h>

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

/** Return the lower-bound position of @a x in @a a
 * @param compare(p,q) returns true if p < q
 * @pre @a a has length equal to @a n
 * @pre @a a is sorted by @a compare
 * @post return R where 0 <= R <= @a n and:
 *   For all 0 <= i < n, 
 *      if i < R, then a[i] < x
 *      otherwise if i >= R, then a[i] >= x 
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

/** Return the lower-bound position of @a x in @a a
 * @param compare(p,q) returns true if p < q
 * @pre @a a has length equal to @a n
 * @pre @a a is sorted by @a compare
 * @post return R where 0 <= R <= @a n and:
 *   For all 0 <= i < n, 
 *      if i < R, then a[i] < x
 *      otherwise if i >= R, then a[i] >= x 
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

void test_harness_bs1(void) {
  int arr[12] = {2,3,4,5,7,8,9,11,13,15,16,17};
  for (int i = 0; i < 12; i++) {
    int location = binary_search(arr, 12, arr[i]);
    if (location < 0) {
      printf("FAILURE: could not find %d in array\n", arr[i]);
      exit(-1);
    } else {
      printf("SUCCESS: found %d at position %d\n", arr[i], location);
    }
  }
  int location = binary_search(arr, 12, 12);
  if (location > 0) {
    printf("FAILURE: -1 should not be in array\n");
    exit(-1);
  } else {
    printf("SUCCESS: return -1 when not found\n");
  }
}

struct IntComp {
  bool operator()(int x, int y) {
    return x < y;
  }
};

void test_harness_bs2(void) {
  int arr[12] = {2,3,4,5,7,8,9,11,13,15,16,17};
  for (int i = 0; i < 12; i++) {
    int location = binary_search2(arr, 12, arr[i], IntComp());
    if (location < 0) {
      printf("FAILURE: could not find %d in array\n", arr[i]);
      exit(-1);
    } else {
      printf("SUCCESS: found %d at position %d\n", arr[i], location);
    }
  }
  int location = binary_search2(arr, 12, 12, IntComp());
  if (location > 0) {
    printf("FAILURE: -1 should not be in array\n");
    exit(-1);
  } else {
    printf("SUCCESS: return -1 when not found\n");
  }
}

void test_harness_lb(void) {
  int arr[8] = {0,1,2,5,5,5,7,9};
  assert(lower_bound(arr, 8, 0, IntComp()) == 0);
  assert(lower_bound(arr, 8, -1, IntComp()) == 0);
  assert(lower_bound(arr, 8, 5, IntComp()) == 3);
  assert(lower_bound(arr, 8, 6, IntComp()) == 6);
  assert(lower_bound(arr, 8, 10, IntComp()) == 8);
}

void test_harness_lbproof(void) {
  int arr[8] = {0,1,2,5,5,5,7,9};
  assert(lower_bound_proof(arr, 8, 0, IntComp()) == 0);
  assert(lower_bound_proof(arr, 8, -1, IntComp()) == 0);
  assert(lower_bound_proof(arr, 8, 5, IntComp()) == 3);
  assert(lower_bound_proof(arr, 8, 6, IntComp()) == 6);
  assert(lower_bound_proof(arr, 8, 10, IntComp()) == 8);
}

int main(void) {
  test_harness_bs1();
  test_harness_bs2();
  test_harness_lb();
  test_harness_lbproof();
}
