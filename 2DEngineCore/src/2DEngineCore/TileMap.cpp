#include <2DEngineCore\TileMap.h>

TileMap::TileMap(int width, int height, int tileSize)
    : width(width), height(height), tileSize(tileSize)
{
    tileMap.resize(width, std::vector<Tile>(height));
}

TileMap::~TileMap() {}

void TileMap::Draw()
{
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            if (tileMap[x][y].texture.id != 0)
            {
                DrawTextureRec(tileMap[x][y].texture, tileMap[x][y].sourceRec, tileMap[x][y].position, WHITE);
            }
        }
    }
}

void TileMap::PlaceTile(int x, int y, const Tile& tile)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        tileMap[x][y] = tile;
        tileMap[x][y].position = { static_cast<float>(x * tileSize), static_cast<float>(y * tileSize) };
    }
}

void TileMap::RemoveTile(int x, int y)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        tileMap[x][y] = Tile();  // Reset to default value
    }
}

int TileMap::GetWidth() const { return width; }

int TileMap::GetHeight() const { return height; }

std::vector<std::vector<Tile>>& TileMap::GetTileMap() { return tileMap; }