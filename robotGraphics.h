#include <string.h>
#include <stdlib.h>

#define SIZE 10
#define SIDELENGTH 25
#define INITOFFSET 20
#define COUNTMARKERS 3
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
    char prevSteps[100];  // A string recording the previoius steps of robot. \{F,L,R} means forward(), left(), right().
} Robot;

typedef struct {
    int markers;
    int blocked;
} Cell;

typedef struct{
    int xs[3];
    int ys[3];
} Triangle;

void drawHome(int x, int y);
void drawRobot(Robot aRobot);
void drawGrid(Robot aRobot, Cell grid[SIZE][SIZE], int initialX, int initialY);