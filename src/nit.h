/*
  The MIT License (MIT)

  Copyright (c) 2014 qeep

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

/*
  nit.h
  This is the public api of the nit library.
*/

#ifndef _defined_nit_h_
#define _defined_nit_h_

/* For size_t, realloc and free. */
#include <stdlib.h>
/* For ULONG_MAX */
#include <limits.h>
/* Has definitions of nit_word, nit_size and NIT_WORD_MAX. */
#include "nit/config.h"

/*! Returned status from the nit functions.
  If a nit function returns anything other than NIT_OK the function call failed
  and the resulting data is undefined. However memory is never leaked. */
enum nit_status
  {
    /*! All is well. */
    NIT_OK = 0,
    /*! Substraction led to underflow. */
    NIT_UNDERFLOW,
    /*! Conversion to unsigned long led to to overflow.
      (the nit does not fit in a unsigned long) */
    NIT_OVERFLOW,
    /*! Could not allocate or reallocate memory. */
    NIT_MEMORY,
    /*! Division by zero. */
    NIT_DIVISION_BY_ZERO,
    /*! Buffer passed to nit_out_* was to small. */
    NIT_BUFFER_TO_SMALL,
    /*! Data in buffer passed to nit_in_* did not follow the correct format. */
    NIT_INVALID_FORMAT,
    /*! Two nits passed to a function shares memory, but
      this is not allowed for that function.
      (tip: x is probably the same nit as y or z when it should not be.) */
    NIT_SHARED_MEMORY,
    /*! One argument or the w pointer passed to a function was NULL when it
      should not be. */
    NIT_NULL_POINTER,
    /*! The nit has a word count of zero when it should be positive. */
    NIT_ZERO_LENGTH,
    /*! Oops, this function is included only as a placeholder.
      Perhaps update the package / repository? */
    NIT_UNINPLEMENTED,
  };

/*! A n-bit unsigned integer. */
struct nit
{
  /*! The integer words that make up this nit.
    The first word is the least significant word.
    There can not be any trailing zero words. */
  nit_word *w;
  /*! The number of words in this nit in number of words.
    A nit can not have zero words. */
  nit_size n;
};


/*
  Feeing memory.
*/

/*! Free the memory of x.
  If x->w is NULL the function does nothing. */
enum nit_status
nit_free (struct nit *x);

/*! Clears the nit structure. */
void
nit_clear (struct nit *x);

/*
  Integer converter
*/

/*! Convert to a nit from unsigned long. */
enum nit_status
nit_from_long (struct nit *x, unsigned long l);

/*! Convert nit to unsigned long.
  Check the returned status for overflow! */
enum nit_status
nit_to_long (struct nit *x, unsigned long *l);

/*
  Reading and writing nits
*/

/*! Write x into buffer in a human readable and platform independent hex format. */
enum nit_status
nit_out_hex (struct nit *x, char *buffer, size_t size);

/*! Read a hexadecimal packed nit from buffer into x. */
enum nit_status
nit_in_hex (struct nit *x, const char *buffer, size_t size);

/*
  Comparisons.
*/

/*! Returns 0 if x == y, -1 if x < y and 1 if x > y. */
int
nit_cmp (struct nit *x, struct nit *y);

/*
  Mathematical operators.
*/

/*! z = x + z */
enum nit_status
nit_add (struct nit *x, struct nit *y, struct nit *z);

/*! x = y - z
  Watch for underflow! */
enum nit_status
nit_sub (struct nit *x, struct nit *y, struct nit *z);

/*! x = y % z */
enum nit_status
nit_mod (struct nit *x, struct nit *y, struct nit *z);

/*! x = y / z */
enum nit_status
nit_div (struct nit *x, struct nit *y, struct nit *z);

/*! x = y * z */
enum nit_status
nit_mul (struct nit *x, struct nit *y, struct nit *z);

/*! x = y ** z */
enum nit_status
nit_pow (struct nit *x, struct nit *y, struct nit *z);

/*
  Bitwise operators
*/

/*! x = y ^ z */
enum nit_status
nit_xor (struct nit *x, struct nit *y, struct nit *z);

/*! x = y & z */
enum nit_status
nit_and (struct nit *x, struct nit *y, struct nit *z);

/*! x = y | z */
enum nit_status
nit_or (struct nit *x, struct nit *y, struct nit *z);

/*! x = ! y */
enum nit_status
nit_not (struct nit *x, struct nit *y);

#endif
