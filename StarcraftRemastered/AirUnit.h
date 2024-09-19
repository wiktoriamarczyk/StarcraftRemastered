#pragma once
#include "Common.h"
#include "Unit.h"

class AirUnit : public Unit
{
public:


protected:
    virtual void RenderShadow(sf::RenderWindow& renderer, string& textureName);
};