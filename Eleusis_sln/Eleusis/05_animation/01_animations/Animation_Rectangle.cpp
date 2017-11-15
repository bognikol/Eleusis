#include "Animation_Impls.h"
#include "Shape.h"

using namespace Eleusis;

void RectangleAnimation::_populateDefaultStartValues()
{
    for (auto target : _animationTargets)
    {
        if (_animationTargets.front()->uiContext() != target->uiContext())
            //FreestandingAnimation object cannot be bound to nodes with different rendering contexts.
            throw std::exception();

        if (width.isUsingDefaultStartValue())          width.startValue(target->width_get());
        if (height.isUsingDefaultStartValue())         height.startValue(target->height_get());
        if (cornerRadius.isUsingDefaultStartValue())   cornerRadius.startValue(target->cornerRadius_get());
        if (top.isUsingDefaultStartValue())            top.startValue(target->getRelativeOffsetVector().Y);
        if (left.isUsingDefaultStartValue())           left.startValue(target->getRelativeOffsetVector().X);
        if (opacity.isUsingDefaultStartValue())        opacity.startValue(target->opacity_get());
        if (shadowOpacity.isUsingDefaultStartValue())  shadowOpacity.startValue(target->shadowOpacity_get());
        if (shadowDistance.isUsingDefaultStartValue()) shadowDistance.startValue(target->shadowDistance_get());
        if (lineThickness.isUsingDefaultStartValue())  lineThickness.startValue(target->lineThickness_get());
    }
}

void RectangleAnimation::_updateToCurrentValues()
{
    for (auto target : _animationTargets)
    {
        if (width.isActive())          target->width_set(_calculateCurrentValue<Length>(&width));
        if (height.isActive())         target->height_set(_calculateCurrentValue<Length>(&height));
        if (cornerRadius.isActive())   target->cornerRadius_set(_calculateCurrentValue<Length>(&cornerRadius));
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

void RectangleAnimation::clear()
{
    Animation::clear();

    width.clear();
    height.clear();
    cornerRadius.clear();
    top.clear();
    left.clear();
    opacity.clear();
    shadowOpacity.clear();
    shadowDistance.clear();
    lineThickness.clear();
    fillColor.clear();
    lineColor.clear();
}

void RectangleAnimation::bind(Eleusis::Rectangle* target)
{
    if (_animationTargets.empty()) _animationTargets.push_back(target);
    else
    {
        _animationTargets.remove(target);
        _animationTargets.push_back(target);
    }
}

void RectangleAnimation::unbind(Eleusis::Rectangle* target)
{
    _animationTargets.remove(target);
}

void RectangleAnimation::registerAnimation()
{
    if (_animationTargets.empty()) return;
    _animationTargets.front()->uiContext()->registerAnimation(this);
}
