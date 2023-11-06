#include "robotGraphics.h"

void forward(Robot* aRobot);
void left(Robot* aRobot);
void right(Robot* aRobot);
int atMarker(Robot aRobot, Cell grid[SIZE][SIZE]);
int canMoveForward(Robot* aRobot, Cell grid[SIZE][SIZE]);
int atHome(Robot aRobot, int initialX, int initialY);
void pickUpMarker(Robot* aRobot, Cell grid[SIZE][SIZE]);
void dropMarker(Robot* aRobot, Cell grid[SIZE][SIZE]);
int isCarryingAMarker(Robot aRobot);
void faceDir(Robot* aRobot, Direction destDir);
