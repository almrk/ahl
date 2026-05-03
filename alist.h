/*
 * Copyright (c) 2026 almrk
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef __ALIST_H
#define __ALIST_H

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
 * internal macros 
 */
/* decides how much the allocation should be increased when needed */
#define __ALIST_ALLOC_SIZE 16
/* gets size of the type that the elements are */
#define __ALIST_TYPE_SIZE(A) sizeof(A.data[0])
/* calculates the capacity needed for the list (A) based on the length change (C) */
#define __ALIST_CALC_CAP(A, C) \
    /* how many 16s needed to represent all or most of the length */ \
    (((A.length + C) / __ALIST_ALLOC_SIZE) * __ALIST_ALLOC_SIZE) + \
    /* figure out whether an extra 16 is needed to fit the array */ \
    ((((A.length + C) / __ALIST_ALLOC_SIZE) * __ALIST_ALLOC_SIZE) < (A.length + C) ? __ALIST_ALLOC_SIZE : 0)

/*
 * public macros
 */
/* simple wrapper for __ALIST_##T structs to make it look good */
#define alist(T) __ALIST_##T
/* defines a new alist struct based on a type (T) for the list to be stored in */
#define alist_new_variant(T) \
    typedef struct { \
        T * data; \
        size_t length; \
        size_t capacity; \
    } __ALIST_##T;
/* preallocate/reserve some space (N) for a future list (A) */
#define alist_reserve(A, N) \
    { \
        A.length = N; \
        A.capacity = __ALIST_CALC_CAP(A, 0); \
        A.data = malloc(A.capacity * __ALIST_TYPE_SIZE(A)); \
        assert(A.data != NULL); \
    }
/* creates a list (A) from an existing array (V) */
#define alist_from(A, V) \
    { \
        A.length = sizeof(V) / sizeof(V[0]); \
        A.capacity = __ALIST_CALC_CAP(A, 0); \
        A.data = malloc(A.capacity * sizeof(V[0])); \
        assert(A.data != NULL); \
        memcpy(A.data, V, sizeof(V)); \
    }
/* frees the list (A) */
#define alist_free(A) \
    { \
        if (A.data != NULL) \
            free(A.data); \
        A.data = NULL; \
        A.length = 0; \
        A.capacity = 0; \
    }
/* inserts a value (V) into list at a position (N) */
#define alist_insert(A, V, N) \
    { \
        assert(N >= 0 && N <= A.length); \
        if (A.length + 1 >= A.capacity) { \
            A.capacity = __ALIST_CALC_CAP(A, 1); \
            A.data = realloc(A.data, A.capacity * __ALIST_TYPE_SIZE(A)); \
            assert(A.data != NULL); \
        } \
        if (N != A.length) \
            memmove(A.data + N + 1, A.data + N, (A.length - N) * __ALIST_TYPE_SIZE(A)); \
        A.data[N] = V; \
        A.length++; \
    }
/* removes a value from the list (A) at position (N) */
#define alist_remove(A, N) \
    { \
        assert(N >= 0 && N < A.length); \
        if (__ALIST_CALC_CAP(A, -1) < A.capacity) { \
            A.capacity = __ALIST_CALC_CAP(A, -1); \
            A.data = realloc(A.data, A.capacity * __ALIST_TYPE_SIZE(A)); \
            assert(A.data != NULL); \
        } \
        if (N != A.length - 1) \
            memmove(A.data + N, A.data + N + 1, (A.length - N - 1) * __ALIST_TYPE_SIZE(A)); \
        A.length--; \
    }
/* wrapper macros around the insert and remove function for readability */
#define alist_push_back(A, V) alist_insert(A, V, A.length)
#define alist_push_front(A, V) alist_insert(A, V, 0)
#define alist_pop_back(A) alist_remove(A, A.length - 1)
#define alist_pop_front(A) alist_remove(A, 0)
/* getter macros for readability */
#define alist_back(A) A.data[A.length - 1]
#define alist_front(A) A.data[0]
/* pretty print the list */
#define alist_print(A, F) \
    { \
        for (size_t i = 0; i < A.length; i++) \
            printf("%s[%ld] = "F"\n", #A, i, A.data[i]); \
    }

#endif /* ALIST_H */
