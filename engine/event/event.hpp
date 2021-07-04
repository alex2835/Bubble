#pragma once

#include "event/key_codes.h"

namespace Bubble
{
   enum EventType
   {
      MouseEvent,
      KeyEvent
   };

   

   struct Event
   {
      EventType Type;
      union
      {
         
      };
      
   };
}