#pragma once
#include "image.h"

class Display {
  void receiveImage(const Image& img);
  Image lastReceivedImage;
};
