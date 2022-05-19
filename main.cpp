#include <raylib.h>
#include <raymath.h>
#include <iostream>

struct Player{
    float x, y, speed, radius, rotation;
    Texture2D sprite;
    
    void initPlayer(float x_, float y_, float speed_, float radius_, float rotation, Texture sprite_){
        x = x_;
        y = y_;
        speed = speed_;
        radius = radius_;
        sprite = sprite_;
    }

    // Source rectangle (part of the texture to use for drawing)
    Rectangle GetSource(){
        return {0.0f, 0.0f, (float)sprite.width, (float)sprite.height};
    }

    // Destination rectangle (screen rectangle where drawing part of texture)
    Rectangle GetDest(){
        return {x, y, (float)sprite.width, (float)sprite.height};
    }

    float GetRotation(){
        return (atan2(GetMouseY() - y, GetMouseX() - x) * 180) / PI;
    }

    Vector2 GetOrigin2(){
        return {66.0f, 77.0f};
    }

    Vector2 GetOrigin(){
        return {x - 66.0f, y - 77.0f};
    }
};

void PlayerInput(Player &player){
    if(IsKeyDown(KEY_W)){
        player.y -= player.speed * GetFrameTime();
    }
    if(IsKeyDown(KEY_S)){
        player.y += player.speed * GetFrameTime();
    }
    if(IsKeyDown(KEY_A)){
        player.x -= player.speed * GetFrameTime();
    }
    if(IsKeyDown(KEY_D)){
        player.x += player.speed * GetFrameTime();
    }
}

int main(void){
    
    const int windowWidth = 1280;
    const int windowHeight = 720;

    InitWindow(windowWidth, windowHeight, "Top Down Shooter Test");
    SetTargetFPS(144);

    Player player; 
    player.initPlayer((float)GetScreenWidth()/2, (float)GetScreenHeight()/2,
         300.0f, 40.0f, 180.0f, LoadTexture("rsrc/top_down_man.png"));

    while(!WindowShouldClose()){

        // Player Inputs
        PlayerInput(player);

        ClearBackground(RAYWHITE);

        BeginDrawing();

            DrawTexturePro(player.sprite, player.GetSource(), player.GetDest(), player.GetOrigin2(),
                player.GetRotation(), WHITE);

        EndDrawing();
    }

    UnloadTexture(player.sprite);

    CloseWindow();

    return 0;
}