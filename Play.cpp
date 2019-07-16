#include <Play.h>
#include <Square.h>

#include <Curie/Input.h>
#include <Curie/Quartz.h>
#include <Curie/RM.h>
#include <Curie/SB.h>
#include <Curie/SH.h>

#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

Play::Play(Quartz& a_Q, RM& a_RM, SB& a_SB)
: m_Q(a_Q)
, m_RM(a_RM)
, m_SB(a_SB)
{
    m_Bump = m_SB.AddSound(m_SB.SForF(5.0), [&](uint32_t t, uint32_t l, SB::working_t& out)
    {
        out = SH(t, l)
            .Sin(9.0)
            .Scale(0.9)
            .Envelope(m_SB.SForF(0.75), m_SB.SForF(0.6), 0.3, m_SB.SForF(0.75))
            .Done();
    });
}

void Play::Run()
{
    Square::load(m_RM);

    bool exit = false;
    while ( ! exit)
    {
        Square s(m_RM);

        Input in(m_Q);
        in.m_KeyDownResponses[{SDLK_LEFT, SDLK_RIGHT, SDLK_UP, SDLK_DOWN}] = [&](SDL_Keycode a_Key)
        {
            static const int32_t speed = 7;

            switch (a_Key)
            {
            case SDLK_LEFT:
                s.x(-speed);
                break;
            case SDLK_RIGHT:
                s.x(speed);
                break;
            case SDLK_UP:
                s.y(-speed);
                break;
            case SDLK_DOWN:
                s.y(speed);
            default:
                break;
            }
            return false;
        };
        in.m_KeyDownResponses[{SDLK_RETURN}] = [](SDL_Keycode a_Key)
        {
            return true;
        };
        in.m_KeyDownResponses[{SDLK_ESCAPE}] = [&](SDL_Keycode a_Key)
        {
            exit = true;
            return exit;
        };

        in.Enter([&]()
        {
            s.write();
        });

    }

    m_Q.Tooth();
}
