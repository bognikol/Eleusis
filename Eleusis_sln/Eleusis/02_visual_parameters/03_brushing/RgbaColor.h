#pragma once

#include "dllexport.h"

#include "event.h" 

namespace Eleusis
{
    class ELEUSIS_API RgbaColor
    {
    private:    double _R;
                double _G;
                double _B;
                double _A;

                enum class BitEncoding { Bit8, Bit16 };

                void _setColorChannelValue(double & colorChannelVariable, double value, bool raiseColorUpdated);
                void _setColorChannelValue(double & colorChannelVariable, int    value, BitEncoding encoding, bool raiseColorUpdated);


    public:     RgbaColor();
                RgbaColor(double R, double G, double B);
                RgbaColor(double R, double G, double B, double A);
                RgbaColor(int R, int G, int B);
                RgbaColor(int R, int G, int B, int A);
                RgbaColor(int32_t hexadecimalColorRepresntation);

                void operator = (const RgbaColor & color);
                void operator = (int32_t hexadecimalColorRepresentation);

                bool operator == (RgbaColor color);

                double R_get() const;
                double G_get() const;
                double B_get() const;
                double A_get() const;

                void R_set(double R);
                void G_set(double G);
                void B_set(double B);
                void A_set(double A);

                int R8bit_get() const;
                int G8bit_get() const;
                int B8bit_get() const;
                int A8bit_get() const;

                void R8bit_set(int R);
                void G8bit_set(int G);
                void B8bit_set(int B);
                void A8bit_set(int A);

                int R16bit_get() const;
                int G16bit_get() const;
                int B16bit_get() const;
                int A16bit_get() const;

                void R16bit_set(int R);
                void G16bit_set(int G);
                void B16bit_set(int B);
                void A16bit_set(int A);

                Event<RgbaColor*, EventArgs*> colorUpdated;
    };
}
