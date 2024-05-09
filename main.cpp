#include "src/core.h"

#define LITERAL_TO_STRING(x) #x

enum PlayerEvents {
    PLAYER_MOVE_FORWARD = 0,
    PLAYER_MOVE_BACKWARD,
    PLAYER_MOVE_LEFT,
    PLAYER_MOVE_RIGHT,
    PLAYER_JUMP,
    PLAYER_ATTACK
};

class Player : public Core::AbstractEntity {
private:
    Model model;
    ModelAnimation* anims;

    i32 animsCount;
    i32 currentFrame;
    i32 currentAnimation;
    bool n;

    f32 speed = 0.01;
    Core::Scene* scene;

public:
    Player(Core::Scene* scene, vec3 pos, bool n) : n{n} {
        this->scene = scene;
        // NOTE : Gowrish - For some reason `this` becomes NULL
        scene->addEntity(this);

        t.pos = pos;
        t.rot = vec3(0, 0, 0);
        t.scale = vec3(0, 0, 0);

        currentFrame = 0;
        currentAnimation = 0;

        this->init();
    }

    void init() {
        model = LoadModel("../res/boom.m3d");
        anims = LoadModelAnimations("../res/boom.m3d", &this->animsCount);
    }

    void update(f32 delta) {
        if (Core::InputHandler::isEvent(PLAYER_MOVE_FORWARD)) {
            vec3 forward = getTransform().pos - vec3(scene->camera.position);
            forward = vec3(forward.x, 0.0, forward.z).normalize();
            getTransform().pos = getTransform().pos + (forward * speed);
        }
        
        if (Core::InputHandler::isEvent(PLAYER_MOVE_BACKWARD)) {
            vec3 forward = getTransform().pos - vec3(scene->camera.position);
            forward = vec3(forward.x, 0.0, forward.z).normalize();
            getTransform().pos = getTransform().pos - (forward * speed);
        }
        
        if (Core::InputHandler::isEvent(PLAYER_MOVE_LEFT)) {
            vec3 forward = vec3(scene->camera.target) - vec3(scene->camera.position);
            forward = vec3(forward.x, 0.0, forward.z).normalize();
            vec3 right = vec3(scene->camera.up) CROSS forward;
            getTransform().pos = getTransform().pos + (right * speed);
        }

        if (Core::InputHandler::isEvent(PLAYER_MOVE_RIGHT)) {
            vec3 forward = vec3(scene->camera.target) - vec3(scene->camera.position);
            forward = vec3(forward.x, 0.0, forward.z).normalize();
            vec3 right = vec3(scene->camera.up) CROSS forward;
            getTransform().pos = getTransform().pos - (right * speed);
        }

        // if (n) {
        //     if (Core::InputHandler::isEvent(PLAYER_JUMP)) {
        //         currentFrame = (currentFrame + 1) % anims[currentAnimation].frameCount;
        //         UpdateModelAnimation(model, anims[currentAnimation], currentFrame);
        //     }
        // } else {
        //     if (Core::InputHandler::isEvent(PLAYER_ATTACK)) {
        //         currentFrame = (currentFrame + 1) % anims[currentAnimation].frameCount;
        //         UpdateModelAnimation(model, anims[currentAnimation], currentFrame);
        //     }
        // }
    }

    void draw() {
        DrawModel(model, getTransform().pos.to_vec(), 1.0f, BLACK);
    }

    ~Player() {
        UnloadModel(model);
        UnloadModelAnimations(anims, animsCount);
    }
};

class MyScene : public Core::Scene {
public:
    Player* mainPlayer;

    MyScene(Camera& cam) {
        DisableCursor();
        SetTargetFPS(60);

        cam.position = vec3(0.0, 1.5, 1.0).to_vec();
        cam.target = vec3().to_vec();
        cam.up = vec3(0.0f, 1.0f, 0.0f).to_vec();
        cam.fovy = 45.0f;
        cam.projection = CAMERA_PERSPECTIVE;

        setCamera(cam);
    }

    void setMainPlayer(Player* player) {
        mainPlayer = player;
    }

    void update(f32 delta) {
        camera.target = mainPlayer->getTransform().pos.to_vec();
        Scene::update(delta);
    }
};

int main(void)
{
    InitWindow(1280, 720, "Test");

    Camera cam;

    DisableCursor();

    Core::InputHandler::registerEvent(PLAYER_MOVE_FORWARD,  LITERAL_TO_STRING(PLAYER_MOVE_FORWARD),   {KEY_W},              {});
    Core::InputHandler::registerEvent(PLAYER_MOVE_BACKWARD, LITERAL_TO_STRING(PLAYER_MOVE_BACKWARD),  {KEY_S},              {});
    Core::InputHandler::registerEvent(PLAYER_MOVE_LEFT,     LITERAL_TO_STRING(PLAYER_MOVE_LEFT),      {KEY_A},              {});
    Core::InputHandler::registerEvent(PLAYER_MOVE_RIGHT,    LITERAL_TO_STRING(PLAYER_MOVE_RIGHT),     {KEY_D},              {});
    Core::InputHandler::registerEvent(PLAYER_JUMP,          LITERAL_TO_STRING(PLAYER_JUMP),           {KEY_SPACE},          {});
    Core::InputHandler::registerEvent(PLAYER_ATTACK,        LITERAL_TO_STRING(PLAYER_ATTACK),         {MOUSE_BUTTON_LEFT},  {});

    MyScene* scene = new MyScene(cam);

    Player* player  = new Player(scene, vec3(0, 1, 0), true);
    scene->setMainPlayer(player);

    // Player* player2 = new Player(scene, vec3(0, 0.5, 0), false);
    // Player* player3 = new Player(scene, vec3(0, 0, 0), true);

    Core::SceneManager::addScene(scene);

    Core::SceneManager::run();

    CloseWindow();
}
