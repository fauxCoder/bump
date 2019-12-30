#include <Square.h>

#include <Curie/SH.h>

uint32_t Square::s_me;
uint32_t Square::s_tail;

Square::Square(RM& a_RM)
: m_RM(a_RM)
, m_entry(m_RM.Add(10))
, m_tail(m_RM.Add(5))
, m_x(10)
, m_y(10)
, m_vx(0)
, m_vy(0)
, m_voice(0)
, m_voice_x(0.0)
, m_voice_y(0.0)
{
}

Square::~Square()
{
    m_RM.Remove(m_entry);
}

void Square::write()
{
    auto vx = m_vx * 7;
    auto vy = m_vy * 7;

    if (vx != 0 && vy != 0)
    {
        // 99/73 approximates the
        // square root of 2
        vx *= 73;
        vx /= 99;
        vy *= 73;
        vy /= 99;
    }

    m_x += vx;
    m_y += vy;

    m_entry.write(s_me, m_x, m_y);
    m_tail.write(s_tail, m_voice_x, m_voice_y);
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

void Square::speak(SB::working_t* samples, size_t count)
{
    static Wave wave_l;
    static Wave wave_r;

    if (m_x > (int32_t)m_voice_x)
    {
        m_voice_x += 0.8;
    }
    else if (m_x < (int32_t)m_voice_x)
    {
        m_voice_x -= 0.8;
    }

    if (m_y > m_voice_y)
        m_voice_y += 0.1;
    else if (m_y < m_voice_y)
        m_voice_y -= 0.1;

    for (uint32_t i = 0; i < count; i += 2)
    {
        wave_l.pending_divisor = std::max(m_voice_x / 15.0, 2.0);
        SB::working_t left = SH(m_voice, 0)
            .wave(wave_l)
            .scale(std::min(std::abs(m_voice_y / 300.0), 0.75))
            ();

        wave_r.pending_divisor = std::max(m_voice_x / 13.0, 6.0);
        SB::working_t right = SH(m_voice++, 0)
            .wave(wave_r)
            .scale(std::min(std::abs(m_voice_y / 300.0), 0.75))
            ();

        SB::combine(samples[i], left);
        SB::combine(samples[i+1], right);
    }
}
