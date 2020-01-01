#pragma once

class Resolution
{
public:
    Resolution(int width, int height);
    
    static void Init (int width, int height);
    
    static int Width() { return m_resWidth; };
    static int Height() { return m_resHeight; };
    
private:
    static int m_resWidth;
    static int m_resHeight;
};
