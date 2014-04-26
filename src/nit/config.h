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
  nit/config.h
  Contains the definitions of important parameters such as choice of integer
  data types to use.
*/

#ifndef _defined_config_h_
#define _defined_config_h_

/* For ULONG_MAX */
#include <limits.h>

/*! The type used in the implementation of nit mathematical operators.
  Change this to the fastest unsigned integer your platform supports!
  Althought its size must be a power of two. */
typedef unsigned long nit_word;

/*! The largest value a word can hold. */
#define NIT_WORD_MAX ULONG_MAX

/*! The size of a nit. */
typedef size_t nit_size;

#endif
