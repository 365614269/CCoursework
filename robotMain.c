#include "graphics.h"
#include "robotControls.h"
#include "robotGraphics.h"
#include <string.h>
#include <stdio.h>
// Adjust the speed of robot at the end of robotGraphics.c!

int markersPosition[COUNTMARKERS][2];
int blocksPosition[COUNTBLOCKS][2];
char pathwayToMarkers[COUNTMARKERS][500] = {};
int initialX = 6;
int initialY = 5;
Direction initialDirection = NORTH;


void initGrid(Robot* aRobot, Cell grid[SIZE][SIZE]) {
    // Place a few blocks on the grid.
    for(int i = 0; i < COUNTBLOCKS; i++) {
        grid[blocksPosition[i][0]][blocksPosition[i][1]].blocked = 1;
    }

    // Place a few markers on the grid.
    for(int i = 0; i < COUNTMARKERS; i++) {
        grid[markersPosition[i][0]][markersPosition[i][1]].markers = 1;
    }

    // Update the robot status according to the command line arguments.
    aRobot->x = initialX;
    aRobot->y = initialY;
    aRobot->dir = initialDirection;
}


void dfs(Robot aRobot, Cell grid[SIZE][SIZE], int booked[SIZE][SIZE]) {
    if (grid[aRobot.x][aRobot.y].markers) {
        booked[aRobot.x][aRobot.y] = 1;

        for(int i = 0; i < COUNTMARKERS; i++) {
            if (aRobot.x == markersPosition[i][0] && aRobot.y == markersPosition[i][1]) {
                strcpy(pathwayToMarkers[i], aRobot.prevSteps);
            }
        }
        return;
    }

    if (booked[aRobot.x][aRobot.y]) {
        return;
    } else {
        booked[aRobot.x][aRobot.y] = 1;
        int dx[4] = {-1, 0, 1, 0};  // Corresponds to NORTH, EAST, SOUTH, WEST
        int dy[4] = {0, 1, 0, -1};

        for(int i = 0; i < 4; i++) {
            int newX = aRobot.x + dx[i];
            int newY = aRobot.y + dy[i];
            
            if (newX >= 0 && newX <= SIZE - 1 && newY >= 0 && newY <= SIZE - 1 &&  
                !grid[newX][newY].blocked) {  // Condition: the newX and newY is within the grid and not blocked

                Robot virtualRobot = {aRobot.x, aRobot.y, aRobot.dir, aRobot.carrysMarker, ' '};  // A new possibility of pathway.
                strcpy(virtualRobot.prevSteps, aRobot.prevSteps);
                
                faceDir(&virtualRobot, i);
                forward(&virtualRobot);
                dfs(virtualRobot, grid, booked);
            }
        }
    }
}


int main(int argc, char **argv) {
    setbuf(stdout, NULL);  // Disable output buffering
    Robot robot = {};
    Cell grid[SIZE][SIZE] = {};
    readMarkers(grid, markersPosition);
    readBlocks(grid, blocksPosition);

    if (argc == 4) {
        initialX = atoi(argv[1]);
        initialY = atoi(argv[2]);
        char* dir = argv[3];
        initialDirection = stringToDirection(dir);
        validateInput(initialX, initialY, initialDirection);
    } else {
        printf("Incorrect number of arguments. It should be 4! Default values are used.\n");
    }

    initGrid(&robot, grid);
    drawBackground(grid, initialX, initialY);

    int booked[SIZE][SIZE] = {};
    dfs(robot, grid, booked);  // Sends out many virtual robots to find the markers
    drawForeground(robot, grid);

    for(int nowMarker = 0; nowMarker < COUNTMARKERS; nowMarker++) {  // Let the real robot follow the recorded pathways
        for(int j = 0; pathwayToMarkers[nowMarker][j] != '\0'; j++) {
            char action = pathwayToMarkers[nowMarker][j];
            move(&robot, action);
            drawForeground(robot, grid);
        }

        pickUpMarker(&robot, grid);
        returnHome(&robot, grid, initialDirection);
        dropMarker(&robot, grid);
        robot.prevSteps[0] = '\0';
    }
    
    return 0;
}

