#include <cmath>
#include "rlgl.h"
#include "constants.h"
#include <vector>

using namespace std;

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
        vector<float> gearRatios = {1.1f, 2.8f, 4.0f};
        int gear = 0;
        int rpm = 800;

        Car(float xPos, float yPos) : xPos(xPos), yPos(yPos) {}

        void updatePos() {

            updateVelocity();
            updateRotation();

            xPos += vel * GetFrameTime() * cos(theta);
            yPos += vel * GetFrameTime() * sin(theta);

        }

        void shiftUp() {
            if (gear < gearRatios.size() - 1) {
                gear++;
                rpm -= 3000;
            }
        }

        void shiftDown() {
            if (gear > 0) {
                gear--;
                rpm += 3000;
            }
        }

        void updateVelocity() {
            float dt = GetFrameTime();


            // increase less as engine is spinning faster 😳
            if (IsKeyDown(KEY_W)) {
                if (rpm < 8000) {
                    rpm *= 1 + (1 - rpm/max_rpm) * dt;
                }
            }

            if (IsKeyPressed(KEY_SPACE)) {
                shiftUp();
            }

            if (IsKeyPressed(KEY_LEFT_SHIFT)) {
                shiftDown();
                if (rpm > 8000) rpm = 8000;
            }


            if (rpm > idle_rpm && !IsKeyDown(KEY_W)) {
                rpm -= (rpm-idle_rpm) * rpm_decay_rate * dt;
            }

            float braking = IsKeyDown(KEY_S) ? 1.0f : 0.0f;

            float engineForce = rpm * engine_strength * gearRatios[gear];
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

