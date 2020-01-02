#include "Color.h"

Color::Color()
{
}

//void Color::MorphInto(sf::Color targetColor, float changeBudget)
//{
//
//}

//sf::Color Color::FloatToRgb(float color[]) const
//{
//
//}


sf::Color Color::FloatToRgb(float color[]) const
{
    sf::Color rgbColor;

    rgbColor.r = static_cast<unsigned int>(color[0] * 255.f);
    rgbColor.g = static_cast<unsigned int>(color[1] * 255.f);
    rgbColor.b = static_cast<unsigned int>(color[2] * 255.f);

    return rgbColor;
}

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
//
//void Color::SetRgb (sf::Color newColor)
//{
//
//}
//
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
