typedef struct {
    Rectangle entity;
    float speed;
    int direction;
    float minX, maxX;
} Enemy;

void moveEnemy(Enemy *e);
