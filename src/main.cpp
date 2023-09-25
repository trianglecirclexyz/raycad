#include <iostream>
#include <cmath>
#include <thread>
#include <raylib-cpp.hpp>

int screen_w = 2 * 800;
int screen_h = 2 * 450;
raylib::Window window(screen_w, screen_h, "raylib [core] example - basic window");

raylib::Font font("res/fonts/Hack-Regular.ttf", 20);
raylib::Color text_colour = raylib::Color::White();

raylib::Color background(0, 0, 20, 0);

int main() {
    // Create a 2D camera
    raylib::Camera2D cam;
    cam.target = raylib::Vector2(static_cast<float>(screen_w) / 2, static_cast<float>(screen_h) / 2);
    cam.offset = raylib::Vector2(static_cast<float>(screen_w) / 2, static_cast<float>(screen_h) / 2);
    cam.rotation = 0.0f;
    cam.zoom = 1.0f;

    bool isMiddleMouseButtonDown = false;
    raylib::Vector2 lastMousePosition;

    while (!window.ShouldClose()) {
        double dt = GetFrameTime();

        // Input Handling
        raylib::Vector2 mouse_pos(
            static_cast<float>(raylib::Mouse::GetX()),
            static_cast<float>(raylib::Mouse::GetY()));

        raylib::Vector2 adj_mouse_pos(
            (1 / cam.zoom) * (mouse_pos.x - cam.offset.x) + cam.target.x,
            (1 / cam.zoom) * (mouse_pos.y - cam.offset.y) + cam.target.y);

        if (raylib::Mouse::IsButtonDown(MOUSE_LEFT_BUTTON)) {
        }
        if (raylib::Mouse::IsButtonDown(MOUSE_RIGHT_BUTTON)) {
        }

        // Middle mouse button panning
        if (raylib::Mouse::IsButtonDown(MOUSE_MIDDLE_BUTTON)) {
            if (!isMiddleMouseButtonDown) {
                lastMousePosition = mouse_pos;
                isMiddleMouseButtonDown = true;
            } else {
                raylib::Vector2 currentMousePosition = mouse_pos;
                raylib::Vector2 mouseDelta = currentMousePosition - lastMousePosition;
                cam.target.x -= (1 / cam.zoom) * mouseDelta.x;
                cam.target.y -= (1 / cam.zoom) * mouseDelta.y;

                lastMousePosition = currentMousePosition;
            }
        } else {
            isMiddleMouseButtonDown = false;
        }

        // Scroll to zoom in and out
        float zoom_speed = 0.075f;
        cam.zoom += zoom_speed * raylib::Mouse::GetWheelMove() * cam.zoom;

        // Rendering
        BeginDrawing();
        {
            window.ClearBackground(background);

            cam.BeginMode();
            {
                int radius = 50;
                Color color = RED;
                DrawCircle(0, 0, radius, color);
            }
            cam.EndMode();

            // Draw FPS
            std::string fps_text = "FPS: " + std::to_string(window.GetFPS());
            text_colour.DrawText(font, fps_text.c_str(), {10, 10}, 20, 0);

        }
        EndDrawing();
    }

    return 0;
}
