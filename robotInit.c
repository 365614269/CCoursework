#include "robotInit.h"
#include <stdio.h>


void readBlocks(Cell grid[SIZE][SIZE], int blocksPosition[COUNTBLOCKS][2]) {
    FILE *fblocks = fopen("blocksPosition.txt", "r");
    if (fblocks == NULL) {
        printf("Failed to open blocksPosition.txt\n");
    }

    for(int countBlock = 0; countBlock < COUNTBLOCKS; countBlock++) {
        int blockX, blockY;

        if (fscanf(fblocks, "%d%d", &blockX, &blockY) != 2) {
            printf("Error reading: Not exactly 2 numbers on the line\n");
            fclose(fblocks);
        }

        blocksPosition[countBlock][0] = blockX;
        blocksPosition[countBlock][1] = blockY;
    }

    fclose(fblocks);
}

void readMarkers(Cell grid[SIZE][SIZE], int markersPosition[COUNTMARKERS][2]) {
    FILE *fmarkers = fopen("markersPosition.txt", "r");
    if (fmarkers == NULL) {
        printf("Failed to open markersPosition.txt\n");
    }
    
    for(int countMarker = 0; countMarker < COUNTMARKERS; countMarker++) {
        int markerX, markerY;

        if (fscanf(fmarkers, "%d%d", &markerX, &markerY) != 2) {
            printf("Error reading: Not exactly 2 numbers on the line\n");
            fclose(fmarkers);
        }

        markersPosition[countMarker][0] = markerX;
        markersPosition[countMarker][1] = markerY;
    }

    fclose(fmarkers);
}

void validateInput(int initialX, int initialY, Direction initialDirection) {
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


int stringToDirection(char* Dir) {
    if (!strcmp(Dir, "north"))
        return 0;
    else if (!strcmp(Dir, "east"))
        return 1;
    else if (!strcmp(Dir, "south"))
        return 2;
    else if (!strcmp(Dir, "west"))
        return 3;
    else {
        printf("Invalid direction: %s\n", Dir);
        return -1;
    }
}
