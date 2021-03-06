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

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Entity.h"

#define PLATFORM_COUNT 62
#define ENEMY_COUNT 3

struct GameState {
    Entity *player;
    Entity *platform;
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

GLuint LoadTexture(const char* filePath) {
    int w, h, n;
    unsigned char* image = stbi_load(filePath, &w, &h, &n, STBI_rgb_alpha);

    if (image == NULL) {
        std::cout << "Unable to load image. Make sure the path is correct\n";
        assert(false);
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_image_free(image);
    return textureID;
}


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
    projectionMatrix = glm::ortho(-10.0f, 10.0f, -7.5f, 7.5f, -2.0f, 2.0f);

    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);

    glUseProgram(program.programID);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    // Initialize Game Objects

    // Initialize Player
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(-8,-3,0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0, -10.0f, 0);
    state.player->speed = 2.0f;
    state.player->textureID = LoadTexture("character_femaleAdventurer_sheet.png");
    
    
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

    state.platform = new Entity[PLATFORM_COUNT];
    
    GLuint platformTextureID = LoadTexture("dirt.png");

    for (int i = 0; i < 20; i++) {
        state.platform[i].entityType = PLATFORM;
        state.platform[i].textureID = platformTextureID;
        state.platform[i].position = glm::vec3(-10+i, -3.25, 0);
    }

    for (int i = 0; i < 19; i++) {
        state.platform[i+20].entityType = PLATFORM;
        state.platform[i+20].textureID = platformTextureID;
        state.platform[i+20].position = glm::vec3(-10, -7.5 + i, 0);
    }

    for (int i = 0; i < 19; i++) {
        state.platform[i + 36].entityType = PLATFORM;
        state.platform[i + 36].textureID = platformTextureID;
        state.platform[i + 36].position = glm::vec3(10, -7.5 + i, 0);
    }

    state.platform[54].textureID = platformTextureID;
    state.platform[54].position = glm::vec3(-9, -0.25, 0);

    state.platform[55].textureID = platformTextureID;
    state.platform[55].position = glm::vec3(-1, -2.25, 0);

    state.platform[56].textureID = platformTextureID;
    state.platform[56].position = glm::vec3(-3, -0.25, 0);

    state.platform[57].textureID = platformTextureID;
    state.platform[57].position = glm::vec3(-8, -0.25, 0);

    state.platform[58].textureID = platformTextureID;
    state.platform[58].position = glm::vec3(-7, -0.25, 0);

    state.platform[59].textureID = platformTextureID;
    state.platform[59].position = glm::vec3(-6, -0.25, 0);

    state.platform[60].textureID = platformTextureID;
    state.platform[60].position = glm::vec3(-5, -0.25, 0);

    state.platform[61].textureID = platformTextureID;
    state.platform[61].position = glm::vec3(-5, 0.75, 0);


    
    for (int i = 0; i < PLATFORM_COUNT; i++) {
        state.platform[i].Update(0, NULL ,NULL, 0, NULL, NULL);
    }


    fontTextureID = LoadTexture("font1.png");

    
    state.enemies = new Entity[ENEMY_COUNT];
    GLuint enemyTextureID = LoadTexture("alienenemy.png");

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



void DrawText(ShaderProgram *program, GLuint fontTextureID, std::string text, float size, float spacing, glm::vec3 position) {

    float width = 1.0f / 16.0f;
    float height = 1.0f / 16.0f;

    std::vector<float> vertices;
    std::vector<float> texCoords;

    for (int i = 0; i < text.size(); i++) {

        int index = (int)text[i];
        float offset = (size + spacing) * i;

        float u = (float)(index % 16) / 16.0f;
        float v = (float)(index / 16) / 16.0f;

        vertices.insert(vertices.end(), {
            offset + (-0.5f * size), 0.5f * size,
            offset + (-0.5f * size), -0.5f * size,
            offset + (0.5f * size), 0.5f * size,
            offset + (0.5f * size), -0.5f * size,
            offset + (0.5f * size), 0.5f * size,
            offset + (-0.5f * size), -0.5f * size,
        });

        texCoords.insert(texCoords.end(), { u, v,
            u, v + height,
            u + width, v,
            u + width, v + height,
            u + width, v,
            u, v + height,
        });
    } // end of for loop

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    program->SetModelMatrix(modelMatrix);

    glUseProgram(program->programID);
    glBindTexture(GL_TEXTURE_2D, fontTextureID);

    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices.data());
    glEnableVertexAttribArray(program->positionAttribute);

    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords.data());
    glEnableVertexAttribArray(program->texCoordAttribute);

    
    glDrawArrays(GL_TRIANGLES, 0, (int)(text.size() * 6));

    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
}


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

        state.player->Update(FIXED_TIMESTEP, state.player, state.platform, PLATFORM_COUNT, state.enemies, ENEMY_COUNT);


        for (int i = 0; i < ENEMY_COUNT; i++) {
            state.enemies[i].Update(FIXED_TIMESTEP,state.player, state.platform, PLATFORM_COUNT, NULL, NULL);
        }

        deltaTime -= FIXED_TIMESTEP;    
    }


    accumulator = deltaTime;
}


void Render() {

    glClear(GL_COLOR_BUFFER_BIT);


    for (int i = 0; i < PLATFORM_COUNT; i++) {
        state.platform[i].Render(&program);
    }

    for (int i = 0; i < ENEMY_COUNT; i++) {
        state.enemies[i].Render(&program);
    }

    if (state.player->fail) {
        DrawText(&program, fontTextureID, "FAIL!", 1, -0.5f, glm::vec3(0, 0, 0));
    }

    if (state.player->win) {
        DrawText(&program, fontTextureID, "WIN!", 1, -0.5f, glm::vec3(0, 0, 0));
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