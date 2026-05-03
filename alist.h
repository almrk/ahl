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
#define __ALIST_TYPE_SIZE(ALIST) sizeof(ALIST.data[0])
/* calculates the capacity needed for the list (ALIST) based on the length change (CHG) */
#define __ALIST_CALC_CAP(ALIST, CHG) \
    /* how many 16s needed to represent all or most of the length */ \
    (((ALIST.length + CHG) / __ALIST_ALLOC_SIZE) * __ALIST_ALLOC_SIZE) + \
    /* figure out whether an extra 16 is needed to fit the array */ \
    ((((ALIST.length + CHG) / __ALIST_ALLOC_SIZE) * __ALIST_ALLOC_SIZE) < (ALIST.length + CHG) ? __ALIST_ALLOC_SIZE : 0)

/*
 * public macros
 */
/* simple wrapper for __ALIST_##TYPE structs to make it look good */
#define alist(TYPE) __ALIST_##TYPE
/* defines a new alist struct based on a type (TYPE) for the list to be stored in */
#define alist_new_variant(TYPE) \
    typedef struct { \
        TYPE##* data; \
        size_t length; \
        size_t capacity; \
    } __ALIST_##TYPE;
/* preallocate/reserve some space (N) for a future list (ALIST) */
#define alist_reserve(ALIST, N) \
    { \
        ALIST.length = N; \
        ALIST.capacity = __ALIST_CALC_CAP(ALIST, 0); \
        ALIST.data = malloc(ALIST.capacity * __ALIST_TYPE_SIZE(ALIST)); \
        assert(ALIST.data != NULL); \
    }
/* creates a list (ALIST) from an existing array (ARR) */
#define alist_from(ALIST, ARR) \
    { \
        ALIST.length = sizeof(ARR) / sizeof(ARR[0]); \
        ALIST.capacity = __ALIST_CALC_CAP(ALIST, 0); \
        ALIST.data = malloc(ALIST.capacity * sizeof(ARR[0])); \
        assert(ALIST.data != NULL); \
        memcpy(ALIST.data, ARR, sizeof(ARR)); \
    }
/* frees the list (ALIST) */
#define alist_free(ALIST) \
    { \
        if (ALIST.data != NULL) \
            free(ALIST.data); \
        ALIST.data = NULL; \
        ALIST.length = 0; \
        ALIST.capacity = 0; \
    }
/* inserts a value (VAL) into list (ALIST) at a position (N) */
#define alist_insert(ALIST, VAL, N) \
    { \
        assert(N >= 0 && N <= ALIST.length); \
        if (ALIST.length + 1 >= ALIST.capacity) { \
            ALIST.capacity = __ALIST_CALC_CAP(ALIST, 1); \
            ALIST.data = realloc(ALIST.data, ALIST.capacity * __ALIST_TYPE_SIZE(ALIST)); \
            assert(ALIST.data != NULL); \
        } \
        if (N != ALIST.length) \
            memmove(ALIST.data + N + 1, ALIST.data + N, (ALIST.length - N) * __ALIST_TYPE_SIZE(ALIST)); \
        ALIST.data[N] = VAL; \
        ALIST.length++; \
    }
/* removes a value from the list (ALIST) at position (N) */
#define alist_remove(ALIST, N) \
    { \
        assert(N >= 0 && N < ALIST.length); \
        if (__ALIST_CALC_CAP(ALIST, -1) < ALIST.capacity) { \
            ALIST.capacity = __ALIST_CALC_CAP(ALIST, -1); \
            ALIST.data = realloc(ALIST.data, ALIST.capacity * __ALIST_TYPE_SIZE(ALIST)); \
            assert(ALIST.data != NULL); \
        } \
        if (N != ALIST.length - 1) \
            memmove(ALIST.data + N, ALIST.data + N + 1, (ALIST.length - N - 1) * __ALIST_TYPE_SIZE(ALIST)); \
        ALIST.length--; \
    }
/* wrapper macros around the insert and remove function for readability */
#define alist_push_back(ALIST, VAL) alist_insert(ALIST, VAL, ALIST.length)
#define alist_push_front(ALIST, VAL) alist_insert(ALIST, VAL, 0)
#define alist_pop_back(ALIST) alist_remove(ALIST, ALIST.length - 1)
#define alist_pop_front(ALIST) alist_remove(ALIST, 0)
/* getter macros for readability */
#define alist_back(ALIST) ALIST.data[ALIST.length - 1]
#define alist_front(ALIST) ALIST.data[0]
/* pretty print the list (ALIST) */
#define alist_print(ALIST, FMT) \
    { \
        for (size_t i = 0; i < ALIST.length; i++) \
            printf("%s[%ld] = "FMT"\n", #ALIST, i, ALIST.data[i]); \
    }

#endif /* __ALIST_H */
