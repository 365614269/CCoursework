#include "robotGraphics.h"
#include "graphics.h"

// Below are the control functions of the robot.

void forward(Robot* aRobot) {
    switch (aRobot->dir) {
        case NORTH: aRobot->x--; break;
        case SOUTH: aRobot->x++; break;
        case EAST: aRobot->y++; break;
        case WEST: aRobot->y--; break;
    }
    strcat(aRobot->prevSteps, "F");
}

void left(Robot* aRobot) {
    switch (aRobot->dir) {
        case NORTH: aRobot->dir = WEST; break;
        case SOUTH: aRobot->dir = EAST; break;
        case EAST: aRobot->dir = NORTH; break;
        case WEST: aRobot->dir = SOUTH; break;
    }
    strcat(aRobot->prevSteps, "L");
}

void right(Robot* aRobot) {
    switch (aRobot->dir) {
        case NORTH: aRobot->dir = EAST; break;
        case SOUTH: aRobot->dir = WEST; break;
        case EAST: aRobot->dir = SOUTH; break;
        case WEST: aRobot->dir = NORTH; break;
    }
    strcat(aRobot->prevSteps, "R");
}

int atMarker(Robot aRobot, Cell grid[SIZE][SIZE]) {
    return grid[aRobot.x][aRobot.y].markers != 0;
}

int canMoveForward(Robot* aRobot, Cell grid[SIZE][SIZE]) {
    switch (aRobot->dir) {
        case NORTH: return !(aRobot->x == 0 || grid[aRobot->x - 1][aRobot->y].blocked);
        case SOUTH: return !(aRobot->x == 9 || grid[aRobot->x + 1][aRobot->y].blocked);
        case EAST: return !(aRobot->y == 9 || grid[aRobot->x][aRobot->y + 1].blocked);
        case WEST: return !(aRobot->y == 0 || grid[aRobot->x][aRobot->y - 1].blocked);
    }
}

int atHome(Robot* aRobot, int initialX, int initialY) {
    return (aRobot->x == initialX && aRobot->y == initialY);
}

void pickUpMarker(Robot* aRobot, Cell grid[SIZE][SIZE]) {
    grid[aRobot->x][aRobot->y].markers--;
    aRobot->carrysMarker = 1;
}

void dropMarker(Robot* aRobot, Cell grid[SIZE][SIZE]) {
    grid[aRobot->x][aRobot->y].markers++;
    aRobot->carrysMarker = 0;
}

int isCarryingAMarker(Robot aRobot) {
    return aRobot.carrysMarker;
}

void moveLeft(Robot* aRobot, int steps, Cell grid[SIZE][SIZE], int initialX, int initialY) {
    left(aRobot);
    drawGrid(*aRobot, grid, initialX, initialY);
    for(int step = 0; step < steps; step++){
        forward(aRobot);
        drawGrid(*aRobot, grid, initialX, initialY);
    }
    right(aRobot);
    drawGrid(*aRobot, grid, initialX, initialY);
}

void moveRight(Robot* aRobot, int steps, Cell grid[SIZE][SIZE], int initialX, int initialY) {
    right(aRobot);
    drawGrid(*aRobot, grid, initialX, initialY);
    for(int step = 0; step < steps; step++){
        forward(aRobot);
        drawGrid(*aRobot, grid, initialX, initialY);
    }
    left(aRobot);
    drawGrid(*aRobot, grid, initialX, initialY);
}


void faceWest(Robot* aRobot) {
    switch (aRobot->dir) {
        case NORTH: left(aRobot); return;
        case SOUTH: right(aRobot); return;
        case EAST: left(aRobot); left(aRobot); break;
        case WEST: return;
    }
}

void faceEast(Robot* aRobot) {
    switch (aRobot->dir) {
        case NORTH: right(aRobot); return;
        case SOUTH: left(aRobot); return;
        case EAST: return;
        case WEST: left(aRobot); left(aRobot); return;
    }
}

void faceNorth(Robot* aRobot) {
    switch (aRobot->dir) {
        case NORTH: return;
        case SOUTH: left(aRobot); left(aRobot); return;
        case EAST: left(aRobot); return;
        case WEST: right(aRobot); return;
    }
}

void faceSouth(Robot* aRobot) {
    switch (aRobot->dir) {
        case NORTH: left(aRobot); left(aRobot); return;
        case SOUTH: return;
        case EAST: right(aRobot); return;
        case WEST: left(aRobot); return;
    }
}