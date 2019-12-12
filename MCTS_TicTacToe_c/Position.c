#include "Position.h"

Position *newPosition(int x, int y) {
    Position *position = (Position *) malloc(sizeof(Position));
    assert(position != (Position *) NULL);

    position->x = x;
    position->y = y;

    return position;
}

void deletePosition(Position *position) {
    free(position);
}
