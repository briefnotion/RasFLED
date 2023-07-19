// ***************************************************************************************
// *
// *    Core       | Everything within this document is proprietary to Core Dynamics.
// *    Dynamics   | Any unauthorized duplication will be subject to prosecution.
// *
// *    Department : (R+D)^2                        Name: screen4.cpp
// *       Sub Dept: Programming
// *    Location ID: 856-45B
// *                                                      (c) 2856 - 2859 Core Dynamics
// ***************************************************************************************

#ifndef SCREEN4_CPP
#define SCREEN4_CPP

#include "screen4.h"

// ---------------------------------------------------------------------------------------

// Graphics
static void glfw_error_callback(int error, const char *description)
{
  fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int SCREEN4::create()
{
  // Init and prepare DISPLAY_SCREEN
  clear_color = ImVec4(0.00f, 0.55f, 0.00f, 0.00f);

  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit())
  {
    printf("Graphics Set Error\n");
    return 2;
  }

  // Create window with graphics context
  int width = 1280;
  int height = 720;

  window = glfwCreateWindow(width, height, "OGL window", nullptr, nullptr);
  monitor = glfwGetPrimaryMonitor();
  mode = glfwGetVideoMode(monitor);

  glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, 0);

  if (window == nullptr)
  {
    printf("Window Set To Monitor Error\n");
    return 2;
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1); // Enable vsync

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;

  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsLight();

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL2_Init();

  io.Fonts->AddFontFromFileTTF("/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf", 18.0f);

  return 0;
}

void SCREEN4::draw()
{
  glfwPollEvents();

  // Start the Dear ImGui frame
  ImGui_ImplOpenGL2_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  const ImGuiViewport* viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
  ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);

  if (ImGui::Begin("Test Window", &show_test_window, flags)) // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
  {
    ImGui::BeginChild("Main", ImVec2(ImGui::GetContentRegionAvail().x - 100, ImGui::GetContentRegionAvail().y), false, flags_c);
    {
      ImGui::BeginChild("Status", ImVec2(ImGui::GetContentRegionAvail().x, 57), true, flags_c);
      {
        static ImGuiInputTextFlags flags = ImGuiInputTextFlags_EscapeClearsAll | ImGuiInputTextFlags_EnterReturnsTrue;

        // IMGUI_API bool  InputText(const char* label, std::string* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
        if (ImGui::InputText("Text", &CONSOLE_INPUT, flags))
        {
          CONSOLE_TEXT = CONSOLE_TEXT + CONSOLE_INPUT + "\n";
          CONSOLE_INPUT = "";
        }

        // Particular widget styling
        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
        ImGui::Text("Hello from another window!");
        ImGui::PopStyleColor();

        // ImGui::SameLine();
      }
      ImGui::EndChild();
  
      ImGui::BeginChild("DISPLAY_SCREEN", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y - 28), false, flags_c);
      {
        // ImGui::Text("Hello from another window!");

        ImGui::SetNextWindowPos(ImGui::GetItemRectMin());
        ImGui::SetNextWindowSize(ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y));

        if (DISPLAY_SCREEN == 0)
        {
          ImGui::Begin("Console", NULL, flags_w);
          {
            static ImGuiWindowFlags flags_console = ImGuiInputTextFlags_ReadOnly | ImGuiInputTextFlags_NoUndoRedo |
                                                    ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse;
            /*
            static ImVector<char> my_str;
            if (my_str.empty())
            {
                my_str.push_back(0);
            }
            Funcs::MyInputTextMultiline("##MyStr", &my_str, ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), flags_console);
            */

            ImGui::InputTextMultiline("##MyStr", &CONSOLE_TEXT, ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), flags_console);
          }
          ImGui::End();
        }

        else if (DISPLAY_SCREEN == 3) // Create a window called "Hello, world!" and append into it.
        {
          ImGui::Begin("Hello, world!", NULL, flags_w);
          {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::BeginGroup();

            ImGui::Text("This is some useful text.");          // Display some text (you can use a format strings too)
            //ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);             // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float *)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
              counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

            ImGui::EndGroup();

            ImGui::SameLine();
            if (ImGui::Button("Exit", ImVec2(50, 50)))
            {
              WINDOW_CLOSE = true;
            }
          }
          ImGui::End();
        }
        else
        {
          ImGui::Begin(" ", NULL, flags_w);
          {
            // Show Nothing
          }
          ImGui::End();
        }
      }
      ImGui::EndChild();

      ImGui::BeginChild("Tabs", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), false, flags_c);
      {
        ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
        if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
        {
          if (ImGui::BeginTabItem("Console"))
          {
            DISPLAY_SCREEN = 0;
            ImGui::EndTabItem();
          }
          if (ImGui::BeginTabItem("Automobile"))
          {
            DISPLAY_SCREEN = 1;
            ImGui::EndTabItem();
          }
          if (ImGui::BeginTabItem("ADSB"))
          {
            DISPLAY_SCREEN = 2;
            ImGui::EndTabItem();
          }
          if (ImGui::BeginTabItem("Hello World"))
          {
            DISPLAY_SCREEN = 3;
            ImGui::EndTabItem();
          }
          ImGui::EndTabBar();
        }
      }
      ImGui::EndChild();
    }
    ImGui::EndChild();

    ImGui::SameLine();

    ImGui::BeginChild("System Menu", ImVec2(0, ImGui::GetContentRegionAvail().y), false, flags_c);
    {
      // Main Menu
      if (DISPLAY_MENU == 0)
      {
        if (ImGui::Button("Test", ImVec2(75, 75)))
        {
          // WINDOW_CLOSE = true;
        }

        if (ImGui::Button("Show\nDemo\nWindow", ImVec2(75, 75)))
        {
          //show_demo_window = true;
        }

        if (ImGui::Button("Show\nHellow\nWorld", ImVec2(75, 75)))
        {
          //show_hello_world = !show_hello_world;
        }

        if (true)
        {
          ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(7.0f, 0.0f, 0.6f));
          ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(7.0f, 0.0f, 0.7f));
          ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(7.0f, 0.0f, 0.8f));
          ImGui::Button("Show\nDemo\nWindow", ImVec2(75, 75));
          ImGui::PopStyleColor(3);
        }
        else
        {
          ImGui::Button("Show\nDemo\nWindow", ImVec2(75, 75));
        }

        if (ImGui::IsItemClicked(0))
        {
          //show_demo_window = !show_demo_window;
        }

        if (ImGui::Button("System 2", ImVec2(75, 75)))
        {
          DISPLAY_MENU = 0;
        }

        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(7.0f, 0.6f, 0.6f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(7.0f, 0.7f, 0.7f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(7.0f, 0.8f, 0.8f));
        if (ImGui::Button("Exit\nExit", ImVec2(75, 75)))
        {
          WINDOW_CLOSE = true;
        }
        ImGui::PopStyleColor(3);

        if (ImGui::Button("Main", ImVec2(75, 75)))
        {
          DISPLAY_MENU = 0;
        }
      }

      // Menu
      if (DISPLAY_MENU == 1)
      {
        if (ImGui::Button("System 3", ImVec2(75, 75)))
        {
          DISPLAY_MENU = 0;
        }

        if (ImGui::Button("System 4", ImVec2(75, 75)))
        {
          DISPLAY_MENU = 0;
        }

        ImGui::BeginDisabled();
        if (ImGui::Button("Test", ImVec2(75, 75)))
        {
          // WINDOW_CLOSE = true;
        }
        ImGui::EndDisabled();

        if (ImGui::InvisibleButton("Test", ImVec2(75, 75)))
        {
          // WINDOW_CLOSE = true;
        }

        if (ImGui::Button("Test", ImVec2(75, 75)))
        {
          // WINDOW_CLOSE = true;
        }

        if (ImGui::Button("Test", ImVec2(75, 75)))
        {
          // WINDOW_CLOSE = true;
        }

        if (ImGui::Button("Main", ImVec2(75, 75)))
        {
          DISPLAY_MENU = 0;
        }
      }

      if (DISPLAY_MENU == 2)
      {
        if (ImGui::Button("Test", ImVec2(75, 75)))
        {
          // WINDOW_CLOSE = true;
        }

        if (ImGui::Button("Test", ImVec2(75, 75)))
        {
          // WINDOW_CLOSE = true;
        }

        if (ImGui::Button("Test", ImVec2(75, 75)))
        {
          // WINDOW_CLOSE = true;
        }

        if (ImGui::Button("Test", ImVec2(75, 75)))
        {
          // WINDOW_CLOSE = true;
        }

        if (ImGui::Button("Test", ImVec2(75, 75)))
        {
          // WINDOW_CLOSE = true;
        }

        if (ImGui::Button("Test", ImVec2(75, 75)))
        {
          // WINDOW_CLOSE = true;
        }

        if (ImGui::Button("Main", ImVec2(75, 75)))
        {
          DISPLAY_MENU = 0;
        }
      }

      if (DISPLAY_MENU == 3)
      {
        if (ImGui::Button("Test", ImVec2(75, 75)))
        {
          // WINDOW_CLOSE = true;
        }

        if (ImGui::Button("Test", ImVec2(75, 75)))
        {
          // WINDOW_CLOSE = true;
        }

        if (ImGui::Button("Test", ImVec2(75, 75)))
        {
          // WINDOW_CLOSE = true;
        }

        if (ImGui::Button("Test", ImVec2(75, 75)))
        {
          // WINDOW_CLOSE = true;
        }

        if (ImGui::Button("Test", ImVec2(75, 75)))
        {
          // WINDOW_CLOSE = true;
        }

        if (ImGui::Button("Test", ImVec2(75, 75)))
        {
          // WINDOW_CLOSE = true;
        }

        if (ImGui::Button("Main", ImVec2(75, 75)))
        {
          DISPLAY_MENU = 0;
        }
      }
    }
    ImGui::EndChild();

  }
  ImGui::End();

  // Rendering
  ImGui::Render();
  int display_w, display_h;
  glfwGetFramebufferSize(window, &display_w, &display_h);
  glViewport(0, 0, display_w, display_h);
  glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);

  ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
  //glUseProgram(last_program);

  glfwMakeContextCurrent(window);
  glfwSwapBuffers(window);
}

void SCREEN4::shutdown()
{
  ImGui_ImplOpenGL2_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();
}

void SCREEN4::printw(string Text)
{
  CONSOLE_TEXT = CONSOLE_TEXT + Text + "\n";
}

// ---------------------------------------------------------------------------------------
#endif