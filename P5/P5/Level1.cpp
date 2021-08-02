#include "Level1.h"

#define LEVEL1_ENEMY_COUNT 1

#define LEVEL1_WIDTH 17
#define LEVEL1_HEIGHT 8

unsigned int level1_data[] =
{
    29, 0,     0,   0,   0,   0,   0,   0,   0,   0,   0,   0,      0,   0,     0,   0,   0,
    29, 0,     0,   0,   0,   0,   0,   0,   0,   0,   0,   0,      0,   0,     0,   0,   0,
    29, 0,     0,   0,   0,   0,   0,   0,   0,   0,   0,   0,      0,   0,     0,   0,   0,
    29, 0,     0,   0,   0,   0,   0,   0,   0,   0,   0,   0,      0,   0,     0,   0,   0,
    29, 0,     0,   0,   0,   0,   0,   0,   0,   0,   0,   0,      0,   0,     0,   0,   0,
    29, 0,     0,   0,   0,   0,   0,   0,   0,  1,    2,   2,   2,   2,  2,  2,  3,
    29, 1,  2,  2,  2,  2,  2,  2,  2,  2,   4,  4,  4,  4, 4, 4, 4,
    29, 4, 4, 4, 4, 4, 4, 4, 4, 4,  4,  4,    4, 4, 4, 4, 4
};

void Level1::Initialize() {
    
    state.nextScene = -1;

    GLuint mapTextureID = Util::LoadTexture("industrial_tilesheet.png");
    state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 14, 8);

    // Move over all of the player and enemy code from initialization.

    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(5, 0, 0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0, -10.0f, 0);
    state.player->speed = 2.0f;
    state.player->textureID = Util::LoadTexture("character_robot_sheetHD.png");


    state.player->animRight = new int[4]{ 38, 39, 40, 41 };
    state.player->animLeft = new int[4]{ 41, 40, 39, 38 };
    //state.player->animUp = new int[4]{ 2, 6, 10, 14 };
    //state.player->animDown = new int[4]{ 0, 4, 8, 12 };
    state.player->animIndices = state.player->animRight;
    state.player->animFrames = 4;
    state.player->animIndex = 0;
    state.player->animTime = 0;
    state.player->animCols = 9;
    state.player->animRows = 5;


    state.player->height = 0.8f;
    state.player->width = 0.7f;

    state.player->jumpPower = 7.0f;


    state.enemies = new Entity[LEVEL1_ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("alienenemy.png");

    state.enemies[0].entityType = ENEMY;
    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(7, -5, 0);
    state.enemies[0].speed = 1.0f;
    state.enemies[0].aiType = WAITANDGO;
    state.enemies[0].aiState = IDLE;
    state.enemies[0].acceleration = glm::vec3(0, -10.0f, 0);
}


void Level1::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.map);

    
    for (int i = 0; i < LEVEL1_ENEMY_COUNT; i++) {
        state.enemies[i].Update(deltaTime, state.player, NULL, NULL, state.map);
    }
    

    if (state.player->position.x >= 16) {
        state.nextScene = 2;
    }

}


void Level1::Render(ShaderProgram* program) {
    
    state.map->Render(program);
    state.player->Render(program);
    
    for (int i = 0; i < LEVEL1_ENEMY_COUNT; i++) {
        state.enemies[i].Render(program);
    }
    
    
}