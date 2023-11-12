# CCoursework
The UCL first year Computer Science Principles of Programming C Coursework.

The aim of the project is to let a robot collect the markers positioned on the graphical grid one after another, and carry them back home.

All the 6 stages required in the CCoursework.pdf are completed.

# Prerequisite
- JDK 21
- gcc

# How to start
The markers and blocks position are read from markersPosition.txt and blocksPosition.txt, respectively.

To compile the code, use the command

- `gcc -o [fileName] main.c robotGraphics.c controls.c graphics.c`

Assign a value to variable fileName, and you will create an executable file called fileName.

To run the executable file, use the command

- `./[fileName] 2 3 south | java -jar drawapp-3.0.jar`

You can see the 3 positional arguments passed, that indicates the starting position and direction of the robot.

The first argument is the x coordinate. Note that x increments downwards in the grid.

The second argument is the y coordinate. Note that y increments to the right of the grid.

The third argument is the direction. Note that direction north is upwards the screen.
It has to be one of these: "north", "east", "south" or "west"

