#include <Square.h>

uint32_t Square::s_me;

Square::Square(RM& a_RM)
: m_RM(a_RM)
, m_me(m_RM.Add(10))
, m_x(10)
, m_y(10)
{
}

void Square::write()
{
    m_me.write(s_me, m_x, m_y);
}
