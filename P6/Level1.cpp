#include "Level1.h"
#include <SDL_mixer.h>
#include <SDL.h>

#define LEVEL1_ENEMY_COUNT 2
#define LEVEL1_COIN_COUNT 7
#define LEVEL1_DOOR_COUNT 3

#define LEVEL1_WIDTH 22
#define LEVEL1_HEIGHT 21

unsigned int level1_data[] =
{
    236,236,236,   236,   236,   236,   236,   236,   236,   236,   236,   236,  236,    236,   236,     236,   236,   236, 236, 236, 236, 236,
    236 ,8 ,  6,   7,    141,   142,   142,   142,   142,   142,   142,   142,   142,    142,   142,     142,   142,   143, 64, 64, 64, 64,
    6   ,24, 22,   23,   205,   206,   206,   206,   206,   206,   206,   206,   206,    206,   206,     206,   206,   207, 64, 64, 64, 64,
    64  ,64, 64,   64,   270,   222,   222,   0,   222,   222,   222,   222,   222,    222,   222,     222,   222,   271, 64, 64, 64, 64,
    64  ,64, 64,   64,   64,      0,   0,   0,   0,   112,     0,   0,   0,    0,   0,     0,   0,   64, 64, 64, 64, 64,
    64  ,64, 64,   64,   64,      0,   0,   0,   0,   112,     0,   0,   0,    0,   0,     0,   0,   64, 64, 64, 64, 64,
    64  ,64, 64,   64,   64,      0,   0,   0,   0,   0,      0,   0,   0,    0,   0,     0,   0,   64, 64, 64, 64, 64,
    64  ,64, 64,   64,   64,      0,   0,   0,   0,   0,     0,   0,   0,    0,   0,     0,   0,   64, 64, 64, 64, 64,
    64  ,64, 64,   64,   64,      0,   0,   0,   0,   112,     0,   0,   0,    0,   0,     0,   0,   64, 64, 64, 64, 64,
    64  ,64, 64,   64,   64,      0,   0,   0,   0,   112,     0,   0,   0,    9,  10,     0,   0,   64, 64, 64, 64, 64,
    64  ,64, 64,   64,   64,     64,  64,  64,  64,   128,     0,   0,   0,   25,  26,     0,   0,   64, 64, 64, 64, 64,
    64  ,64, 64,   64,   64,      0,   0,   0,   0,   0,      0,   0,   0,    0,   0,     0,   0,   64, 64, 64, 64, 64,
    64  ,64, 64,   64,   64,      0,   0,   0,   0,   0,      0,   0,   0,    0,   0,     0,   0,   64, 64, 64, 64, 64,
    64  ,64, 64,   64,   64,      0,   100,   100,   0,   0,      0,   0,   0,    0,   0,     0,   0,   64, 64, 64, 64, 64,
    64  ,64, 64,   64,   64,      0,   0,   0,   0,   0,      0,   0,   0,    0,   0,     0,   0,   64, 64, 64, 64, 64,
    64  ,64, 64,   64,   64,      0,   0,   0,   0,   0,      0,   0,   0,    0,   0,     0,   0,   64, 64, 64, 64, 64,
    64  ,64, 64,   64,   64,     64,   64,   64,   64,       64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64, 64, 
    64  ,64, 64,   64,   64,     64,   64,   64,   64,       64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64, 64,
    64  ,64, 64,   64,   64,     64,   64,   64,   64,       64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64, 64,
    64  ,64, 64,   64,   64,     64,   64,   64,   64,       64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64, 64,64
};

unsigned int bLevel1_data[] =
{
    0,0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0, 0,
    0,0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0, 0,
    0,0, 0,   0,   0,   0,   0,  0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0, 0,
    0,0, 0,   0,   0,   0,   0,   269,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0, 0,
    0,0, 0,   0,   0,   77,   42,   42,   42,   0,   42,   42,   42,    42,   42,     42,   79,   0, 0, 0, 0, 0,
    0,0, 0,   0,   0,   77,   42,   42,   42,   0,   42,   42,   42,    42,   42,     42,   79,   0, 0, 0, 0, 0,
    0,0, 0,   0,   0,   77,   42,   42,   42,   88,   42,   42,   42,    42,   42,     42,   79,   0, 0, 0, 0, 0,
    0,0, 0,   0,   0,   203,   42,   42,   42,   104,   42,   42,   42,    42,   42,     42,   79,   0, 0, 0, 0, 0,
    0,0, 0,   0,   0,   77,   42,   42,   42,   0,   42,   42,   42,    42,   42,     42,   79,   0, 0, 0, 0, 0,
    0,0, 0,   0,   0,   77,   42,   42,   42,   0,   42,   42,   42,    0,   0,     42,   79,   0, 0, 0, 0, 0,
    0,0, 0,   0,   0,   0,     0,   0,   0,    0,   42,   42,   42,    0,   0,     42,   79,   0, 0, 0, 0, 0,
    0,0, 0,   0,   0,   77,   42,   42,   42,   42,   42,   42,   42,    42,   42,     42,   79,   0, 0, 0, 0, 0,
    0,0, 0,   0,   0,   77,   42,   42,   42,   42,   42,   42,   42,    42,   42,     42,   79,   0, 0, 0, 0, 0,
    0,0, 0,   0,   0,   77,   0,   0,   42,   42,   42,   42,   42,    42,   42,     42,   79,   0, 0, 0, 0, 0,
    0,0, 0,   0,   0,   77,   42,   42,   42,   42,   42,   42,   42,    42,   42,     42,   79,   0, 0, 0, 0, 0,
    0,0, 0,   0,   0,   93,   94,   94,   94,   94,   94,   94,   94,    94,   94,     94,   95,   0, 0, 0, 0, 0,
    0,0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0, 0,
    0,0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0, 0,
    0,0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0, 0,
    0,0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0, 0
};


Mix_Music* overMusic;

void Level1::Initialize() {
    
    state.nextScene = -1;

    GLuint mapTextureID = Util::LoadTexture("TOPDOWN.png");
    GLuint bMapTextureID = Util::LoadTexture("TOPDOWN.png");
    GLuint itemTextureID = Util::LoadTexture("item8BIT_coin.png");
    state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 16, 30);
    state.bMap = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, bLevel1_data, bMapTextureID, 1.0f, 16, 30);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4896);
    overMusic = Mix_LoadMUS("overworld.mp3");
    Mix_PlayMusic(overMusic, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 22);


    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(5.1, -6.6, 0);
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


    state.enemies = new Entity[LEVEL1_ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("Castle(AllFrame).png");

    state.enemies[0].entityType = ENEMY;
    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(11, -8, 0);
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

    state.enemies[1].entityType = ENEMY;
    state.enemies[1].textureID = enemyTextureID;
    state.enemies[1].position = glm::vec3(9, -12, 0);
    state.enemies[1].speed = 1.0f;
    state.enemies[1].aiType = WAITANDGO;
    state.enemies[1].aiState = IDLE;
    state.enemies[1].acceleration = glm::vec3(0, 0, 0);
    state.enemies[1].animRight = new int[1]{ 5 };
    state.enemies[1].animIndices = state.enemies->animRight;
    state.enemies[1].animFrames = 1;
    state.enemies[1].animIndex = 0;
    state.enemies[1].animTime = 0;
    state.enemies[1].animCols = 4;
    state.enemies[1].animRows = 35;
    
    state.coin = new Entity[LEVEL1_COIN_COUNT];

    state.coin[0].entityType = COIN;
    state.coin[0].position = glm::vec3(7, -5, 0);
    state.coin[0].textureID = itemTextureID;

    
    state.coin[1].entityType = COIN;
    state.coin[1].position = glm::vec3(8, -9, 0);
    state.coin[1].textureID = itemTextureID;


    state.coin[2].entityType = COIN;
    state.coin[2].position = glm::vec3(11, -9, 0);
    state.coin[2].textureID = itemTextureID;

    state.coin[3].entityType = COIN;
    state.coin[3].position = glm::vec3(15, -8, 0);
    state.coin[3].textureID = itemTextureID;

    state.coin[4].entityType = COIN;
    state.coin[4].position = glm::vec3(15, -12, 0);
    state.coin[4].textureID = itemTextureID;


    state.coin[5].entityType = COIN;
    state.coin[5].position = glm::vec3(11, -12, 0);
    state.coin[5].textureID = itemTextureID;


    state.coin[6].entityType = COIN;
    state.coin[6].position = glm::vec3(7, -15, 0);
    state.coin[6].textureID = itemTextureID;
 


    state.door = new Entity[LEVEL1_DOOR_COUNT];
    state.door[0].entityType = DOOR;
    state.door[0].position = glm::vec3(7, -3, 0);
    state.door[0].textureID = mapTextureID;
    state.door[0].animRight = new int[1]{ 30 };
    state.door[0].animIndices = state.door->animRight;
    state.door[0].animFrames = 1;
    state.door[0].animIndex = 0;
    state.door[0].animTime = 0;
    state.door[0].animCols = 16;
    state.door[0].animRows = 30;

    state.door[1].entityType = DOOR;
    state.door[1].position = glm::vec3(13, -13, 0);
    state.door[1].textureID = mapTextureID;
    state.door[1].animRight = new int[1]{ 30 };
    state.door[1].animIndices = state.door->animRight;
    state.door[1].animFrames = 1;
    state.door[1].animIndex = 0;
    state.door[1].animTime = 0;
    state.door[1].animCols = 16;
    state.door[1].animRows = 30;
    state.door[1].isActive = false;

    state.door[2].entityType = DOOR;
    state.door[2].position = glm::vec3(14, -5, 0);
    state.door[2].textureID = mapTextureID;
    state.door[2].animRight = new int[1]{ 39 };
    state.door[2].animIndices = state.door->animRight;
    state.door[2].animFrames = 1;
    state.door[2].animIndex = 0;
    state.door[2].animTime = 0;
    state.door[2].animCols = 16;
    state.door[2].animRows = 30;
    state.door[2].isActive = false;

}



void Level1::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.coin, LEVEL1_COIN_COUNT, state.door, LEVEL1_DOOR_COUNT, state.map);

    
    for (int i = 0; i < LEVEL1_ENEMY_COUNT; i++) {
        state.enemies[i].Update(deltaTime, state.player, NULL, NULL, NULL, NULL,NULL, NULL, state.map);
    }
    
    for (int i = 0; i < LEVEL1_COIN_COUNT; i++) {
        state.coin[i].Update(deltaTime, state.player, NULL, NULL, NULL, NULL, NULL, NULL, state.map);
    }

    for (int i = 0; i < LEVEL1_DOOR_COUNT; i++) {
        state.door[i].Update(deltaTime, state.player, NULL, NULL, NULL, NULL, NULL, NULL, state.map);
    }

    if (state.player->coinCount > 9) {
        state.door[0].isActive = false;
        state.door[1].isActive = true;
    }
    if (state.player->winCond == 1 ) {
        state.door[1].isActive = false;
        state.door[2].isActive = true;
    }
    


    if (state.player->doorState < 9 && state.player->doorState > 0) {
        state.nextScene = 2;
        state.player->doorState = 0;
    } else if(state.player->doorState > 9 && state.player->winCond == 0){
        state.nextScene = 3;
        state.player->doorState = 0;
    }
    else if (state.player->doorState > 9 && state.player->winCond == 1) {
        state.nextScene = 4;
    }
    
    
  

}

    
void Level1::Render(ShaderProgram* program) {
    
    state.map->Render(program);
    state.bMap->Render(program);
    state.player->Render(program);


    for (int i = 0; i < LEVEL1_ENEMY_COUNT; i++) {
        state.enemies[i].Render(program);
    }
    
    for (int i = 0; i < LEVEL1_COIN_COUNT; i++) {
        state.coin[i].Render(program);
    }
    
    for (int i = 0; i < LEVEL1_DOOR_COUNT; i++) {
        state.door[i].Render(program);
    }

}