#pragma once
#include <imgui_impl_sdl2.h>
#include <SDL_gesture.h>
#include "memory_viewer.h"
#ifndef _DEBUGGER_H
#define _DEBUGGER_H



class Debugger
{
public:
    Debugger();
    ~Debugger();

    void HandleEvent(SDL_Event& _event);
    void Render();

private:
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    ImGuiIO io;

    SDL_Window *mWindow;
    SDL_GLContext mGlContext;
    MemoryViewer mMemoryViewer;
};

#endif // _DEBUGGER_H
