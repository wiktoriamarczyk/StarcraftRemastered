#pragma once
#include "Common.h"
#include "Unit.h"

class AirUnit : public Unit
{
public:
    virtual void Render(sf::RenderWindow& renderer)override;


protected:
    int m_ElevationIdleRange = 20;

    virtual void MoveToTarget(float deltaTime, vec2 position)override;
};