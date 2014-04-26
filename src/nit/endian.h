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
  nit/endian.h
  Implements functions that converts nits between big and little endian.
*/

#ifndef _defined_nit_endian_h_
#define _defined_nit_endian_h_

#include "nit.h"

/*! Copy y to x but convert y from network endian format
  to host endian format. x and y can reside in the same memory. */
enum nit_status
nit_to_host (struct nit *x, struct nit *y);

/*! Copy y to x but convert y from host endian format to
  network endian format. x and y can reside in the same memory. */
enum nit_status
nit_to_portable (struct nit *x, struct nit *y);

#endif
