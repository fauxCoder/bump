#pragma once

#include <Curie/RM.h>
#include <Curie/SB.h>

struct Square
{
    static uint32_t s_me;
    static uint32_t s_tail;

    static void load(RM& a_RM)
    {
        s_me = a_RM.AddImage("content/card.png");
        s_tail = a_RM.AddImage("content/tail.png");
    }

    static std::set<SDL_Keycode> keys_down()
    {
        return {
            SDLK_LEFT,
            SDLK_RIGHT,
            SDLK_UP,
            SDLK_DOWN,
        };
    }

    static std::set<SDL_Keycode> keys_up()
    {
        return {
            SDLK_LEFT,
            SDLK_RIGHT,
            SDLK_UP,
            SDLK_DOWN,
        };
    }

    Square(RM&);

    ~Square();

    void write();

    bool key_down(SDL_Keycode);

    bool key_up(SDL_Keycode);

    void speak(SB::working_t*, size_t);

    RM& m_RM;
    RM::Entry m_entry;
    RM::Entry m_tail;
    int32_t m_x;
    int32_t m_y;
    int32_t m_vx;
    int32_t m_vy;

    uint32_t m_voice;
    double m_voice_x;
    double m_voice_y;
};
