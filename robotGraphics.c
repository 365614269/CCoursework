// Below are the drawing functions of the aRobot.
#include "graphics.h"
#include "robotGraphics.h"


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

int absoluteY(Robot aRobot, int relative) {
    return INITOFFSET + SIDELENGTH * aRobot.x + relative;
}

int absoluteX(Robot aRobot, int relative) {
    return INITOFFSET + SIDELENGTH * aRobot.y + relative;
}

void fillXY(Triangle* triangle, Robot aRobot) {
    // the relative position compared to the block
    int relativePosY[4][3] = {
        {22, 4, 22},
        {4, 22, 4},
        {4, 13, 22},
        {4, 13, 22}
    };
    int relativePosX[4][3] = {
        {4, 13, 22},
        {4, 13, 22},
        {4, 22, 4},
        {22, 4, 22}
    };
    int dir = aRobot.dir;
    // use a for loop if you want
    int y0 = absoluteY(aRobot, relativePosY[dir][0]);
    int y1 = absoluteY(aRobot, relativePosY[dir][1]);
    int y2 = absoluteY(aRobot, relativePosY[dir][2]);
    int x0 = absoluteX(aRobot, relativePosX[dir][0]);
    int x1 = absoluteX(aRobot, relativePosX[dir][1]);
    int x2 = absoluteX(aRobot, relativePosX[dir][2]);
    fillXs(triangle, x0, x1, x2);
    fillYs(triangle, y0, y1, y2);
}

void drawHome(int x, int y) {
    setColour(blue);
    fillRect(INITOFFSET + SIDELENGTH * y, INITOFFSET + SIDELENGTH * x, SIDELENGTH, SIDELENGTH); // Fill the home square with blue.
    setColour(black);
}

void drawRobot(Robot aRobot) {
    setColour(green);
    Triangle equilateralTriangle;

    fillXY(&equilateralTriangle, aRobot);

    fillPolygon(3, equilateralTriangle.xs, equilateralTriangle.ys);

    if (aRobot.carrysMarker) {  // If the robot carrys a marker, draw a marker on it.
        setColour(red);
        fillOval(INITOFFSET + aRobot.y * SIDELENGTH + 5, INITOFFSET + aRobot.x * SIDELENGTH + 5, 15, 15);
    }
    setColour(black);
}

void drawGrid(Robot aRobot, Cell grid[SIZE][SIZE], int initialX, int initialY) {
    clear();
    drawHome(initialX, initialY);

    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            drawRect(INITOFFSET + i * SIDELENGTH, INITOFFSET + j * SIDELENGTH, SIDELENGTH, SIDELENGTH);  // Draw a square cell at position (i,j)
            if (grid[i][j].markers) {  // Draw a red dot as a marker.
                setColour(red);
                fillOval(INITOFFSET + j * SIDELENGTH + 5, INITOFFSET + i * SIDELENGTH + 5, 15, 15);
                setColour(black);
            } else if (grid[i][j].blocked) {
                setColour(gray);
                fillRect(INITOFFSET + j * SIDELENGTH, INITOFFSET + i * SIDELENGTH, SIDELENGTH, SIDELENGTH);
                setColour(black);
            }
        }
    }

    drawRobot(aRobot);
    sleep(0);  // Adjust the speed of the robot here!
}