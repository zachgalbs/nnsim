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

    // For a closed Catmull-Rom spline, we need to duplicate points at the beginning and end ts
    vector<Vector2> trackShape = {
        {300, 200},
        {900, 200},
        {1000, 300},
        {900, 400},
        {300, 400},
        {200, 300}
    };

    // Wrap points for closed loop: add last two points at start, first two points at end
    vector<Vector2> f1TrackPoints;
    f1TrackPoints.push_back(trackShape[trackShape.size() - 2]); // Second to last
    f1TrackPoints.push_back(trackShape[trackShape.size() - 1]); // Last
    for (const auto& point : trackShape) {
        f1TrackPoints.push_back(point);
    }
    f1TrackPoints.push_back(trackShape[0]); // First
    f1TrackPoints.push_back(trackShape[1]); // Second

    Track f1Track = Track(f1TrackPoints, 60, GRAY);

    std::cout << screenW/2 << screenH/2 << endl;
    Car player(screenW / 2, screenH / 2);

    std::cout << player.xPos << " " << player.yPos << std::endl << player.vSize;


    while(!WindowShouldClose()) {

        player.updatePos();

        BeginDrawing();

        f1Track.DrawTrack();

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
    DrawSplineCatmullRom(trackPoints.data(), trackPoints.size(), width, color);
}


