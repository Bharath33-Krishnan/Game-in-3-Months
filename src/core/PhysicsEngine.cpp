#include "PhysicsEngine.hpp"
#include "collision/Collider.hpp"
#include "raylib/raylib.h"
#include <cmath>

std::vector<Core::Collider*> Core::PhysicsEngine::colliders(MAX_COLLIDERS);
std::vector<std::vector<bool>> Core::PhysicsEngine::collission_data;
std::vector<std::vector<std::vector<int>>> Core::PhysicsEngine::colliders_per_cell;
std::vector<std::vector<int>> Core::PhysicsEngine::num_colliders_per_cell;
int Core::PhysicsEngine::num_colliders = 0;
int Core::PhysicsEngine::cellsX = 0;
int Core::PhysicsEngine::cellsY = 0;
bool Core::PhysicsEngine::is_initialized = false;
Camera2D* Core::PhysicsEngine::cam;


void Core::PhysicsEngine::registerCollider(Collider *col){
    int id = num_colliders++;
    col->setId(id);
    colliders[id] = col;
}

void Core::PhysicsEngine::Init(){
    auto collission_data_bools = std::vector<bool>(MAX_COLLIDERS,false);
    collission_data = std::vector<std::vector<bool>>(MAX_COLLIDERS,collission_data_bools);

    cellsX = GetScreenWidth()/GRID_CELL_SIZE;
    cellsY = GetScreenHeight()/GRID_CELL_SIZE;

    auto cellVector = std::vector<int>(MAX_COLLIDERS_PER_CELL,0);
    auto cellXVector = std::vector<std::vector<int>>(cellsY,cellVector);
    colliders_per_cell = std::vector<std::vector<std::vector<int>>>(cellsX,cellXVector);

    auto num_cellVector = std::vector<int>(cellsY,0);
    num_colliders_per_cell = std::vector<std::vector<int>>(cellsX,num_cellVector);

    is_initialized = true;
}

void Core::PhysicsEngine::RegisterCam(Camera2D *scene_cam){
    cam = scene_cam;
}

void Core::PhysicsEngine::GenerateSpatialGrid(){
    for(int x = 0; x < cellsX ; x++){
        for(int y = 0; y < cellsY ; y++){
            num_colliders_per_cell[x][y] = 0;
        }
    }
    for(int col_id = 0; col_id < num_colliders ; col_id++){
        Collider* collider = colliders[col_id];
        if(collider == nullptr)
            break;// NOTE: Bharath: Should it be break or continue idk
        vec2 col_pos = collider->getParameter(ColParams::POS);
        vec2 col_size = collider->getParameter(ColParams::SCALE);
        vec2 neg_col_size = vec2(-col_size.x,-col_size.y);
        vec2 col_rot = collider->getParameter(ColParams::ROT);

        vec2 rot_vec_X = vec2(cos(col_rot.x * DEG2RAD),sin(col_rot.x * DEG2RAD));
        vec2 rot_vec_Y = vec2(-sin(col_rot.x * DEG2RAD),cos(col_rot.x * DEG2RAD));

        // NOTE: Bharath: This method isn't perfect at all, and I don't have any great Ideas, But having most colliders
        //                Less than GRID_CELL_SIZE will be really good for performance unless GRID_CELL_SIZE is too big
        vec2 col_size_indices_start = GetColIndicesFloor(neg_col_size);
        vec2 col_size_indices_stop  = GetColIndicesCeil(col_size);
        for(int i = col_size_indices_start.x; i <= col_size_indices_stop.x; i++){
            for(int j = col_size_indices_start.y; j <= col_size_indices_stop.y; j++){
                vec2 pos_ind = GetColIndicesFloor(col_pos);
                pos_ind = pos_ind + i*rot_vec_X + j * rot_vec_Y;
                if(pos_ind.x >= cellsX || pos_ind.y >= cellsY)
                    continue;
                if(pos_ind.x < 0 || pos_ind.y < 0)
                    continue;
                if( num_colliders_per_cell[pos_ind.x][pos_ind.y] + 1 >= MAX_COLLIDERS_PER_CELL)
                    break;
                int cur_num_col_cell = num_colliders_per_cell[pos_ind.x][pos_ind.y]++;
                colliders_per_cell[pos_ind.x][pos_ind.y][cur_num_col_cell] = col_id;
            }
        }

    }
}

void Core::PhysicsEngine::SolveCollissionsForCell(int x, int y){
    for(int i = 0; i < num_colliders_per_cell[x][y]; i++){
        Collider* curr_col = colliders[colliders_per_cell[x][y][i]];
        for(int j = i+1; j < num_colliders_per_cell[x][y]; j++){
            Collider* other_col = colliders[colliders_per_cell[x][y][j]];
            curr_col->SolveCollision(other_col);
        }
    }
}

void Core::PhysicsEngine::SolveCollissions(){
    for(int x = 0; x < cellsX ; x++){
        for(int y = 0; y < cellsY ; y++){
            SolveCollissionsForCell(x,y);
        }
    }
}

std::vector<Core::Collider*> Core::PhysicsEngine::getColliders(){
    return colliders;
}

void Core::PhysicsEngine::drawGrid(){
    for(int gridX = 0; gridX <= cellsX; gridX+=1){
        DrawLine(gridX*GRID_CELL_SIZE, 0, gridX*GRID_CELL_SIZE, GetScreenHeight(), GREEN);
    }

    for(int gridY = 0; gridY <= cellsY; gridY+=1){
        DrawLine(0, gridY*GRID_CELL_SIZE, GetScreenWidth(), gridY*GRID_CELL_SIZE, GREEN);
    }

    for(int x = 0; x < cellsX ; x++)
        for(int y = 0; y < cellsY ; y++)
            for(int i = 0; i < num_colliders_per_cell[x][y]; i++)
                DrawText(TextFormat("%d",colliders_per_cell[x][y][i]) ,x * GRID_CELL_SIZE + i*10, y * GRID_CELL_SIZE, 10, RED);
}
