#include <cmath>
#include "rlgl.h"
#include "constants.h"

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
        int rpm = 800;

        Car(float xPos, float yPos) : xPos(xPos), yPos(yPos) {}

        void updatePos() {

            updateVelocity();
            updateRotation();

            xPos += vel * GetFrameTime() * cos(theta);
            yPos += vel * GetFrameTime() * sin(theta);

            rpm = idle_rpm + vel * gear_ratio;

        }
        void updateVelocity() {
            float dt = GetFrameTime();

            float throttle = IsKeyDown(KEY_W) ? 1.0f : 0.0f;
            float braking = IsKeyDown(KEY_S) ? 1.0f : 0.0f;

            float engineForce = throttle * engine_strength;
            float brakeForce = braking * break_strength;
            float frictionForce = vel * friction_strength; // grows with speed

            float force = engineForce - frictionForce - brakeForce;

            float a = force / mass; // derived from f=ma 😂✌️

            vel += a * dt;
            if (vel < 0) vel = 0; // don't roll backwards 😳
        }
        // update the rotation
        void updateRotation() {
            if (IsKeyDown(KEY_A)) {
                theta -= turn_strength * GetFrameTime();
            }

            if (IsKeyDown(KEY_D)) {
                theta += turn_strength * GetFrameTime();
            }
        }
};

