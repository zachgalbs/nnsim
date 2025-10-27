#include <iostream>
#include "raylib.h"
#include "rlgl.h"
#include "constants.h"
#include "car.h"
#include "track.h"

using namespace std;

int main() {

    InitWindow(screenW, screenH, "fuck you");
    SetTargetFPS(60);

    std::cout << screenW/2 << screenH/2 << endl;
    Car player(screenW / 2, screenH / 2);

    std::cout << player.xPos << " " << player.yPos << std::endl << player.vSize;

    while(!WindowShouldClose()) {

        player.updatePos();

        BeginDrawing();

        Track track = Track();
        track.DrawTrack();

        DrawText(TextFormat("RPM: %d", player.rpm), 50, 50, 20, WHITE);

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
