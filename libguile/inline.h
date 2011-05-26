/* classes: h_files */

#ifndef SCM_INLINE_H
#define SCM_INLINE_H

/* Copyright (C) 2001, 2002, 2003, 2004, 2006, 2008, 2009, 2010,
 *   2011 Free Software Foundation, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 3 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301 USA
 */

/* This file is for inline functions.  On platforms that don't support
   inlining functions, they are turned into ordinary functions.  On
   platforms that do support inline functions, the definitions are still
   compiled into the library, once, in inline.c.  */

#include <stdio.h>
#include <string.h>

#include "libguile/__scm.h"

#include "libguile/pairs.h"
#include "libguile/gc.h"
#include "libguile/threads.h"
#include "libguile/array-handle.h"
#include "libguile/ports.h"
#include "libguile/numbers.h"
#include "libguile/error.h"


SCM_INLINE SCM scm_array_handle_ref (scm_t_array_handle *h, ssize_t pos);
SCM_INLINE void scm_array_handle_set (scm_t_array_handle *h, ssize_t pos, SCM val);

SCM_INLINE int scm_is_pair (SCM x);
SCM_INLINE int scm_is_string (SCM x);

SCM_INLINE int scm_get_byte_or_eof (SCM port);
SCM_INLINE int scm_peek_byte_or_eof (SCM port);
SCM_INLINE void scm_putc (char c, SCM port);
SCM_INLINE void scm_puts (const char *str_data, SCM port);


SCM_INLINE SCM scm_cell (scm_t_bits car, scm_t_bits cdr);
SCM_INLINE SCM scm_double_cell (scm_t_bits car, scm_t_bits cbr,
			     scm_t_bits ccr, scm_t_bits cdr);
SCM_INLINE SCM scm_words (scm_t_bits car, scm_t_uint16 n_words);

#if SCM_CAN_INLINE || defined SCM_INLINE_C_IMPLEMENTING_INLINES
/* Either inlining, or being included from inline.c.  */

SCM_INLINE_IMPLEMENTATION SCM
scm_array_handle_ref (scm_t_array_handle *h, ssize_t p)
{
  if (SCM_UNLIKELY (p < 0 && ((size_t)-p) > h->base))
    /* catch overflow */
    scm_out_of_range (NULL, scm_from_ssize_t (p));
  /* perhaps should catch overflow here too */
  return h->impl->vref (h, h->base + p);
}

SCM_INLINE_IMPLEMENTATION void
scm_array_handle_set (scm_t_array_handle *h, ssize_t p, SCM v)
{
  if (SCM_UNLIKELY (p < 0 && ((size_t)-p) > h->base))
    /* catch overflow */
    scm_out_of_range (NULL, scm_from_ssize_t (p));
  /* perhaps should catch overflow here too */
  h->impl->vset (h, h->base + p, v);
}

SCM_INLINE_IMPLEMENTATION int
scm_is_pair (SCM x)
{
  /* The following "workaround_for_gcc_295" avoids bad code generated by
     i386 gcc 2.95.4 (the Debian packaged 2.95.4-24 at least).

     Under the default -O2 the inlined SCM_I_CONSP test gets "optimized" so
     the fetch of the tag word from x is done before confirming it's a
     non-immediate (SCM_NIMP).  Needless to say that bombs badly if x is a
     immediate.  This was seen to afflict scm_srfi1_split_at and something
     deep in the bowels of ceval().  In both cases segvs resulted from
     deferencing a random immediate value.  srfi-1.test exposes the problem
     through a short list, the immediate being SCM_EOL in that case.
     Something in syntax.test exposed the ceval() problem.

     Just "volatile SCM workaround_for_gcc_295 = lst" is enough to avoid the
     problem, without even using that variable.  The "w=w" is just to
     prevent a warning about it being unused.
     */
#if defined (__GNUC__) && __GNUC__ == 2 && __GNUC_MINOR__ == 95
  volatile SCM workaround_for_gcc_295 = x;
  workaround_for_gcc_295 = workaround_for_gcc_295;
#endif

  return SCM_I_CONSP (x);
}

SCM_INLINE_IMPLEMENTATION int
scm_is_string (SCM x)
{
  return SCM_NIMP (x) && (SCM_TYP7 (x) == scm_tc7_string);
}

/* Port I/O.  */

SCM_INLINE_IMPLEMENTATION int
scm_get_byte_or_eof (SCM port)
{
  int c;
  scm_t_port *pt = SCM_PTAB_ENTRY (port);

  if (pt->rw_active == SCM_PORT_WRITE)
    /* may be marginally faster than calling scm_flush.  */
    scm_ptobs[SCM_PTOBNUM (port)].flush (port);

  if (pt->rw_random)
    pt->rw_active = SCM_PORT_READ;

  if (pt->read_pos >= pt->read_end)
    {
      if (SCM_UNLIKELY (scm_fill_input (port) == EOF))
	return EOF;
    }

  c = *(pt->read_pos++);

  return c;
}

/* Like `scm_get_byte_or_eof' but does not change PORT's `read_pos'.  */
SCM_INLINE_IMPLEMENTATION int
scm_peek_byte_or_eof (SCM port)
{
  int c;
  scm_t_port *pt = SCM_PTAB_ENTRY (port);

  if (pt->rw_active == SCM_PORT_WRITE)
    /* may be marginally faster than calling scm_flush.  */
    scm_ptobs[SCM_PTOBNUM (port)].flush (port);

  if (pt->rw_random)
    pt->rw_active = SCM_PORT_READ;

  if (pt->read_pos >= pt->read_end)
    {
      if (SCM_UNLIKELY (scm_fill_input (port) == EOF))
	return EOF;
    }

  c = *pt->read_pos;

  return c;
}

SCM_INLINE_IMPLEMENTATION void
scm_putc (char c, SCM port)
{
  SCM_ASSERT_TYPE (SCM_OPOUTPORTP (port), port, 0, NULL, "output port");
  scm_lfwrite (&c, 1, port);
}

SCM_INLINE_IMPLEMENTATION void
scm_puts (const char *s, SCM port)
{
  SCM_ASSERT_TYPE (SCM_OPOUTPORTP (port), port, 0, NULL, "output port");
  scm_lfwrite (s, strlen (s), port);
}


#endif
#endif
