/* Generic helper function for repacking arrays.
   Copyright 2003, 2004, 2005, 2007 Free Software Foundation, Inc.
   Contributed by Paul Brook <paul@nowt.org>

This file is part of the GNU Fortran 95 runtime library (libgfortran).

Libgfortran is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

In addition to the permissions in the GNU General Public License, the
Free Software Foundation gives you unlimited permission to link the
compiled version of this file into combinations with other programs,
and to distribute those combinations without any restriction coming
from the use of this file.  (The General Public License restrictions
do apply in other respects; for example, they cover modification of
the file, and distribution when not linked into a combine
executable.)

Libgfortran is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public
License along with libgfortran; see the file COPYING.  If not,
write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
Boston, MA 02110-1301, USA.  */

#include "libgfortran.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

extern void internal_unpack (gfc_array_char *, const void *);
export_proto(internal_unpack);

void
internal_unpack (gfc_array_char * d, const void * s)
{
  index_type count[GFC_MAX_DIMENSIONS];
  index_type extent[GFC_MAX_DIMENSIONS];
  index_type stride[GFC_MAX_DIMENSIONS];
  index_type stride0;
  index_type dim;
  index_type dsize;
  char *dest;
  const char *src;
  int n;
  int size;
  int type;

  dest = d->data;
  /* This check may be redundant, but do it anyway.  */
  if (s == dest || !s)
    return;

  type = GFC_DESCRIPTOR_TYPE (d);
  size = GFC_DESCRIPTOR_SIZE (d);
  switch (type)
    {
    case GFC_DTYPE_INTEGER:
    case GFC_DTYPE_LOGICAL:
      switch (size)
	{
	case sizeof (GFC_INTEGER_1):
	  internal_unpack_1 ((gfc_array_i1 *) d, (const GFC_INTEGER_1 *) s);
	  return;

	case sizeof (GFC_INTEGER_2):
	  internal_unpack_2 ((gfc_array_i2 *) d, (const GFC_INTEGER_2 *) s);
	  return;

	case sizeof (GFC_INTEGER_4):
	  internal_unpack_4 ((gfc_array_i4 *) d, (const GFC_INTEGER_4 *) s);
	  return;

	case sizeof (GFC_INTEGER_8):
	  internal_unpack_8 ((gfc_array_i8 *) d, (const GFC_INTEGER_8 *) s);
	  return;

#if defined (HAVE_GFC_INTEGER_16)
	case sizeof (GFC_INTEGER_16):
	  internal_unpack_16 ((gfc_array_i16 *) d, (const GFC_INTEGER_16 *) s);
	  return;
#endif
	}
      break;

    case GFC_DTYPE_REAL:
      switch (size)
	{
	case sizeof (GFC_REAL_4):
	  internal_unpack_r4 ((gfc_array_r4 *) d, (const GFC_REAL_4 *) s);
	  return;

	case sizeof (GFC_REAL_8):
	  internal_unpack_r8 ((gfc_array_r8 *) d, (const GFC_REAL_8 *) s);
	  return;

#if defined(HAVE_GFC_REAL_10)
	case sizeof (GFC_REAL_10):
	  internal_unpack_r10 ((gfc_array_r10 *) d, (const GFC_REAL_10 *) s);
	  return;
#endif

#if defined(HAVE_GFC_REAL_16)
	case sizeof (GFC_REAL_16):
	  internal_unpack_r16 ((gfc_array_r16 *) d, (const GFC_REAL_16 *) s);
	  return;
#endif

	}

    case GFC_DTYPE_COMPLEX:
      switch (size) 
	{
	case sizeof (GFC_COMPLEX_4):
	  internal_unpack_c4 ((gfc_array_c4 *)d, (const GFC_COMPLEX_4 *)s);
	  return;

	case sizeof (GFC_COMPLEX_8):
	  internal_unpack_c8 ((gfc_array_c8 *)d, (const GFC_COMPLEX_8 *)s);
	  return;

#if defined(HAVE_GFC_COMPLEX_10)
	case sizeof (GFC_COMPLEX_10):
	  internal_unpack_c10 ((gfc_array_c10 *) d, (const GFC_COMPLEX_10 *) s);
	  return;
#endif

#if defined(HAVE_GFC_COMPLEX_16)
	case sizeof (GFC_COMPLEX_16):
	  internal_unpack_c16 ((gfc_array_c16 *) d, (const GFC_COMPLEX_16 *) s);
	  return;
#endif

	}
    default:
      break;
    }

  if (d->dim[0].stride == 0)
    d->dim[0].stride = 1;

  dim = GFC_DESCRIPTOR_RANK (d);
  dsize = 1;
  for (n = 0; n < dim; n++)
    {
      count[n] = 0;
      stride[n] = d->dim[n].stride;
      extent[n] = d->dim[n].ubound + 1 - d->dim[n].lbound;
      if (extent[n] <= 0)
        abort ();

      if (dsize == stride[n])
        dsize *= extent[n];
      else
        dsize = 0;
    }

  src = s;

  if (dsize != 0)
    {
      memcpy (dest, src, dsize * size);
      return;
    }

  stride0 = stride[0] * size;

  while (dest)
    {
      /* Copy the data.  */
      memcpy (dest, src, size);
      /* Advance to the next element.  */
      src += size;
      dest += stride0;
      count[0]++;
      /* Advance to the next source element.  */
      n = 0;
      while (count[n] == extent[n])
        {
          /* When we get to the end of a dimension, reset it and increment
             the next dimension.  */
          count[n] = 0;
          /* We could precalculate these products, but this is a less
             frequently used path so probably not worth it.  */
          dest -= stride[n] * extent[n] * size;
          n++;
          if (n == dim)
            {
              dest = NULL;
              break;
            }
          else
            {
              count[n]++;
              dest += stride[n] * size;
            }
        }
    }
}
