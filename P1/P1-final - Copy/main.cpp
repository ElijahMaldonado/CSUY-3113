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

SDL_Window* displayWindow;
bool gameIsRunning = true;

ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix, fishMatrix, fishMatrixTwo;

float player_x = -10;
float player_rotate = 0;

float fish_x = -10;

float fishTwo_x = -10;

GLuint playerTextureID;
GLuint fishTextureID;
GLuint fishTwoTextureID;

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
    displayWindow = SDL_CreateWindow("Textured!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);

#ifdef _WINDOWS
    glewInit();
#endif

    glViewport(0, 0, 640, 480);

    program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");

    viewMatrix = glm::mat4(1.0f);
    modelMatrix = glm::mat4(1.0f);
    fishMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(-10.0f, 10.0f, -7.5f, 7.5f, -2.0f, 2.0f);

    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);
    //program.SetColor(1.0f, 1.0f, 0.0f, 1.0f);

    glUseProgram(program.programID);

    //background color
    glClearColor(0.13f, 0.0f, 0.5f, 1.0f); 
    glEnable(GL_BLEND);
    
    // Good setting for transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    playerTextureID = LoadTexture("ctg.png");
    fishTextureID = LoadTexture("fishies.png");

}

float lastTicks = 0.0f;

void ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) {
            gameIsRunning = false;
        }
    }
}

void Update() {
    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float deltaTime = ticks - lastTicks;
    lastTicks = ticks;

    
    player_x += 1.0f * deltaTime;
    player_rotate += -90.0f * deltaTime;
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(player_x, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(player_rotate), glm::vec3(0.0f, 1.00f, 1.0f)); 

    fish_x += 2.0f * deltaTime;
    fishMatrix = glm::mat4(1.0f);
    fishMatrix = glm::translate(fishMatrix, glm::vec3(-fish_x, -3.0f, 0.7f));
    fishMatrix = glm::scale(fishMatrix, glm::vec3(2.0f, 2.0f, 2.0f));
    //fishMatrix = glm::rotate(fishMatrix, glm::radians(player_rotate), glm::vec3(0.0f, 1.00f, 1.0f));

    fishTwo_x += 1.0f * deltaTime;
    fishMatrixTwo = glm::mat4(1.0f);
    fishMatrixTwo = glm::translate(fishMatrixTwo, glm::vec3(-fishTwo_x, 3.0f, 0.7f));
    fishMatrixTwo = glm::scale(fishMatrixTwo, glm::vec3(2.0f, 2.0f, 2.0f));

    //modelMatrix = glm::rotate(modelMatrix, glm::radians(45.0f), glm::vec3(0.0f, 0.00f, 1.0f));
    //modelMatrix = glm::scale(modelMatrix, glm::vec3(1.01f, 1.01f, 1.0f));

}

void Render() { 
    float vertices[] = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };

    glClear(GL_COLOR_BUFFER_BIT);    
      
    glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, vertices); 
    glEnableVertexAttribArray(program.positionAttribute); 
    
    glVertexAttribPointer(program.texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords); 
    glEnableVertexAttribArray(program.texCoordAttribute); 
   
    program.SetModelMatrix(modelMatrix);
    glBindTexture(GL_TEXTURE_2D, playerTextureID); 
    glDrawArrays(GL_TRIANGLES, 0 , 6);    


    program.SetModelMatrix(fishMatrix);
    glBindTexture(GL_TEXTURE_2D, fishTextureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    program.SetModelMatrix(fishMatrixTwo);
    glBindTexture(GL_TEXTURE_2D, fishTextureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);


    
    glDisableVertexAttribArray(program.positionAttribute);    
    glDisableVertexAttribArray(program.texCoordAttribute); 
    
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
