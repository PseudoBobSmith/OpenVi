/*      $OpenBSD: string.h,v 1.31 2016/09/09 18:12:37 millert Exp $     */
/*      $NetBSD: string.h,v 1.6 1994/10/26 00:56:30 cgd Exp $   */

/*-
 * Copyright (c) 1990 The Regents of the University of California.
 * Copyright (c) 2022 Jeffrey H. Johnson <trnsz@pobox.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *      @(#)string.h    5.10 (Berkeley) 3/9/91
 */


#ifndef _COMPAT_STRING_H_
# define _COMPAT_STRING_H_

size_t   openbsd_strlcpy(char *, const char *, size_t);

# ifndef __OpenBSD__

#  include <sys/types.h>

void     explicit_bzero(void *, size_t);
void     strmode(int, char *);

int      timingsafe_bcmp(const void *, const void *, size_t);
int      timingsafe_memcmp(const void *, const void *, size_t);

char    *strcasestr(const char *, const char *);
void    *memrchr(const void *, int, size_t);

# endif /* ifndef __OpenBSD__ */

#endif /* _COMPAT_STRING_H_ */

#include_next <string.h>
