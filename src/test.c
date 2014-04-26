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
  test.c
  Runs a test suite on nit.
  Exits with status zero and produces no output if all tests are passed.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "nit.h"

char*
status (enum nit_status s)
{
  switch (s)
    {
    case NIT_OK:
      return "NIT_OK";
    case NIT_UNDERFLOW:
      return "NIT_UNDERFLOW";
    default:
      return "unknown";
    }
}

/*! Print bytes to stderr. */
void
bytes (void *b, size_t n)
{
  size_t k = 0;
  for (k = 0; k < n; k++)
    printf ("%x ", ((unsigned char*)b)[k]);
}

/*! Convert a long with ULONG_MAX to a nit and back to a long. */
void
to_and_from_long (unsigned long lv)
{
  char *name = "to_and_from_long";
  enum nit_status s = NIT_OK;
  unsigned long l = 0;
  struct nit x;

  nit_clear (&x);

  s = nit_from_long (&x, lv);
  if (s != NIT_OK)
    {
      fprintf (stderr, "%s: nit_from_long returned %s\n", name, status (s));
    }

  s = nit_to_long (&x, &l);
  if (s != NIT_OK)
    {
      fprintf (stderr, "%s: nit_to_long returned %s\n", name, status (s));
    }

  if (l != lv)
    {
      fprintf (stderr, "%s: long value was not preserved.\n was ", name);
      bytes (&l, sizeof (l));
      printf (" should be ");
      bytes (&lv, sizeof (lv));
      printf ("\n nit was ");
      bytes (x.w, sizeof (*x.w) * x.n);
      printf ("\n");
    }

  nit_free (&x);
}

void
to_and_from_hex ()
{
  struct nit x;
  char buffer[100];
  char *hexstr = "aabbccdd";
  enum nit_status s = NIT_OK;
  unsigned long l = 0;

  nit_clear (&x);

  s = nit_from_long (&x, 0xaabbccdd);
  if (s != NIT_OK)
    {
      fprintf (stderr, "nit_from_long returned %s\n", status (s));
    }

  memset (buffer, 0, sizeof (buffer));

  s = nit_out_hex (&x, buffer, sizeof (buffer) - 1);
  if (s != NIT_OK)
    {
      fprintf (stderr, "nit_out_hex returned %s\n", status (s));
    }

  if (memcmp (hexstr, buffer, strlen (hexstr)) != 0)
    {
      fprintf (stderr, "nit_out_hex did not output correct data.\n"
	       " should be \"%s\"\n was \"%s\"\n", hexstr, buffer);
    }

  s = nit_in_hex (&x, buffer, sizeof (buffer) - 1);
  if (s != NIT_OK)
    {
      fprintf (stderr, "nit_in_hex returned %s\n", status (s));
    }

  s = nit_to_long (&x, &l);
  if (s != NIT_OK)
    {
      fprintf (stderr, "nit_to_long returned %s\n", status (s));
    }

  if (l != 0xaabbccdd)
    {
      fprintf (stderr, "long value was not preserved after\n"
	       " long->nit->hex->nit->long conversion.\n");
    }

  nit_free (&x);
}

void
platform ()
{
  printf ("word %lu long %lu\n",
	  (unsigned long) sizeof (nit_word),
	  (unsigned long) sizeof (long));
}

int
main (int argc, char **argv)
{
  int i = 0;
  if (argc > 1)
    {
      for (i = 0; i < argc; i++)
	{
	  if (strcmp (argv[i], "-p") == 0)
	    platform ();
	}
    }
  else
    {
      to_and_from_long (0x44332211);
      to_and_from_long (ULONG_MAX);
      to_and_from_hex ();
    }

  return 0;
}
