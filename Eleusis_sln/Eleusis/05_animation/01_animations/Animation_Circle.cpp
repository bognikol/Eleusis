#include "Animation_Impls.h"
#include "Shape.h"

#include "Application.h"

using namespace Eleusis;

void CircleAnimation::_populateDefaultStartValues()
{
    for (auto target : _animationTargets)
    {
        if (_animationTargets.front()->uiContext() != target->uiContext())
            //FreestandingAnimation object cannot be bound to nodes with different rendering contexts.
            throw std::exception();

        if (radius.isUsingDefaultStartValue())         radius.startValue(target->radius_get());
        if (top.isUsingDefaultStartValue())            top.startValue(target->getRelativeOffsetVector().Y);
        if (left.isUsingDefaultStartValue())           left.startValue(target->getRelativeOffsetVector().X);
        if (opacity.isUsingDefaultStartValue())        opacity.startValue(target->opacity_get());
        if (shadowOpacity.isUsingDefaultStartValue())  shadowOpacity.startValue(target->shadowOpacity_get());
        if (shadowDistance.isUsingDefaultStartValue()) shadowDistance.startValue(target->shadowDistance_get());
        if (lineThickness.isUsingDefaultStartValue())  lineThickness.startValue(target->lineThickness_get());
    }
}

void CircleAnimation::_updateToCurrentValues()
{
    for (auto target : _animationTargets)
    {
        if (radius.isActive())         target->radius_set(_calculateCurrentValue<Length>(&radius));
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

void CircleAnimation::clear()
{
    Animation::clear();

    radius.clear();
    top.clear();
    left.clear();
    opacity.clear();
    shadowOpacity.clear();
    shadowDistance.clear();
    lineThickness.clear();
    fillColor.clear();
    lineColor.clear();
}

void CircleAnimation::bind(Circle* target)
{
    if (_animationTargets.empty()) _animationTargets.push_back(target);
    else
    {
        _animationTargets.remove(target);
        _animationTargets.push_back(target);
    }
}

void CircleAnimation::unbind(Circle* target)
{
    _animationTargets.remove(target);
}

void CircleAnimation::registerAnimation()
{
    /*
    TODO: 
    --IMPORTANT--
    Currently, if _animationTarget list is empty, we do not register anmation,
    but, in other respects, we proceed as usual. However, I beleive we should
    carrefully examine whether this is a good approach or it is better to throw 
    an exception here. Animation which started but is not registered will never finish
    because state of animation is updated only at occasional calls to Animation::update()
    by UIContext. If we never call update(), animation will never reexmine its state
    and figure out that it is finished.
    */

	if (_animationTargets.empty()) return;
    _animationTargets.front()->uiContext()->registerAnimation(this);
}
