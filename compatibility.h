/*------------------------------------------------------------------------
 *  Copyright (C) 2000-2008, Universidad de Zaragoza, SPAIN
 *
 *  Contact Addresses: Danilo Tardioli                   dantard@unizar.es
 *
 *  eBottle is free software;  you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the
 *  Free Software Foundation;  either version 2, or (at your option) any
 *  later version.
 *
 *  eBottle is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY;  without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  distributed with eBottle; see file COPYING. If not,  write to the
 *  Free Software  Foundation, 59 Temple Place - Suite 330, Boston, MA
 *  02111-1307, USA.
 *
 *  As a special exception, if you link this unit with other files to
 *  produce an executable, this unit does not by itself cause the resulting
 *  executable to be covered by the GNU General Public License.  This
 *  exception does not however invalidate any other reasons why the
 *  executable file might be covered by the GNU Public License.
 *
 *-------------------------------------------------------------------------*/

/**
 * \mainpage eBottle Documentation
 *
 * \author Danilo Tardioli et al. (UniZar) \<dantard@unizar.es\> \n
 * 			Pablo Urcola (documentation) \<urcola@unizar.es\> \n
 * 			D. Tardioli, P. Urcola (debug)
 *
 * \version 0.1 beta
 *
 * \section Introduction
 *
 * The idea of this project came out when we were testing YARP for communicating different processes using <b> YARP Bottles </b>.
 * We realised that, for large data transmission, the execution time was surprinsingly huge, even if we were working in a single computer.
 *
 * Another test, with smaller data but with a high frequency requirement was made and again we found the same problem.
 *
 * We discovered that one of the critic points where the program spent most of the time was at the assignment operator, that is, the copy method.
 *
 * After making some consults to YARP developers, they told us that Bottles and Values were not designed for efficient transmission but for human readable data purposes.
 *
 * We decided, as YARP developers suggest us, to reimplement the Bottle and Value classes in order to make copy method and data transmission faster and more efficient.
 *
 * We present here a new implementation which is more efficient and tries to keep all the compatibility with the original Bottles.
 *
 * <img src="eBottle2.png" alt="Comparative graphics">
 * This figure shows a comparative of the execution time (in seconds) of a program that simply makes assignments between bottles of different sizes.
 *
 *
 * \section Usage
 *
 * The eBootle can be used in any YARP-based project in the same way as any other YARP object. However in case you have already written code using standard YARP Bottle and want to improve its performance, you only have to include the compatibility.h file in all the source files that use the Bottles. This file simply makes a redefinition of the Value and Bottle to eValue and eBottle forcing the compiler to use the latters.
 *
 *
 * \section Feedback
 *
 * We have implemented many of the functionality that the original Bottle and Value clasess have.
 * Our tests work with both implementations, with a difference in the efficiency.
 * But some of you may need other funcitonality offered by the original Bottle that we have not implemented.
 * Please, let us know and we will consider to include it.
 *
 * Furthermore, if you find any bug that we have not discovered, contact us at dantard@unizar.es or urcola@unizar.es in order to solve the problem.
 */


/** \file compatibility.h
 *
 * \brief Compatibility file
 *
 * \author Danilo Tardioli et al. (UniZar) \<dantard@unizar.es\>
 *
 * \version 0.1 beta
 *
 * \date May 2008
 *
 * This file enables the swapping between the <a href='http://eris.liralab.it/yarp/specs/dox/user/html/d3/d3e/classyarp_1_1os_1_1Bottle.html'> Bottle</a>
 * and <a href='http://eris.liralab.it/yarp/specs/dox/user/html/d9/dad/classyarp_1_1os_1_1Value.html'>Value</a>
 * classes from YARP default implementation and the eBottle and eValue with
 * no need of any other source modification.
 *
 * <b>All the files that use YARP <a href='http://eris.liralab.it/yarp/specs/dox/user/html/d3/d3e/classyarp_1_1os_1_1Bottle.html'>Bottles</a>
 * and <a href='http://eris.liralab.it/yarp/specs/dox/user/html/d9/dad/classyarp_1_1os_1_1Value.html'>Values</a>
 * must include this header at the begining</b> to allow the swapping.
 *
 * The use of one or the other implementation is controlled by the flag EBOTTLE.
 * When defined, then the eBottle implementation will override the default one.
 * Otherwise, the YARP implementation will be used.
 */

#ifndef _COMPATIBILITY_H
#define	_COMPATIBILITY_H

/**
 * \brief Implementation swapping flag
 *
 * This flag controles the implementation that will be use for the Bottle and Value classes.
 * If it is defined, then the eBottle and eValue implementations will be used.
 * Otherwise, the default YARP <a href='http://eris.liralab.it/yarp/specs/dox/user/html/d3/d3e/classyarp_1_1os_1_1Bottle.html'>Bottle</a>
 *  and <a href='http://eris.liralab.it/yarp/specs/dox/user/html/d9/dad/classyarp_1_1os_1_1Value.html'>Value</a>
 *  will be employed.
 * \ref EBOTTLE
 */

#define EBOTTLE

#ifdef EBOTTLE

#include <yarp/os/eBottle.h>

/**
 * Redefines the <a href='http://eris.liralab.it/yarp/specs/dox/user/html/d3/d3e/classyarp_1_1os_1_1Bottle.html'>YARP Bottle</a> as eBottle
 */
#define Bottle eBottle

/**
 * Redefines the <a href='http://eris.liralab.it/yarp/specs/dox/user/html/d9/dad/classyarp_1_1os_1_1Value.html'>YARP Value</a> as eValue
 */
#define Value eValue

#endif

#endif	/* _COMPATIBILITY_H */

