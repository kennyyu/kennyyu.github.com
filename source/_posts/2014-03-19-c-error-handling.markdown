---
layout: post
title: "C Error Handling"
date: 2014-03-19 19:42
comments: true
categories: [c, error handling]
---

After taking an operating systems class last year and taking a data systems
class this semester, I've picked up a few C patterns
to make it easier to handle error conditions in C.

Consider the following example from my data systems class, where I initialize
a directory to act as persistent storage for my database.

``` c storage struct
struct storage {
    char st_dbdir[128];   // name of the db directory
    struct file *st_file; // pointer to metadata file
    struct lock *st_lock; // protect addition of columns
    struct columnarray *st_open_cols; // array of open columns
};
```

<!-- more -->

Here's a first pass at initializing a storage struct. In this example,
I ignore all errors and will throw an assertion error if an error
occurs.

``` c storage: naive initialization
struct storage *
storage_init(char *dbdir)
{
    struct storage *storage = malloc(sizeof(struct storage));
    assert(storage != NULL);

    storage->st_lock = lock_create();
    assert(storage->st_lock != NULL);

    storage->st_open_cols = columnarray_create();
    assert(storage->st_open_cols != NULL);

    assert(mkdir(dbdir, S_IRWXU) == 0);

    strcpy(storage->st_dbdir, dbdir);
    char buf[128];
    sprintf(buf, "%s/%s", dbdir, METADATA_FILENAME);
    storage->st_file = file_open(buf);
    assert(storage->st_file != NULL);

    return storage;
}
```

Obviously, this is not robust. If any of the operations return
an error, we would get an assertion failure and our server
process would exit unexpectedly. Thus, we need to check for errors
and cleanup all the calls that occurred before the error.

``` c storage: quadratic error handling
struct storage *
storage_init(char *dbdir)
{
    struct storage *storage = malloc(sizeof(struct storage));
    if (storage == NULL) {
        return NULL;
    }

    storage->st_lock = lock_create();
    if (storage->st_lock == NULL) {
        free(storage);
        return NULL;
    }

    storage->st_open_cols = columnarray_create();
    if (storage->st_open_cols == NULL) {
        lock_destroy(storage->st_lock);
        free(storage);
        return NULL;
    }

    int result = mkdir(dbdir, S_IRWXU);
    if (result) {
        columnarray_destroy(storage->st_open_cols);
        lock_destroy(storage->st_lock);
        free(storage);
        return NULL;
    }

    strcpy(storage->st_dbdir, dbdir);
    char buf[128];
    sprintf(buf, "%s/%s", dbdir, METADATA_FILENAME);
    storage->st_file = file_open(buf);
    if (storage->st_file == NULL) {
        assert(rmdir(dbdir) == 0);
        columnarray_destroy(storage->st_open_cols);
        lock_destroy(storage->st_lock);
        free(storage);
        return NULL;
    }

    return storage;
}
```

As you can see, performing error handling naively like this
results in quadratic growth in cleanup operations: each
error checking needs to cleanup every operation before it,
and as a result, the `free(storage)` line gets repeated
multiple times. Can we do better?

Yes! The key to this is use `goto` statements. Many
introductory computer science courses discourage use
of goto statements, and rightfully so: goto statements,
if used inappropriately, can lead to spaghetti code
and can make code very difficult to reason about. However,
error handling is a perfect use for goto statements
to avoid quadratic code growth.

``` c storage: goto error handling
struct storage *
storage_init(char *dbdir)
{
    struct storage *storage = malloc(sizeof(struct storage));
    if (storage == NULL) {
        goto done;
    }

    storage->st_lock = lock_create();
    if (storage->st_lock == NULL) {
        goto cleanup_malloc;
    }

    storage->st_open_cols = columnarray_create();
    if (storage->st_open_cols == NULL) {
        goto cleanup_lock;
    }

    int result = mkdir(dbdir, S_IRWXU);
    if (result) {
        goto cleanup_colarray;
    }

    strcpy(storage->st_dbdir, dbdir);
    char buf[128];
    sprintf(buf, "%s/%s", dbdir, METADATA_FILENAME);
    storage->st_file = file_open(buf);
    if (storage->st_file == NULL) {
        goto cleanup_mkdir;
    }

    // success
    result = 0;
    goto done;

  cleanup_mkdir:
    assert(rmdir(dbdir) == 0);
  cleanup_colarray:
    columnarray_destroy(storage->st_open_cols);
  cleanup_lock:
    lock_destroy(storage->st_lock);
  cleanup_malloc:
    free(storage);
    storage = NULL;
  done:
    return storage;
}
```

By laying out
the error handling code labels in reverse order in which
the operations were invoked, we can quickly jump
to the appropriate position to start cleaning up
all the operations that occurred before it. This eliminates
the quadratic code growth in error handling! Furthermore,
there is only one exit point of this function (at the very
bottom), and reasoning about exit points for this version
is much easier than the previous version, especially
when we throw in concurrencry primitivies and needing to remember
to release locks.

To eliminate the boiler plate of checking the return value
and then jumping to the appropriate label on error, I wrote
a couple of useful macros. It relies on design decision
to make all functions that may have an error:

1. Return `NULL` (e.g., if the function allocates a data structure)
2. Return `int`, where the int is an error code specific to your application, and 0 is success.

``` c dberror.h
#ifndef _DBERROR_H_
#define _DBERROR_H_

enum dberror {
    DBSUCCESS = 0,
    DBENOMEM,
    ... // other errors
};

const char *dberror_string(enum dberror result);

void dberror_log(char *msg, const char *file,
                 int line, const char *func);

#define DBLOG(result) \
        dberror_log((char *) dberror_string((result)), \
                     __FILE__, __LINE__, __func__);

#endif
```
In this code, I define an enumeration `enum dberror` to represent
the different kinds of error codes for my database application.
I also provide a `DBLOG(result)` macro which, when given an error
code, prints out the human readable string for that code, as well
as the file, line number, and function where `DBLOG` was invoked.
By designing your internal API using the two points above and invoking
`DBLOG` every time an error occurs, we effectively get a stack
trace for every error!

Now let's combine this error logging facility to reduce the
boiler plate for the error handling code above.

``` c try.h
#ifndef _TRY_H_
#define _TRY_H_

#include <stddef.h>
#include "dberror.h"

#define TRY(result, expr, cleanup) \
    (result) = (expr); \
    if ((result)) { \
        DBLOG((result)); \
        goto cleanup; \
    }

#define TRYNULL(result, err, var, expr, cleanup) \
    (var) = (expr); \
    if ((var) == NULL) { \
        (result) = (err); \
        DBLOG((result)); \
        goto cleanup; \
    }

#endif
```

The `TRY` macro allows us to execute `expr`, and if
that returns a nonzero error code, we jump to the provided
cleanup label.

The `TRYNULL` macro is similar--it assigns `var` to be the
result of `expr`, checks if `var` is `NULL`, and if it is,
assigns the appropriate error code to result and jumps to
the cleanup label.

Using this, let's write our final version of storage:

```c storage: try pattern
struct storage *
storage_init(char *dbdir)
{
    int result;
    struct storage *storage;

    TRYNULL(result, DBENOMEM, storage, malloc(sizeof(struct storage)), done);
    TRYNULL(result, DBENOMEM, storage->st_lock, lock_create(), cleanup_malloc);
    TRYNULL(result, DBENOMEM, storage->st_open_cols, columnarray_create(), cleanup_lock);
    TRY(result, mkdir(dbdir, S_IRWXU), cleanup_colarray);

    strcpy(storage->st_dbdir, dbdir);
    char buf[128];
    sprintf(buf, "%s/%s", dbdir, METADATA_FILENAME);
    TRYNULL(result, DBEIONOFILE, storage->st_file, file_open(buf), cleanup_mkdir);

    // success
    result = 0;
    goto done;

  cleanup_mkdir:
    assert(rmdir(dbdir) == 0);
  cleanup_colarray:
    columnarray_destroy(storage->st_open_cols);
  cleanup_lock:
    lock_destroy(storage->st_lock);
  cleanup_malloc:
    free(storage);
    storage = NULL;
  done:
    return storage;
}
```

Nice and simple! Here's all the things that this pattern addressed:

* Allow error handling using only linear, and not quadratic, code growth.
* Our `TRY` and `TRYNULL` macros eliminate the boiler plate, and automatically performs logging to give us a stack trace of errors.
