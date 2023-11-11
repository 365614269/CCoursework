#include <string.h>
#include <stdlib.h>

#define SIZE 10
#define SIDELENGTH 25
#define INITOFFSET 20
#define COUNTMARKERS 4
#define COUNTBLOCKS 10

typedef enum {
    NORTH,
    EAST,
    SOUTH,
    WEST
} Direction;

typedef struct {
    int x, y;
    Direction dir;
    int carrysMarker;
    char prevSteps[500];  // A string recording the previoius steps of robot. \{F,L,R} means forward(), left(), right().
} Robot;

typedef struct {
    int markers;
    int blocked;
} Cell;

typedef struct{
    int xs[3];
    int ys[3];
} Triangle;

void render(Robot aRobot, Cell grid[SIZE][SIZE]);
void drawBackground(Cell grid[SIZE][SIZE]);

