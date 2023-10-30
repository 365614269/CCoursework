#include <string.h>
#include <stdlib.h>


#define SIZE 10
#define SIDELENGTH 25
#define INITOFFSET 20
#define COUNTMARKERS 5
#define COUNTBLOCKS 10

typedef enum {
    NORTH,
    SOUTH,
    EAST,
    WEST
} Direction;

struct Robot {
    int x, y;
    Direction dir;
    int carrysMarker;
    char prevSteps[100];  // A string recording the previoius steps of robot. {F,L,R} means forward(), left(), right().
};
typedef struct Robot Robot;

struct Cell {
    int markers;
    int blocked;
};
typedef struct Cell Cell;

struct Triangle{
    int xs[3];
    int ys[3];
};
typedef struct Triangle Triangle;

void drawHome(int x, int y);
void drawRobot(Robot aRobot);
void drawGrid(Robot aRobot, Cell grid[SIZE][SIZE], int initialX, int initialY);
