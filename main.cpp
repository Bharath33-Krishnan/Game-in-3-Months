#include "Engine/Engine.h"
#include "Engine/src/core/PhysicsEngine.hpp"
#include "Engine/src/core/collider/BoxCollider2D.hpp"
#include "Engine/src/core/collider/Collider.hpp"

#define LITERAL_TO_STRING(x) #x

enum PlayerEvents {
    PLAYER_MOVE_UP = 0,
    PLAYER_MOVE_DOWN,
    PLAYER_MOVE_LEFT,
    PLAYER_MOVE_RIGHT,
    PLAYER_ROLL,
    PLAYER_ATTACK
};

class Player : public Core::Drawable {
private:
    Core::EngineMaterial *material;

    f32 speed = 200.0f;
    Core::Scene *scene;

    // SpriteSheet sprite;
    Texture2D tex;

    std::vector<SpriteSheet> running_anims;
    PlayerEvents running_state;

public:
    Core::Collider* collider;

    Player(Core::Scene *scene, vec2 pos) {
        this->scene = scene;
        // NOTE : Gowrish - For some reason `this` becomes NULL
        scene->addEntity(this);

        t.pos = pos;
        t.rot = 0.0f;
        t.scale = .1f;
        material = new Core::EngineMaterial(0, "../res/shaders/simple_frag.frag.glsl");

        this->init();
    }

    void init() {
        tex = *Core::SpriteManager::getTexture("player1");

        // sprite = SpriteSheet::CreateSpriteSheet("player2", vec2(0.0, 0.0), 16., 0., 1., true);
        // sprite.ChangeFPS(30);
        running_anims = std::vector<SpriteSheet>(4);
        collider = new Core::BoxCollider2D(t,vec2(50,50));
        for (int i = 0; i < 4; i++) {
            running_anims[i] = SpriteSheet::CreateSpriteSheet("player_running_anim", vec2(0, 0), 16, i, 4, true);
            running_anims[i].ChangeFPS(30);
        }
    }

    void update(f32 delta) {
        vec2 vel(0);
        running_state = PLAYER_MOVE_UP;
        if (Core::InputHandler::isEvent(PLAYER_MOVE_UP)) {
            vel.y -= speed;
            running_state = PLAYER_MOVE_UP;
        }
        if (Core::InputHandler::isEvent(PLAYER_MOVE_DOWN)) {
            vel.y += speed;
            running_state = PLAYER_MOVE_DOWN;
        }
        if (Core::InputHandler::isEvent(PLAYER_MOVE_LEFT)) {
            vel.x -= speed;
            running_state = PLAYER_MOVE_LEFT;
        }
        if (Core::InputHandler::isEvent(PLAYER_MOVE_RIGHT)) {
            vel.x += speed;
            running_state = PLAYER_MOVE_RIGHT;
        }
        if (vel.x == 0 && vel.y == 0)
            return;

        getTransform().pos = getTransform().pos + (speed * delta) * vel.normalize();
    }


    void drawGfx() {
        // BeginShaderMode(material->getShader());
        // DrawTextureEx(tex, getTransform().pos.to_vec(), getTransform().rot,
        // getTransform().scale, WHITE);
        // sprite.AnimateFrame(getTransform());

        running_anims[running_state].AnimateFrame(getTransform());
        collider->drawCollider();
        Core::PhysicsEngine::drawGrid();

        // EndShaderMode();
    }

    ~Player() {
        UnloadTexture(tex);
        delete material;
    }
};


class Tree : public Core::Drawable {
private:
    i32 animsCount;
    i32 currentFrame;
    i32 currentAnimation;

    f32 speed = 1000.0f;
    Core::Scene* scene;

    SpriteSheet sprite;

public:
    Core::Collider* collider;

    Tree(Core::Scene* scene, vec2 pos) {
        this->scene = scene;
        // NOTE : Gowrish - For some reason `this` becomes NULL
        scene->addEntity(this);

        t.pos = pos;
        t.rot = 0.0f;
        t.scale = 3.f;
        t.pivotOffset = vec2(0.0,50.0);
        // this->setLayer(2);

        currentFrame = 0;
        currentAnimation = 0;

        this->init();
    }

    void init() {
        // Image img = LoadImage("../res/player.png");
        sprite = SpriteSheet::CreateSpriteSheet("Tree", vec2(0.0,0.0),4.0, 0.0, 1.0 , true);
        sprite.ChangeFPS(sprite.getFPS()*4);
        collider = new Core::BoxCollider2D(t,vec2(50,50));
        // UnloadImage(img);
    }

    void update(f32 delta) {
        // vec2 vel(0);
        // if (Core::InputHandler::isEvent(PLAYER_MOVE_UP)) {
        //     vel.y -= speed;
        // }
        // if (Core::InputHandler::isEvent(PLAYER_MOVE_DOWN)) {
        //     vel.y += speed;
        // }
        // if (Core::InputHandler::isEvent(PLAYER_MOVE_LEFT)) {
        //     vel.x -= speed;
        // }
        // if (Core::InputHandler::isEvent(PLAYER_MOVE_RIGHT)) {
        //     vel.x += speed;
        // }
        // getTransform().rot += speed * delta;
        // if (vel.x == 0 && vel.y == 0) return;

        // getTransform().pos = getTransform().pos + (speed * delta) * vel.normalize();
        // getTransform().pos.print();
    }


    void drawGfx() {
        sprite.DrawFrame(0,getTransform());
        collider->drawCollider();
    }
};



class treeparticle : public ParticleEmitter{
private:
    Player* pl;
public:

    treeparticle(Player* pl,Core::Scene* scene,vec2 pos){
        this->pl = pl;
        this->scene = scene;
        // NOTE : Gowrish - For some reason `this` becomes NULL
        scene->addEntity(this);
        this->setLayer(5);

        t.pos = pos;
        t.rot = 0.0f;
        t.scale = 3.f;
        t.pivotOffset = vec2(0.0,50.0);
        // this->setLayer(2);

        this->init();
    }

    void init()override{

        particleEmitterData data;
        data.tex = SpriteSheet::CreateSpriteSheet("particles", vec2(0.0,0.0),9.0, 1.0, 9.0 , true);
        data.texFrame = 4;

        data.angleRange = vec2(50.,140.);
        data.emissionVariance = 1;
        data.emissionRate = 2;
        data.particle_lifetime = 3;
        data.startColor = RED; 
        data.endColor = BLUE;
        data.blendMode = BLEND_ALPHA_PREMULTIPLY;
        data.start_endSize  = vec2(.5,.5);
        data.rotSpeed = 0.0;
        data.speed = 50.0;

        this->data = data;
        // this->setLayer(1);
        this->initParticlePool();
    }
    void update(f32 delta) override{
        ParticleEmitter::update(delta);
        getTransform().pos = pl->getTransform().pos; 
    
    }


};



class MyScene : public Core::Scene {
private:
    float time = 0;

public:
    Player *mainPlayer;

    MyScene(Camera2D &cam) {
        // DisableCursor();
        SetTargetFPS(60);

        setCamera(cam);
        Core::SpriteManager::loadTexture("player1", "../res/player.png");

        // Core::SpriteManager::loadTexture("player2", "../res/spaceman_running_forward.png");
        Core::SpriteManager::loadTexture("player_running_anim", "../res/spaceman_running.png");
        Core::SpriteManager::loadTexture("Tree","../res/48x48 trees.png");
        Core::SpriteManager::loadTexture("particles","../res/particles.png");
    };

    void loadResources() {
        // NOTE : Bharath -> Load Tilemap file and other big files
        TraceLog(LOG_INFO, "Loading...");
        // while(time <= 5){
        //     time = GetTime();
        // }
        TraceLog(LOG_INFO, "Finished Loading");
        loading = false;
    }

    void setMainPlayer(Player *player) { mainPlayer = player; }

    void update(f32 delta) {
        camera.target = mainPlayer->getTransform().pos.to_vec();
        Scene::update(delta);
    }
};

int main(void) {
    InitWindow(1280, 720, "Test");

    Camera2D cam;
    cam.offset = { GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
    cam.rotation = 0.0f;
    cam.zoom = 1.0f;

    DisableCursor();
    Core::PhysicsEngine::Init();

    Core::InputHandler::registerEvent(PLAYER_MOVE_UP,     LITERAL_TO_STRING(PLAYER_MOVE_FORWARD),   {KEY_W},              {});
    Core::InputHandler::registerEvent(PLAYER_MOVE_DOWN,   LITERAL_TO_STRING(PLAYER_MOVE_BACKWARD),  {KEY_S},              {});
    Core::InputHandler::registerEvent(PLAYER_MOVE_LEFT,   LITERAL_TO_STRING(PLAYER_MOVE_LEFT),      {KEY_A},              {});
    Core::InputHandler::registerEvent(PLAYER_MOVE_RIGHT,  LITERAL_TO_STRING(PLAYER_MOVE_RIGHT),     {KEY_D},              {});
    Core::InputHandler::registerEvent(PLAYER_ROLL,        LITERAL_TO_STRING(PLAYER_JUMP),           {KEY_SPACE},          {});
    Core::InputHandler::registerEvent(PLAYER_ATTACK,      LITERAL_TO_STRING(PLAYER_ATTACK),         {MOUSE_BUTTON_LEFT},  {});

    MyScene *scene = new MyScene(cam);

    Core::SceneManager::addScene(scene);
    // for(int i = 0;i<=900;i++){
    //    new Tree(scene,vec2(GetRenderWidth()*i/90.,GetRenderHeight()/2.0)); 
    // }
    new Tree(scene,vec2(GetRenderWidth()/2.0,GetRenderHeight()/2.0)); 
    Player *player = new Player(scene, vec2(GetRenderWidth() / 2.0, GetRenderHeight() / 2.0));
    new treeparticle(player,scene,vec2(GetRenderWidth()/3.0,GetRenderHeight()/2.0));
    scene->setMainPlayer(player);

    Core::SceneManager::run();

    CloseWindow();
}
