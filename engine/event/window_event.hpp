#pragma once

#include <cstdint>

namespace Bubble
{
   enum WindowEventType
   {
      Resize,
      Close
   };

   struct WindowEvent
   {
      WindowEventType Type;
      int Width;
      int Hight;
   };
}