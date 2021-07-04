#pragma once

#include <queue>

namespace Bubble
{
   template <typename EventType>
   class EventQueue
   {
      void PushEvent(EventType event) { mEvents.push(event) };
      
      EventType PollEvent() 
      {
         EventType temp = mEvents.front();
         mEvents.pop();
         return temp;
      };

      size_t Size() { return mEvents.size(); }

      private:
         std::queue<EventType> mEvents;
   };
}