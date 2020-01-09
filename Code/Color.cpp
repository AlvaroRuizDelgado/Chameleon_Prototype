#include "Color.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>

Color::Color(int r, int g, int b) :
    m_rgbFloat{ 0.f, 0.f, 0.f }
    , m_rgbInt { 0, 0, 0 }
{
    this->SetRgb(r, g, b);
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
        }
        //this->SetRgb(m_rgbFloat[0], m_rgbFloat[1], m_rgbFloat[2]);
    }
    // DEBUG
//    std::cout << "- Target  : " << m_targetColorF[0] << " " << m_targetColorF[1] << " " << m_targetColorF[2] << std::endl;
//    std::cout << "- Current : " << m_bgColorF[0] << " " << m_bgColorF[1] << " " << m_bgColorF[2] << std::endl;
    return false;
}

// https://en.wikipedia.org/wiki/HSL_and_HSV
void Color::UpdateHsvFromRgb()
{
    const float MAX = std::max({ m_rgbFloat[0], m_rgbFloat[1], m_rgbFloat[2] });
    const float MIN = std::min({ m_rgbFloat[0], m_rgbFloat[1], m_rgbFloat[2] });

    // ** HUE **
    if (MAX == MIN)
    {
        m_hue = 0;
    }
    else if (MAX == m_rgbFloat[0])
    {
        m_hue = 60.f/360.f * (0 + (m_rgbFloat[1] - m_rgbFloat[2]) / (MAX - MIN));
    }
    else if (MAX == m_rgbFloat[1])
    {
        m_hue = 60.f/360.f * (2 + (m_rgbFloat[2] - m_rgbFloat[0]) / (MAX - MIN));
    }
    else if (MAX == m_rgbFloat[2])
    {
        m_hue = 60.f/360.f * (4 + (m_rgbFloat[0] - m_rgbFloat[1]) / (MAX - MIN));
    }
    if (m_hue < 0)
    {
        m_hue += 360.f / 360.f;
    }

    // ** SATURATION **
    if (0 == MAX)
    {
        m_saturation = 0;
    }
    else
    {
        m_saturation = (MAX - MIN) / MAX;
    }

    // ** BRIGHTNESS **
    m_brightness = MAX;

    // ** LUMINOSITY **
    //m_luminosity = (MAX + MIN) / 2.f;
}

void Color::UpdateRgbFromHsv()
{
    this->SetRgb(this->HsvToRgb(5.f), this->HsvToRgb(3.f), this->HsvToRgb(1.f));
}

// https://en.wikipedia.org/wiki/HSL_and_HSV
float Color::HsvToRgb(float n)
{
    float k = std::fmod(n + m_hue * 6.f, 6);
    float result = m_brightness - m_brightness * m_saturation * std::max(std::min({ k, 4 - k, 1.f }), 0.f);
    return result;
}

void Color::SetHue(float newHue)
{
    m_hue = newHue;
    this->UpdateRgbFromHsv();
}

void Color::SetSaturation(float newSat)
{
    m_saturation = newSat;
    this->UpdateRgbFromHsv();
}

void Color::SetBrightness(float newBright)
{
    m_brightness = newBright;
    this->UpdateRgbFromHsv();
}

std::wstring Color::GetHexa() const
{
    std::wstringstream wstream;
    for (int channel : m_rgbInt)
    {
        wstream << std::uppercase << std::setfill(L'0') << std::setw(2) << std::hex << channel;
    }
    return wstream.str();
}

void Color::SetRgb (int r, int g, int b)
{
    m_rgbInt[0] = r;
    m_rgbInt[1] = g;
    m_rgbInt[2] = b;
    for (int i = 0; i < NUM_CHANNELS; ++i)
    {
        m_rgbFloat[i] = this->IntToFloat(m_rgbInt[i]);
    }
    this->UpdateHsvFromRgb();
}

void Color::SetRgb (float r, float g, float b)
{
    m_rgbFloat[0] = r;
    m_rgbFloat[1] = g;
    m_rgbFloat[2] = b;
    for (int i = 0; i < NUM_CHANNELS; ++i)
    {
        m_rgbInt[i] = this->FloatToInt(m_rgbFloat[i]);
    }
    //this->UpdateHsvFromRgb();
}

void Color::SetColor (Color newColor)
{
    this->SetRgb(newColor.R(), newColor.G(), newColor.B());
}

constexpr int Color::WHITE[3];
constexpr int Color::BLACK[3];
constexpr int Color::GREEN[3];
constexpr int Color::RED[3];
constexpr int Color::BLUE[3];
constexpr int Color::YELLOW[3];
