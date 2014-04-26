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
  util.c
  This file implements functions listed in util.h.
*/

/* Temporary for snprint and sscanf.
   Will be removed. */
#include <stdio.h>

#include "nit/util.h"

enum nit_status
nit_resize (struct nit *x, nit_size n)
{
  nit_word *w = NULL;
  nit_size i = 0;

  if (x == NULL)
    return NIT_NULL_POINTER;

  w = realloc (x->w, sizeof (*x->w) * n);

  if (w == NULL && n > 0)
    return NIT_MEMORY;

  if (n > x->n)
    {
      for (i = x->n; i < n; i++)
        {
          w[i] = 0;
        }
    }

  x->w = w;
  x->n = n;

  return NIT_OK;
}

enum nit_status
nit_shrink (struct nit *x)
{
  nit_size i = 0;

  if ((x == NULL) || (x->w == NULL))
    return NIT_NULL_POINTER;
  if (x->n == 0)
    return NIT_ZERO_LENGTH;

  /* Iterate from the last word to the first until the
     word is no longer zero. */
  for (i = 0; (i < x->n) && (x->w[x->n - i - 1] == 0); i++);

  /* Then resize the nit to hold up to and including that word. */
  return nit_resize (x, x->n - i);
}

/*! Print portable representation of w into buffer. */
void
nit_out_hex_word (nit_word w, char *buffer, nit_size size)
{
  /* A hack for now. */
  snprintf (buffer, size, "%x",  w);
}

void
nit_in_hex_word (nit_word *w, char *buffer, nit_size size)
{
  /* A hack for now. */
  sscanf (buffer, "%lx", w);
}
