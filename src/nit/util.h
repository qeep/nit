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
  nit/util.h
  This file defines usefull support functions used ín the implementations
  of the public api functions. Please do not use these functions in your
  application as they are not explicitly tested and they are not stable.
*/

#ifndef _defined_nit_util_h_
#define _defined_nit_util_h_

#include "nit.h"

/*! Resizes the word memory of the nit.
  If the number of words is increased the new words are set to zero. */
enum nit_status
nit_resize (struct nit *x, nit_size n);

/*! Shrink x so that there are no trailing zeroes. */
enum nit_status
nit_shrink (struct nit *x);

/*! Like nit_cmp but only compares the most significant word. */
int
nit_lazy_cmp (struct nit *x, struct nit *y);

/*! Output portable representation of w into buffer. */
void
nit_out_hex_word (nit_word w, char *buffer, nit_size size);

/*! Input portable representation from buffer into w. */
void
nit_in_hex_word (nit_word *w, char *buffer, nit_size size);

#endif
