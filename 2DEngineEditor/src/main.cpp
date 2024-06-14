//#include <raylib.h>
//#include <raymath.h>
//#include <imgui.h>

#include <backends/imgui_impl_opengl3.h>
#include <imgui_impl_raylib.h>

int main() {

    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Farish Engine");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    SetTargetFPS(60);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplRaylib_Init();
    ImGui_ImplOpenGL3_Init();

    while (!WindowShouldClose())
    {
        ImGui_ImplRaylib_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Test");
        ImGui::End();

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Render ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        EndDrawing();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplRaylib_Shutdown();
    ImGui::DestroyContext();

    CloseWindow();

    return 0;
}