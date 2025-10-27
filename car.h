#include <cmath>
#include "rlgl.h"

class Car {
    public:
        float vel = 0;
        float mass = 5;
        float xPos = 0;
        float yPos = 0;
        float vSize = 10;
        Color vColor = RED;
        float theta = 0;
        float steeringAngle = 0;
        int rpm = 0;

        // * methods

        Car(float xPos, float yPos) : xPos(xPos), yPos(yPos) {}

        void updatePos() {

            vel += rpm * GetFrameTime() * 1/20;

            if (rpm > 0 && !(IsKeyDown(KEY_W))) {
                rpm -=  20;
            }

            if (IsKeyDown(KEY_W) && rpm < 8000) {
                rpm += 20;
            }

            if (IsKeyDown(KEY_S) && vel > 0) {
                vel--;

            }

            if (IsKeyDown(KEY_S) && rpm > 0) {
                rpm -= 20;
            }

            if (IsKeyDown(KEY_A)) {
                updateRotation(-2);
            }

            if (IsKeyDown(KEY_D)) {
                updateRotation(2);
            }
            xPos += vel * GetFrameTime() * cos(theta);
            yPos += vel * GetFrameTime() * sin(theta);
            drag(0.5);

        }
        // update the rotation
        void updateRotation(float direction) {
            theta += direction * GetFrameTime();
        }
        void drag(float strength) {
            vel -= vel * strength * GetFrameTime();
        }
};

