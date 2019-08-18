#pragma once

#include <Curie/RM.h>

struct Square
{
    static void load(RM& a_RM)
    {
        s_me = a_RM.AddImage("content/card.png");
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

    static uint32_t s_me;

    Square(RM& a_RM);

    void write();

    bool key_down(SDL_Keycode);

    bool key_up(SDL_Keycode);

    RM& m_RM;
    RM::Entry m_entry;
    int32_t m_x;
    int32_t m_y;
    int32_t m_vx;
    int32_t m_vy;
};
