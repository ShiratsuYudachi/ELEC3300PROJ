#include "WS2812.hpp"
#include "main.h"
#pragma once
#ifndef LIGHTCONTROLER_HPP
#define LIGHTCONTROLER_HPP


void playStartAnimation();

void playCompleteAnimation();

extern enum STATUS{
  STANDBY,
  OPERATING,
  WARNING,
  FATAL,
  RESETTING
} lightStatus;
void updateLightEffect();

#endif