#pragma once
#include <cmath>
#include <vector>
#include "collision/Collider.hpp"

#define PHYSICS_CLOCK_PER_FRAME 8
#define MAX_COLLIDERS 1000
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
    static int num_colliders;
    static int cellsX;
    static int cellsY;

    static std::vector<Collider*> colliders;
    static std::vector<std::vector<std::vector<int>>> colliders_per_cell;
    static std::vector<std::vector<int>> num_colliders_per_cell;

    static void SolveCollissionsForCell(int x,int y,float phy_delta);
public:
    //************ Public Property ************
    static bool is_initialized;
    static std::vector<std::vector<bool>> collission_data;

    //************ Functions ************
    static void Init();
    static void RegisterCam(Camera2D* scene_cam);
    static void registerCollider(Collider* col);
    static void GenerateSpatialGrid();
    static void SolveCollissions(float phy_delta);
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
