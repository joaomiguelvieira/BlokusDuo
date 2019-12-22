#ifndef TIME_INTERVAL_H
#define TIME_INTERVAL_H

#include <sys/time.h>
#include <stdlib.h>
#include <assert.h>

typedef struct TimeInterval_ {
    struct timeval start, end;
} TimeInterval;

TimeInterval *newTimeInterval();
void deleteTimeInterval(TimeInterval *timeInterval);
void setStartTimeInterval(TimeInterval *timeInterval);
void setEndTimeInterval(TimeInterval *timeInterval);
double getElapsedMillisTimeInterval(TimeInterval *timeInterval);

#endif
