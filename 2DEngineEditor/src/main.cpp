#include <raylib.h>
#include <raymath.h>
#include <imgui.h>

#include <backends/imgui_impl_opengl3.h>
#include <imgui_impl_raylib.h>

#include <2DEngineCore\Tile.h>
#include <2DEngineCore\TileMap.h>
#include <2DEngineCore\Camera.h>
#include <2DEngineCore\UIModule.h>
#include <2DEngineCore\Input.h>

const int screenWidth = 1200;
const int screenHeight = 800;
const int tileSize = 32;
const int gridWidth = 32;
const int gridHeight = 32;

int main()
{
    InitWindow(screenWidth, screenHeight, "2D Top-Down Engine");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    TileMap map(gridWidth, gridHeight, tileSize);

    Texture2D tileset = { 0 };
    bool tilesetLoaded = false;
    int tilesetRows, tilesetCols;
    Tile selectedTile;

    Camera2D camera = InitCamera();

    SetTargetFPS(60);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplRaylib_Init();
    ImGui_ImplOpenGL3_Init();

    int selectedTileIndex = -1;

    while (!WindowShouldClose())
    {
        ImGui_ImplRaylib_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        UpdateCamera(camera);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode2D(camera);
        map.Draw();

        Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), camera);
        Vector2 tilePosition = { floor(mousePosition.x / tileSize), floor(mousePosition.y / tileSize) };

        DrawRectangleLines(tilePosition.x * tileSize, tilePosition.y * tileSize, tileSize, tileSize, RED);

        EndMode2D();

        DrawTilesetMenu(tileset, tilesetLoaded, tilesetRows, tilesetCols, selectedTile, selectedTileIndex, tileSize);

        HandleTilePlacement(map, tilesetLoaded, selectedTileIndex, selectedTile, tilePosition, gridWidth, gridHeight);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        EndDrawing();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplRaylib_Shutdown();
    ImGui::DestroyContext();

    if (tilesetLoaded)
    {
        UnloadTexture(tileset);
    }

    CloseWindow();

    return 0;
}