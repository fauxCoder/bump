#include <Square.h>

uint32_t Square::s_me;

Square::Square(RM& a_RM)
: m_RM(a_RM)
, m_me(m_RM.Add(10))
, m_x(10)
, m_y(10)
, m_vx(0)
, m_vy(0)
{
}

void Square::write()
{
    auto vx = m_vx * 7;
    auto vy = m_vy * 7;

    m_x += vx;
    m_y += vy;

    m_me.write(s_me, m_x, m_y);
}

bool Square::key_down(SDL_Keycode a_key)
{
    switch(a_key)
    {
    case SDLK_LEFT:
        m_vx = -1;
        break;
    case SDLK_RIGHT:
        m_vx = 1;
        break;
    case SDLK_UP:
        m_vy = -1;
        break;
    case SDLK_DOWN:
        m_vy = 1;
        break;
    default:
        break;
    }

    return false;
}

bool Square::key_up(SDL_Keycode a_key)
{
    switch(a_key)
    {
    case SDLK_LEFT:
        if (m_vx == -1) m_vx = 0;
        break;
    case SDLK_RIGHT:
        if (m_vx == 1) m_vx = 0;
        break;
    case SDLK_UP:
        if (m_vy == -1) m_vy = 0;
        break;
    case SDLK_DOWN:
        if (m_vy == 1) m_vy = 0;
        break;
    default:
        break;
    }

    return false;
}
