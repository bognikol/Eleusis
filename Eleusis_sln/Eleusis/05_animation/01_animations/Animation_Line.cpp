#include "Animation_Impls.h"
#include "Shape.h"

using namespace Eleusis;

void LineAnimation::_populateDefaultStartValues()
{
    for (auto target : _animationTargets)
    {
        if (_animationTargets.front()->uiContext() != target->uiContext())
            //FreestandingAnimation object cannot be bound to nodes with different rendering contexts.
            throw std::exception();

        if (endPointX.isUsingDefaultStartValue())      endPointX.startValue(target->endPointX_get());
        if (endPointY.isUsingDefaultStartValue())      endPointY.startValue(target->endPointY_get());
        if (top.isUsingDefaultStartValue())            top.startValue(target->getRelativeOffsetVector().Y);
        if (left.isUsingDefaultStartValue())           left.startValue(target->getRelativeOffsetVector().X);
        if (opacity.isUsingDefaultStartValue())        opacity.startValue(target->opacity_get());
        if (shadowOpacity.isUsingDefaultStartValue())  shadowOpacity.startValue(target->shadowOpacity_get());
        if (shadowDistance.isUsingDefaultStartValue()) shadowDistance.startValue(target->shadowDistance_get());
        if (lineThickness.isUsingDefaultStartValue())  lineThickness.startValue(target->lineThickness_get());
    }
}

void LineAnimation::_updateToCurrentValues()
{
    for (auto target : _animationTargets)
    {
        if (endPointX.isActive())      target->endPointX_set(_calculateCurrentValue<Length>(&endPointX));
        if (endPointY.isActive())      target->endPointY_set(_calculateCurrentValue<Length>(&endPointY));
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

void LineAnimation::clear()
{
    Animation::clear();

    endPointX.clear();
    endPointY.clear();
    top.clear();
    left.clear();
    opacity.clear();
    shadowOpacity.clear();
    shadowDistance.clear();
    lineThickness.clear();
    fillColor.clear();
    lineColor.clear();
}

void LineAnimation::bind(Line* target)
{
    if (_animationTargets.empty()) _animationTargets.push_back(target);
    else
    {
        _animationTargets.remove(target);
        _animationTargets.push_back(target);
    }
}

void LineAnimation::unbind(Line* target)
{
    _animationTargets.remove(target);
}

void LineAnimation::registerAnimation()
{
    if (_animationTargets.empty()) return;
    _animationTargets.front()->uiContext()->registerAnimation(this);
}
