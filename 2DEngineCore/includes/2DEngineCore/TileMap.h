#ifndef TILEMAP_H
#define TILEMAP_H

#include <raylib.h>
#include <vector>
#include <2DEngineCore\Tile.h>

class TileMap
{
public:
    TileMap(int width, int height, int tileSize);
    ~TileMap();

    void Draw();
    void PlaceTile(int x, int y, const Tile& tile);
    void RemoveTile(int x, int y);

    int GetWidth() const;
    int GetHeight() const;
    std::vector<std::vector<std::vector<Tile>>>& GetTileMap();

private:
    int width;
    int height;
    int tileSize;
    std::vector<std::vector<std::vector<Tile>>> tileMap;
};

#endif // TILEMAP_H