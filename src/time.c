#include <gloomy/time.h>


GLMY_TimePrec GLMY_TimePrecNow()
{
   struct timespec now;
   int result = clock_gettime(CLOCK_REALTIME, &now);
   // TODO: Create error messaging system

   GLMY_TimePrec time;
   time.s = (long)now.tv_sec;
   time.ns = now.tv_nsec;

   return time;
}

GLMY_TimePrec GLMY_TimePrecProcessNow()
{
   struct timespec now;
   int result = clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &now);
   // TODO: Create error messaging system

   GLMY_TimePrec time;
   time.s = (long)now.tv_sec;
   time.ns = now.tv_nsec;

   return time;
}

GLMY_TimePrec GLMY_TimePrecThreadNow()
{
   struct timespec now;
   int result = clock_gettime(CLOCK_THREAD_CPUTIME_ID, &now);
   // TODO: Create error messaging system

   GLMY_TimePrec time;
   time.s = (long)now.tv_sec;
   time.ns = now.tv_nsec;

   return time;
}

GLMY_TimePrec GLMY_TimePrecDiff(GLMY_TimePrec start, GLMY_TimePrec end)
{
   GLMY_TimePrec temp;
   
   if ((end.ns - start.ns) < 0) {

      // If negative "steal" a second from seconds and add to nanoseconds
      temp.s = end.s - start.s - 1;
      temp.ns = 1000000000 + end.ns - start.ns;

   } else {

      temp.s = end.s - start.s;
      temp.ns = end.ns - start.ns;

   }

   return temp;
}

double GLMY_TimePrecToSeconds(GLMY_TimePrec time)
{
   double seconds = (double)time.s;
   seconds += ((double)time.ns / 1000000000);
   return seconds; 
}

double GLMY_TimePrecToMilliseconds(GLMY_TimePrec time)
{
   double milliseconds = (double)time.s * 1000;
   milliseconds += ((double)time.ns / 1000000);
   return milliseconds;
}


