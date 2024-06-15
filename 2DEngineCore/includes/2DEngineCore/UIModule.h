#ifndef UIMODULE_H
#define UIMODULE_H

#include <raylib.h>
#include <imgui.h>
#include <2DEngineCore\Tile.h>

void DrawTilesetMenu(Texture2D& tileset, bool& tilesetLoaded, int& tilesetRows, int& tilesetCols, Tile& selectedTile, int& selectedTileIndex, int tileSize);

#endif // UIMODULE_H