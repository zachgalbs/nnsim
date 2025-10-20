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

        theta += steeringAngle * passedTime;

        if (vel > 0) {
            vel -= 10 * passedTime;
        }

    }



};


int main() {

    InitWindow(screenW, screenH, "fuck you");
    SetTargetFPS(120);

    Car player(screenW / 2, screenH / 2);

    std::cout << player.xPos << " " << player.yPos << std::endl << player.vSize;

    while(!WindowShouldClose()) {

        ClearBackground(BLACK);

        if (IsKeyDown(KEY_W)) {
            player.vel++;
        }

        if (IsKeyDown(KEY_A) && player.steeringAngle < 5) {
            player.steeringAngle ++;
        }

        if (IsKeyDown(KEY_D) && player.steeringAngle > -5) {
            player.steeringAngle --;
        }

        player.updatePos(GetFrameTime());

        BeginDrawing();
        DrawCircle(player.xPos, player.yPos, player.vSize, player.vColor);
        EndDrawing();


    }





    return 0;
}
