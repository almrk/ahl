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
#ifndef AMAP_H
#define AMAP_H

#include <stddef.h>

/*
 * public macros
 */
/* wrapper for AMAP_##KT##_##VT */
#define amap(KT, VT) AMAP_MAP_##KT##_##VT;
/* defines a new amap struct based on the key (KT) and value (VT) type */
#define amap_new_variant(KT, VT) \
    typedef struct AMAP_ENTRY_##KT##_##VT { \
        KT key; \
        VT value; \
        struct AMAP_ENTRY_##KT##_##VT *next; \
    } AMAP_ENTRY_##KT##_##VT; \
    typedef struct { \
        AMAP_ENTRY_##KT##_##VT **buckets; \
        size_t count; \
        size_t size; \
    } AMAP_MAP_##KT##_##VT;
/* frees the map (A) */
#define amap_free(A)
#define amap_insert(A, K, V)
#define amap_remove(A, K)
#define amap_contains()

#endif /* AMAP_H */
