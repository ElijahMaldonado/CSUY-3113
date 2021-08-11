#include "Level5.h"
#include <SDL_mixer.h>
#include <SDL.h>



#define LEVEL5_WIDTH 20
#define LEVEL5_HEIGHT 20

unsigned int level5_data[] =
{
    64, 64,   64,   64,   64,   64,   64,   64,   64,   64,   64,  64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,  64,   64,   64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   61,   62,   63,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   77,   30,   79,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   93,   94,   95,   64,   64,   64,    0,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,   64,   64,  64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
};

unsigned int bLevel5_data[] =
{
    0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,   0,  0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,   0,   0,   0,   203,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0,
    0, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,     0,   0,   0, 0, 0, 0
};

Mix_Music* finalfinMusic;

void Level5::Initialize() {

    state.nextScene = -1;

    GLuint mapTextureID = Util::LoadTexture("TOPDOWN.png");
    GLuint bMapTextureID = Util::LoadTexture("TOPDOWN.png");
    GLuint itemTextureID = Util::LoadTexture("item8BIT_coin.png");


    state.map = new Map(LEVEL5_WIDTH, LEVEL5_HEIGHT, level5_data, mapTextureID, 1.0f, 16, 30);
    state.bMap = new Map(LEVEL5_WIDTH, LEVEL5_HEIGHT, bLevel5_data, bMapTextureID, 1.0f, 16, 30);


    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4896);
    finalfinMusic = Mix_LoadMUS("endSmiley.mp3");
    Mix_PlayMusic(finalfinMusic, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 22);

    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(8.11, -9.741, 0);
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

}


void Level5::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, NULL, NULL, state.coin, NULL, NULL, NULL, state.map);

    state.player->win = true;
}


void Level5::Render(ShaderProgram* program) {

    state.map->Render(program);
    state.bMap->Render(program);
    state.player->Render(program);


}