#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Entity.h"

#define PLATFORM_COUNT 36

struct GameState {
    Entity *player;
    Entity *platform;
};

GameState state;

SDL_Window* displayWindow;
bool gameIsRunning = true;

ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix;

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
    SDL_Init(SDL_INIT_VIDEO);
    displayWindow = SDL_CreateWindow("LunarLander!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);

#ifdef _WINDOWS
    glewInit();
#endif

    glViewport(0, 0, 640, 480);

    program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");

    viewMatrix = glm::mat4(1.0f);
    modelMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);

    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);

    glUseProgram(program.programID);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    // Initialize Game Objects

    // Initialize Player
    state.player = new Entity();
    state.player->position = glm::vec3(0,3.75,0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0, 0, 0);
    state.player->speed = 0.2f;
    state.player->textureID = LoadTexture("playerShip1_blue.png");
    
    /*
    state.player->animRight = new int[4]{ 3, 7, 11, 15 };
    state.player->animLeft = new int[4]{ 1, 5, 9, 13 };
    state.player->animUp = new int[4]{ 2, 6, 10, 14 };
    state.player->animDown = new int[4]{ 0, 4, 8, 12 };

    state.player->animIndices = state.player->animRight;
    state.player->animFrames = 4;
    state.player->animIndex = 0;
    state.player->animTime = 0;
    state.player->animCols = 4;
    state.player->animRows = 4;
    */

    state.player->height = 0.8f;
    state.player->width = 0.7f;

    state.player->jumpPower = 4.0f;

    state.platform = new Entity[PLATFORM_COUNT];
    
    GLuint platformTextureID = LoadTexture("platformPack_tile016.png");
    GLuint winPlatformTextureID = LoadTexture("platformPack_tile013.png");

    state.platform[0].textureID = platformTextureID;
    state.platform[0].position = glm::vec3(-1, -3.25, 0);

    state.platform[1].textureID = platformTextureID;
    state.platform[1].position = glm::vec3(0, -3.25, 0);

    state.platform[2].textureID = platformTextureID;
    state.platform[2].position = glm::vec3(1, -3.25, 0);

    state.platform[3].textureID = platformTextureID;
    state.platform[3].position = glm::vec3(-2, -3.25, 0);

    state.platform[4].textureID = platformTextureID;
    state.platform[4].position = glm::vec3(-3, -3.25, 0);

    state.platform[5].textureID = platformTextureID;
    state.platform[5].position = glm::vec3(-4, -3.25, 0);

    state.platform[6].textureID = platformTextureID;
    state.platform[6].position = glm::vec3(4, -3.25, 0);

    state.platform[7].textureID = platformTextureID;
    state.platform[7].position = glm::vec3(5, -3.25, 0);

    state.platform[8].textureID = platformTextureID;
    state.platform[8].position = glm::vec3(-5, -3.25, 0);

    state.platform[9].textureID = platformTextureID;
    state.platform[9].position = glm::vec3(-5, -2.25, 0);

    state.platform[10].textureID = platformTextureID;
    state.platform[10].position = glm::vec3(-5, -1.25, 0);

    state.platform[11].textureID = platformTextureID;
    state.platform[11].position = glm::vec3(-5, -.25, 0);

    state.platform[12].textureID = platformTextureID;
    state.platform[12].position = glm::vec3(-5, .75, 0);

    state.platform[13].textureID = platformTextureID;
    state.platform[13].position = glm::vec3(-5, 1.75, 0);

    state.platform[14].textureID = platformTextureID;
    state.platform[14].position = glm::vec3(-5, 2.75, 0);

    state.platform[15].textureID = platformTextureID;
    state.platform[15].position = glm::vec3(-5, 3.75, 0);

    state.platform[16].textureID = platformTextureID;
    state.platform[16].position = glm::vec3(5, -2.25, 0);

    state.platform[17].textureID = platformTextureID;
    state.platform[17].position = glm::vec3(5, -1.25, 0);

    state.platform[18].textureID = platformTextureID;
    state.platform[18].position = glm::vec3(5, -.25, 0);

    state.platform[19].textureID = platformTextureID;
    state.platform[19].position = glm::vec3(5, .75, 0);

    state.platform[20].textureID = platformTextureID;
    state.platform[20].position = glm::vec3(5, 1.75, 0);

    state.platform[21].textureID = platformTextureID;
    state.platform[21].position = glm::vec3(5, 2.75, 0);

    state.platform[22].textureID = platformTextureID;
    state.platform[22].position = glm::vec3(5, 3.75, 0);

    state.platform[23].textureID = platformTextureID;
    state.platform[23].position = glm::vec3(-4, -1.25, 0);

    state.platform[24].textureID = platformTextureID;
    state.platform[24].position = glm::vec3(-3, -1.25, 0);

    state.platform[25].textureID = platformTextureID;
    state.platform[25].position = glm::vec3(-2, -1.25, 0);

    state.platform[26].textureID = platformTextureID;
    state.platform[26].position = glm::vec3(-1, -1.25, 0);

    state.platform[27].textureID = platformTextureID;
    state.platform[27].position = glm::vec3(-1, 1.75, 0);

    state.platform[28].textureID = platformTextureID;
    state.platform[28].position = glm::vec3(2, 1.75, 0);

    state.platform[29].textureID = platformTextureID;
    state.platform[29].position = glm::vec3(1, 1.75, 0);

    state.platform[30].textureID = platformTextureID;
    state.platform[30].position = glm::vec3(0, 1.75, 0);

    state.platform[31].textureID = platformTextureID;
    state.platform[31].position = glm::vec3(-5, -3.25, 0);

    state.platform[32].textureID = platformTextureID;
    state.platform[32].position = glm::vec3(4, -1.25, 0);

    state.platform[33].textureID = platformTextureID;
    state.platform[33].position = glm::vec3(4, -3.25, 0);

    state.platform[34].textureID = winPlatformTextureID;
    state.platform[34].position = glm::vec3(2, -3.25, 0);

    state.platform[35].textureID = winPlatformTextureID;
    state.platform[35].position = glm::vec3(3, -3.25, 0);


    for (int i = 0; i < PLATFORM_COUNT; i++) {
        state.platform[i].Update(0, NULL, 0);
    }


    GLuint fontTextureID = LoadTexture("font1.png");


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
                state.player->acceleration = glm::vec3(state.player->acceleration.x, -0.5f, 0);

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

GLuint fontTextureID = LoadTexture("font1.png");

GLuint dafont = fontTextureID;

void DrawText(ShaderProgram *program, GLuint dafont, std::string text, float size, float spacing, glm::vec3 position) {

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
    glBindTexture(GL_TEXTURE_2D, dafont);

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
    
    if (state.player->collidedLeft  || state.player->collidedRight 
        || state.player->collidedTop  || state.player->collidedBottom ) {
        state.player->position = glm::vec3(state.player->position.x, state.player->position.y,0);

        if (state.platform[34].collided || state.platform[35].collided) {
            state.player->win;
        }
        else {
            state.player->fail;
        }
    }



    while (deltaTime >= FIXED_TIMESTEP) {        
        // Update. Notice it's FIXED_TIMESTEP. Not deltaTime

        state.player->Update(FIXED_TIMESTEP, state.platform, PLATFORM_COUNT);

        deltaTime -= FIXED_TIMESTEP;    
    }



    accumulator = deltaTime;
}


void Render() {

    glClear(GL_COLOR_BUFFER_BIT);


    for (int i = 0; i < PLATFORM_COUNT; i++) {
        state.platform[i].Render(&program);
    }

    if (state.player->fail) {
        DrawText(&program, fontTextureID, "FAIL!", 1, -0.5f, glm::vec3(0, 0, 0));
    }

    if (state.player->win) {
        DrawText(&program, fontTextureID, "FAIL!", 1, -0.5f, glm::vec3(0, 0, 0));
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