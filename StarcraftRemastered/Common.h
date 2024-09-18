#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<cstdio>
#include<filesystem>
#include<string>
#include<vector>
#include<memory>
#include<optional>

#include"vec2.h"

using std::string;
using std::filesystem::path;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::optional;
using std::nullopt;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const string APP_NAME = "Starcraft";
const path DATA_PATH = "../Data/";
static constexpr double PI = 3.141592653589793238462643383279502884;

enum class eDrawMode
{
    NORMAL,
    ADDITIVE,
};

struct DisplayParameters
{
    eDrawMode DrawMode  = eDrawMode::NORMAL;
    vec2 DrawScale      = vec2(1.0f, 1.0f);
    vec2 Pivot          = vec2(0.5, 0.5);
    sf::Color DrawColor = sf::Color::White;
    float Rotation      = 0.0f;
};