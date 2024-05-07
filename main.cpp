#include "raylib/raylib.h"
// #include "src/test/Test.h"
#include "src/core.h"

class Player : public Core::AbstractEntity {
private:
    Model model;
    ModelAnimation* anims;

    i32 animsCount;
    i32 currentFrame;
    i32 currentAnimation;

public:
    Player(Core::Scene* scene) {

        // NOTE : Gowrish - For some reason `this` becomes NULL
        scene->addEntity(this);

        transform t = getTransform();
        t.pos = vec3(0, 0, 0);
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
        currentFrame = (currentFrame + 1) % anims[currentAnimation].frameCount;
        UpdateModelAnimation(model, anims[currentAnimation], currentFrame);
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
    MyScene(Camera& cam) {
        DisableCursor();
        SetTargetFPS(60);

        cam.position = vec3(1.5f).to_vec();
        cam.target = vec3().to_vec();
        cam.up = vec3(0.0f, 1.0f, 0.0f).to_vec();
        cam.fovy = 45.0f;
        cam.projection = CAMERA_PERSPECTIVE;

        setCamera(cam);
    }
};

int main(void)
{
    InitWindow(1280, 720, "Test");

    Camera cam;

    DisableCursor();

    MyScene* scene = new MyScene(cam);
    Player* player = new Player(scene);

    Core::SceneManager::addScene(scene);

    Core::SceneManager::run();

    CloseWindow();
}
