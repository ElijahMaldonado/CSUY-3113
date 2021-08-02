#include "menu.h"


#define MENU_WIDTH 14
#define MENU_HEIGHT 8

GLuint f2ontTextureID;

unsigned int menu_data[] =
{
    29, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    29, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    29, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    29, 0,    0,    0,   0,   0,   0,   0,   0,   0,   0,   0,      0,   0,
    29, 0,     0,   0,   0,   0,   0,   0,   0,   0,   0,   0,      0,   0,
    29, 0,     0,   0,   0,   0,   0,   0,   0,   1, 2,  2,   2 ,    3,
    29, 1,   2,  2,  2,  2,  2,  2,  2,  3,  4,  4,  4,  4,
    29, 4, 4, 4, 4, 4, 4, 4,4,  4, 4, 4,  4,  4
};

void Menu::Initialize() {

    state.nextScene = -1;
    
    GLuint mapTextureID = Util::LoadTexture("industrial_tilesheet.png");
    state.map = new Map(MENU_WIDTH, MENU_HEIGHT, menu_data, mapTextureID, 1.0f, 14, 8);

    // Move over all of the player and enemy code from initialization.

    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(5, 3, 0);
    state.player->speed = 0.0f;
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

    f2ontTextureID = Util::LoadTexture("font2.png");

}


void Menu::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, NULL, state.map);


    if (state.player->position.x >= 12) {
        state.nextScene = 1;
    }
}


void Menu::Render(ShaderProgram* program) {

    state.map->Render(program);
    state.player->Render(program);

    Util::DrawText(program, f2ontTextureID, "Press Enter to begin!", .75, -0.5f, glm::vec3(2, -4, 0));

}