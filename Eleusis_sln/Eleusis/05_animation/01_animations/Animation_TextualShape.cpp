#include "Animation_Impls.h"
#include "Shape.h"

using namespace Eleusis;

void TextualShapeAnimation::_populateDefaultStartValues()
{
    for (auto target : _animationTargets)
    {
        if (_animationTargets.front()->uiContext() != target->uiContext())
            //FreestandingAnimation object cannot be bound to nodes with different rendering contexts.
            throw std::exception();

        if (textSize.isUsingDefaultStartValue())       textSize.startValue(target->textSize_get());
        if (letterSpacing.isUsingDefaultStartValue())  letterSpacing.startValue(target->letterSpacing_get());
        if (lineSpacing.isUsingDefaultStartValue())    lineSpacing.startValue(target->lineSpacing_get());
        if (top.isUsingDefaultStartValue())            top.startValue(target->getRelativeOffsetVector().Y);
        if (left.isUsingDefaultStartValue())           left.startValue(target->getRelativeOffsetVector().X);
        if (opacity.isUsingDefaultStartValue())        opacity.startValue(target->opacity_get());
        if (shadowOpacity.isUsingDefaultStartValue())  shadowOpacity.startValue(target->shadowOpacity_get());
        if (shadowDistance.isUsingDefaultStartValue()) shadowDistance.startValue(target->shadowDistance_get());
        if (lineThickness.isUsingDefaultStartValue())  lineThickness.startValue(target->lineThickness_get());
    }
}

void TextualShapeAnimation::_updateToCurrentValues()
{
    for (auto target : _animationTargets)
    {
        if (textSize.isActive())       target->textSize_set(_calculateCurrentValue<Length>(&textSize));
        if (letterSpacing.isActive())  target->letterSpacing_set(_calculateCurrentValue<Length>(&letterSpacing));
        if (lineSpacing.isActive())    target->lineSpacing_set(_calculateCurrentValue<Length>(&lineSpacing));
        if (top.isActive())            target->LayoutGuest.Classic.top(_calculateCurrentValue<Length>(&top));
        if (left.isActive())           target->LayoutGuest.Classic.left(_calculateCurrentValue<Length>(&left));
        if (opacity.isActive())        target->opacity_set(_calculateCurrentValue<double>(&opacity));
        if (shadowOpacity.isActive())  target->shadowOpacity_set(_calculateCurrentValue<double>(&shadowOpacity));
        if (shadowDistance.isActive()) target->shadowDistance_set(_calculateCurrentValue<Vector>(&shadowDistance));
        if (lineThickness.isActive())  target->lineThickenss_set(_calculateCurrentValue<double>(&lineThickness));
        if (fillColor.isActive())      target->fillColor_set(_calculateCurrentValue<RgbaColor>(&fillColor));
        if (lineColor.isActive())      target->lineColor_set(_calculateCurrentValue<RgbaColor>(&lineColor));
    }
}

void TextualShapeAnimation::clear()
{
    Animation::clear();

    textSize.clear();
    letterSpacing.clear();
    lineSpacing.clear();
    top.clear();
    left.clear();
    opacity.clear();
    shadowOpacity.clear();
    shadowDistance.clear();
    lineThickness.clear();
    fillColor.clear();
    lineColor.clear();
}

void TextualShapeAnimation::bind(TextualShape* target)
{
    if (_animationTargets.empty()) _animationTargets.push_back(target);
    else
    {
        _animationTargets.remove(target);
        _animationTargets.push_back(target);
    }
}

void TextualShapeAnimation::unbind(TextualShape* target)
{
    _animationTargets.remove(target);
}

void TextualShapeAnimation::registerAnimation()
{
    if (_animationTargets.empty()) return;
    _animationTargets.front()->uiContext()->registerAnimation(this);
}