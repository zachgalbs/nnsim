#include <iostream>
#include <stdlib.h>
#include <thread>
#include "raylib.h"
#include "rlgl.h"
#include "constants.h"
#include <cmath>

using namespace std;


struct Car {
    float vel;
    float mass = 5;
    float xPos;
    float yPos;
    float vSize = 10;
    Color vColor = RED;
    float theta;
    float steeringAngle;

    // * methods

    Car(float xPos, float yPos) : xPos(xPos), yPos(yPos) {}

    void updatePos(float passedTime) {
        xPos += vel * passedTime * cos(theta);
        yPos += vel * passedTime * sin(theta);
        if (vel > 0) {
            vel -= 10 * passedTime;
        }

    }
    // update the rotation
    void updateRotation(float passedTime, float idkwhattocallthisbrah) {
        theta += idkwhattocallthisbrah * passedTime;
    }

};


int main() {

    InitWindow(screenW, screenH, "fuck you");
    SetTargetFPS(120);

    Car player(screenW / 2, screenH / 2);

    std::cout << player.xPos << " " << player.yPos << std::endl << player.vSize;

    while(!WindowShouldClose()) {
        if (IsKeyDown(KEY_W)) {
            player.vel++;
        }
        if (IsKeyDown(KEY_S) && player.vel > 0) {
            player.vel--;
        }

        if (IsKeyDown(KEY_A)) {
            player.updateRotation(GetFrameTime(), -2);
        }

        if (IsKeyDown(KEY_D)) {
            player.updateRotation(GetFrameTime(), 2);
        }

        player.updatePos(GetFrameTime());

        BeginDrawing();
        rlDisableBackfaceCulling();
        ClearBackground(BLACK);
        // leftmost
        Vector2 v1 = {(player.xPos) + player.vSize * cos(player.theta + 3*PI/4 ), (player.yPos) + player.vSize * sin(player.theta + 3*PI/4)};
        Vector2 v2 = {(player.xPos) + player.vSize * cos(player.theta + 5*PI/4), (player.yPos) + player.vSize * sin(player.theta + 5*PI/4)};
        // rightmost
        Vector2 v3 = {(player.xPos) + player.vSize * cos(player.theta ), (player.yPos) + player.vSize * sin(player.theta)};
        DrawTriangle(v1, v2, v3, player.vColor);
        EndDrawing();

    }
    return 0;
}
