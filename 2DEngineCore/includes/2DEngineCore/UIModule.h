#ifndef UIMODULE_H
#define UIMODULE_H

#include <raylib.h>
#include <imgui.h>
#include <vector>
#include <string>
#include <2DEngineCore\Tile.h>

struct TileSet
{
    Texture2D texture;
    int rows;
    int cols;
};

void DrawTileSetMenu(std::vector<TileSet>& tileSets, bool& tileSetLoaded, Tile& selectedTile, int& selectedTileIndex, int tileSize);

#endif // UIMODULE_H