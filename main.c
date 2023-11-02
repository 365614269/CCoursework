#include "graphics.h"
#include "robotGraphics.h"
#include "controls.h"
#include <string.h>
#include <stdio.h>


int markersPos[COUNTMARKERS][2] = {{0, 5}, {4, 6}, {7, 2}};
int blocksPos[COUNTBLOCKS][2] = {{0, 4}, {5, 3}, {6, 8}, {7, 6}, {3, 3}, {6, 0}, {0, 6}, {5, 5}, {2, 6}, {0, 1}};
char pathways[COUNTMARKERS][500];

void returnHome(Robot* aRobot, Cell grid[SIZE][SIZE], int initialX, int initialY, int initialDirection) {
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

    faceDir(aRobot, initialDirection);
}


void dfs(Robot aRobot, Cell grid[SIZE][SIZE], int booked[SIZE][SIZE]) {
    if (grid[aRobot.x][aRobot.y].markers) {
        for(int i = 0; i < COUNTMARKERS; i++) {
            if (aRobot.x == markersPos[i][0] && aRobot.y == markersPos[i][1]) {
                strcpy(pathways[i], aRobot.prevSteps);
            }
        }
        return;
    }

    if (booked[aRobot.x][aRobot.y]) {
        // printf("APATH %d %d %s\n", aRobot.x, aRobot.y, aRobot.prevSteps);
        return;
    } else {
        booked[aRobot.x][aRobot.y] = 1;
        int dx[4] = {-1, 0, 1, 0};  // Corresponds to NORTH, EAST, SOUTH, WEST
        int dy[4] = {0, 1, 0, -1};
        // printf("%d %d %d %s\n", aRobot.x, aRobot.y, aRobot.dir, aRobot.prevSteps);

        for(int i = 0; i < 4; i++){
            int newX = aRobot.x + dx[i];
            int newY = aRobot.y + dy[i];

            if (newX >= 0 && newX <= SIZE - 1 && newY >= 0 && newY <= SIZE - 1 && 
                !grid[newX][newY].blocked) {

                Robot newRobot = {aRobot.x, aRobot.y, aRobot.dir, aRobot.carrysMarker, ' '};
                strcpy(newRobot.prevSteps, aRobot.prevSteps);
                
                faceDir(&newRobot, i);
                forward(&newRobot);
                dfs(newRobot, grid, booked);
            }
        }
    }
}


int main(int argc, char **argv) {
    setbuf(stdout, NULL);  // Disable output buffering
    Robot robot = {};
    Cell grid[SIZE][SIZE] = {};

    int initialX = 6;
    int initialY = 5;
    Direction initialDirection = NORTH;


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

    int booked[SIZE][SIZE] = {};
    dfs(robot, grid, booked);
    drawGrid(robot, grid, initialX, initialY);

    // printf("BUFFERED %d %s\n", strlen(buffered), buffered);
    int nowMarker = 0;
    while (nowMarker < COUNTMARKERS){
        for(int j = 0; pathways[nowMarker][j] != '\0'; j++) {
            char action = pathways[nowMarker][j];

            if (action == 'F') {
                forward(&robot);
            } else if (action == 'L') {
                left(&robot);
            } else if (action == 'R') {
                right(&robot);
            } else {
                printf("Invalid action.");
            }
            drawGrid(robot, grid, initialX, initialY);
        }

        printf("nowMarker0=%d\n", nowMarker);
        returnHome(&robot, grid, initialX, initialY, initialDirection);
        printf("nowMarker1=%d\n", nowMarker);
        dropMarker(&robot, grid);
        robot.prevSteps[0] = '\0';
        printf("nowMarker=%d\n", nowMarker);
        nowMarker = nowMarker + 1;
    }

    return 0;
}