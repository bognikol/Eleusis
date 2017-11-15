#pragma once

#include "dllexport.h"

#include "pango/pangocairo.h"

namespace Eleusis
{
    enum class ELEUSIS_API FontStyle
    {
        Normal,
        Italic,
        Oblique
    };

    enum class ELEUSIS_API FontVariant
    {
        Normal,
        SmallCaps
    };

    enum class ELEUSIS_API FontStretch
    {
        s100_UltraCondensed,
        s200_ExtraCondensed,
        s300_Condensed,
        s400_SemiCondensed,
        s500_Normal,
        s600_SemiExpanded,
        s700_Expanded,
        s800_ExtraExpanded,
        s900_UltraExpanded
    };

    enum class ELEUSIS_API FontWeight
    {
        w100_Thin = 100,
        w200_Ultralight = 200,
        w300_Light = 300,
        w350_Semilight = 350,
        w380_Book = 380,
        w400_Normal = 400,
        w500_Medium = 500,
        w600_Semibold = 600,
        w700_Ultrabold = 700,
        w800_Heavy = 800,
        w900_Ultraheavy = 900

    };

    enum class ELEUSIS_API UnderlineType
    {
        None,
        Single,
        Double,
        Low,
        Curly
    };

    enum class ELEUSIS_API CharacterGravity
    {
        South,
        East,
        North,
        West,
        Auto
    };

    enum class ELEUSIS_API CharacterGravityHint
    {
        Natural,
        Strong,
        Line
    };

    enum class ELEUSIS_API ParagraphAlignment
    {
        Left,
        Center,
        Right,
        JustifiedLeft,
        JustifiedCenter,
        JustifiedRight
    };
    
    // TODO: move these global functions
    PangoAlignment convertParagraphAligmentToPangoAligment(ParagraphAlignment alignment);
    bool convertParagraphAlignmentToJustification(ParagraphAlignment alignment);

    enum class ELEUSIS_API EllipsizeType
    {
        None,
        Start,
        Middle,
        End
    };

    PangoEllipsizeMode convertEllipsizeTypeToPangoEllipsize(EllipsizeType ellipsizeType);

}

