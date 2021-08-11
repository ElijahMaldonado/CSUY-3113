#include "Menu.h"
#include <SDL_mixer.h>
#include <SDL.h>



#define MENU_WIDTH 20
#define MENU_HEIGHT 20

unsigned int menu_data[] =
{
    64, 64,   64,   64,   64,   64,   64,   64,   64,   64,   64,  64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,  64,   64,   64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,   64,   64,   64,   64,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
    64, 64,   64,   64,   64,   64,   64,   64,    0,   64,   64,   64,    64,   64,     64,   64,   64, 64, 64, 64,
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

unsigned int bMenu_data[] =
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

Mix_Music* finMusic;

void Menu::Initialize() {

    state.nextScene = -1;

    GLuint mapTextureID = Util::LoadTexture("TOPDOWN.png");
    GLuint bMapTextureID = Util::LoadTexture("TOPDOWN.png");
    GLuint itemTextureID = Util::LoadTexture("item8BIT_coin.png");


    state.map = new Map(MENU_WIDTH, MENU_HEIGHT, menu_data, mapTextureID, 1.0f, 16, 30);
    state.bMap = new Map(MENU_WIDTH, MENU_HEIGHT, bMenu_data, bMapTextureID, 1.0f, 16, 30);


    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4896);
    finMusic = Mix_LoadMUS("endSmiley.mp3");
    Mix_PlayMusic(finMusic, -1);
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


void Menu::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, NULL, NULL, state.coin, NULL,NULL,NULL, state.map);

}


void Menu::Render(ShaderProgram* program) {

    state.map->Render(program);
    state.bMap->Render(program);
    state.player->Render(program);


}