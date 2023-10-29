#include <string.h>


#define SIZE 10


struct Robot {
    int x,y;
    char *dir;
    int carrysMarker;
    char prevSteps[100];  // A string recording the previoius steps of robot. {F,L,R} means forward(), left(), right().
};

struct Cell {
    int markers;
    int blocked;
};


void drawHome(int x, int y);
void drawRobot(struct Robot aRobot);
void drawGrid(struct Robot aRobot, struct Cell grid[SIZE][SIZE], int initialX, int initialY);