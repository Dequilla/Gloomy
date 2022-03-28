#ifndef __GLMY_TIME_H__
#define __GLMY_TIME_H__

// To enable clock_gettime etc.
#define _POSIX_C_SOURCE 199309L
#include <time.h>

typedef struct {
    union {
        long seconds;
        long s;
    };

    union {
        long nanoseconds;
        long ns;
    };
} GLMY_TimePrec;

GLMY_TimePrec GLMY_TimePrecNow();
GLMY_TimePrec GLMY_TimePrecProcessNow();
GLMY_TimePrec GLMY_TimePrecThreadNow();

GLMY_TimePrec GLMY_TimePrecDiff(GLMY_TimePrec start, GLMY_TimePrec end);

double GLMY_TimePrecToSeconds(GLMY_TimePrec time);
double GLMY_TimePrecToMilliseconds(GLMY_TimePrec time);

#endif
