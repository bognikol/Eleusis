#include "RgbaColor.h"

using namespace Eleusis;

RgbaColor::RgbaColor() 
{
    _setColorChannelValue(_R, 0.0, false);
    _setColorChannelValue(_G, 0.0, false);
    _setColorChannelValue(_B, 0.0, false);
    _setColorChannelValue(_A, 1.0, false);
}

RgbaColor::RgbaColor(double R, double G, double B) 
{ 
    _setColorChannelValue(_R, R,   false); 
    _setColorChannelValue(_G, G,   false);
    _setColorChannelValue(_B, B,   false);
    _setColorChannelValue(_A, 1.0, false);
}

RgbaColor::RgbaColor(double R, double G, double B, double A)
{ 
    _setColorChannelValue(_R, R, false);
    _setColorChannelValue(_G, G, false);
    _setColorChannelValue(_B, B, false);
    _setColorChannelValue(_A, A, false);
}

RgbaColor::RgbaColor(int R, int G, int B)       
{ 
    _setColorChannelValue(_R, R, BitEncoding::Bit8, false);
    _setColorChannelValue(_G, G, BitEncoding::Bit8, false);
    _setColorChannelValue(_B, B, BitEncoding::Bit8, false);
    _setColorChannelValue(_A, 255, BitEncoding::Bit8, false);
}

RgbaColor::RgbaColor(int R, int G, int B, int A)
{ 
    _setColorChannelValue(_R, R, BitEncoding::Bit8, false);
    _setColorChannelValue(_G, G, BitEncoding::Bit8, false);
    _setColorChannelValue(_B, B, BitEncoding::Bit8, false);
    _setColorChannelValue(_A, A, BitEncoding::Bit8, false);
}

RgbaColor::RgbaColor(int32_t hexadecimalColorRepresntation)
{
    uint8_t R = (hexadecimalColorRepresntation >> 24) & 0xFF;
    uint8_t G = (hexadecimalColorRepresntation >> 16) & 0xFF;
    uint8_t B = (hexadecimalColorRepresntation >> 8)  & 0xFF;
    uint8_t A =  hexadecimalColorRepresntation        & 0xFF;

    _setColorChannelValue(_R, R, BitEncoding::Bit8, false);
    _setColorChannelValue(_G, G, BitEncoding::Bit8, false);
    _setColorChannelValue(_B, B, BitEncoding::Bit8, false);
    _setColorChannelValue(_A, A, BitEncoding::Bit8, false);
}

void RgbaColor::operator = (const RgbaColor & color)
{
    _setColorChannelValue(_R, color.R_get(), false);
    _setColorChannelValue(_G, color.G_get(), false);
    _setColorChannelValue(_B, color.B_get(), false);
    _setColorChannelValue(_A, color.A_get(), false);

    raiseEvent colorUpdated(this, nullptr);
}

void RgbaColor::operator = (int32_t hexadecimalColorRepresntation)
{
    uint8_t R = (hexadecimalColorRepresntation >> 24) & 0xFF;
    uint8_t G = (hexadecimalColorRepresntation >> 16) & 0xFF;
    uint8_t B = (hexadecimalColorRepresntation >> 8)  & 0xFF;
    uint8_t A =  hexadecimalColorRepresntation        & 0xFF;

    _setColorChannelValue(_R, R, BitEncoding::Bit8, false);
    _setColorChannelValue(_G, G, BitEncoding::Bit8, false);
    _setColorChannelValue(_B, B, BitEncoding::Bit8, false);
    _setColorChannelValue(_A, A, BitEncoding::Bit8, false);
    
    raiseEvent colorUpdated(this, nullptr);
}

bool RgbaColor::operator == (RgbaColor color)
{
    if (_R == color._R &&
        _G == color._G &&
        _B == color._B &&
        _A == color._A)
        return true;

    return false;
}

void RgbaColor::_setColorChannelValue(double & colorChannel, double value, bool raiseColorUpdated)
{
    if (value >= 1.0 && colorChannel != 1.0)
    {
        colorChannel = 1.0;
        if (raiseColorUpdated)
            raiseEvent colorUpdated(this, nullptr);
        return;
    }
    if (value <= 0.0 && colorChannel != 0.0)
    {
        colorChannel = 0.0;
        if (raiseColorUpdated)
            raiseEvent colorUpdated(this, nullptr);
        return;
    }
    if (value != colorChannel)
    {
        colorChannel = value;
        if (raiseColorUpdated)
            raiseEvent colorUpdated(this, nullptr);
    }
}

void RgbaColor::_setColorChannelValue(double & colorChannel, int value, BitEncoding encoding, bool raiseColorUpdated)
{
    int l_channelMax = 0;

    switch (encoding)
    {
    case BitEncoding::Bit8:  l_channelMax = 255;   break;
    case BitEncoding::Bit16: l_channelMax = 65535; break;
    }

    if (value >= l_channelMax && colorChannel != 1.0)
    {
        colorChannel = 1.0;
        if (raiseColorUpdated)
            raiseEvent colorUpdated(this, nullptr);
        return;
    }
    if (value <= 0 && colorChannel != 0.0)
    {
        colorChannel = 0.0;
        if (raiseColorUpdated)
            raiseEvent colorUpdated(this, nullptr);
        return;
    }
    if (value != static_cast<int>(colorChannel * static_cast<double>(l_channelMax) + 0.5)) //+0.5 is added becuase (int) conversion always rounds toward lower integer (more preciselly toward 0), not toward nearest integer
    {
        colorChannel = static_cast<double>(value) / static_cast<double>(l_channelMax);
        if (raiseColorUpdated)
            raiseEvent colorUpdated(this, nullptr);
    }
}

double RgbaColor::R_get() const { return _R; }
double RgbaColor::G_get() const { return _G; }
double RgbaColor::B_get() const { return _B; }
double RgbaColor::A_get() const { return _A; }

void RgbaColor::R_set(double R) { _setColorChannelValue(_R, R, true); }
void RgbaColor::G_set(double G) { _setColorChannelValue(_G, G, true); }
void RgbaColor::B_set(double B) { _setColorChannelValue(_B, B, true); }
void RgbaColor::A_set(double A) { _setColorChannelValue(_A, A, true); }

int RgbaColor::R8bit_get() const { return static_cast<int>(_R * 255.0 + 0.5); } //+0.5 is added becuase (int) conversion always rounds toward lower integer (more preciselly toward 0), not toward nearest integer
int RgbaColor::G8bit_get() const { return static_cast<int>(_G * 255.0 + 0.5); }
int RgbaColor::B8bit_get() const { return static_cast<int>(_B * 255.0 + 0.5); }
int RgbaColor::A8bit_get() const { return static_cast<int>(_A * 255.0 + 0.5); }

void RgbaColor::R8bit_set(int R) { _setColorChannelValue(_R, R, BitEncoding::Bit8, true); }
void RgbaColor::G8bit_set(int G) { _setColorChannelValue(_G, G, BitEncoding::Bit8, true); }
void RgbaColor::B8bit_set(int B) { _setColorChannelValue(_B, B, BitEncoding::Bit8, true); }
void RgbaColor::A8bit_set(int A) { _setColorChannelValue(_A, A, BitEncoding::Bit8, true); }

int RgbaColor::R16bit_get() const { return static_cast<int>(_R * 65535 + 0.5); }
int RgbaColor::G16bit_get() const { return static_cast<int>(_G * 65535 + 0.5); }
int RgbaColor::B16bit_get() const { return static_cast<int>(_B * 65535 + 0.5); }
int RgbaColor::A16bit_get() const { return static_cast<int>(_A * 65535 + 0.5); }

void RgbaColor::R16bit_set(int R) { _setColorChannelValue(_R, R, BitEncoding::Bit16, false); };
void RgbaColor::G16bit_set(int G) { _setColorChannelValue(_R, G, BitEncoding::Bit16, false); };
void RgbaColor::B16bit_set(int B) { _setColorChannelValue(_R, B, BitEncoding::Bit16, false); };
void RgbaColor::A16bit_set(int A) { _setColorChannelValue(_R, A, BitEncoding::Bit16, false); };