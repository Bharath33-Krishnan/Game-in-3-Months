#include "raylib/raylib.h"
#include "src/core.h"
#include <cmath>

#define LITERAL_TO_STRING(x) #x
#define DEG_TO_RAD(x) (x * M_PI / 180.0f)
#define RAD_TO_DEG(x) (x * 180.0f / M_PI)
#define LERP(a, b, t) (a + (b - a) * t)

enum PlayerEvents {
    PLAYER_MOVE_UP = 0,
    PLAYER_MOVE_DOWN,
    PLAYER_MOVE_LEFT,
    PLAYER_MOVE_RIGHT,
    PLAYER_DASH,
    PLAYER_LIGHT_ATTACK,
    PLAYER_HEAVY_ATTACK,
    PLAYER_IDLE,
};

class Player : public Core::AbstractEntity {
private:
    i32 animsCount;
    i32 currentFrame;
    i32 currentAnimation;

    f32 speed = 300.0f;
    Core::Scene* scene;

    struct {
        f32 lattack_cooldown  = 0.1f; // light attack
        f32 hattack_cooldown  = 2.0f; // heavy attack
        f32 roll_cooldown     = 0.5f;
        f32 attack_cooldown_timer;
        f32 roll_cooldown_timer;
    } cooldown_state ;

    struct {
        f32 start_angle;
        f32 end_angle;
    } slash;


    PlayerEvents currentState;

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
        Image img = LoadImage("../res/player.png");
        tex = LoadTextureFromImage(img);
        UnloadImage(img);
    }

    void update(f32 delta) {
        vec2 vel(0);

        if (Core::InputHandler::isEvent(PLAYER_MOVE_UP)) {
            vel.y -= speed;
            vel = vel.normalize();
        }
        if (Core::InputHandler::isEvent(PLAYER_MOVE_DOWN)) {
            vel.y += speed;
            vel = vel.normalize();
        }
        if (Core::InputHandler::isEvent(PLAYER_MOVE_LEFT)) {
            vel.x -= speed;
            vel = vel.normalize();
        }
        if (Core::InputHandler::isEvent(PLAYER_MOVE_RIGHT)) {
            vel.x += speed;
            vel = vel.normalize();
        }
        if (Core::InputHandler::isEvent(PLAYER_DASH)) {
            if (cooldown_state.roll_cooldown_timer < 0.0f) {
                cooldown_state.roll_cooldown_timer = cooldown_state.roll_cooldown;
                vel = 5 * vel;
                vel = vel.normalize();
            }
        }
        if (Core::InputHandler::isEvent(PLAYER_LIGHT_ATTACK)) {
            if (cooldown_state.attack_cooldown_timer < 0.0f) {
                cooldown_state.attack_cooldown_timer = cooldown_state.lattack_cooldown;
                currentState = PLAYER_LIGHT_ATTACK;

                vec2 mouse = GetMousePosition();
                vec2 mouse_rel = mouse - getTransform().pos.to_vec();

                f32 mouse_angle = RAD_TO_DEG(atan2(mouse_rel.y, mouse_rel.x));

                // Angle to draw ring
                slash.start_angle = mouse_angle - 60;
                slash.end_angle = mouse_angle + 60;
            }
        }

        if (cooldown_state.attack_cooldown_timer >= 0.0f) {
            cooldown_state.attack_cooldown_timer -= delta;
        } else {
            currentState = PLAYER_IDLE;
        }

        if (vel.x == 0 && vel.y == 0) return;
        vel.print();
        getTransform().pos = getTransform().pos + (speed * delta) * vel;
    }

    void draw() {
        vec2 pos = getTransform().pos - 0.5 * vec2(50);
        DrawRectangleV(pos.to_vec(), vec2(50).to_vec(), RED);
        // DrawTextureEx(tex, getTransform().pos.to_vec(), getTransform().rot, getTransform().scale, WHITE);

        if (currentState == PLAYER_LIGHT_ATTACK) {
            f32 final_angle = LERP(slash.end_angle, slash.start_angle, (cooldown_state.attack_cooldown_timer / cooldown_state.lattack_cooldown));
            // Sword Trail
            DrawRing(getTransform().pos.to_vec(), 62.0f, 60.0f, slash.start_angle, final_angle, 5, RED);

            // Sword
            vec2 sword_end = getTransform().pos + 60.0f * vec2(cos(DEG_TO_RAD(final_angle)), sin(DEG_TO_RAD(final_angle)));
            DrawLineEx(sword_end.to_vec(), getTransform().pos.to_vec(), 10, RED);
        }
    }
    ~Player() {
        UnloadTexture(tex);
    }
};

class MyScene : public Core::Scene {
public:
    Player* mainPlayer;

    MyScene(Camera2D& cam) {
        SetTargetFPS(60);
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
    ToggleFullscreen();
    Camera2D cam;

    Core::InputHandler::registerEvent(PLAYER_MOVE_UP,       LITERAL_TO_STRING(PLAYER_MOVE_FORWARD),   {KEY_W},                              {});
    Core::InputHandler::registerEvent(PLAYER_MOVE_DOWN,     LITERAL_TO_STRING(PLAYER_MOVE_BACKWARD),  {KEY_S},                              {});
    Core::InputHandler::registerEvent(PLAYER_MOVE_LEFT,     LITERAL_TO_STRING(PLAYER_MOVE_LEFT),      {KEY_A},                              {});
    Core::InputHandler::registerEvent(PLAYER_MOVE_RIGHT,    LITERAL_TO_STRING(PLAYER_MOVE_RIGHT),     {KEY_D},                              {});
    Core::InputHandler::registerEvent(PLAYER_DASH,          LITERAL_TO_STRING(PLAYER_JUMP),           {KEY_LEFT_SHIFT},                     {});
    Core::InputHandler::registerEvent(PLAYER_LIGHT_ATTACK,  LITERAL_TO_STRING(PLAYER_ATTACK),         {MOUSE_BUTTON_LEFT},                  {});
    Core::InputHandler::registerEvent(PLAYER_HEAVY_ATTACK,  LITERAL_TO_STRING(PLAYER_ATTACK),         {MOUSE_BUTTON_LEFT, KEY_LEFT_SHIFT},  {});

    MyScene* scene = new MyScene(cam);

    Player* player  = new Player(scene, vec2(GetRenderWidth()/2.0, GetRenderHeight()/2.0));
    scene->setMainPlayer(player);

    Core::SceneManager::addScene(scene);

    Core::SceneManager::run();

    CloseWindow();
}
