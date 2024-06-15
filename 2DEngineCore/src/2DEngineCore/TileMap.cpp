#include <2DEngineCore\TileMap.h>

TileMap::TileMap(int width, int height, int tileSize)
    : width(width), height(height), tileSize(tileSize)
{
    tileMap.resize(width, std::vector<std::vector<Tile>>(height));
}

TileMap::~TileMap() {}

void TileMap::Draw()
{
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            for (const Tile& tile : tileMap[x][y])
            {
                if (tile.texture.id != 0)
                {
                    DrawTextureRec(tile.texture, tile.sourceRec, tile.position, WHITE);
                }
            }
        }
    }
}

void TileMap::PlaceTile(int x, int y, const Tile& tile)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        tileMap[x][y].push_back(tile);
        tileMap[x][y].back().position = { static_cast<float>(x * tileSize), static_cast<float>(y * tileSize) };
    }
}

void TileMap::RemoveTile(int x, int y)
{
    if (x >= 0 && x < width && y >= 0 && y < height && !tileMap[x][y].empty())
    {
        tileMap[x][y].pop_back();  // Удаление последнего добавленного тайла
    }
}

int TileMap::GetWidth() const { return width; }

int TileMap::GetHeight() const { return height; }

std::vector<std::vector<std::vector<Tile>>>& TileMap::GetTileMap() { return tileMap; }