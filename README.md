# CCoursework
The UCL first year Computer Science Principles of Programming C Coursework.

The aim of the project is to let a robot collect the markers positioned on the graphical grid one after another, and carry them back home. 

All the 6 stages required in the CCoursework.pdf are completed.

To compile the code, use the command

- gcc -o fileName main.c robotGraphics.c controls.c graphics.c

Fill in the desired fileName, and you will create an executable file.

To run the executable file, use the command

- ./fileName 2 3 south | java -jar drawapp-3.0.jar

You can see the 3 positional arguments passed, that indicates the starting position and direction of the robot.

The first argument is the x coordinate. Note that x increments downwards in the grid.

The second argument is the y coordinate. Note that x increments to the right in the grid.

The third argument is the direction. Note that direction north is upwards the screen.

Note that you'll need JDK 21 installed.