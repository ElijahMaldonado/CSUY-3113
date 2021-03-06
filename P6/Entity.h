#pragma once
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
#include <vector>
#include "Map.h"

enum EntityType {PLAYER, PLATFORM, ENEMY, COIN, DOOR};

enum AITYPE { WALKER, WAITANDGO, STROLLER };
enum AIState { IDLE, WALKING, ATTACKING };

class Entity {
public:
    EntityType entityType;
    AITYPE aiType;
    AIState aiState;

    glm::vec3 position;
    glm::vec3 movement;
    glm::vec3 acceleration;
    glm::vec3 velocity;

    float width = 1;
    float height = 1;
    int winCond = 0;
    int lives = 3;
    int coinCount = 0;
    int doorState = 0;

    bool jump = false;
    float jumpPower = 1;
    bool fail = false;
    bool win = false;
    bool soundCheck = false;

    float speed;

    GLuint textureID;

    glm::mat4 modelMatrix;

    int* animRight = NULL;
    int* animLeft = NULL;
    int* animUp = NULL;
    int* animDown = NULL;

    int* animIndices = NULL;
    int animFrames = 0;
    int animIndex = 0;
    float animTime = 0;
    int animCols = 0;
    int animRows = 0;

    bool isActive = true;

    bool collidedTop = false;
    bool collidedBottom = false;
    bool collidedLeft = false;
    bool collidedRight = false;
    bool collided = false;

    bool collidedWithEnemyTop = false;
    bool collidedWithEnemyBottom = false;
    bool collidedWithEnemyLeft = false;
    bool collidedWithEnemyRight = false;


    Entity();


    bool CheckCollision(Entity *other);
    void CheckCollisionsX(Entity *objects, int objectCount);
    void CheckCollisionsY(Entity *objects, int objectCount);
    void CheckCollisionsX(Map* map);
    void CheckCollisionsY(Map* map);

    void Update(float deltaTime, Entity *player, Entity* objects, int objectCount, Entity* sObjects, int sObjectCount, Entity* tObjects, int tObjectCount, Map *map);
    void Render(ShaderProgram* program);
    void DrawSpriteFromTextureAtlas(ShaderProgram* program, GLuint textureID, int index);

    void AI(Entity *player);
    void AIWalker(Entity *player);
    void AIWaitAndGo(Entity *player);
    void AIStroller(Entity* player);
};