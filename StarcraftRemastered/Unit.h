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
    virtual vec2 GetPosition()const { return m_CurrentPosition; }
    virtual void SetPosition(vec2 position) { m_CurrentPosition = position; }
    virtual float GetRotation()const { return m_CurrentRotation; }
    virtual void SetRotation(float rotation) { m_CurrentRotation = rotation; }

protected:
    vec2            m_StartPosition = vec2(800, 500);
    vec2            m_CurrentPosition;
    vec2            m_Direction;
    optional<vec2>  m_TargetPosition = nullopt;
    float           m_TargetRotation = 0.f;
    float           m_Speed = 400.0f;
    float           m_RotationSpeed = 220.f;
    float           m_CurrentRotation = 0.f;
};