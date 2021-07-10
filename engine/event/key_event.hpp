#pragma once

#include <cstdint>
#include "key_codes.hpp"

namespace Bubble
{
   enum class KeyEventType : uint8_t
   {
      Down,
      Up,
      Pressed
   };

   struct KeyEvent
   {
      KeyEventType Type;
      KeyCode Key;
   };
}