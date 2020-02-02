#include <utils.h>

namespace rl {

float distanceSquare(const sf::Vector2f a, const sf::Vector2f b)
{
    return /* sqrt( */pow(a.x - b.x, 2) + pow(a.y - b.y , 2)/* ) */;
}

float randf()
{
    return rand() % 100001 / (float)100000;
}

float randf_range(float lo, float up)
{
    if(lo > up) std::swap(lo, up);
    return lo + (up - lo) * randf();
}

int randi(int lo, int up)
{
    if(lo > up) std::swap(lo, up);
    return rand() % (up - lo + 1) + lo;
}

}