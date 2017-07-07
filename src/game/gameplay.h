#ifndef GAMEPLAY_H
#define GAMEPLAY_H

const float PLAYER_SPEED = 4;
const float PHANTOM_SPEED = 4;
const float PHANTOM_EXPLOSIVE_SPEED = 1.5;
const float PHANTOM_FAST_SPEED = 8;
const float PHANTOM_KILLER_SPEED = 2.5;
const float PLAYER_PHANTOM_SPEED = 3;

const float MIN_VELOCITY = 0.001;
const float PATH_PRECISION = 1e-5;

const int COINS_PER_LEVEL = 15;

const float INVINCIBILITY_TIME = 1.f;

const int BOSS_LIVES = 4;
const float BOSS_SPAWN_TIME = 10.f;

const float PLAYER_LIGHT_RADIUS = 5.f;

const int DUEL_MODE_PLAYER_OBJECTIVE = 30;
const int DUEL_MODE_PHANTOM_OBJECTIVE = -15;

#endif // GAMEPLAY_H
