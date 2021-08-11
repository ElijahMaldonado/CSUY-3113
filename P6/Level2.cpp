#include "Level2.h"

#define LEVEL2_ENEMY_COUNT 1
#define LEVEL2_COIN_COUNT 2
#define LEVEL2_DOOR_COUNT 1

#define LEVEL2_WIDTH 20
#define LEVEL2_HEIGHT 20

unsigned int level2_data[] =
{
    0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,    1,   1,     1,   1,   1, 1, 0, 0,
    0, 0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 1, 0, 0,
    0, 0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,    1, 0, 0, 0,
    0, 0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 1, 0, 0,
    0, 0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 1, 0, 0,
    0, 0,   1,   0,   0,   0,   0,   1,   0,   0,   0,   0,    0,   0,     0,   0,   0, 1, 0, 0,
    0, 0,   1,   0,   0,   0,   0,   1,   1,   0,   0,   0,    0,   0,     0,   0,   0, 1, 0, 0,
    0, 0,   1,   0,   0,   0,   0,   0,   1,   1,   0,   0,    0,   0,     0,   0,   0, 1, 0, 0,
    0, 0,   1,   0,   0,   0,   0,   0,   0,   0,   1,   1,    0,   0,     0,   0,   0, 1, 0, 0,
    0, 0,   1,   0,   0,   0,   0,   0,   0,   0,   1,   1,    1,   1,     1,   1,   1, 1, 0, 0,
    0, 0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 1, 0, 0,
    0, 0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 1, 0, 0,
    0, 0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 1, 0, 0,
    0, 0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 1, 0, 0,
    0, 0,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 1, 0, 0,
    0, 0,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,    1,   1,     1,   1,   1, 1, 0, 0,
    0, 0,   0,   0,   0,   0,   0,  0,   0,   0,   0,   0,    0,   0,     0,   0,   0,  0, 0, 0,
    0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
};

unsigned int bLevel2_data[] =
{
    0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 0,   240,   241,      241,     241,     241,     241,     241,     241,     241,     241,      241,     241,       241,     241,  241, 242, 0, 0,
    0, 0,   256,   257,   257,   257,   251,   251,   251,   251,   251,   251,    251,   251,     251,   251,   251, 258, 0, 0,
    0, 0,   256,   251,   251,   251,   251,   251,   251,   251,   251,   251,    251,   251,     251,   257,   251, 258, 0, 0,
    0, 0,   256,   251,   251,   251,   257,   257,   251,   251,   257,   251,    251,   251,     251,   251,   251, 258, 0, 0,
    0, 0,   256,   251,   251,   251,   251,   251,   251,   251,   251,   251,    251,   251,     251,   251,   251, 258, 0, 0,
    0, 0,   256,   257,   257,   251,   284,   267,   268,   251,   257,   251,    251,   257,     257,   257,   251, 258, 0, 0,
    0, 0,   256,   251,   251,   251,   284,   267,   267,   251,   251,   251,    251,   257,     257,   251,   251, 258, 0, 0,
    0, 0,   256,   251,   257,   251,   251,   251,   283,   267,   251,   251,    251,   251,     257,   251,   251, 258, 0, 0,
    0, 0,   256,   257,   251,   251,   251,   251,   251,   284,   267,   267,    251,   251,     257,   251,   251, 258, 0, 0,
    0, 0,   256,   251,   251,   257,   251,   251,   251,   284,   283,   283,    267,   283,     267,   283,   267, 258, 0, 0,
    0, 0,   256,   251,   257,   251,   251,   251,   257,   251,   251,   251,    251,   251,     251,   257,   251,258,0, 0, 0,
    0, 256,   251,   251,   251,   257,   251,   251,   257,   257,   251,   251,    251,   251,     257,   251,   258, 0, 0, 0,
    0, 256,   251,   257,   251,   251,   251,   251,   251,   251,   251,   251,    251,   251,     257,   251,   258, 0, 0, 0,
    0, 256,   251,   251,   251,   251,   257,   251,   251,   257,   251,   251,    251,   251,     251,   257,   258, 0, 0, 0,
    0, 256,   251,   251,   251,   251,   251,   251,   251,   251,   251,   251,    251,   251,     251,   257,   258, 0, 0, 0,
    0, 272,   273,   273,   273,   273,   273,   273,   273,   273,   273,   273,    273,   273,     273,   273,   274, 0, 0, 0,
    0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0
};

void Level2::Initialize() {

    state.nextScene = -1;

    GLuint mapTextureID = Util::LoadTexture("TOPDOWN.png");
    GLuint bMapTextureID = Util::LoadTexture("TOPDOWN.png");
    GLuint itemTextureID = Util::LoadTexture("item8BIT_coin.png");
    state.map = new Map(LEVEL2_WIDTH, LEVEL2_HEIGHT, level2_data, mapTextureID, 1.0f, 16, 30);
    state.bMap = new Map(LEVEL2_WIDTH, LEVEL2_HEIGHT, bLevel2_data, bMapTextureID, 1.0f, 16, 30);

    // Move over all of the player and enemy code from initialization.

    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(6, -4, 0);
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

    state.player->jumpPower = 7.0f;


    state.enemies = new Entity[LEVEL2_ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("Castle(AllFrame).png");

    state.enemies[0].entityType = ENEMY;
    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(9, -7, 0);
    state.enemies[0].speed = 1.0f;
    state.enemies[0].aiType = WAITANDGO;
    state.enemies[0].aiState = IDLE;
    state.enemies[0].acceleration = glm::vec3(0, -10.0f, 0);
    state.enemies[0].animRight = new int[1]{ 5 };
    state.enemies[0].animIndices = state.enemies->animRight;
    state.enemies[0].animFrames = 1;
    state.enemies[0].animIndex = 0;
    state.enemies[0].animTime = 0;
    state.enemies[0].animCols = 4;
    state.enemies[0].animRows = 35;


    state.coin = new Entity[LEVEL2_COIN_COUNT];

    state.coin[0].entityType = COIN;
    state.coin[0].position = glm::vec3(5, -8, 0);
    state.coin[0].textureID = itemTextureID;


    state.coin[1].entityType = COIN;
    state.coin[1].position = glm::vec3(13, -9, 0);
    state.coin[1].textureID = itemTextureID;


    state.door = new Entity[LEVEL2_DOOR_COUNT];

    state.door[0].entityType = DOOR;
    state.door[0].position = glm::vec3(14, -13, 0);
    state.door[0].textureID = mapTextureID;
    state.door[0].animRight = new int[1]{ 30 };
    state.door[0].animIndices = state.door->animRight;
    state.door[0].animFrames = 1;
    state.door[0].animIndex = 0;
    state.door[0].animTime = 0;
    state.door[0].animCols = 16;
    state.door[0].animRows = 30;
    
}


void Level2::Update(float deltaTime) {
    
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL2_ENEMY_COUNT, state.coin, LEVEL2_COIN_COUNT, state.door, LEVEL2_DOOR_COUNT, state.map);


    for (int i = 0; i < LEVEL2_ENEMY_COUNT; i++) {
        state.enemies[i].Update(deltaTime, state.player, NULL, NULL, NULL, NULL, NULL, NULL, state.map);
    }

    for (int i = 0; i < LEVEL2_COIN_COUNT; i++) {
        state.coin[i].Update(deltaTime, state.player, NULL, NULL, NULL, NULL, NULL, NULL, state.map);
    }

    for (int i = 0; i < LEVEL2_DOOR_COUNT; i++) {
        state.door[i].Update(deltaTime, state.player, NULL, NULL, NULL, NULL, NULL, NULL, state.map);
    }

    if (state.player->coinCount < 11) {
        state.door[0].isActive = true;
    }

    if (state.player->doorState >= 1) {
        state.nextScene = 1;
        state.player->doorState = 0;
    }


}


void Level2::Render(ShaderProgram* program) {

    state.map->Render(program);
    state.bMap->Render(program);
    state.player->Render(program);


    for (int i = 0; i < LEVEL2_ENEMY_COUNT; i++) {
        state.enemies[i].Render(program);
    }

    for (int i = 0; i < LEVEL2_COIN_COUNT; i++) {
        state.coin[i].Render(program);
    }

    for (int i = 0; i < LEVEL2_DOOR_COUNT; i++) {
        state.door[i].Render(program);
    }

}