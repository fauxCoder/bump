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

#include <cstdlib>

Play::Play(Quartz& a_Q, RM& a_RM, SB& a_SB)
: m_Q(a_Q)
, m_RM(a_RM)
, m_SB(a_SB)
{
    m_Bump = m_SB.CreateSound(m_SB.SForF(12.0), 1,
    [&](uint32_t t, uint32_t l, std::vector<std::array<SB::working_t, SB::s_chunk>>& out, size_t offset)
    {
        SB::working_t left = SH(t, l)
            .Sin(12.0)
            .Scale(0.75)
            .Envelope(m_SB.SForF(0.75), m_SB.SForF(0.6), 0.3, m_SB.SForF(0.75))
            .Done();

        out[0][offset] = left;
    });

    m_Stereo = m_SB.CreateSound(m_SB.SForF(12.0), 2,
    [&](uint32_t t, uint32_t l, std::vector<std::array<SB::working_t, SB::s_chunk>>& out, size_t offset)
    {
        SB::working_t left = SH(t, l)
            .Sin(12.0)
            .Scale(0.8)
            .Envelope(m_SB.SForF(0.5), m_SB.SForF(0.6), 0.3, m_SB.SForF(0.75))
            .Done();

        SB::working_t right = SH(t, l)
            .Sin(18.0)
            .Scale(0.4)
            .Envelope(m_SB.SForF(0.5), m_SB.SForF(0.6), 0.3, m_SB.SForF(0.75))
            .Done();

        out[0][offset] = left;
        out[1][offset] = right;
    });
}

void Play::Run()
{
    Square::load(m_RM);

    Square s(m_RM);
    m_SB.AddSource(std::bind(&Square::speak, &s, std::placeholders::_1, std::placeholders::_2));

    bool exit = false;
    while ( ! exit)
    {
        Input in;
        in.link(s);

        in.m_KeyDownResponses[Catch({SDLK_a})] = [&](SDL_Keycode a_key)
        {
            m_SB.PlaySound(m_Bump);
            return false;
        };
        in.m_KeyDownResponses[Catch({SDLK_o})] = [&](SDL_Keycode a_key)
        {
            m_SB.PlaySound(m_Stereo);
            return false;
        };
        in.m_KeyDownResponses[Catch({SDLK_RETURN})] = [](SDL_Keycode a_key)
        {
            return true;
        };
        in.m_KeyDownResponses[Catch({SDLK_ESCAPE})] = [&](SDL_Keycode a_key)
        {
            exit = true;
            return exit;
        };

        in.open([&]()
        {
            s.write();
            m_Q.Tooth();
        });
    }

    m_Q.Tooth();
}
