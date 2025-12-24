#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include "base.h"
#include "mmu.h"
#include "memory_viewer.h"

void MemoryViewer::Render()
{
    ImGui::SetNextWindowPos(ImVec2(0, 468));
    if (ImGui::Begin("Memory Viewer", nullptr))
    {
        ImGui::BeginChild("##scrolling", ImVec2(0, 0));

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

        int memSize = mMmu.GetRomSize();
        const u8* data = mMmu.GetRom();

        int addrDigitsCount = 0;
        for (int n = memSize - 1; n > 0; n >>= 4)
            addrDigitsCount++;

        float glyphWidth = ImGui::CalcTextSize("F").x;
        float cellWidth = glyphWidth * 3;
        float lineHeight = ImGui::GetTextLineHeight();
        int lineTotalCount = (int)((memSize + mNumRows - 1) / mNumRows );
        ImGuiListClipper clipper;
        clipper.Begin(lineTotalCount, lineHeight);

        
        while (clipper.Step()) {
            for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
            {
                int addr = i * mNumRows;
                ImGui::Text("%0*X: ", addrDigitsCount, addr);
                ImGui::SameLine();

                float lineStartX = ImGui::GetCursorPosX();

                for (int n = 0; n < mNumRows && addr < memSize; n++, addr++)
                {
                    ImGui::SameLine(lineStartX + cellWidth * n);
                    ImGui::Text("%02X ", data[addr]);
                }

                ImGui::SameLine(lineStartX + cellWidth * mNumRows + glyphWidth * 2);

                ImVec2 screen_pos = ImGui::GetCursorScreenPos();
                ImGui::GetWindowDrawList()->AddLine(ImVec2(screen_pos.x - glyphWidth, screen_pos.y - 9999), ImVec2(screen_pos.x - glyphWidth, screen_pos.y + 9999), ImColor(ImGui::GetStyle().Colors[ImGuiCol_Border]));

                addr = i * mNumRows;
                for (int n = 0; n < mNumRows && addr < memSize; n++, addr++)
                {
                    if (n > 0) ImGui::SameLine();
                    int c = data[addr];
                    ImGui::Text("%c", (c >= 32 && c < 128) ? c : '.');
                }
            }
        }

        clipper.End();
        ImGui::PopStyleVar(2);

        ImGui::EndChild();
        
// Works fine
//mMemoryeditor.DrawWindow("Memory Viewer", nullptr, 0);

            //bool Open = true;
            //if (ImGui::Begin("Memory Viewer", &Open, ImGuiWindowFlags_NoScrollbar))
            //{
            //    ImGui::BeginChild("##scrolling", ImVec2(0, -ImGui::GetItemsLineHeigthWithSpacing()), ImGuiChildFlags_None, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoNav);
            //}

            //ImGui::End();

        //ImGui::BeginChild("##scrolling", ImVec2(0, 0));

        //ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
        //ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

        //int addrDigitsCount = 0;
        //for (int n = MMU::BootRomSize - 1; n > 0; n >>= 4)
        //    addrDigitsCount++;

        //float glypWidth = ImGui::CalcTextSize("F").x;
        //float cellWidth = glypWidth * 3;
        //float lineHeight = ImGui::GetTextLineHeight();
        //int lineTotalCount = (int)((MMU::BootRomSize + nNumRows - 1) / nNumRows);
        //ImGuiListClipper clipper; // lineTotalCount, lineHeight);

        //for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
        //{
        //    int addr = i * nNumRows;
        //    //ImGui::Text("%0*X:", addr_digits)
        //}

        //ImGuiStyle& style = ImGui::GetStyle();
        //const float OptFooterExtraHeight = 0.0f;
        //float height_separator = style.ItemSpacing.y;
        //float footer_height = OptFooterExtraHeight;
        //
        ////if (OptShowOptions)
        //    //footer_height += height_separator + ImGui::GetFrameHeightWithSpacing() * 1;
        ////if (OptShowDataPreview)
        //    footer_height += height_separator + ImGui::GetFrameHeightWithSpacing() * 1 + ImGui::GetTextLineHeightWithSpacing() * 3;        
        //ImGui::BeginChild("##scrolling", ImVec2(-FLT_MIN, -footer_height), ImGuiChildFlags_None, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoNav);

        // Render();

        //ImGui::EndChild();


    }

    ImGui::End();
}

