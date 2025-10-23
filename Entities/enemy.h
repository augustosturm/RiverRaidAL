typedef struct {
    Rectangle entity;
    float speed;
    int direction;
    float minX, maxX;
} Enemy;

/**
 * @brief Moves the enemy along the X axis.
 *
 * @param Enemy e Pointer to the enemy.
 * @return void
 */
void moveEnemy(Enemy *e);

/**
 * @brief Changes the enemy's direction when it reaches the movement limit.
 *
 * @param Enemy e Pointer to the enemy.
 * @return void
 */
void changeEnemyDirection(Enemy *e);
