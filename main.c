#include "graphics.h"
#include "controls.h"
#include <string.h>
#include <stdio.h>
// Adjust the speed of robot at the end of robotGraphics.c!

int markersPos[COUNTMARKERS][2] = {{9, 2}, {0, 0}, {4, 6}, {7, 3}};
int blocksPos[COUNTBLOCKS][2] = {{0, 4}, {5, 3}, {6, 8}, {7, 6}, {3, 3}, {6, 0}, {0, 6}, {5, 5}, {2, 6}, {0, 1}};
char pathways[COUNTMARKERS][500] = {};
extern int initialX = 6;
extern int initialY = 5;
extern Direction initialDirection = NORTH;


void validateInput() {
    if (initialX >= 0 && initialX <= 9 &&
        initialY >= 0 && initialY <= 9 &&
        initialDirection != -1)
    {
        return;
    } else {
        initialX = 6;
        initialY = 5;
        initialDirection = 0;
        printf("Illegal value for arguments, default values are used.\n");
    }
}


void initGrid(Robot* aRobot, Cell grid[SIZE][SIZE]) {
    // Place a few blocks on the grid.
    for(int i = 0; i < COUNTBLOCKS; i++) {
        grid[blocksPos[i][0]][blocksPos[i][1]].blocked = 1;
    }

    // Place a few markers on the grid.
    for(int i = 0; i < COUNTMARKERS; i++) {
        grid[markersPos[i][0]][markersPos[i][1]].markers = 1;
    }

    // Update the robot status according to the command line arguments.
    aRobot->x = initialX;
    aRobot->y = initialY;
    aRobot->dir = initialDirection;
}


int stringToDirection(char* Dir) {
    if (!strcmp(Dir, "north"))
        return 0;
    else if (!strcmp(Dir, "south"))
        return 2;
    else if (!strcmp(Dir, "east"))
        return 1;
    else if (!strcmp(Dir, "west"))
        return 3;
    else {
        printf("Invalid direction: %s\n", Dir);
        return -1;
    }
}


void dfs(Robot aRobot, Cell grid[SIZE][SIZE], int booked[SIZE][SIZE]) {
    if (grid[aRobot.x][aRobot.y].markers) {
        booked[aRobot.x][aRobot.y] = 1;

        for(int i = 0; i < COUNTMARKERS; i++) {
            if (aRobot.x == markersPos[i][0] && aRobot.y == markersPos[i][1]) {
                strcpy(pathways[i], aRobot.prevSteps);
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

    if (argc == 4) {
        initialX = atoi(argv[1]);
        initialY = atoi(argv[2]);
        char* dir = argv[3];
        initialDirection = stringToDirection(dir);
        validateInput();
    } else {
        printf("Too few or too many arguments, default values are used.\n");
    }

    initGrid(&robot, grid);
    drawBackground(grid);

    int booked[SIZE][SIZE] = {};
    dfs(robot, grid, booked);
    render(robot, grid);

    int nowMarker = 0;

    while (nowMarker < COUNTMARKERS) {
        for(int j = 0; pathways[nowMarker][j] != '\0'; j++) {
            char action = pathways[nowMarker][j];
            move(&robot, action);
            render(robot, grid);
        }

        pickUpMarker(&robot, grid);
        int reNowMarker = returnHome(&robot, grid, nowMarker);
        nowMarker = reNowMarker;
        dropMarker(&robot, grid);
        robot.prevSteps[0] = '\0';
        nowMarker++;
    }
    
    return 0;
}

