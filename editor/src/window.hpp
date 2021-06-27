#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <stdexcept>
#include <deque>
#include <string_view>
using std::literals::operator""sv;
using std::literals::operator""s;

namespace Bubble
{
   static void error_callback(int error, const char* description)
   {
      fputs(description, stderr);
   }

   static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
   {
      if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
         glfwSetWindowShouldClose(window, GL_TRUE);
   }

   class Window
   {
   public:
      Window(int width = 640, int height = 480, std::string_view name = "Window"sv)
      {
         glfwSetErrorCallback(error_callback);

         if (!glfwInit())
            throw std::runtime_error("Glfw init failed");

         mWindow = glfwCreateWindow(width, height, &name.front(), NULL, NULL);
         
         if (!mWindow)
         {
            glfwTerminate();
            throw std::runtime_error("Glfw window creation failed");
         }

         glfwMakeContextCurrent(mWindow);
         glfwSetKeyCallback(mWindow, key_callback);
         glfwSwapInterval(1);

         if (int error = glewInit(); error != GLEW_OK)
            throw std::runtime_error("Glew init failed: "s + (char*)glewGetErrorString(error));
      }

      bool PollEvent()
      {
         
      }

      void SetVerticalSync(bool on)
      {
         glfwSwapInterval(on);
      }

      void SwapBuffer()
      {
         glfwSwapBuffers(mWindow);
         glfwPollEvents();
      }

      bool ShouldClose()
      {
         return glfwWindowShouldClose(mWindow);
      }

      ~Window()
      {
         glfwDestroyWindow(mWindow);
         glfwTerminate();
      }

   private:
      GLFWwindow* mWindow;
      std::deque<int> mEvents;
   };
}