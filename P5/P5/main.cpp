#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1

#include <SDL_mixer.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"


#include "Util.h"
#include "Entity.h"
#include "Map.h"
#define ENEMY_COUNT 3

 
#define LEVEL1_WIDTH 14
#define LEVEL1_HEIGHT 5

unsigned int level1_data[] =
{
    0,     0,   0,   0, 0, 0,   0,   0,   0,   0,   0,   0,   0,   0, 
    0,     0,   0,   0, 0, 0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,     0,   0,   0, 0, 0,   0,   0,   0,  21,  22,  22,  22,  23,
    21,   22,  22,  23, 0, 0,  21,  22,  22,  25, 122, 122, 122, 123,
    121, 122, 122, 123, 33, 33, 121, 122, 122, 122, 122, 122, 122, 122
};

struct GameState {
    Map *map;
    Entity *player;
    Entity *enemies;
};

GameState state;

SDL_Window* displayWindow;
bool gameIsRunning = true;

ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix;

GLuint fontTextureID;

Mix_Music *music;
Mix_Chunk *bounce;

int winCondition = ENEMY_COUNT;


void Initialize() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    displayWindow = SDL_CreateWindow("AI!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);

#ifdef _WINDOWS
    glewInit();
#endif

    glViewport(0, 0, 640, 480);

    program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4896);
    music = Mix_LoadMUS("Siren1Loop.mp3");
    Mix_PlayMusic(music, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 8);

    bounce = Mix_LoadWAV("converted_OldSchool1.wav");
    Mix_VolumeChunk(bounce, MIX_MAX_VOLUME / 10 );

    viewMatrix = glm::mat4(1.0f);
    modelMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);

    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);

    glUseProgram(program.programID);

    glClearColor(.62f, .81f, .92f, 1.0f);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    // Initialize Game Objects

    // Initialize Player
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(0,0,0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0, -10.0f, 0);
    state.player->speed = 2.0f;
    state.player->textureID = Util::LoadTexture("character_femaleAdventurer_sheet.png");
    
    
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
  

    fontTextureID = Util::LoadTexture("font1.png");

    
    state.enemies = new Entity[ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("alienenemy.png");

    state.enemies[0].entityType = ENEMY;

    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(4, -2.25, 0);

    state.enemies[0].aiType = WAITANDGO;
    state.enemies[0].aiState = IDLE;

    state.enemies[0].speed = 1.0f;
    state.enemies[0].acceleration = glm::vec3(0, -9.81, 0);

    state.enemies[1].entityType = ENEMY;

    state.enemies[1].textureID = enemyTextureID;
    state.enemies[1].position = glm::vec3(-6, 2.25, 0);

    state.enemies[1].aiType = STROLLER;
    state.enemies[1].aiState = WALKING;

    state.enemies[1].speed = 1.0f;
    state.enemies[1].acceleration = glm::vec3(0, -9.81, 0);

    state.enemies[2].entityType = ENEMY;

    state.enemies[2].textureID = enemyTextureID;
    state.enemies[2].position = glm::vec3(0, -2.25, 0);

    state.enemies[2].aiType = WALKER;
    state.enemies[2].aiState = IDLE;

    state.enemies[2].speed = 1.0f;
    state.enemies[2].acceleration = glm::vec3(0, -9.81, 0);

    GLuint mapTextureID = Util::LoadTexture("tiles_packed.png");
    state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 20, 9);
    

    

}

void ProcessInput() {

    state.player->movement = glm::vec3(0);

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
        case SDL_WINDOWEVENT_CLOSE:
            gameIsRunning = false;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                // Move the player left
                break;

            case SDLK_RIGHT:
                // Move the player right
                break;

            case SDLK_SPACE:
                if (state.player->collidedBottom) {
                    state.player->jump = true;
                }
                break;
            }
            break; // SDL_KEYDOWN
        }
    }

    const Uint8* keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_LEFT]) {
        state.player->movement.x = -1.0f;
        state.player->animIndices = state.player->animLeft;
    }
    else if (keys[SDL_SCANCODE_RIGHT]) {
        state.player->movement.x = 1.0f;
        state.player->animIndices = state.player->animRight;
    }


    if (glm::length(state.player->movement) > 1.0f) {
        state.player->movement = glm::normalize(state.player->movement);
    }

}

#define FIXED_TIMESTEP 0.0166666f

float lastTicks = 0;
float accumulator = 0.0f;


void Update() {    
    float ticks = (float)SDL_GetTicks() / 1000.0f;    
    float deltaTime = ticks - lastTicks;    
    lastTicks = ticks;

    deltaTime += accumulator;  

    
    
    if (deltaTime < FIXED_TIMESTEP) {
        accumulator = deltaTime;        
        return;    
    }    


    if (state.player->collidedWithEnemyBottom && state.enemies->collidedTop) {
       Mix_PlayChannel(-1, bounce, 0);
    }

    if (state.player->winCond == 0) {
        state.player->win;
    }




    while (deltaTime >= FIXED_TIMESTEP) {        
        // Update. Notice it's FIXED_TIMESTEP. Not deltaTime

        state.player->Update(FIXED_TIMESTEP, state.player, state.enemies, ENEMY_COUNT, state.map); //broken

        /*
        for (int i = 0; i < ENEMY_COUNT; i++) {
            state.enemies[i].Update(FIXED_TIMESTEP,state.player, state.platform, PLATFORM_COUNT, NULL, NULL);
        }
        */

        deltaTime -= FIXED_TIMESTEP;    
    }

    accumulator = deltaTime;

    viewMatrix = glm::mat4(1.0f);
    viewMatrix = glm::translate(viewMatrix,glm::vec3(-state.player->position.x, 0, 0)); 
}


void Render() {

    glClear(GL_COLOR_BUFFER_BIT);

    program.SetViewMatrix(viewMatrix);

    state.map->Render(&program);

    /*
    for (int i = 0; i < ENEMY_COUNT; i++) {
        state.enemies[i].Render(&program);
    }
    */


    if (state.player->fail) {
        Util::DrawText(&program, fontTextureID, "FAIL!", 1, -0.5f, glm::vec3(0, 0, 0));
    }

    if (state.player->win) {
        Util::DrawText(&program, fontTextureID, "WIN!", 1, -0.5f, glm::vec3(0, 0, 0));
    }


    state.player->Render(&program);

    SDL_GL_SwapWindow(displayWindow);
}


void Shutdown() {
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    Initialize();

    while (gameIsRunning) {
        ProcessInput();
        Update();
        Render();
    }

    Shutdown();
    return 0;
}