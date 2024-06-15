#include <2DEngineCore\UIModule.h>
#include <tinyfiledialogs.h>

void DrawTileSetMenu(std::vector<TileSet>& tileSets, bool& tileSetLoaded, Tile& selectedTile, int& selectedTileIndex, int tileSize) {
    static int currentTab = 0;

    ImGui::Begin("TileSet Menu");
    if (ImGui::Button("Load TileSet")) {
        const char* lFilterPatterns[2] = { "*.png", "*.jpg" };
        const char* filename = tinyfd_openFileDialog("Load TileSet", "", 2, lFilterPatterns, NULL, 0);
        if (filename) {
            TileSet newTileSet;
            newTileSet.texture = LoadTexture(filename);
            if (newTileSet.texture.id != 0) {
                tileSetLoaded = true;
                newTileSet.cols = newTileSet.texture.width / tileSize;
                newTileSet.rows = newTileSet.texture.height / tileSize;
                tileSets.push_back(newTileSet);
                currentTab = tileSets.size() - 1; // Переключение на новую вкладку
            }
            else {
                tileSetLoaded = false;
                TraceLog(LOG_ERROR, "Failed to load tileset texture.");
            }
        }
    }

    if (!tileSets.empty()) {
        ImGui::BeginTabBar("TileSets");
        for (int i = 0; i < tileSets.size(); ++i) {
            std::string tabLabel = "TileSet " + std::to_string(i + 1);
            if (ImGui::BeginTabItem(tabLabel.c_str())) {
                currentTab = i;
                ImGui::EndTabItem();
            }
        }
        ImGui::EndTabBar();

        TileSet& currentTileSet = tileSets[currentTab];
        ImGui::Text("Select a tile:");
        for (int i = 0; i < currentTileSet.rows; i++) {
            for (int j = 0; j < currentTileSet.cols; j++) {
                ImVec2 uv0 = ImVec2((float)j * tileSize / currentTileSet.texture.width, (float)i * tileSize / currentTileSet.texture.height);
                ImVec2 uv1 = ImVec2((float)(j + 1) * tileSize / currentTileSet.texture.width, (float)(i + 1) * tileSize / currentTileSet.texture.height);
                ImGui::PushID(i * currentTileSet.cols + j);
                if (ImGui::ImageButton((void*)(intptr_t)currentTileSet.texture.id, ImVec2((float)tileSize, (float)tileSize), uv0, uv1)) {
                    selectedTile.texture = currentTileSet.texture;
                    selectedTile.sourceRec = { (float)(j * tileSize), (float)(i * tileSize), (float)tileSize, (float)tileSize };
                    selectedTileIndex = i * currentTileSet.cols + j;
                }
                if (selectedTileIndex == i * currentTileSet.cols + j) {
                    ImGui::GetWindowDrawList()->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255, 255, 0, 255));
                }
                ImGui::PopID();
                ImGui::SameLine();
            }
            ImGui::NewLine();
        }
    }
    ImGui::End();
}