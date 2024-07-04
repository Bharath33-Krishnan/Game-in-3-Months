#pragma once
#include "../PhysicsEngine.hpp"
#include "../entity.hpp"
#include "Collider.hpp"
#include "data_types.hpp"
#include "raylib/raylib.h"

namespace Core {

class CircleCollider2D : public Collider {
public:
  transform &base_t;
  f32 rad;

  //********* Override Solver ***********
  bool SolveCollision(Collider *other, f32 phy_delta) override;

  //********* Constructors ***********
  inline CircleCollider2D(transform &base_t, f32 rad) : base_t(base_t) {
    PhysicsEngine::registerCollider(this);
    this->collider_type = ColliderType::CIRCLE_2D;
    this->Offset = .5*vec2(rad);
    this->rad = rad;
  }
  inline CircleCollider2D(transform &base_t, f32 rad, bool isStationary)
      : base_t(base_t) {
    PhysicsEngine::registerCollider(this);
    this->collider_type = ColliderType::CIRCLE_2D;
    this->rad = rad;
    this->Offset = .5*vec2(rad);
    this->isStationary = isStationary;
  }
  inline CircleCollider2D(transform &base_t, f32 rad, bool isStationary,
                          bool isTrigger)
      : base_t(base_t) {
    PhysicsEngine::registerCollider(this);
    this->collider_type = ColliderType::CIRCLE_2D;
    this->rad = rad;
    this->Offset = .5*vec2(rad);
    this->isTrigger = isTrigger;
    this->isStationary = isStationary;
  }

  inline void drawCollider() override {
    DrawCircleLines(base_t.pos.x, base_t.pos.y, rad, GREEN);
  }

  inline vec2 getParameter(ColParams param) override {
    switch (param) {
    case ColParams::POS:
      return base_t.pos - Offset;
    case ColParams::ROT:
      return base_t.rot;
    case ColParams::SCALE:
      return vec2(rad);
    default:
      return vec2(-1);
    }
  }

  ~CircleCollider2D() {}
};

}; // namespace Core
