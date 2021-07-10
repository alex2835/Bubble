#pragma once

#include "mouse_event.hpp"
#include "key_event.hpp"
#include "window_event.hpp"
namespace Bubble
{
   enum class EventType : uint8_t
   {
      MouseEvent,
      KeyEvent,
      WindowEvent
   };

   struct Event
   {
      EventType Type;
      union
      {
         MouseEvent Mouse;
         KeyEvent Key;
         WindowEvent Window;
      };
      
   };
}