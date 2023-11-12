#include "graphics.h"
#include "robotControls.h"
#include <string.h>
#include <stdio.h>
// Adjust the speed of robot at the end of robotGraphics.c!

int markersPosition[COUNTMARKERS][2];
int blocksPosition[COUNTBLOCKS][2];
char pathwayToMarkers[COUNTMARKERS][500] = {};
int initialX = 6;
int initialY = 5;
Direction initialDirection = NORTH;


void readBlocks(Cell grid[SIZE][SIZE]){
    FILE *fblocks = fopen("blocksPosition.txt", "r");
    if (fblocks == NULL) printf("Failed to open blocksPosition.txt\n");

    for(int countBlock = 0; countBlock < COUNTBLOCKS; countBlock++) {
        int blockX, blockY;

        if (fscanf(fblocks, "%d%d", &blockX, &blockY) != 2) {
            printf("Error reading from blocksPosition.txt\n");
            fclose(fblocks);
        }

        blocksPosition[countBlock][0] = blockX;
        blocksPosition[countBlock][1] = blockY;
    }

    fclose(fblocks);
}

void readMarkers(Cell grid[SIZE][SIZE]) {
    FILE *fmarkers = fopen("markersPosition.txt", "r");
    if (fmarkers == NULL) printf("Failed to open markersPosition.txt\n");
    
    for(int countMarker = 0; countMarker < COUNTMARKERS; countMarker++) {
        int markerX, markerY;

        if (fscanf(fmarkers, "%d%d", &markerX, &markerY) != 2) {
            printf("Error reading from markersPosition.txt\n");
            fclose(fmarkers);
        }

        markersPosition[countMarker][0] = markerX;
        markersPosition[countMarker][1] = markerY;
    }

    fclose(fmarkers);
}

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
    readMarkers(grid);
    readBlocks(grid);

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
    drawBackground(grid, initialX, initialY);

    int booked[SIZE][SIZE] = {};
    dfs(robot, grid, booked);
    drawForeground(robot, grid);

    for(int nowMarker = 0; nowMarker < COUNTMARKERS; nowMarker++) {
        for(int j = 0; pathwayToMarkers[nowMarker][j] != '\0'; j++) {
            char action = pathwayToMarkers[nowMarker][j];
            move(&robot, action);
            drawForeground(robot, grid);
        }

        pickUpMarker(&robot, grid);
        returnHome(&robot, grid, nowMarker, initialDirection);
        dropMarker(&robot, grid);
        robot.prevSteps[0] = '\0';
    }
    
    return 0;
}

