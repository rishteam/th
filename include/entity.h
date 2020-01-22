#pragma once

namespace rl {

class Entity
{
public:
    Entity()
    {
        m_x = m_y = 0.f;
        m_visible = true;
    }

    void setPos(float x, float y)
    {
        m_x = x;
        m_y = y;
    }
private:
    float m_x, m_y;
    float angle, speed;
    bool m_visible;
};

}