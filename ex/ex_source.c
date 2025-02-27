/*      $OpenBSD: ex_source.c,v 1.11 2021/10/24 21:24:17 deraadt Exp $  */

/*-
 * Copyright (c) 1992, 1993, 1994
 *      The Regents of the University of California.  All rights reserved.
 * Copyright (c) 1992, 1993, 1994, 1995, 1996
 *      Keith Bostic.  All rights reserved.
 * Copyright (c) 2022 Jeffrey H. Johnson <trnsz@pobox.com>
 *
 * See the LICENSE.md file for redistribution information.
 */

#include "../include/compat.h"

#include <sys/types.h>
#include <sys/queue.h>
#include <sys/stat.h>

#include <bitstring.h>
#include <errno.h>
#include <bsd_fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <bsd_stdlib.h>
#include <bsd_string.h>
#include <bsd_unistd.h>

#include "../common/common.h"

#undef open

/*
 * ex_sourcefd -- :source already opened file
 *      Execute ex commands from the given file descriptor
 *
 * PUBLIC: int ex_sourcefd(SCR *, EXCMD *, int);
 */
int
ex_sourcefd(SCR *sp, EXCMD *cmdp, int fd)
{
        struct stat sb;
        int len;
        char *bp, *name;

        name = cmdp->argv[0]->bp;
        if (fstat(fd, &sb))
                goto err;

        /*
         * XXX
         * I'd like to test to see if the file is too large to malloc.  Since
         * we don't know what size or type off_t's or size_t's are, what the
         * largest unsigned integral type is, or what random insanity the local
         * C compiler will perpetrate, doing the comparison in a portable way
         * is flatly impossible.  So, put an fairly unreasonable limit on it,
         * I don't want to be dropping core here.
         */
#define MEGABYTE        1048576
        if (sb.st_size > MEGABYTE) {
                errno = ENOMEM;
                goto err;
        }

        MALLOC(sp, bp, (size_t)sb.st_size + 1);
        if (bp == NULL) {
                (void)close(fd);
                return (1);
        }
        bp[sb.st_size] = '\0';

        /* Read the file into memory. */
        len = read(fd, bp, (int)sb.st_size);
        (void)close(fd);
        if (len == -1 || len != sb.st_size) {
                if (len != sb.st_size)
                        errno = EIO;
                free(bp);
err:            msgq_str(sp, M_SYSERR, name, "%s");
                return (1);
        }

        /* Put it on the ex queue. */
        return (ex_run_str(sp, name, bp, (size_t)sb.st_size, 1, 1));
}

/*
 * ex_source -- :source file
 *      Execute ex commands from a file.
 *
 * PUBLIC: int ex_source(SCR *, EXCMD *);
 */
int
ex_source(SCR *sp, EXCMD *cmdp)
{
        char *name;
        int fd;

        name = cmdp->argv[0]->bp;
        if ((fd = open(name, O_RDONLY)) >= 0)
                return (ex_sourcefd(sp, cmdp, fd));

        msgq_str(sp, M_SYSERR, name, "%s");
        return (1);
}
