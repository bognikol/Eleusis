#include "TextualTypes.h"
#include "pango/pangocairo.h"

namespace Eleusis
{
    PangoAlignment convertParagraphAligmentToPangoAligment(ParagraphAlignment aligment)
    {
        switch (aligment)
        {
        case ParagraphAlignment::Left:
        case ParagraphAlignment::JustifiedLeft:
            return PangoAlignment::PANGO_ALIGN_LEFT;
        case ParagraphAlignment::Center:
        case ParagraphAlignment::JustifiedCenter:
            return PangoAlignment::PANGO_ALIGN_CENTER;
        case ParagraphAlignment::Right:
        case ParagraphAlignment::JustifiedRight:
        default:
            return PangoAlignment::PANGO_ALIGN_RIGHT;
        }
    }

    bool convertParagraphAlignmentToJustification(ParagraphAlignment alignment)
    {
        switch (alignment)
        {
            case ParagraphAlignment::JustifiedLeft:
            case ParagraphAlignment::JustifiedCenter:
            case ParagraphAlignment::JustifiedRight:
                return true;
            default:
                return false;
        }
    }

    PangoEllipsizeMode convertEllipsizeTypeToPangoEllipsize(EllipsizeType ellipsizeType)
    {
        switch (ellipsizeType)
        {
        case EllipsizeType::End:    return PangoEllipsizeMode::PANGO_ELLIPSIZE_END;
        case EllipsizeType::Middle: return PangoEllipsizeMode::PANGO_ELLIPSIZE_MIDDLE;
        case EllipsizeType::Start:  return PangoEllipsizeMode::PANGO_ELLIPSIZE_START;
        case EllipsizeType::None:   return PangoEllipsizeMode::PANGO_ELLIPSIZE_NONE;
        default:                    return PangoEllipsizeMode::PANGO_ELLIPSIZE_NONE;
        }
    }


}
