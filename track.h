#include "raylib.h"
#include "constants.h"

class Track {
    int xPos;
    int yPos;
    int width;
    Color color;
    public:
        Track(int xPos = screenW/2, int yPos = screenH/2, int width = 50, Color color = GRAY) : xPos(xPos), yPos(yPos), width(width), color(color) {}
        void DrawTrack() {
            DrawEllipse(xPos, yPos, 200 + width, 120 + width, color);
            DrawEllipse(xPos, yPos, 200, 120, BLACK);
        }
};
