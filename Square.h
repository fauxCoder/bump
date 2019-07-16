#pragma once

#include <Curie/RM.h>

struct Square
{
    static void load(RM& a_RM)
    {
        s_me = a_RM.AddImage("content/card.png");
    }

    static uint32_t s_me;

    Square(RM& a_RM);

    void x(int32_t a_d) { m_x += a_d; }
    void y(int32_t a_d) { m_y += a_d; }

    void write();

    RM& m_RM;
    RM::Entry m_me;
    int32_t m_x;
    int32_t m_y;
};
