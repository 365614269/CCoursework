// Below are the drawing functions of the aRobot.
#include "graphics.h"
#include "robotGraphics.h"
#define SIZE 10
#define SIDELENGTH 25
#define INITOFFSET 20


void fillXs(Triangle* triangle, int x0, int x1, int x2) {
    triangle->xs[0] = x0;
    triangle->xs[1] = x1;
    triangle->xs[2] = x2;
}

void fillYs(Triangle* triangle, int y0, int y1, int y2) {
    triangle->ys[0] = y0;
    triangle->ys[1] = y1;
    triangle->ys[2] = y2;
}

void drawHome(int x, int y) {
    setColour(blue);
    fillRect(INITOFFSET + SIDELENGTH*y, INITOFFSET + SIDELENGTH*x, SIDELENGTH, SIDELENGTH); // Fill the home square with blue.
    setColour(black);
}

void drawRobot(Robot aRobot) {
    setColour(green);
    Triangle equilateralTriangle;

    switch (aRobot.dir) {
        case NORTH: 
            fillYs(&equilateralTriangle, INITOFFSET + SIDELENGTH*aRobot.x + 22, INITOFFSET + SIDELENGTH*aRobot.x + 4, INITOFFSET + SIDELENGTH*aRobot.x + 22);
            fillXs(&equilateralTriangle, INITOFFSET + SIDELENGTH*aRobot.y + 4, INITOFFSET + SIDELENGTH*aRobot.y + 13, INITOFFSET + SIDELENGTH*aRobot.y + 22);
            break;
        case SOUTH:
            fillYs(&equilateralTriangle, INITOFFSET + SIDELENGTH*aRobot.x + 4, INITOFFSET + SIDELENGTH*aRobot.x + 22, INITOFFSET + SIDELENGTH*aRobot.x + 4);
            fillXs(&equilateralTriangle, INITOFFSET + SIDELENGTH*aRobot.y + 4, INITOFFSET + SIDELENGTH*aRobot.y + 13, INITOFFSET + SIDELENGTH*aRobot.y + 22);
            break;
        case EAST:
            fillYs(&equilateralTriangle, INITOFFSET + SIDELENGTH*aRobot.x + 4, INITOFFSET + SIDELENGTH*aRobot.x + 13, INITOFFSET + SIDELENGTH*aRobot.x + 22);
            fillXs(&equilateralTriangle, INITOFFSET + SIDELENGTH*aRobot.y + 4, INITOFFSET + SIDELENGTH*aRobot.y + 22, INITOFFSET + SIDELENGTH*aRobot.y + 4);
            break;
        case WEST:
            fillYs(&equilateralTriangle, INITOFFSET + SIDELENGTH*aRobot.x + 4, INITOFFSET + SIDELENGTH*aRobot.x + 13, INITOFFSET + SIDELENGTH*aRobot.x + 22);
            fillXs(&equilateralTriangle, INITOFFSET + SIDELENGTH*aRobot.y + 22, INITOFFSET + SIDELENGTH*aRobot.y + 4, INITOFFSET + SIDELENGTH*aRobot.y + 22);
            break;
    }

    fillPolygon(3, equilateralTriangle.xs, equilateralTriangle.ys);

    if (aRobot.carrysMarker) {  // If the robot carrys a marker, draw a marker on it.
        setColour(red);
        fillOval(INITOFFSET + aRobot.y*SIDELENGTH + 5, INITOFFSET + aRobot.x*SIDELENGTH + 5, 15, 15);
    }
    setColour(black);
}

void drawGrid(Robot aRobot, Cell grid[SIZE][SIZE], int initialX, int initialY) {
    clear();
    drawHome(initialX, initialY);

    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            drawRect(INITOFFSET + i*SIDELENGTH, INITOFFSET + j*SIDELENGTH, SIDELENGTH, SIDELENGTH);  // Draw a square cell at position (i,j)
            if (grid[i][j].markers) {  // Draw a red dot as a marker.
                setColour(red);
                fillOval(INITOFFSET + j*SIDELENGTH + 5, INITOFFSET + i*SIDELENGTH + 5, 15, 15);
                setColour(black);
            } else if (grid[i][j].blocked) {
                setColour(gray);
                fillRect(INITOFFSET + j*SIDELENGTH, INITOFFSET + i*SIDELENGTH, SIDELENGTH, SIDELENGTH);
                setColour(black);
            }
        }
    }

    drawRobot(aRobot);
    sleep(100);  // Adjust the speed of the robot here!
}