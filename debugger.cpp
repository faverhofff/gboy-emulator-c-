#include <SDL.h>
#include <SDL_opengl.h>
#include "base.h"
#include "debugger.h"
#include <imgui_impl_opengl2.h>
#include "memory_viewer.h"


Debugger::Debugger()
{
    float main_scale = 1.0f; // Placeholder for content scale retrieval
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    mWindow = SDL_CreateWindow("Debugger", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)(1024 * main_scale), (int)(768 * main_scale), window_flags);
    if (mWindow == nullptr)
    {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        throw std::runtime_error("Failed to create SDL window");
    }

    mGlContext = SDL_GL_CreateContext(mWindow);
    SDL_GL_MakeCurrent(mWindow, mGlContext);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(mWindow, mGlContext);
    ImGui_ImplOpenGL2_Init();
}

Debugger::~Debugger()
{
    SDL_GL_DeleteContext(mGlContext);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Debugger::HandleEvent(SDL_Event& _event)
{
    ImGui_ImplSDL2_ProcessEvent(&_event);
}

void Debugger::Render()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    mMemoryViewer.Render();

    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(mWindow);
}