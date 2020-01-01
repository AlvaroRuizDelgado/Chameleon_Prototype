#include "Resolution.h"

Resolution::Resolution(int width, int height)
{
    Init(width, height);
}

void Resolution::Init (int width, int height)
{
    m_resWidth = width;
    m_resHeight = height;
};

int Resolution::m_resWidth;
int Resolution::m_resHeight;
