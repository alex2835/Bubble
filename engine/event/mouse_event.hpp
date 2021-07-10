#pragma once

#include <cstdint>
#include "key_codes.hpp"

namespace Bubble
{
   enum class MouseKeyEventType : uint8_t
   {
      Down,
      Up,
   };

   struct MouseEvent
   {
      MouseKeyEventType Type;
      KeyCode Key;
   };
}