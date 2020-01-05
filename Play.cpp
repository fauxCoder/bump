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
    double base_freq = 600.0;
    double twelf = std::pow(2.0, 1.0 / 12.0);
    Wave wave;

    wave.tune(base_freq * std::pow(twelf, 40 - 49));
    m_C = m_SB.CreateSound(m_SB.SForF(12.0),
    [&](uint32_t t, uint32_t l, SB::working_t& mono)
    {
        mono = SH(t, l)
            .wave(wave)
            .scale(0.90)
            .envelope(m_SB.SForF(0.25), m_SB.SForF(0.8), 0.4, m_SB.SForF(2.6))
            ();
    });

    wave.tune(base_freq * std::pow(twelf, 41 - 49));
    m_D = m_SB.CreateSound(m_SB.SForF(12.0),
    [&](uint32_t t, uint32_t l, SB::working_t& mono)
    {
        mono = SH(t, l)
            .wave(wave)
            .scale(0.90)
            .envelope(m_SB.SForF(0.25), m_SB.SForF(0.8), 0.4, m_SB.SForF(2.6))
            ();
    });

    wave.tune(base_freq * std::pow(twelf, 42 - 49));
    m_E = m_SB.CreateSound(m_SB.SForF(12.0),
    [&](uint32_t t, uint32_t l, SB::working_t& mono)
    {
        mono = SH(t, l)
            .wave(wave)
            .scale(0.90)
            .envelope(m_SB.SForF(0.25), m_SB.SForF(0.8), 0.4, m_SB.SForF(2.6))
            ();
    });

    m_Stereo = m_SB.CreateSound(m_SB.SForF(12.0),
    [&](uint32_t t, uint32_t l, SB::working_t& left, SB::working_t& right)
    {
        static Wave wl;
        wl.tune(420.0);
        left = SH(t, l)
            .wave(wl)
            .scale(0.8)
            .envelope(m_SB.SForF(0.5), m_SB.SForF(0.6), 0.3, m_SB.SForF(0.75))
            ();

        static Wave wr;
        wr.tune(480.0);
        right = SH(t, l)
            .wave(wr)
            .scale(0.4)
            .envelope(m_SB.SForF(0.5), m_SB.SForF(0.6), 0.3, m_SB.SForF(0.75))
            ();
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
            m_SB.PlaySound(m_C);
            return false;
        };
        in.m_KeyDownResponses[Catch({SDLK_o})] = [&](SDL_Keycode a_key)
        {
            m_SB.PlaySound(m_D);
            return false;
        };
        in.m_KeyDownResponses[Catch({SDLK_e})] = [&](SDL_Keycode a_key)
        {
            m_SB.PlaySound(m_E);
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
            m_Q.tooth();
        });
    }

    m_Q.tooth();
}
