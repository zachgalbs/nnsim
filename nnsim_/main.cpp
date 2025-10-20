#include <iostream>
#include <stdlib.h>
#include <thread>
#include "raylib.h"
#include "constants.h"
#include <cmath>

using namespace std;


class Car {
public:
    double vel;
    double mass = 5;
    double xPos;
    double yPos;
    double vSize = 10;
    Color vColor = RED;
    double theta;
    double steeringAngle;

    // * methods

    Car(double xPos, double yPos) : xPos(xPos), yPos(yPos) {}

    void updatePos(double passedTime) {
        xPos += vel * passedTime * cos(theta);
        yPos += vel * passedTime * sin(theta);
        if (vel > 0) {
            vel -= 10 * passedTime;
        }

    }
    // update the rotation
    void updateRotation(double passedTime, double idkwhattocallthisbrah) {
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
        ClearBackground(BLACK);
        // leftmost
        Vector2 v1 = {static_cast<float>(player.xPos) - 20, static_cast<float>(player.yPos) - 20};
        Vector2 v2 = {static_cast<float>(player.xPos) - 20, static_cast<float>(player.yPos) + 20};
        // rightmost
        Vector2 v3 = {static_cast<float>(player.xPos) + 20, static_cast<float>(player.yPos)};
        DrawTriangle(v1, v2, v3, player.vColor);
        EndDrawing();

    }
    return 0;
}
