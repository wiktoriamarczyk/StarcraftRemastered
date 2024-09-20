#pragma once
#include "AirUnit.h"

class Battlecruiser : public AirUnit
{
public:
    bool Initialize()override;
    void Update(float deltaTime)override;
    void Render(sf::RenderWindow& renderer)override;

private:

};