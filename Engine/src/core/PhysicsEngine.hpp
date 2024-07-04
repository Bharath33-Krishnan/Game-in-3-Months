#pragma once
#include <cmath>
#include <vector>
#include "collision/Collider.hpp"

#define PHYSICS_CLOCK_PER_FRAME 8
#define MAX_COLLIDERS 10000
#define MAX_COLLIDERS_PER_CELL 10

#define GRID_CELL_SIZE 50

namespace Core{
/*
 * NOTE: Bharath: Physics Engine Does Not Manage Colliders,
 * its destruction and initialisation should be managed by the programmer
 * Its just a container for quick access for collission calculations
 *
 * FIX:  Bharath: Later Optimisation, we can reuse space occupied by colliders of destroyed 
 *       objects
*/
class PhysicsEngine{

private:
    //************ Properties ************
    static Camera2D* cam;
    static i32 num_colliders;
    static i32 cellsX;
    static i32 cellsY;

    static std::vector<Collider*> colliders;
    static std::vector<std::vector<std::vector<i32>>> colliders_per_cell;
    static std::vector<std::vector<i32>> num_colliders_per_cell;
    static std::vector<std::vector<i64>> collission_data;

    static void SolveCollissionsForCell(i32 x,i32 y,f32 phy_delta);
public:
    //************ Public Property ************
    static bool is_initialized;

    //************ Functions ************
    static void Init();
    static void RegisterCam(Camera2D* scene_cam);
    static void registerCollider(Collider* col);
    static void GenerateSpatialGrid();
    static void SolveCollissions(f32 phy_delta);
    static bool GetCachedCollissionData(Collider* A,Collider* B);
    static inline vec2 GetColIndicesFloor(vec2 col_pos){
        return  vec2(floor(col_pos.x/GRID_CELL_SIZE),
                     floor(col_pos.y/GRID_CELL_SIZE));
    }
    static inline vec2 GetColIndicesCeil(vec2 col_pos){
        return  vec2(ceil(col_pos.x/GRID_CELL_SIZE),
                     ceil(col_pos.y/GRID_CELL_SIZE));
    }

    //************ Getters ************
    static std::vector<Collider*>& getColliders();

    //************ GIZMO functions ************
    static void drawGrid();
};

};
