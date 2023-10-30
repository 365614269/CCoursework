#include <stdio.h>
#include "graphics.h"
#include "robotGraphics.h"
#include "controls.h"

#define SIZE 10  // The size of grid is SIZE*SIZE
#define SIDELENGTH 25  // The sidelength of each cell
#define COUNTMARKERS 5
#define COUNTBLOCKS 10


void escapeVertical(Robot* aRobot, Cell grid[SIZE][SIZE], int nowCase, int initialX, int initialY) {
    int flag = 1;
    int offset = 1;

    while (flag) {
        int LHS = aRobot->y - offset;
        int RHS = aRobot->y + offset;

        if (LHS >= 0 && !grid[LHS][aRobot->y + nowCase].blocked) {
            moveRight(aRobot, offset, grid, initialX, initialY);
            flag = 0;
        } else if (RHS <= 9 && !grid[RHS][aRobot->y + nowCase].blocked) {
            moveLeft(aRobot, offset, grid, initialX, initialY);
            flag = 0;
        }
        
        offset++;
    }
}

void escapeHorizontal(Robot* aRobot, Cell grid[SIZE][SIZE], int nowCase, int initialX, int initialY) {
    int flag = 1;
    int offset = 1;

    while (flag) {
        int LHS = aRobot->x - offset;
        int RHS = aRobot->x + offset;

        if (LHS >= 0 && !grid[LHS][aRobot->y + nowCase].blocked) {
            moveRight(aRobot, offset, grid, initialX, initialY);
            flag = 0;
        } else if (RHS <= 9 && !grid[RHS][aRobot->y + nowCase].blocked) {
            moveLeft(aRobot, offset, grid, initialX, initialY);
            flag = 0;
        }
        
        offset++;
    }
}


void goToColumn(Robot* aRobot, int destY, Cell grid[SIZE][SIZE], int initialX, int initialY) {
    int nowCase;
    if (destY > aRobot->y) {
        faceEast(aRobot);
        nowCase = 1;
    } else if (destY < aRobot->y) {
        faceWest(aRobot);
        nowCase = -1;
    } else {
        return;
    }

    while (aRobot->y != destY) {
        if (canMoveForward(aRobot, grid)) {
            forward(aRobot);
            drawGrid(*aRobot, grid, initialX, initialY);
        } else {  // Get rid of the wall in the front.
            escapeVertical(aRobot, grid, nowCase, initialX, initialY);
        }
    }
}

void goToRow(Robot* aRobot, int destX, Cell grid[SIZE][SIZE], int initialX, int initialY) {
    int nowCase;
    if (destX > aRobot->x){
        faceSouth(aRobot);
        nowCase = 1;
    } else if (destX < aRobot->x){
        faceNorth(aRobot);
        nowCase = -1;
    } else {
        return;
    }

    while (aRobot->x != destX) {
        int offset = 1;
        if (canMoveForward(aRobot, grid)) {
            forward(aRobot);
            drawGrid(*aRobot, grid, initialX, initialY);
        } else {  // Get rid of the wall in the front.
            escapeHorizontal(aRobot, grid, nowCase, initialX, initialY);
        }
    }
}

void findNextMarker(Robot* aRobot, int destX, int destY, Cell grid[SIZE][SIZE], int initialX, int initialY) {
    goToColumn(aRobot, destY, grid, initialX, initialY);
    goToRow(aRobot, destX, grid, initialX, initialY);
}

void returnHome(Robot* aRobot, Cell grid[SIZE][SIZE], int initialX, int initialY) {
    pickUpMarker(aRobot, grid);
    left(aRobot);
    left(aRobot);
    drawGrid(*aRobot, grid, initialX, initialY);

    for(int prevStep = strlen(aRobot->prevSteps) - 3; prevStep >= 0; prevStep--) {
        if (aRobot->prevSteps[prevStep] == 'L') {
            right(aRobot);
        } else if (aRobot->prevSteps[prevStep] == 'R') {
            left(aRobot);
        } else if (aRobot->prevSteps[prevStep] == 'F') {
            forward(aRobot);
        }
        drawGrid(*aRobot, grid, initialX, initialY);
    }
}


int main(int argc, char **argv) {
    Robot robot = {};
    Cell grid[SIZE][SIZE] = {};

    int initialX = 6;
    int initialY = 5;
    Direction initialDirection = NORTH;

    int markersPos[COUNTMARKERS][2] = {{0, 5}, {9, 2}, {0, 0}, {2, 7}, {4, 6}};
    int blocksPos[COUNTBLOCKS][2] = {{0, 4}, {5, 3}, {6, 8}, {7, 6}, {3, 3}, {6, 0}, {0, 6}, {5, 5}, {2, 6}, {0, 1}};

    if (argc == 4) {
        initialX = atoi(argv[1]);
        initialY = atoi(argv[2]);
        char* dir = argv[3];
        if (!strcmp(dir, "north"))
            initialDirection = NORTH;
        else if (!strcmp(dir, "south"))
            initialDirection = SOUTH;
        else if (!strcmp(dir, "east"))
            initialDirection = EAST;
        else if (!strcmp(dir, "west"))
            initialDirection = WEST;
        else {
            printf("Invalid direction: %s", dir);
        }
    }

    // Place a few blocks on the grid.
    for(int i = 0; i < COUNTBLOCKS; i++) {
        grid[blocksPos[i][0]][blocksPos[i][1]].blocked = 1;
    }

    // Place a few markers on the grid.
    for(int i = 0; i < COUNTMARKERS; i++) {
        grid[markersPos[i][0]][markersPos[i][1]].markers = 1;
    }

    // Update the robot status according to the command line arguments.
    robot.x = initialX;
    robot.y = initialY;
    robot.dir = initialDirection;
    
    for(int i = 0; i < COUNTMARKERS; i++) {
        drawGrid(robot, grid, initialX, initialY);
        drawRobot(robot);
        
        findNextMarker(&robot, markersPos[i][0], markersPos[i][1], grid, initialX, initialY);

        drawGrid(robot, grid, initialX, initialY);
        
        returnHome(&robot, grid, initialX, initialY);
        dropMarker(&robot, grid);
        
        robot.prevSteps[0] = '\0';  // Clear the previous steps of the robot.
    }

    return 0;
}