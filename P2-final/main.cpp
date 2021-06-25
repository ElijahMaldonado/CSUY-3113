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
glm::mat4 viewMatrix, leftMatrix, projectionMatrix, rightMatrix, ballMatrix;

// Start at 0, 0, 0
glm::vec3 playerOne_position = glm::vec3(-5, 0, 0);
glm::vec3 playerTwo_position = glm::vec3(5, 0, 0);
glm::vec3 ball_position = glm::vec3(0, 0, 0);

// Don’t go anywhere (yet).
glm::vec3 playerOne_movement = glm::vec3(0, 0, 0);
glm::vec3 playerTwo_movement = glm::vec3(0, 0, 0);
glm::vec3 ball_movement = glm::vec3(0, 0, 0);

float player_speed = 1.0f;
float ball_speed = 1.0f;


bool collisionCheck() {

    float xdist = fabs(playerOne_position.x - ball_position.x) - ((.05 + .15) / 2.0f);
    float ydist = fabs(playerOne_position.y - ball_position.y) - ((.1 + .15) / 2.0f);
    float xTwodist = fabs(playerTwo_position.x - ball_position.x) - ((.05 + .15) / 2.0f);
    float yTwodist = fabs(playerTwo_position.y - ball_position.y) - ((.1 + .15) / 2.0f);
  
    if (xdist < 0 && ydist < 0 || xTwodist < 0 && yTwodist < 0) {
        return true;
    }
}

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
    displayWindow = SDL_CreateWindow("PONG!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);

#ifdef _WINDOWS
    glewInit();
#endif

    glViewport(0, 0, 640, 480);

    program.Load("shaders/vertex.glsl", "shaders/fragment.glsl");
    
    viewMatrix = glm::mat4(1.0f);
    leftMatrix = glm::mat4(1.0f);
    rightMatrix = glm::mat4(1.0f);
    ballMatrix = glm::mat4(1.0f);
    
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);

    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);
    program.SetColor(1.0f, 1.0f, 0.0f, 1.0f);

    glUseProgram(program.programID);

    //background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
    glEnable(GL_BLEND);
    
    // Good setting for transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

float lastTicks = 0.0f;

void ProcessInput() {
    
    //without this the player will keep moving in a direction until another key is pressed
    playerOne_movement = glm::vec3(0);
    playerTwo_movement = glm::vec3(0);
    

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
                        ball_movement = glm::vec3(3, 3, 0);
                        break;                           
                }                
                break; // SDL_KEYDOWN        
        }    
    }
    
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    
    if (keys[SDL_SCANCODE_A]) { 
        //playerOne_movement.x = -1.0f;
    }
    
    else if (keys[SDL_SCANCODE_D]) { 
        //playerOne_movement.x = 1.0f;
    }

    if (keys[SDL_SCANCODE_W]) {
            playerOne_movement.y = 4.0f;
    }

    else if (keys[SDL_SCANCODE_S]) {
        playerOne_movement.y = -4.0f;
    }
    
    //diagonal
    if (glm::length(playerOne_movement) > 1.0f) { 
        //player_movement = glm::normalize(player_movement); 
    }

    if (keys[SDL_SCANCODE_LEFT]) {
        //playerOne_movement.x = -1.0f;
    }

    else if (keys[SDL_SCANCODE_RIGHT]) {
        //playerOne_movement.x = 1.0f;
    }

    if (keys[SDL_SCANCODE_UP]) {
        playerTwo_movement.y = 4.0f;
    }

    else if (keys[SDL_SCANCODE_DOWN]) {
        playerTwo_movement.y = -4.0f;
    }

    //diagonal
    if (glm::length(playerTwo_movement) > 1.0f) {
        //player_movement = glm::normalize(player_movement); 
    }

}

void Update() {

    float ticks = (float)SDL_GetTicks() / 1000.0f;
    float deltaTime = ticks - lastTicks;
    lastTicks = ticks;
    rightMatrix = glm::mat4(1.0f);


    // Add (direction * units per second * elapsed time)
    leftMatrix = glm::mat4(1.0f);
    rightMatrix = glm::mat4(1.0f);
    ballMatrix = glm::mat4(1.0f);

    playerOne_position += playerOne_movement * player_speed * deltaTime;
    playerTwo_position += playerTwo_movement * player_speed * deltaTime;
    ball_position += ball_movement * ball_speed * deltaTime;

    leftMatrix = glm::translate(leftMatrix, playerOne_position);
    rightMatrix = glm::translate(rightMatrix, playerTwo_position);
    ballMatrix = glm::translate(ballMatrix, ball_position);


    if (playerOne_position.y >= 3) {
        playerOne_position = glm::vec3(-5, 3, 0);
    } else if (playerOne_position.y <= -3) {
        playerOne_position = glm::vec3(-5, -3, 0);
    }

    if (playerTwo_position.y >= 3) {
        playerTwo_position = glm::vec3(5, 3, 0);
    }
    else if (playerTwo_position.y <= -3) {
        playerTwo_position = glm::vec3(5, -3, 0);
    }

    if(ball_position.y >= 3.75 || ball_position.y <= -3.75) {
        ball_movement.y = -ball_movement.y;  
    }
    
    if (ball_position.x >= 5 || ball_position.x <= -5) {
        ball_movement.x = -ball_movement.x;
    }
    
    if (collisionCheck()) {
        ball_movement.x = -ball_movement.x;
        ball_movement.y = -ball_movement.y;
    }
    if (collisionCheck) {
        ball_movement.x = -ball_movement.x;
        ball_movement.y = -ball_movement.y;
    }
}

void Render() {
    
    float paddleVertices[] = {-0.25, -0.75, 0.25, -0.75, 0.25, 0.75, -0.25, -0.75, 0.25, 0.75, -0.25, 0.75};
    float ballVertices[] = { -0.125, -0.125, 0.125, -0.125, 0.125, 0.125, -0.125, -0.125, 0.125, 0.125, -0.125, 0.125 };
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    program.SetModelMatrix(leftMatrix);
    glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, paddleVertices);
    glEnableVertexAttribArray(program.positionAttribute);      
    glDrawArrays(GL_TRIANGLES, 0, 6);
    

    program.SetModelMatrix(rightMatrix);
    glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, paddleVertices);
    glEnableVertexAttribArray(program.positionAttribute);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    program.SetModelMatrix(ballMatrix);
    glVertexAttribPointer(program.positionAttribute, 2, GL_FLOAT, false, 0, ballVertices);
    glEnableVertexAttribArray(program.positionAttribute);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(program.positionAttribute);
    
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
