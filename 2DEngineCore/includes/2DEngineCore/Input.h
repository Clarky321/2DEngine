#ifndef INPUT_H
#define INPUT_H

#include <2DEngineCore\TileMap.h>

void HandleTilePlacement(TileMap& map, bool tilesetLoaded, int selectedTileIndex, const Tile& selectedTile, Vector2 tilePosition, int gridWidth, int gridHeight);

#endif // INPUT_H