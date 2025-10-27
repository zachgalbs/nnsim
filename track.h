#include <vector>
#include "raylib.h"
#include "constants.h"

using namespace std;

class Track {
    vector<Vector2> trackPoints;
    int width;
    Color color;
    public:
        Track(const vector<Vector2> &trackPoints, int width = 50, Color color = GRAY) : color(color), trackPoints(trackPoints) {}
        void DrawTrack();
};
