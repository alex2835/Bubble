
#include "window.hpp"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Bubble
{
   // Callbacks
   static void error_callback(int error, const char* description)
   {
      fputs(description, stderr);
   }

   static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
   {
      if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
         glfwSetWindowShouldClose(window, GL_TRUE);
   }

    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        //mouse_input[button] = action;
    }

    void mouse_callback(GLFWwindow* window, double xpos, double ypos)
    {
        //MoffsetX = (xpos - lastX) * sensetivity;
        //MoffsetY = (lastY - ypos) * sensetivity;
        //lastX = xpos;
        //lastY = ypos;
    }

    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
    {
        //Mfov_offset -= yoffset;
    }


    void window_size_callback(GLFWwindow* window, int width, int height)
    {
        //Window* pWindow = windows[window];
        //pWindow->Resize(width, height);
    }

    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        //glViewport(0, 0, width, height);
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

      // set callback functions
      glfwSetKeyCallback(mWindow, key_callback);
      glfwSetMouseButtonCallback(mWindow, mouse_button_callback);
      glfwSetCursorPosCallback(mWindow, mouse_callback);
      glfwSetScrollCallback(mWindow, scroll_callback);
      glfwSetWindowSizeCallback(mWindow, window_size_callback);
      glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);

      glfwSwapInterval(1);
      
      if (int error = glewInit(); error != GLEW_OK)
            throw std::runtime_error("Glew init failed: "s + (char*)glewGetErrorString(error));
   }

   bool Window::PollEvent()
   {
      return false;
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