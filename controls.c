#include "robotGraphics.h"
#include "graphics.h"
#define SIZE 10

// Below are the control functions of the robot.

void forward(struct Robot* aRobot) {
    if (!strcmp(aRobot->dir,"east")) {
        aRobot->y++;
    } else if (!strcmp(aRobot->dir,"west")) {
        aRobot->y--;
    } else if (!strcmp(aRobot->dir, "north")) {
        aRobot->x--;
    } else if (!strcmp(aRobot->dir, "south")) {
        aRobot->x++;
    }
    strcat(aRobot->prevSteps, "F");
}

void left(struct Robot* aRobot) {
    if (!strcmp(aRobot->dir,"east")) {
        aRobot->dir = "north";
    } else if (!strcmp(aRobot->dir,"west")) {
        aRobot->dir = "south";
    } else if (!strcmp(aRobot->dir, "north")) {
        aRobot->dir = "west";
    } else if (!strcmp(aRobot->dir, "south")) {
        aRobot->dir = "east";
    }
    strcat(aRobot->prevSteps, "L");
}

void right(struct Robot* aRobot) {
    if (!strcmp(aRobot->dir,"east")) {
        aRobot->dir = "south";
    } else if (!strcmp(aRobot->dir,"west")) {
        aRobot->dir = "north";
    } else if (!strcmp(aRobot->dir, "north")) {
        aRobot->dir = "east";
    } else if (!strcmp(aRobot->dir, "south")) {
        aRobot->dir = "west";
    }
    strcat(aRobot->prevSteps, "R");
}

int atMarker(struct Robot aRobot, struct Cell grid[SIZE][SIZE]) {
    return grid[aRobot.x][aRobot.y].markers != 0;
}

int canMoveForward(struct Robot* aRobot, struct Cell grid[SIZE][SIZE]) {
    if (!strcmp(aRobot->dir,"east")) {
        return !(aRobot->y==9 || grid[aRobot->x][aRobot->y + 1].blocked);
    } else if (!strcmp(aRobot->dir,"west")) {
        return !(aRobot->y==0 || grid[aRobot->x][aRobot->y - 1].blocked);
    } else if (!strcmp(aRobot->dir, "north")) {
        return !(aRobot->x==0 || grid[aRobot->x - 1][aRobot->y].blocked);
    } else if (!strcmp(aRobot->dir, "south")) {
        return !(aRobot->x==9 || grid[aRobot->x + 1][aRobot->y].blocked);
    }
}

int atHome(struct Robot* aRobot, int initialX, int initialY) {
    return (aRobot->x==initialX && aRobot->y==initialY);
}

void pickUpMarker(struct Robot* aRobot, struct Cell grid[SIZE][SIZE]) {
    grid[aRobot->x][aRobot->y].markers--;
    aRobot->carrysMarker = 1;
}

void dropMarker(struct Robot* aRobot, struct Cell grid[SIZE][SIZE]) {
    grid[aRobot->x][aRobot->y].markers++;
    aRobot->carrysMarker = 0;
}

int isCarryingAMarker(struct Robot aRobot) {
    return aRobot.carrysMarker;
}

void moveLeft(struct Robot* aRobot, int steps, struct Cell grid[SIZE][SIZE], int initialX, int initialY) {
    left(aRobot);
    drawGrid(*aRobot, grid, initialX, initialY);
    for(int step = 0; step < steps; step++){
        forward(aRobot);
        drawGrid(*aRobot, grid, initialX, initialY);
    }
    right(aRobot);
    drawGrid(*aRobot, grid, initialX, initialY);
}

void moveRight(struct Robot* aRobot, int steps, struct Cell grid[SIZE][SIZE], int initialX, int initialY) {
    right(aRobot);
    drawGrid(*aRobot, grid, initialX, initialY);
    for(int step = 0; step < steps; step++){
        forward(aRobot);
        drawGrid(*aRobot, grid, initialX, initialY);
    }
    left(aRobot);
    drawGrid(*aRobot, grid, initialX, initialY);
}


void faceWest(struct Robot* aRobot) {
    if (!strcmp(aRobot->dir,"east")) {
        left(aRobot);
        left(aRobot);
    } else if (!strcmp(aRobot->dir, "north")) {
        left(aRobot);
    } else if (!strcmp(aRobot->dir, "south")) {
        right(aRobot);
    }
}

void faceEast(struct Robot* aRobot) {
    if (!strcmp(aRobot->dir,"west")) {
        left(aRobot);
        left(aRobot);
    } else if (!strcmp(aRobot->dir, "south")) {
        left(aRobot);
    } else if (!strcmp(aRobot->dir, "north")) {
        right(aRobot);
    }
}

void faceNorth(struct Robot* aRobot) {
    if (!strcmp(aRobot->dir,"south")) {
        left(aRobot);
        left(aRobot);
    } else if (!strcmp(aRobot->dir, "east")) {
        left(aRobot);
    } else if (!strcmp(aRobot->dir, "west")) {
        right(aRobot);
    }
}

void faceSouth(struct Robot* aRobot) {
    if (!strcmp(aRobot->dir,"north")) {
        left(aRobot);
        left(aRobot);
    } else if (!strcmp(aRobot->dir, "west")) {
        left(aRobot);
    } else if (!strcmp(aRobot->dir, "east")) {
        right(aRobot);
    }
}