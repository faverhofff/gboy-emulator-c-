#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include "base.h"
#include "memory_viewer.h"

void MemoryViewer::Render()
{
    if (ImGui::Begin("Memory Viewer", nullptr))
    {
        ImGui::SetWindowSize(ImVec2(1024, 300));
        ImGui::SetWindowPos(ImVec2(0, 500));
    }

    ImGui::End();
}