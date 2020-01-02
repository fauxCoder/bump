#pragma once

#include <cstdint>
#include <vector>

struct Quartz;
struct RM;
struct SB;

struct Play
{
    Play(Quartz& a_Q, RM& a_RM, SB& a_SB);

    ~Play()
    {
    }

    void Run();

    Quartz& m_Q;

    RM& m_RM;

    SB& m_SB;

    uint32_t m_Bump;
    uint32_t m_Stereo;

    uint32_t m_C;
    uint32_t m_D;
    uint32_t m_E;
    uint32_t m_F;
    uint32_t m_G;
    uint32_t m_A;
    uint32_t m_B;
};
