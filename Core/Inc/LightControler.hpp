#include "WS2812.hpp"
#include "main.h"
#ifndef LIGHTCONTROLER_HPP
#define LIGHTCONTROLER_HPP
#define LUMINANCE_MULTIPLIER 0.1
class LightStream{
  int startIndex;
  int endIndex;
  int length;
  float duration; // in s
  int startTick;
  RGB color;
public:
  LightStream(int startIndex, int endIndex, int length, float duration, RGB color) : startIndex(startIndex), endIndex(endIndex), length(length), duration(duration), color(color) {}

  void start(){
    startTick = HAL_GetTick();
  }

  void calculatePosition(int& start, int& end){
    int tick = HAL_GetTick();
    float progress = (tick - startTick) / (duration * 1000);
    auto min = [](int a, int b){return a < b ? a : b;};
    auto max = [](int a, int b){return a > b ? a : b;};
    start = max(0, startIndex + (endIndex - startIndex) * progress - length);
    end = min(start + length, LED_NUM);
  }

  void setToColor(){ // true: not finished, false: finished
    int start, end;
    calculatePosition(start, end);
    for (int i = start; i < end; i++){
      setColor(i, color.red, color.green, color.blue);
    }
  }
  bool isFinished(){
    return HAL_GetTick() - startTick > duration * 1000;
  }
};

void playStartAnimation(){
  // LightStream stream1(0, 84, 3, 3, RGB(10, 0, 0));
  // stream1.start();
  // while (!stream1.isFinished()){
  //   stream1.setToColor();
  // }
  
  int current = 0;
  int length = 10;

  RGB color = RGB(0, 20, 0);

  while (current < LED_NUM){
    auto max = [](int a, int b){return a > b ? a : b;};
    auto min = [](int a, int b){return a < b ? a : b;};
    for (int i = current; i < min(current + length, LED_NUM); i++){
      setColor(i, color);
    }
    if (current > 0){
      setColor(current - 1, 0, 0, 0);
    }
    
    for (int i = LED_NUM - current - 1; i > max(LED_NUM - current - length, 0); i--){
      setColor(i, color);
    }
    if (current > 0){
      setColor(LED_NUM - current, 0, 0, 0);
    }
    HAL_Delay(20);
    current++;
  }
}

int startTick = 0;
void updateStandbyAnimation(){
    // period = 3s
    int period = 3000;
    if (startTick == 0){
      startTick = HAL_GetTick();
    }
    int tick = HAL_GetTick();
    float progress = (tick - startTick)%period / (float)period;
    for (int i = 0; i < LED_NUM; i++){
      if (progress < 0.5){
        setColor(i, 0, progress * 255, 0);
      } else {
        setColor(i, 0, 128 - (progress - 0.5)*255, 0);
      }
    }
}

#endif