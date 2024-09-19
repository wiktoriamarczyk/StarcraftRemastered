#pragma once
#include "Common.h"
#include "Race.h"

class Unit
{
public:
    virtual bool Initialize()=0;
    virtual void Update(float deltaTime)=0;
    virtual void Render(sf::RenderWindow& renderer)=0;
    virtual void CommandMovement(vec2 position) {};
};