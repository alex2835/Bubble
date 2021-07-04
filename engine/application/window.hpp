#pragma once


#include <stdexcept>
#include <deque>
#include <string_view>
using std::literals::operator""sv;
using std::literals::operator""s;

class GLFWwindow;

namespace Bubble
{
   class Window
   {
   public:
      Window(int width = 640, int height = 480, std::string_view name = "Window"sv);
      bool PollEvent();
      void SetVerticalSync(bool on);
      void SwapBuffer();
      bool ShouldClose();
      ~Window();

   private:
      GLFWwindow* mWindow;
   };
}