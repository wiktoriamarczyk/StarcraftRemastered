#pragma once
#include "Unit.h"

class Battlecruiser : public Unit
{
public:
    bool Initialize()override;
    void Update(float deltaTime)override;
    void Render(sf::RenderWindow& renderer)override;
    void CommandMovement(vec2 position)override;
    vec2 GetPosition()const { return m_CurrentPosition; }
    void SetPosition(vec2 position) { m_CurrentPosition = position; }
    float GetRotation()const { return m_CurrentRotation; }
    void SetRotation(float rotation) { m_CurrentRotation = rotation; }

private:
    vec2            m_StartPosition = vec2(800, 500);
    vec2            m_CurrentPosition;
    optional<vec2>  m_TargetPosition = nullopt;
    float           m_Speed = 400.0f;
    float           m_RotationSpeed = 220.f;
    vec2            m_Direction;
    float           m_CurrentRotation = 0;
    float           m_TargetRotation = 0;

    string m_TextureName = "218_hd2_diffuse_000.png";
    string m_TexturePath = DATA_PATH.string() + "Terran/Units/Battlecruiser/" + m_TextureName;

    void MoveToTarget(float deltaTime);
    void RotateToTarget(float deltaTime);
};