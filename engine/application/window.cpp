
#include "window.hpp"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

   Window::Window(int width, int height, std::string_view name)
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

   bool Window::PollEvent()
   {
      
   }

   void Window::SetVerticalSync(bool on)
   {
      glfwSwapInterval(on);
   }

   void Window::SwapBuffer()
   {
      glfwSwapBuffers(mWindow);
      glfwPollEvents();
   }

   bool Window::ShouldClose()
   {
      return glfwWindowShouldClose(mWindow);
   }

   Window::~Window()
   {
      glfwDestroyWindow(mWindow);
      glfwTerminate();
   }
}