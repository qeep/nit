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
  nit.c
  In this file all the functions listed in nit.h are implemented,
  but only this functions. Move other functions to util.c and add it to util.h.
*/

#include "nit.h"
#include "nit/util.h"

enum nit_status
nit_free (struct nit *x)
{
  return nit_resize (x, 0);
}

void
nit_clear (struct nit *x)
{
  x->w = NULL;
  x->n = 0;
}

enum nit_status
nit_from_long (struct nit *x, unsigned long l)
{
  enum nit_status s = NIT_OK;
  nit_size n = 0, i = 0;

  if (x == NULL)
    return NIT_NULL_POINTER;

  n = (sizeof (l) / sizeof (*x->w))
    + ((sizeof (l) % sizeof (*x->w)) ? 1 : 0);

  s = nit_resize (x, n);
  if (s != NIT_OK)
    return s;

  for (i = 0; i < n; i++)
    {
      x->w[i] = l & NIT_WORD_MAX;
      l = l >> sizeof (*x->w) * 8;
    }

  s = nit_shrink (x);

  return s;
}

enum nit_status
nit_to_long (struct nit *x, unsigned long *l)
{
  nit_size i = 0;

  if (x == NULL || x->w == NULL || l == NULL)
    return NIT_NULL_POINTER;

  if (x->n * sizeof (*x->w) > sizeof (*l))
    return NIT_OVERFLOW;

  for (i = x->n - 1; i > 0; i--)
    {
      *l |= x->w[i];
      *l = *l << sizeof (*x->w) * 8;
    }

  *l |= x->w[0];

  return NIT_OK;
}

enum nit_status
nit_out_hex (struct nit *x, char *buffer, size_t size)
{
  nit_size i = 0;
  /* Length of a word in readable hex. */
  nit_size k = sizeof (*x->w) * 2;

  if (x == NULL || x->w == NULL)
    return NIT_NULL_POINTER;

  /* Make sure the nit fits in the buffer. */
  if (x->n * k > size)
    return NIT_BUFFER_TO_SMALL;

  /* Print each word. */
  for (i = x->n - 1; i > 0; i--)
    {
      nit_out_hex_word (x->w[i], buffer, size);
      buffer += k, size -= k;
    }

  /* Print the least significant word. */
  nit_out_hex_word (x->w[0], buffer, size);

  return NIT_OK;
}

enum nit_status
nit_in_hex (struct nit *x, const char *buffer, size_t size)
{
  return NIT_UNINPLEMENTED;
}
