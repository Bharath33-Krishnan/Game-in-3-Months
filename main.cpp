#include "raylib/raylib.h"
#include "src/core.h"
#include "src/core/entity.hpp"
#include "src/core/graphics/lightingMaterial.hpp"

#define LITERAL_TO_STRING(x) #x

enum PlayerEvents {
    PLAYER_MOVE_UP = 0,
    PLAYER_MOVE_DOWN,
    PLAYER_MOVE_LEFT,
    PLAYER_MOVE_RIGHT,
    PLAYER_ROLL,
    PLAYER_ATTACK
};

class Player : public Core::AbstractEntity {
private:
    i32 animsCount;
    i32 currentFrame;
    i32 currentAnimation;

    f32 speed = 1000.0f;
    Core::Scene* scene;

    Texture2D tex;

public:
    Player(Core::Scene* scene, vec2 pos) {
        this->scene = scene;
        // NOTE : Gowrish - For some reason `this` becomes NULL
        scene->addEntity(this);

        t.pos = pos;
        t.rot = 0.0f;
        t.scale = 0.5f;

        currentFrame = 0;
        currentAnimation = 0;

        this->init();
    }

    void init() {
<<<<<<< HEAD
        Image img = LoadImage("../res/player.png");
        tex = LoadTextureFromImage(img);
        UnloadImage(img);
=======
        model = LoadModel("../res/boom.m3d");
        // Mesh cube_mesh= GenMeshCube(1.0, 1.0, 1.0);
        // model = LoadModelFromMesh(cube_mesh);
        GenMeshTangents(model.meshes);
        anims = LoadModelAnimations("../res/boom.m3d", &this->animsCount);
        Texture2D albedoTex = LoadTexture("../res/Textures/Rock_albedo.png");
        Texture2D normalTex = LoadTexture("../res/Textures/Rock_normal.png");

        addTexture(albedoTex, MATERIAL_MAP_ALBEDO);
        addTexture(normalTex, MATERIAL_MAP_NORMAL);
    }

    void addTexture(Texture2D& tex,i32 loc){
        model.materials[0].maps[loc].texture = tex;
>>>>>>> 73beb33 (Initial Lighting Setup)
    }

    void update(f32 delta) {
        vec2 vel(0);
        if (Core::InputHandler::isEvent(PLAYER_MOVE_UP)) {
            vel.y -= speed;
        }
        if (Core::InputHandler::isEvent(PLAYER_MOVE_DOWN)) {
            vel.y += speed;
        }
        if (Core::InputHandler::isEvent(PLAYER_MOVE_LEFT)) {
            vel.x -= speed;
        }
        if (Core::InputHandler::isEvent(PLAYER_MOVE_RIGHT)) {
            vel.x += speed;
        }
        if (vel.x == 0 && vel.y == 0) return;

        getTransform().pos = getTransform().pos + (speed * delta) * vel.normalize();
        // getTransform().pos.print();
    }

    void setMaterial(Core::EngineMaterial* mat){
        model.materials[0].shader = mat->getShader();
    }

    void draw() {
<<<<<<< HEAD
        DrawTextureEx(tex, getTransform().pos.to_vec(), getTransform().rot, getTransform().scale, WHITE);
=======
        // DrawPlane(Vector3Zero(), (Vector2) { 10.0, 10.0 }, WHITE);
        DrawModel(model, getTransform().pos.to_vec(), 1.0f, WHITE);
>>>>>>> 73beb33 (Initial Lighting Setup)
    }

    ~Player() {
        UnloadTexture(tex);
    }
};

class MyScene : public Core::Scene {
public:
<<<<<<< HEAD
    Player* mainPlayer;

    MyScene(Camera2D& cam) {
        DisableCursor();
        SetTargetFPS(60);

=======
    MyScene(Camera& cam, Core::GraphicsEngine& gfxEngine) {
        DisableCursor();
        SetTargetFPS(60);


        Core::LightingMaterial* mat1 = new Core::LightingMaterial("../res/shaders/lighting.vert.glsl","../res/shaders/lighting.frag.glsl"); 
        mat1->initMaterial(vec3(0.1,0.0,0.5),cam);
        gfxEngine.RegisterMaterial(mat1);

        Player* player = new Player(this);
        mat1->SubscribeToMaterial(player);

        mat1->CreateLight(LIGHT_POINT, vec3(1.0,2.0,1.0),vec3(0.0),RED);

        this->gfxEngine = gfxEngine;
        cam.position = vec3(1.5f).to_vec();
        cam.target = vec3().to_vec();
        cam.up = vec3(0.0f, 1.0f, 0.0f).to_vec();
        cam.fovy = 45.0f;
        cam.projection = CAMERA_PERSPECTIVE;

>>>>>>> 73beb33 (Initial Lighting Setup)
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

    Camera2D cam;

    DisableCursor();

<<<<<<< HEAD
    Core::InputHandler::registerEvent(PLAYER_MOVE_UP,       LITERAL_TO_STRING(PLAYER_MOVE_FORWARD),   {KEY_W},              {});
    Core::InputHandler::registerEvent(PLAYER_MOVE_DOWN,     LITERAL_TO_STRING(PLAYER_MOVE_BACKWARD),  {KEY_S},              {});
    Core::InputHandler::registerEvent(PLAYER_MOVE_LEFT,     LITERAL_TO_STRING(PLAYER_MOVE_LEFT),      {KEY_A},              {});
    Core::InputHandler::registerEvent(PLAYER_MOVE_RIGHT,    LITERAL_TO_STRING(PLAYER_MOVE_RIGHT),     {KEY_D},              {});
    Core::InputHandler::registerEvent(PLAYER_ROLL,          LITERAL_TO_STRING(PLAYER_JUMP),           {KEY_SPACE},          {});
    Core::InputHandler::registerEvent(PLAYER_ATTACK,        LITERAL_TO_STRING(PLAYER_ATTACK),         {MOUSE_BUTTON_LEFT},  {});

    MyScene* scene = new MyScene(cam);

    Player* player  = new Player(scene, vec2(GetRenderWidth()/2.0, GetRenderHeight()/2.0));
    scene->setMainPlayer(player);
=======

    Core::GraphicsEngine gfxEngine;
    
    MyScene* scene = new MyScene(cam,gfxEngine);
>>>>>>> 73beb33 (Initial Lighting Setup)

    Core::SceneManager::addScene(scene);

    // TraceLog(LOG_INFO,"********** Debug Text ************"); 
    Core::SceneManager::run();

    CloseWindow();
}
