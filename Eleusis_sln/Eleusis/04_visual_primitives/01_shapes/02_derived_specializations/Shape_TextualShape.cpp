#include "Shape.h"
#include "pango/pangocairo.h"

using namespace Eleusis;
using namespace std;

namespace Eleusis { extern cairo_t* _cairoUtilityContext; }

TextualShape::TextualShape()
{
    _requestGeometryUpdate();
}

TextualShape::TextualShape(std::string text)
{
    _text = text;
    _filterCacheIsStale = true;
    _requestGeometryUpdate();
}

void TextualShape::text_set(std::string text)
{ 
    if (_text == text) return;

    _text = text; 
    _filterCacheIsStale = true;
    _requestGeometryUpdate();
}

void TextualShape::fontFamily_set(std::string fontFamily)
{ 
    if (_fontFamily == fontFamily) return;

    _fontFamily = fontFamily;
    _filterCacheIsStale = true;
    _requestGeometryUpdate();
}

void TextualShape::fontStyle_set(FontStyle fontStyle)
{ 
    if (_fontStyle == fontStyle) return;

    _fontStyle = fontStyle;
    _filterCacheIsStale = true;
    _requestGeometryUpdate();
}

void TextualShape::fontWeight_set(FontWeight fontWeight)
{ 
    if (_fontWeight == fontWeight) return;

    _fontWeight = fontWeight;
    _filterCacheIsStale = true;
    _requestGeometryUpdate();
}

void TextualShape::fontVariant_set(FontVariant fontVariant)
{  
    if (_fontVariant == fontVariant) return;

    _fontVariant = fontVariant;
    _filterCacheIsStale = true;
    _requestGeometryUpdate();
}

void TextualShape::fontStrech_set(FontStretch fontStrech)
{
    if (_fontStretch == fontStrech) return;

    _fontStretch = fontStrech;
    _filterCacheIsStale = true;
    _requestGeometryUpdate();
}

void TextualShape::fontFallback_set(bool fontFallback)
{
    if (_fontFallback == fontFallback) return;

    _fontFallback = fontFallback;
    _filterCacheIsStale = true;
    _requestGeometryUpdate();
}

void TextualShape::textSize_set(Length textSize)
{ 
    if (_textSize == textSize) return;

    _textSize = textSize;
    _filterCacheIsStale = true;
    _requestGeometryUpdate();
}

void TextualShape::letterSpacing_set(Length letterSpacing)
{ 
    if (_letterSpacing == letterSpacing) return;

    _letterSpacing = letterSpacing;
    _filterCacheIsStale = true;
    _requestGeometryUpdate();
}

void TextualShape::lineSpacing_set(Length lineSpacing)
{ 
    if (_lineSpacing == lineSpacing) return;

    _lineSpacing = lineSpacing;
    _filterCacheIsStale = true;
    _requestGeometryUpdate();
}

void TextualShape::underline_set(UnderlineType underline)
{ 
    if (_underline == underline) return;

    _underline = underline; 
    _filterCacheIsStale = true;
    _requestGeometryUpdate();
}

void TextualShape::strikeThrough_set(bool strikeThrough)
{ 
    if (_strikeThrough == strikeThrough) return;

    _strikeThrough = strikeThrough;
    _filterCacheIsStale = true;
    _requestGeometryUpdate();
}

void TextualShape::gravity_set(CharacterGravity gravity)
{
    if (_gravity == gravity) return;

    _gravity = gravity;
    _filterCacheIsStale = true;
    _requestGeometryUpdate();
}

void TextualShape::gravityHint_set(CharacterGravityHint gravityHint)
{
    if (_gravityHint == gravityHint) return;

    _gravityHint = gravityHint;
    _filterCacheIsStale = true;
    _requestGeometryUpdate();
}

void TextualShape::italic()
{ 
    if (_italicApplied) return;
    _italicApplied = true;

    if (_fontStyle == FontStyle::Italic) return;

    _fontStyle = FontStyle::Italic;
    _filterCacheIsStale = true;
    _requestGeometryUpdate();
}

void TextualShape::unitalic()
{
    if (!_italicApplied) return;
    _italicApplied = false;

    if (_fontStyle == FontStyle::Normal) return;

    _fontStyle = FontStyle::Normal;
    _filterCacheIsStale = true;
    _requestGeometryUpdate();
}

void TextualShape::bold()
{ 
    if (_boldApplied) return;

    _boldApplied = true;

    switch (_fontWeight)
    {
    case FontWeight::w100_Thin: 
        _fontWeight = FontWeight::w300_Light;
        break;
    case FontWeight::w200_Ultralight:
        _fontWeight = FontWeight::w400_Normal;
        break;
    case FontWeight::w300_Light:
    case FontWeight::w350_Semilight:
        _fontWeight = FontWeight::w500_Medium;
        break;
    case FontWeight::w380_Book:
    case FontWeight::w400_Normal:
        _fontWeight = FontWeight::w600_Semibold;
        break;
    case FontWeight::w500_Medium:
        _fontWeight = FontWeight::w700_Ultrabold;
        break;
    case FontWeight::w600_Semibold:
        _fontWeight = FontWeight::w800_Heavy;
        break;
    case FontWeight::w700_Ultrabold:
    case FontWeight::w800_Heavy:
        _fontWeight = FontWeight::w900_Ultraheavy;
        break;
    case FontWeight::w900_Ultraheavy:
    default:
        break;
    }

    _filterCacheIsStale = true;
    _requestGeometryUpdate();
}

void TextualShape::unbold()
{
    if (!_boldApplied) return;

    _boldApplied = false;

    switch (_fontWeight)
    {
    case FontWeight::w300_Light:
    case FontWeight::w350_Semilight:
    case FontWeight::w380_Book:
        _fontWeight = FontWeight::w100_Thin;
        break;
    case FontWeight::w400_Normal:
        _fontWeight = FontWeight::w200_Ultralight;
        break;
    case FontWeight::w500_Medium:
        _fontWeight = FontWeight::w300_Light;
        break;
    case FontWeight::w600_Semibold:
        _fontWeight = FontWeight::w400_Normal;
        break;
    case FontWeight::w700_Ultrabold:
        _fontWeight = FontWeight::w500_Medium;
        break;
    case FontWeight::w800_Heavy:
        _fontWeight = FontWeight::w600_Semibold;
        break;
    case FontWeight::w900_Ultraheavy:
        _fontWeight = FontWeight::w700_Ultrabold;
        break;
    default:
        break;
    }

    _filterCacheIsStale = true;
    _requestGeometryUpdate();
}

void TextualShape::_updateGeometry()
{
    if (_geometryUpdateExecuted) return;

    /*
    pango_cairo_layout_path() seems to be sensitive to surface size of the Cairo context.
    If surface size is small and Pango determines that path will not fit the surface,
    pango_cairo_layout_path() will not copy whole path to the Cairo context. From our
    perspective, this is unacceptable behavior.

    This is the reason why TextualShapes were truncated when _cairoUtilityContext created
    from small surface is used for copying path. After increasing surface, TextualShapes rendered
    correctly. Current problem is that _cairoUtilityContext's surface is using substantial
    amount of memory. Also, truncation can happen again if rendering surface is substantially
    larger then _cairoUtilityContext's surface size.
    */

    PangoLayout* l_layout = pango_cairo_create_layout(_cairoUtilityContext);

    pango_layout_set_spacing(l_layout, static_cast<int>(_lineSpacing.getValueRelativeTo(parent()->getAbsoluteSizeVector().Y) * PANGO_SCALE));
    pango_layout_set_text(l_layout, _text.c_str(), -1);

    PangoAttrList* l_attributeList = pango_attr_list_new();

    pango_attr_list_insert(l_attributeList, pango_attr_family_new(_fontFamily.c_str()));
    pango_attr_list_insert(l_attributeList, pango_attr_style_new(static_cast<PangoStyle>(_fontStyle)));
    pango_attr_list_insert(l_attributeList, pango_attr_weight_new(static_cast<PangoWeight>(_fontWeight)));
    pango_attr_list_insert(l_attributeList, pango_attr_variant_new(static_cast<PangoVariant>(_fontVariant)));
    pango_attr_list_insert(l_attributeList, pango_attr_stretch_new(static_cast<PangoStretch>(_fontStretch)));
    pango_attr_list_insert(l_attributeList, pango_attr_fallback_new(_fontFallback));
    pango_attr_list_insert(l_attributeList, pango_attr_size_new(static_cast<int>(_textSize.getValueRelativeTo(parent()->getAbsoluteSizeVector().Y) * PANGO_SCALE)));
    pango_attr_list_insert(l_attributeList, pango_attr_strikethrough_new(_strikeThrough));
    pango_attr_list_insert(l_attributeList, pango_attr_letter_spacing_new(static_cast<int>(_letterSpacing.getValueRelativeTo(parent()->getAbsoluteSizeVector().Y) * PANGO_SCALE)));
    pango_attr_list_insert(l_attributeList, pango_attr_underline_new(static_cast<PangoUnderline>(_underline)));
    pango_attr_list_insert(l_attributeList, pango_attr_gravity_new(static_cast<PangoGravity>(_gravity)));
    pango_attr_list_insert(l_attributeList, pango_attr_gravity_hint_new(static_cast<PangoGravityHint>(_gravityHint)));

    pango_layout_set_attributes(l_layout, l_attributeList);
    pango_cairo_layout_path(_cairoUtilityContext, l_layout);

    cairo_path_t* l_cairoPath = cairo_copy_path(_cairoUtilityContext);
    cairo_new_path(_cairoUtilityContext);

    delete _geometry; _geometry = new Geometry(l_cairoPath);

    _absoluteSizeVector = _geometry->getExtent().sizeVector();

    _filterCacheIsStale = true;

    cairo_path_destroy(l_cairoPath);

    pango_attr_list_unref(l_attributeList);
    g_object_unref(l_layout);

    _geometryUpdateExecuted = true;
}

void TextualShape::_updateAbsoluteSizeVector(bool* changed, Vector parentAbsoluteSizeVector)
{
    _updateAbsoluteVectorExecutedOnce = true;

    if (_geometry == nullptr) *changed = true;
    else                      *changed = false;
}