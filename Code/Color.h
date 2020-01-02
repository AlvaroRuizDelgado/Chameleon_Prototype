#pragma once

class Color
{
public:
    Color(int r = 0, int g = 0, int b = 0);
    
    bool MorphInto(int targetColor[], float changeBudget);
    
    // Getters / setters
    int* GetRgb() { return m_rgbInt; };
    int R() const { return m_rgbInt[0]; }
    int G() const { return m_rgbInt[1]; }
    int B() const { return m_rgbInt[2]; }
//    std::string GetHex() const;
    float GetHue() const { return m_hue; };
    float GetSaturation() const { return m_saturation; };
    float GetBrightness() const { return m_brightness; };
    
    void SetRgb (int r, int g, int b);
    void SetColor (Color newColor);
    void SetHue (float newHue);
    void SetSaturation (float newSat);
    void SetBrigthness (float newBright);
    
private:
    int FloatToInt(float channel) const { return static_cast<int>(channel*255.f); };
    float IntToFloat(int channel) const { return static_cast<float>(channel)/255.f; };
    void UpdateHueFromRgb();
    void UpdateRgbFromHue();
    void UpdateHex();
    
private:
    float m_rgbFloat[3];
    int m_rgbInt[3];
    float m_hue;
    float m_saturation;
    float m_brightness;
//    std::string m_hex;
    
public:
    static constexpr int WHITE[3] { 0, 0, 0 };
    static constexpr int BLACK[3] { 255, 255, 255 };
    static constexpr int GREEN[3] { 50, 200, 50 };
    static constexpr int RED[3] { 220, 50, 50 };
    static constexpr int BLUE[3] { 20, 80, 220 };
    static constexpr int YELLOW[3] { 240, 240, 20 };
    
    static constexpr int NUM_CHANNELS { 3 };
};
