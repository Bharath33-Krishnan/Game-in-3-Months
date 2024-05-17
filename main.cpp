#include "raylib/raylib.h"
#include "src/core.h"


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
    i32 animsCount;
    i32 currentFrame;
    i32 currentAnimation;
    Core::EngineMaterial* material;

    f32 speed = 1000.0f;
    Core::Scene* scene;

    SpriteSheet sprite;
    Texture2D tex;

public:
    Player(Core::Scene* scene, vec2 pos) {
        this->scene = scene;
        // NOTE : Gowrish - For some reason `this` becomes NULL
        scene->addEntity(this);

        t.pos = pos;
        t.rot = 0.0f;
        t.scale = 2.f;
        material = new Core::EngineMaterial(0,"../res/shaders/simple_frag.frag.glsl");

        currentFrame = 0;
        currentAnimation = 0;

        this->init();
    }

    void init() {
        // Image img = LoadImage("../res/player.png");
        tex = *Core::SpriteManager::getTexture("player1");
        sprite = SpriteSheet::CreateSpriteSheet("player2", vec2(0.0,0.0), 5.0, 1.0, 4.0 , true);
        sprite.ChangeFPS(sprite.getFPS()*4);
        // UnloadImage(img);
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


    void drawGfx() {
        BeginShaderMode(material->getShader());
            // DrawTextureEx(tex, getTransform().pos.to_vec(), getTransform().rot, getTransform().scale, WHITE);
            sprite.AnimateFrame(getTransform());
        EndShaderMode();
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
    Tree(Core::Scene* scene, vec2 pos) {
        this->scene = scene;
        // NOTE : Gowrish - For some reason `this` becomes NULL
        scene->addEntity(this);

        t.pos = pos;
        t.rot = 0.0f;
        t.scale = 3.f;
        this->setLayer(2);

        currentFrame = 0;
        currentAnimation = 0;

        this->init();
    }

    void init() {
        // Image img = LoadImage("../res/player.png");
        sprite = SpriteSheet::CreateSpriteSheet("Tree", vec2(0.0,0.0),4.0, 0.0, 1.0 , true);
        sprite.ChangeFPS(sprite.getFPS()*4);
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
        // if (vel.x == 0 && vel.y == 0) return;

        // getTransform().pos = getTransform().pos + (speed * delta) * vel.normalize();
        // getTransform().pos.print();
    }


    void drawGfx() {
        sprite.DrawFrame(0,getTransform());
    }
};

class MyScene : public Core::Scene {
private:
    float time = 0;
public:
    Player* mainPlayer;

    MyScene(Camera2D& cam) {
        DisableCursor();
        SetTargetFPS(60);

        setCamera(cam);
        Core::SpriteManager::loadTexture("player1","../res/player.png");
        Core::SpriteManager::loadTexture("player2","../res/enemy_test.png");
        Core::SpriteManager::loadTexture("Tree","../res/48x48 trees.png");
    };

    void loadResources(){
        //NOTE : Bharath -> Load Tilemap file and other big files
        TraceLog(LOG_INFO,"Loading...");
        // while(time <= 5){
        //     time = GetTime();
        // }
        TraceLog(LOG_INFO,"Finished Loading");
        loading = false;
        
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

    Core::InputHandler::registerEvent(PLAYER_MOVE_UP,       LITERAL_TO_STRING(PLAYER_MOVE_FORWARD),   {KEY_W},              {});
    Core::InputHandler::registerEvent(PLAYER_MOVE_DOWN,     LITERAL_TO_STRING(PLAYER_MOVE_BACKWARD),  {KEY_S},              {});
    Core::InputHandler::registerEvent(PLAYER_MOVE_LEFT,     LITERAL_TO_STRING(PLAYER_MOVE_LEFT),      {KEY_A},              {});
    Core::InputHandler::registerEvent(PLAYER_MOVE_RIGHT,    LITERAL_TO_STRING(PLAYER_MOVE_RIGHT),     {KEY_D},              {});
    Core::InputHandler::registerEvent(PLAYER_ROLL,          LITERAL_TO_STRING(PLAYER_JUMP),           {KEY_SPACE},          {});
    Core::InputHandler::registerEvent(PLAYER_ATTACK,        LITERAL_TO_STRING(PLAYER_ATTACK),         {MOUSE_BUTTON_LEFT},  {});

    MyScene* scene = new MyScene(cam);

    Core::SceneManager::addScene(scene);

    // for(int i = 0;i<=900;i++){
    //    new Tree(scene,vec2(GetRenderWidth()*i/90.,GetRenderHeight()/2.0)); 
    // }
   new Tree(scene,vec2(GetRenderWidth()/2.0,GetRenderHeight()/2.0)); 
    Player* player  = new Player(scene, vec2(GetRenderWidth()/2.0, GetRenderHeight()/2.0));
    scene->setMainPlayer(player);

    Core::SceneManager::run();

    CloseWindow();
}
