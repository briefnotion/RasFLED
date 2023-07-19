// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: screen4.h
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2859 Core Dynamics
// ***************************************************************************************

#ifndef SCREEN4_H
#define SCREEN4_H

#include <stdio.h>
#include <string>

// Graphics
#include "../../imgui/imgui.h"
#include "../../imgui/misc/cpp/imgui_stdlib.h"
#include "../../imgui/backends/imgui_impl_opengl2.h"
#include "../../imgui/backends/imgui_impl_glfw.h"
#include <GLFW/glfw3.h>

using namespace std;

// ---------------------------------------------------------------------------------------


static void glfw_error_callback(int error, const char* description);


class SCREEN4
{
  private:

  bool use_work_area = true;

  ImGuiWindowFlags flags =     ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | 
                                      ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | 
                                      ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBringToFrontOnFocus;
  ImGuiWindowFlags flags_c =   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | 
                                      ImGuiWindowFlags_NoSavedSettings;
  ImGuiWindowFlags flags_w =   ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | 
                                      ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse;

  bool show_another_window = true;
  bool show_test_window = false;

  ImVec4 clear_color;
  GLFWwindow *  window = nullptr;

  GLFWmonitor * monitor = nullptr;
  const GLFWvidmode * mode = nullptr;
  //ImGuiIO& io = ImGui::GetIO(); //(void)io;
  
  int width = 1280;
  int height = 720;

  // Screen Variables
  int DISPLAY_MENU = 0;
  int DISPLAY_SCREEN = 0;
  string CONSOLE_TEXT = "";

  public:

  // Screen Return Variables
  bool WINDOW_CLOSE = false;
  string CONSOLE_INPUT = "";

  int create();
  // Create Screen and set variables
  // Return 0 OK
  // Return 2 error

  void draw();
  // Render window to terminal

  void shutdown();
  // Proper close of imgui

  // ----

  void printw(string Text);

};

// ---------------------------------------------------------------------------------------
#endif