#include "robotControls.h"
#include "graphics.h"
#include <stdio.h>


extern Direction initialDirection;

void forward(Robot* aRobot) {
    int dx[] = {-1, 0, 1, 0};  // Corresponds to NORTH, EAST, SOUTH, WEST
    int dy[] = {0, 1, 0, -1};

    aRobot->x += dx[aRobot->dir];
    aRobot->y += dy[aRobot->dir];
    strcat(aRobot->prevSteps, "F");
}

void left(Robot* aRobot) {
    if (aRobot->dir == NORTH) {
        aRobot->dir = WEST;
    } else {
        aRobot->dir--;
    }
    
    strcat(aRobot->prevSteps, "L");
}

void right(Robot* aRobot) {
    if (aRobot->dir == WEST) {
        aRobot->dir = NORTH;
    } else {
        aRobot->dir++;
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

int atHome(Robot aRobot, int initialX, int initialY) {
    return (aRobot.x == initialX && aRobot.y == initialY);
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

void faceDir(Robot* aRobot, Direction destDir) {
    Direction nowDir = aRobot->dir;

    if (destDir > nowDir) {
        for(int i = 0; i < destDir - nowDir; i++) {
            right(aRobot);
        }
    } else if (destDir < nowDir) {
        for(int i = 0; i < nowDir - destDir; i++) {
            left(aRobot);
        }
    } else {
        return;
    }
}

void move(Robot* aRobot, char action) {
    if (action == 'F') {
        forward(aRobot);
    } else if (action == 'L') {
        left(aRobot);
    } else if (action == 'R') {
        right(aRobot);
    } else {
        printf("Invalid action %c\n", action);
    }
}

int returnHome(Robot* aRobot, Cell grid[SIZE][SIZE], int nowMarker) {
    left(aRobot);
    left(aRobot);
    drawForeground(*aRobot, grid);

    for(int prevStep = strlen(aRobot->prevSteps) - 3; prevStep >= 0; prevStep--) {
        if (aRobot->prevSteps[prevStep] == 'L') {
            right(aRobot);
        } else if (aRobot->prevSteps[prevStep] == 'R') {
            left(aRobot);
        } else if (aRobot->prevSteps[prevStep] == 'F') {
            forward(aRobot);
        }
        drawForeground(*aRobot, grid);
    }
    
    faceDir(aRobot, initialDirection);
    return nowMarker;
}

