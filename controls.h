#define SIZE 10


void forward(struct Robot* aRobot);
void left(struct Robot* aRobot);
void right(struct Robot* aRobot);
int atMarker(struct Robot aRobot, struct Cell grid[SIZE][SIZE]);
int canMoveForward(struct Robot* aRobot, struct Cell grid[SIZE][SIZE]);
int atHome(struct Robot aRobot, int initialX, int initialY);
void pickUpMarker(struct Robot* aRobot, struct Cell grid[SIZE][SIZE]);
void dropMarker(struct Robot* aRobot, struct Cell grid[SIZE][SIZE]);
int isCarryingAMarker(struct Robot aRobot);
void moveLeft(struct Robot* aRobot, int steps, struct Cell grid[SIZE][SIZE], int initialX, int initialY);
void moveRight(struct Robot* aRobot, int steps, struct Cell grid[SIZE][SIZE], int initialX, int initialY);
void faceWest(struct Robot* aRobot);
void faceEast(struct Robot* aRobot);
void faceNorth(struct Robot* aRobot);
void faceSouth(struct Robot* aRobot);
// void moveDelta(struct Robot* aRobot, int dx, int dy);