/******************************************************************************

    @file    StateOS: os.h
    @author  Rajmund Szymanski
    @date    27.05.2021
    @brief   This file contains definitions for StateOS.

 ******************************************************************************

   Copyright (c) 2018-2021 Rajmund Szymanski. All rights reserved.

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to
   deal in the Software without restriction, including without limitation the
   rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
   sell copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
   IN THE SOFTWARE.

 ******************************************************************************/

#ifndef __STATEOS_H
#define __STATEOS_H

#include "osversion.h"
#include "oskernel.h"
#include "osalloc.h"
#include "ossys.h"
#include "inc/osclock.h"
#include "inc/oscriticalsection.h"
#include "inc/osspinlock.h"
#include "inc/osonceflag.h"
#include "inc/osevent.h"
#include "inc/ossignal.h"
#include "inc/osflag.h"
#include "inc/osbarrier.h"
#include "inc/ossemaphore.h"
#include "inc/osmutex.h"
#include "inc/osfastmutex.h"
#include "inc/osconditionvariable.h"
#include "inc/osrwlock.h"
#include "inc/oslist.h"
#include "inc/osmemorypool.h"
#include "inc/osrawbuffer.h"
#include "inc/osmessagequeue.h"
#include "inc/osmailboxqueue.h"
#include "inc/oseventqueue.h"
#include "inc/osjobqueue.h"
#include "inc/ostimer.h"
#include "inc/ostask.h"

#endif//__STATEOS_H
