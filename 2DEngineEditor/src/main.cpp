#include <raylib.h>
#include <raymath.h>
#include <imgui.h>

#include <backends/imgui_impl_opengl3.h>
#include <imgui_impl_raylib.h>
#include <tinyfiledialogs.h>

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

bool showGrid = true;  // Переменная для включения/отключения сетки

void DrawGrid(int width, int height, int tileSize)
{
    for (int x = 0; x < width * tileSize; x += tileSize)
    {
        for (int y = 0; y < height * tileSize; y += tileSize)
        {
            DrawRectangleLines(x, y, tileSize, tileSize, LIGHTGRAY);
        }
    }
}

void DrawInterface(bool& showGrid)
{
    ImGui::Begin("Settings");
    ImGui::Checkbox("Show Grid", &showGrid);  // Добавляем чекбокс для включения/отключения сетки
    ImGui::End();
}

int main()
{
    InitWindow(screenWidth, screenHeight, "2D Top-Down Engine");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    TileMap map(gridWidth, gridHeight, tileSize);

    std::vector<TileSet> tileSets;
    bool tileSetLoaded = false;
    Tile selectedTile;
    int selectedTileIndex = -1;

    Camera2D camera = InitCamera();

    SetTargetFPS(60);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplRaylib_Init();
    ImGui_ImplOpenGL3_Init();

    bool showGrid = true;

    while (!WindowShouldClose()) {
        ImGui_ImplRaylib_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        UpdateCamera(camera);

        if (IsKeyPressed(KEY_G)) {
            showGrid = !showGrid;
        }

        // Добавляем интерфейс
        DrawInterface(showGrid);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode2D(camera);

        if (showGrid) {
            DrawGrid(gridWidth, gridHeight, tileSize);
        }

        map.Draw();

        Vector2 mousePosition = GetScreenToWorld2D(GetMousePosition(), camera);
        Vector2 tilePosition = { floor(mousePosition.x / tileSize), floor(mousePosition.y / tileSize) };

        DrawRectangleLines(tilePosition.x * tileSize, tilePosition.y * tileSize, tileSize, tileSize, RED);

        EndMode2D();

        DrawTileSetMenu(tileSets, tileSetLoaded, selectedTile, selectedTileIndex, tileSize);

        HandleTilePlacement(map, tileSetLoaded, selectedTileIndex, selectedTile, tilePosition, gridWidth, gridHeight);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        EndDrawing();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplRaylib_Shutdown();
    ImGui::DestroyContext();

    for (auto& tileSet : tileSets)
    {
        UnloadTexture(tileSet.texture);
    }

    CloseWindow();

    return 0;
}