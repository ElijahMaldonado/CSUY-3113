#include "Level4.h"
#include <SDL_mixer.h>
#include <SDL.h>



#define LEVEL4_WIDTH 20
#define LEVEL4_HEIGHT 20
#define LEVEL4_ENEMY_COUNT 2
#define LEVEL4_DOOR_COUNT 1

unsigned int level4_data[] =
{
    64, 64,   64,   64,   64,   64,   64,   64,   64,   64,   64,  64,    64,   64,     64,   64,   64, 64, 64, 64,
    64,  64,   64,  64,   64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64,  0,   0,   0,    64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 0,   0,    0,    64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 0,   0,    0,    64,    0,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   0,   64,   64,    0,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   0,   64,     0,   0,     0,    0,    0,    0,    0,    0,     0,    0,      0,  64,   64, 64, 64, 64,
    64, 64,   0,   64,     0,   64,   64,   64,   64,   64,   64,   64,    64,   64,     0,   64,   64, 64, 64, 64,
    64, 64,   0,    0,     0,   64,    0,    0,    0,   64,   64,   64,    64,   64,     0,  64,   64, 64, 64, 64,
    64, 64,   0,    0,     0,   64,    0,   64,    0,   64,     0,   0,    0,   64,     0,  64,   64, 64, 64, 64,
    64, 64,   0,    0,     0,   64,    0,   64,    0,   64,   64,   64,    0,   64,     0,  64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,   64,    0,   64,    0,   64,   64,   64,    0,   64,     0,  64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,    0,    0,   64,    0,   0,   64,   64,     0,   64,     0,  64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,    0,   64,   64,    64,   0,   0,     0,    0,   64,     0,  64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,    0,   64,   64,   64,   64,   64,   64,    64,   64,     0,  64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,    0,    0,    0,    0,    0,    0,    0,     0,    0,     0,  64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,   64,   64,  64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
};

unsigned int bLevel4_data[] =
{
    64, 0,    0,  0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 0,    0,  0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 61,  62, 63,   0,   0,  0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 77,  30, 79,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 93,  42, 95,   0,  42,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 0,   42,  0,   0,  42,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 0,   42,  0,  42,  42,  42,  42,  42,  42,  42,  42,   42,  42,    42,   0,   0, 0, 0, 0,
    0, 0,   42,  0,  42,   0,   0,   0,   0,   0,   0,   0,    0,   0,    42,   0,   0, 0, 0, 0,
    0, 0,   42, 62,  42,   0,  42,  42,  42,   0,   0,   0,    0,   0,    42,   0,   0, 0, 0, 0,
    0, 0,   42, 42,  42,   0,  42,   0,  42,   0,  42,  42,   42,   0,    42,   0,   0, 0, 0, 0,
    0, 0,   42, 42,  42,   0,  42,   0,  42,   0,   0,   0,   42,   0,   42,  0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,   0,  42,   0,  42,   0,   0,   0,   42,   0,    42,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,  42,  42,   0,  42,  42,   0,   0,   42,   0,    42,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,  42,   0,   0,   0,  42,  42,  42,   42,   0,    42,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,  42,   0,   0,   0,   0,   0,   0,    0,   0,    42,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,  42,  42,  42,  42,  42,  42,  42,   42,   42,    42,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,    0,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0
};


void Level4::Initialize() {

    state.nextScene = -1;

    GLuint mapTextureID = Util::LoadTexture("TOPDOWN.png");
    GLuint bMapTextureID = Util::LoadTexture("TOPDOWN.png");
    GLuint itemTextureID = Util::LoadTexture("item8BIT_coin.png");


    state.map = new Map(LEVEL4_WIDTH, LEVEL4_HEIGHT, level4_data, mapTextureID, 1.0f, 16, 30);
    state.bMap = new Map(LEVEL4_WIDTH, LEVEL4_HEIGHT, bLevel4_data, bMapTextureID, 1.0f, 16, 30);

    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(2, -3, 0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0, 0, 0);
    state.player->speed = 2.5f;
    state.player->textureID = Util::LoadTexture("Char5_walk_16px.png");

    state.player->animRight = new int[4]{ 15, 12, 13, 14 };
    state.player->animLeft = new int[4]{ 7, 4, 5, 6 };
    state.player->animUp = new int[4]{ 9, 10, 11, 8 };
    state.player->animDown = new int[4]{ 1, 2, 3, 16 };
    state.player->animIndices = state.player->animRight;
    state.player->animFrames = 4;
    state.player->animIndex = 0;
    state.player->animTime = 0;
    state.player->animCols = 4;
    state.player->animRows = 4;


    state.player->height = 0.8f;
    state.player->width = 0.7f;

    state.enemies = new Entity[LEVEL4_ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("Castle(AllFrame).png");

    state.enemies[0].entityType = ENEMY;
    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(5, -4, 0);
    state.enemies[0].speed = 1.0f;
    state.enemies[0].aiType = WAITANDGO;
    state.enemies[0].aiState = IDLE;
    state.enemies[0].acceleration = glm::vec3(0, 0, 0);
    state.enemies[0].animRight = new int[1]{ 5 };
    state.enemies[0].animIndices = state.enemies->animRight;
    state.enemies[0].animFrames = 1;
    state.enemies[0].animIndex = 0;
    state.enemies[0].animTime = 0;
    state.enemies[0].animCols = 4;
    state.enemies[0].animRows = 35;
    state.enemies[0].height = 0.8f;
    state.enemies[0].width = 0.7f;


    state.door = new Entity[LEVEL4_DOOR_COUNT];

    state.door[0].entityType = DOOR;
    state.door[0].position = glm::vec3(10, -9, 0);
    state.door[0].textureID = mapTextureID;
    state.door[0].animRight = new int[1]{ 30 };
    state.door[0].animIndices = state.door->animRight;
    state.door[0].animFrames = 1;
    state.door[0].animIndex = 0;
    state.door[0].animTime = 0;
    state.door[0].animCols = 16;
    state.door[0].animRows = 30;

}


void Level4::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL4_ENEMY_COUNT, NULL, NULL, state.door, LEVEL4_DOOR_COUNT, state.map);

    for (int i = 0; i < LEVEL4_ENEMY_COUNT; i++) {
        state.enemies[i].Update(deltaTime, state.player, NULL, NULL, NULL, NULL, NULL, NULL, state.map);
    }

    for (int i = 0; i < LEVEL4_DOOR_COUNT; i++) {
        state.door[i].Update(deltaTime, state.player, NULL, NULL, NULL, NULL, NULL, NULL, state.map);
    }

    if (state.player->doorState > 0) {
        state.nextScene = 5;
    }

}


void Level4::Render(ShaderProgram* program) {

    state.map->Render(program);
    state.bMap->Render(program);
    state.player->Render(program);

    for (int i = 0; i < LEVEL4_ENEMY_COUNT; i++) {
        state.enemies[i].Render(program);
    }

    for (int i = 0; i < LEVEL4_DOOR_COUNT; i++) {
        state.door[i].Render(program);
    }

}