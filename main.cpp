#include <iostream>
#include "raylib.h"
#include "rlgl.h"
#include "constants.h"
#include "car.h"
#include "track.h"
#include <vector>

using namespace std;

int main() {

    InitWindow(screenW, screenH, "fuck you");
    SetTargetFPS(60);

    vector<Vector2> trackPoints = {
        {420,  200},
        {680,  190},
        {940,  230},
        {1100, 340},
        {1140, 520},
        {1000, 660},
        {740,  720},
        {480,  700},
        {300,  600},
        {420, 200},
    };
    for (auto & trackPoint : trackPoints) {
        trackPoint.y -= 100;
        trackPoint.x -= 50;
    }


    std::cout << screenW/2 << screenH/2 << endl;
    Car player(screenW / 2, screenH / 2);

    std::cout << player.xPos << " " << player.yPos << std::endl << player.vSize;


    Track track = Track(trackPoints, 50, GRAY);

    while(!WindowShouldClose()) {

        player.updatePos();

        BeginDrawing();

        track.DrawTrack();

        DrawText(TextFormat("RPM: %d", player.rpm), 50, 50, 20, WHITE);
        DrawText(TextFormat("Gear: %d", player.gear), 50, 75, 20, WHITE);



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



void Track::DrawTrack() {

    for (int i = 0; i < trackPoints.size() - 1; i++) {
        DrawLineBezier(trackPoints[i], trackPoints[i+1], 50.0f, GRAY);
    }
}


