#include "Color.h"

#include <iostream>
#include <cmath>

Color::Color() :
    m_rgbFloat{ 0.f, 0.f, 0.f }
    , m_rgbInt { 0, 0, 0 }
{
}

bool Color::MorphInto(int targetColor[], float changeBudget)
{
    float colorDiff[3]{ 0.f };
    float totalDiff{ 0.f };
    for (int i = 0; i < NUM_CHANNELS; ++i)
    {
        colorDiff[i] = this->IntToFloat(targetColor[i]) - m_rgbFloat[i];
        if (0.001 > abs(colorDiff[i]))    // 1/255 = 0.0039
        {
            colorDiff[i] = 0.f;
        }
        totalDiff += abs(colorDiff[i]);
    }
    if (0 == totalDiff)
    {
        return true;
    }
    else
    {
        // DEBUG
//        std::cout << "Total diff: " << totalDiff << std::endl;
        float channelBudget{ 0.f };
        for (int i = 0; i < NUM_CHANNELS; ++i)
        {
            // How much this channel can change this frame
            channelBudget = (colorDiff[i] / totalDiff) * changeBudget;
            // Clamp it to prevent overshooting
            if (abs(channelBudget) > abs(colorDiff[i]))
            {
                channelBudget = colorDiff[i];
            }
            m_rgbFloat[i] += channelBudget;
            m_rgbInt[i] = this->FloatToInt(m_rgbFloat[i]);
            std::cout << "  * Channel " << i << ": " << m_rgbFloat[i] << " to " << m_rgbInt[i] << std::endl;
        }
    }
    // DEBUG
//    std::cout << "- Target  : " << m_targetColorF[0] << " " << m_targetColorF[1] << " " << m_targetColorF[2] << std::endl;
//    std::cout << "- Current : " << m_bgColorF[0] << " " << m_bgColorF[1] << " " << m_bgColorF[2] << std::endl;
    return false;
}

//sf::Color Color::FloatToRgb(float color[]) const
//{
//
//}


//sf::Color Color::FloatToRgb(float color[]) const
//{
//    sf::Color rgbColor;
//
//    rgbColor.r = static_cast<unsigned int>(color[0] * 255.f);
//    rgbColor.g = static_cast<unsigned int>(color[1] * 255.f);
//    rgbColor.b = static_cast<unsigned int>(color[2] * 255.f);
//
//    return rgbColor;
//}

//void Color::UpdateHueFromRgb()
//{
//
//}
//
//void Color::UpdateRgbFromHue()
//{
//
//}
//
//void Color::UpdateHex()
//{
//
//}
//
////    std::string GetHex() const;

void Color::SetRgb (int r, int g, int b)
{
    m_rgbInt[0] = r;
    m_rgbInt[1] = g;
    m_rgbInt[2] = b;
    for (int i = 0; i < NUM_CHANNELS; ++i)
    {
        m_rgbFloat[i] = this->IntToFloat(m_rgbInt[i]);
//        m_rgbFloat[i] = static_cast<float>(m_rgbInt[i]) / 255.f;
    }
}

//void Color::SetHue (float newHue)
//{
//
//}
//
//void Color::SetSaturation (float newSat)
//{
//
//}
//
//void Color::SetBrigthness (float newBright)
//{
//
//}
