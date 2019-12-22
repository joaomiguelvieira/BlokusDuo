#include "TimeInterval.h"

TimeInterval *newTimeInterval() {
    TimeInterval *timeInterval = (TimeInterval *) malloc(sizeof(TimeInterval));
    assert(timeInterval != (TimeInterval *) NULL);

    return timeInterval;
}

void deleteTimeInterval(TimeInterval *timeInterval) {
    free(timeInterval);
}

void setStartTimeInterval(TimeInterval *timeInterval) {
    gettimeofday(&timeInterval->start, NULL);
}

void setEndTimeInterval(TimeInterval *timeInterval) {
    gettimeofday(&timeInterval->end, NULL);
}

double getElapsedMillisTimeInterval(TimeInterval *timeInterval) {
    return (double) (timeInterval->end.tv_sec - timeInterval->start.tv_sec) * 1000.0 + (timeInterval->end.tv_usec - timeInterval->start.tv_usec) / 1000.0;
}
