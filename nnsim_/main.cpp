#include "raylib.h"

int main() {
    const int W = 800, H = 450;
    InitWindow(W, H, "raylib smoke test");
    SetTargetFPS(60);

    float angle = 0.0f;
    const Vector2 rectSize = {200.0f, 100.0f};
    const Vector2 rectCenter = {W / 2.0f, H / 2.0f};
    bool dark = false;

    while (!WindowShouldClose()) {
        // --- Update ---
        angle += 90.0f * GetFrameTime();     // degrees per second
        if (IsKeyPressed(KEY_SPACE)) dark = !dark;

        // --- Draw ---
        BeginDrawing();
        ClearBackground(dark ? BLACK : RAYWHITE);

        Color ink = dark ? RAYWHITE : BLACK;
        DrawText("raylib is working ✅", 20, 20, 22, ink);
        DrawText("Mouse = circle; SPACE = dark mode; ESC = quit", 20, 48, 20, ink);

        // circle follows mouse
        DrawCircleV(GetMousePosition(), 20.0f, SKYBLUE);

        // rotating rectangle about its center
        Rectangle r = {rectCenter.x - rectSize.x / 2.0f,
                       rectCenter.y - rectSize.y / 2.0f,
                       rectSize.x, rectSize.y};
        DrawRectanglePro(r, {rectSize.x / 2.0f, rectSize.y / 2.0f}, angle, ORANGE);

        DrawFPS(W - 90, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
