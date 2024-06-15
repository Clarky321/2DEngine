#include <2DEngineCore\Input.h>
#include <raylib.h>

void HandleTilePlacement(TileMap& map, bool tilesetLoaded, int selectedTileIndex, const Tile& selectedTile, Vector2 tilePosition, int gridWidth, int gridHeight)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && tilesetLoaded && selectedTileIndex != -1)
    {
        int gridX = static_cast<int>(tilePosition.x);
        int gridY = static_cast<int>(tilePosition.y);
        if (gridX >= 0 && gridX < gridWidth && gridY >= 0 && gridY < gridHeight)
        {
            map.PlaceTile(gridX, gridY, selectedTile);
        }
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        int gridX = static_cast<int>(tilePosition.x);
        int gridY = static_cast<int>(tilePosition.y);
        if (gridX >= 0 && gridX < gridWidth && gridY >= 0 && gridY < gridHeight)
        {
            map.RemoveTile(gridX, gridY);
        }
    }
}