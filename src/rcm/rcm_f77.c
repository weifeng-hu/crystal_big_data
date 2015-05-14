/*
 * Copyright (c) 2005 David Fritzsche
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any
 * damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any
 * purpose, including commercial applications, and to alter it and
 * redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must
 *    not claim that you wrote the original software.
 *    If you use this software in a product, an acknowledgment in the
 *    product documentation would be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must
 *    not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 *    distribution.
 */

/**
 * @file rcm_f77.c
 *
 * Version 0.9. September 21, 2005.
 *
 * This file provides two interface/wrapper functions to call
 * @c genrcmi()/@c genrcml() from Fortran programs.
 * @c GENRCM is intended to be a drop-in replacement for the SPARSPAK
 * version. @c GENRCM2 adds some of the additional features of
 * @c rcm.c.
 *
 * As the C Compiler does not know about Fortran, several preprocessor
 * symbols are used to give this knowledge to the Fortran compiler.
 *
 *
 * <dl>
 * <dt><b>@c F77_INT</b> [default: int]</dt>
 * <dd>if defined it should expand to the name
 *   of the C type to be used to represent the Fortran integer type.
 *   Note: The C interface is only compiled for int and long. Hence
 *   the compilation will likely fail or result in a faulty program if
 *   you define @c F77_INT to anything different from @c int or @c long.
 * </dd>
 * <dt><b>@c F77_GENRCMI</b></dt>
 * <dd>
 *   the name of the C function to call. If you define
 *   @c F77_INT outside this file, you also have to define
 *   @c F77_GENRCMI, either to @c genrcmi or @c genrcml.
 *   If @c #RCM_PREFIX is set, the prefix is added automatically.
 *   Do not add the prefix manually to the definition of
 *   @c F77_GENRCMI, this would only result in errors.
 * </dd>
 *
 * <dt><b><code>F77_FUNC(name,NAME)</code></b></dt>
 * <dd>
 *   a macro taking two arguments and resulting in
 *   the external name (used in @c *.o files) the Fortran compiler
 *   gives to
 *   the Fortran function/subroutine NAME (which is also the external
 *   name of functions called by Fortran).
 *   Notice that if you use
 *   <a href="http://www.gnu.org/software/autoconf/">GNU Autoconf</a>,
 *   just use @c AC_F77_WRAPPERS
 *   (see the section about
 *   <a href="http://www.gnu.org/software/autoconf/manual/autoconf-2.57/html_node/autoconf_66.html">Fortran 77 Compiler Characteristics</a>
 *   in the Autoconf Manual for more details on @c AC_F77_WRAPPERS)
 *   to get a correct definition for @c F77_FUNC.
 *
 *   If this macro is not defined, a heuristic is used to define it.
 *   The default behavior is to use the lowercase name and add a single
 *   underscore, e.g., <code>F77_FUNC(genrcm,GENRCM)</code> would become
 *   @c genrcm_.
 *   This seems to be the most common style (and is the one used
 *   by g77 and gfortran).
 *   Several other schemes can be selected by defining one or several
 *   of the following symbols:
 *   <dl>
 *     <dt>@c __2UNDERSCORE__</dt>
 *       <dd>
 *         Add TWO underscores to the name.
 *         <code>F77_FUNC(genrcm,GENRCM)</code>
 *         becomes @c genrcm__ or @c GENRCM__.
 *       </dd>
 *
 *     <dt>@c __UNDERSCORE__  or  @c ADD_ [default behavior]</dt>
 *       <dd>
 *         Add ONE underscore.
 *         <code>F77_FUNC(genrcm,GENRCM)</code> becomes
 *         @c genrcm_ or @c GENRCM_.
 *       </dd>
 *
 *     <dt>@c __NOCHANGE__  or  @c NOCHANGE</dt>
 *       <dd>
 *         Don't add underscores.
 *         <code>F77_FUNC(genrcm,GENRCM)</code> becomes
 *         @c genrcm or @c GENRCM.
 *       </dd>
 *     
 *     <dt>@c UPCASE  or  @c __CAPS__</dt>
 *       <dd>
 *         Use the uppercase version of the name.
 *         <code>F77_FUNC(genrcm,GENRCM)</code>
 *         becomes @c GENRCM, @c GENRCM_ or @c GENRCM__,
 *         depending on the underscore-adding preprocessor symbols.
 *       </dd>
 *     </dl>
 *   </dd>
 * </dl>
 */

#include "rcm.h"

/** @cond no-doxygen */

#ifndef F77_INT
#  define F77_INT int
#  define F77_GENRCMI genrcmi
#endif

#ifndef RCM_PREFIX
# define RCM_PREFIX
#endif

#ifndef CAT_2
# define DIRECT_CAT_2(a,b) a ## b
# define CAT_2(a,b) DIRECT_CAT_2(a,b)
#endif

#define F77_TO_C_GENRCM CAT_2(RCM_PREFIX,F77_GENRCMI)

#if !defined(F77_FUNC)

# if defined(__2UNDERSCORE__)
#  define F77_NAME(name) name ## __
# elif defined(__UNDERSCORE__) || defined(ADD_)
#  define F77_NAME(name) name ## _
# elif defined(__NOCHANGE__) || defined(NOCHANGE)
#  define F77_NAME(name) name
# else
#  define F77_NAME(name) name ## _
# endif

# if defined(UPCASE) || defined(__CAPS__)
#  define F77_FUNC(name,NAME) F77_NAME(NAME)
# else
#  define F77_FUNC(name,NAME) F77_NAME(name)
# endif

#endif

/*** @endcond */

/**
 * @brief Drop-in replacement for the SPARSPAK @c GENRCM subroutine.
 */
void F77_FUNC(genrcm,GENRCM)(F77_INT *n, F77_INT *xadj, F77_INT *adj,
                             F77_INT *perm, F77_INT *mask, F77_INT *deg)
{
    F77_INT i;
    signed char *xmask = (signed char*)mask;
    for (i = 0; i < *n; ++i) {
        xmask[i] = (signed char) mask[i];
    }
    F77_TO_C_GENRCM(*n, RCM_FORTRAN_INDICES, xadj, adj, perm, xmask, deg);
}


/**
 * @brief Fortran callable wrapper to @c genrcmi()/@c genrcml().
 */
void F77_FUNC(genrcm2,GENRCM2)(F77_INT *n, F77_INT *flags, F77_INT *xadj,
                               F77_INT *adj, F77_INT *perm, F77_INT *mask,
                               F77_INT *deg)
{
    F77_INT i;
    signed char *xmask = (signed char*) mask;
    int xflags = *flags;
    for (i = 0; i < *n; ++i) {
        xmask[i] = (signed char) mask[i];
    }
    if (!(xflags & RCM_C_INDICES)) {
        xflags |= RCM_FORTRAN_INDICES;
    }
    F77_TO_C_GENRCM(*n, xflags, xadj, adj, perm, xmask, deg);
}
