// Below are the drawing functions of the aRobot.
#include "graphics.h"
#include "robotGraphics.h"

extern int initialX;
extern int initialY;

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
        {4, 13, 22},
        {4, 22, 4},
        {4, 13, 22}
    };
    int relativePosX[4][3] = {
        {4, 13, 22},
        {4, 22, 4},
        {4, 13, 22},
        {22, 4, 22}
    };
    int dir = aRobot.dir;

    for(int i = 0; i < 3; i++) {
        triangle->xs[i] = absoluteX(aRobot, relativePosX[dir][i]);
        triangle->ys[i] = absoluteY(aRobot, relativePosY[dir][i]);
    }
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

void drawGrid(Robot aRobot, Cell grid[SIZE][SIZE]) {
    clear();
    drawHome(initialX, initialY);

    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            drawRect(INITOFFSET + i * SIDELENGTH, INITOFFSET + j * SIDELENGTH, SIDELENGTH, SIDELENGTH);  // Draw a square cell at position (i,j)
            if (grid[i][j].markers) {  // Draw a red dot as a marker.
                setColour(red);
                fillOval(INITOFFSET + j * SIDELENGTH + 5, INITOFFSET + i * SIDELENGTH + 5, 15, 15);
                setColour(black);
            } else if (grid[i][j].blocked) {  // Draw a grey block as an obstacle.
                setColour(gray);
                fillRect(INITOFFSET + j * SIDELENGTH, INITOFFSET + i * SIDELENGTH, SIDELENGTH, SIDELENGTH);
                setColour(black);
            }
        }
    }

    drawRobot(aRobot);
    sleep(1);  // Adjust the speed of the robot here!
}