#pragma once

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
   };
}