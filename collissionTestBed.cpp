#include "raylib/raylib.h"
#include "src/core.h"
#include "src/assets/sprite_manager.hpp"
#include "src/assets/particle_emitter.hpp"
#include "src/core/PhysicsEngine.hpp"
#include "src/core/collision/BoxCollider2D.hpp"
#include "src/core/scene.hpp"

#define LITERAL_TO_STRING(x) #x

enum Events{ 
    MOUSE_CLICK_LEFT,
    CHANGE_MODE
};

enum DrawModes{
    DRAW_MODE_RECTANGLE = 0,
    DRAW_MODE_CIRCLE = 1
};

class Circle: public Core::Drawable {
private:
    float rad;

    Core::Collider* my_Collider;
public:
    Circle(Core::Scene* scene,vec2 center,vec2 point){
        scene->addEntity(this);
        t.pos = center;
        t.rot = 0;
        t.scale = 1;
        rad = (point - center).magnitude();


        this->init();
    }

    void init() {
        my_Collider = new Core::CircleCollider2D(t,rad);
    }

    void update(f32 delta){
    }

    void drawGfx(){
        // DrawCircle(t.pos.x,t.pos.y , t.scale,BLUE);
        my_Collider->drawCollider();
    }

    ~Circle(){
        delete my_Collider;
    }
};


class Rectangle_Obj: public Core::Drawable {
private:
    vec2 diagonal;

    Core::Collider* my_Collider;
public:
    Rectangle_Obj(Core::Scene* scene,vec2 lCorner,vec2 rCorner){
        scene->addEntity(this);
        t.pos = lCorner;
        t.rot = 0;
        t.scale = 1;

        diagonal = rCorner - lCorner;

        this->init();
    }

    void init() {
        my_Collider = new Core::BoxCollider2D(t,diagonal);
    }

    void update(f32 delta){
    }

    void drawGfx(){
        // DrawRectangle(t.pos.x,t.pos.y, diagonal.x, diagonal.y,RED);
        my_Collider->drawCollider();
    }

    ~Rectangle_Obj(){
        delete my_Collider;
    }
};

class Player : public Core::Drawable {
private:
    Core::Scene *scene;
    
    bool mouse_clicked = false; 
    bool drawModeChanged = false;
    u16 drawMode = 0;

    vec2 initialMousePos;
    vec2 finalMousePos;

public:
    Player(Core::Scene *scene, vec2 pos) {
        this->scene = scene;
        // NOTE : Gowrish - For some reason `this` becomes NULL
        scene->addEntity(this);

        t.pos = pos;
        t.rot = 0.0f;
        t.scale = .1f;

        this->init();
    }

    void init() {
    }

    void update(f32 delta) {
        if(Core::InputHandler::isEvent(CHANGE_MODE))
        {
            if(drawModeChanged == false)
                drawMode = (drawMode + 1)%2;
            drawModeChanged = true;
        }
        else{
            drawModeChanged = false;
        }

        
        if(Core::InputHandler::isEvent(MOUSE_CLICK_LEFT) && mouse_clicked == false)
            mouse_clicked = true;
        else if(!Core::InputHandler::isEvent(MOUSE_CLICK_LEFT) && mouse_clicked)
        {
            
            switch(drawMode){
                case DRAW_MODE_RECTANGLE:
                    new Rectangle_Obj(this->scene,initialMousePos,finalMousePos);
                    break;
                case DRAW_MODE_CIRCLE:
                    new Circle(this->scene,initialMousePos,finalMousePos);
                    break;
            }
            mouse_clicked = false;
        }
        
    }

    void drawUI(){
        // NOTE : Draws UI for Drawing Modes
        float UI_padding = 25;
        DrawRectangle(UI_padding - 10, GetScreenHeight() - 1.5*UI_padding, UI_padding * TextLength("MODE_RECTANGLE")/2.0 ,2*UI_padding, BLACK);
        switch(drawMode){
            case DRAW_MODE_RECTANGLE:
                DrawText("MODE_RECTANGLE", UI_padding, GetScreenHeight() - UI_padding , 15, GREEN);
                break;
            case DRAW_MODE_CIRCLE:
                DrawText("MODE_CIRCLE", UI_padding, GetScreenHeight() - UI_padding , 15, GREEN);
                break;
        }

        if(!mouse_clicked)
            initialMousePos = vec2(GetMousePosition());
        else
            finalMousePos = vec2(GetMousePosition());
    }

    void drawSquare(vec2 lCorner, vec2 rCorner){
        vec2 diagonal = rCorner - lCorner;
        DrawRectangle(lCorner.x, lCorner.y, diagonal.x, diagonal.y, RED);
    }


    void drawCircle(vec2 center , vec2 point){
        vec2 rad = point - center;
        DrawCircle(center.x,center.y , rad.magnitude(), BLUE);
    }

    void drawGfx(){
        Core::PhysicsEngine::drawGrid();
        drawUI();

        if(!mouse_clicked)
            return;

        switch(drawMode){
            case DRAW_MODE_RECTANGLE:
                drawSquare(initialMousePos, finalMousePos);
                break;
            case DRAW_MODE_CIRCLE:
                drawCircle(initialMousePos, finalMousePos);
                break;
        }

        DrawCircle(initialMousePos.x , initialMousePos.y, 5, RED);
        DrawCircle(finalMousePos.x , finalMousePos.y, 5, BLUE);
    }

    ~Player() {
    }
};


class MyScene : public Core::Scene {
private:
    float time = 0;

public:
    Player *mainPlayer = nullptr;

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
        if(mainPlayer != nullptr)
            camera.target = mainPlayer->getTransform().pos.to_vec();
        else
            camera.target = vec2(GetRenderWidth() / 2.0, GetRenderHeight() / 2.0).to_vec();
        Scene::update(delta);
    }
};

int main(void) {
    InitWindow(1280, 720, "Test");

    Camera2D cam;
    cam.offset = { GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
    cam.rotation = 0.0f;
    cam.zoom = 1.0f;


    MyScene *scene = new MyScene(cam);
    Core::PhysicsEngine::Init();
    Player *player = new Player(scene, vec2(GetRenderWidth() / 2.0, GetRenderHeight() / 2.0));

    Core::InputHandler::registerEvent(MOUSE_CLICK_LEFT, LITERAL_TO_STRING(MOUSE_CLICK_LEFT), 
                                      {MOUSE_BUTTON_LEFT}, {});
    Core::InputHandler::registerEvent(CHANGE_MODE, LITERAL_TO_STRING(CHANGE_MODE), 
                                      {KEY_SPACE}, {});

    Core::SceneManager::addScene(scene);
    // scene->setMainPlayer(player);

    Core::SceneManager::run();

    CloseWindow();
}
