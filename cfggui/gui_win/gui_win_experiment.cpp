/* ************************************************************************************************/ // clang-format off
// flipflip's cfggui
//
// Copyright (c) 2021 Philippe Kehl (flipflip at oinkzwurgl dot org),
// https://oinkzwurgl.org/hacking/ubloxcfg
//
// This program is free software: you can redistribute it and/or modify it under the terms of the
// GNU General Public License as published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
// even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with this program.
// If not, see <https://www.gnu.org/licenses/>.

#include <cstring>
#include <cmath>

#include "ff_stuff.h"

#include "GL/gl3w.h"
#include "nanovg.h"

#include "gui_inc.hpp"

#include "gui_win_experiment.hpp"

/* ****************************************************************************************************************** */

GuiWinExperiment::GuiWinExperiment() :
    GuiWin("Experiments"),
    _openFileDialog{_winName + "OpenFileDialog"},
    _saveFileDialog{_winName + "SaveFileDialog"},
    _running{false}
{
    _winSize = { 100, 50 };
    _winFlags |= ImGuiWindowFlags_NoDocking;
}

GuiWinExperiment::~GuiWinExperiment()
{
}

// ---------------------------------------------------------------------------------------------------------------------

void GuiWinExperiment::DrawWindow()
{
    if (!_DrawWindowBegin())
    {
        return;
    }

    if (ImGui::BeginTabBar("Tabs"))
    {
        if (ImGui::BeginTabItem("GuiWinFileDialog"))
        {
            _DrawGuiWinFileDialog();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("GuiWidgetOpenGl"))
        {
            _DrawGuiWidgetOpenGl();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("GuiNotify"))
        {
            _DrawGuiNotify();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("GuiWidgetMap"))
        {
            _DrawGuiWidgetMap();
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    _DrawWindowEnd();
}

// ---------------------------------------------------------------------------------------------------------------------

void GuiWinExperiment::_DrawGuiWinFileDialog()
{
    if (ImGui::Button("Open a file..."))
    {
        if (!_openFileDialog.IsInit())
        {
            _openFileDialog.InitDialog(GuiWinFileDialog::FILE_OPEN);
            _openFileDialog.SetDirectory("/usr/share/doc");
        }
        else
        {
            _openFileDialog.Focus();
        }
    }
    ImGui::SameLine();
    ImGui::Text("--> %s", _openFilePath.c_str());


    if (ImGui::Button("Save a file..."))
    {
        if (!_saveFileDialog.IsInit())
        {
            _saveFileDialog.InitDialog(GuiWinFileDialog::FILE_SAVE);
            _saveFileDialog.SetFilename("saveme.txt");
            _saveFileDialog.SetTitle("blablabla...");
            //_saveFileDialog->SetConfirmOverwrite(false);
        }
        else
        {
            _saveFileDialog.Focus();
        }
    }
    ImGui::SameLine();
    ImGui::Text("--> %s", _saveFilePath.c_str());


    if (_openFileDialog.IsInit())
    {
        if (_openFileDialog.DrawDialog())
        {
            _openFilePath = _openFileDialog.GetPath();
            DEBUG("open file done");
        }
    }
    if (_saveFileDialog.IsInit())
    {
        if (_saveFileDialog.DrawDialog())
        {
            _saveFilePath = _saveFileDialog.GetPath();
            DEBUG("save file done");
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void GuiWinExperiment::_DrawGuiWidgetOpenGl()
{
    // https://learnopengl.com/Advanced-OpenGL/Framebuffers

    if (ImGui::Button(_running ? "stop##running" : "start##running"))
    {
        if (!_running)
        {
            _running = true;
        }
        else
        {
            _running = false;
        }
    }

    if (_running)
    {
        if (_gl.BeginDraw())
        {
            NVGcontext *vg = (NVGcontext *)_gl.NanoVgBeginFrame();

            nvgBeginPath(vg);
            nvgRect(vg, 100,100, 120,30);
            nvgFillColor(vg, nvgRGBA(255,192,0,255));
            nvgFill(vg);

            _gl.NanoVgDebug();

            _gl.NanoVgEndFrame();

            // more OpenGL here...

            _gl.EndDraw();
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void GuiWinExperiment::_DrawGuiNotify()
{
    if (ImGui::Button("Notice: title, text"))
    {
        GuiNotify::Notice("Hear, hear!", "blabla");
    }
    if (ImGui::Button("Notice: title, no text"))
    {
        GuiNotify::Notice("Hear, hear!", "");
    }
    if (ImGui::Button("Error: title, text"))
    {
        GuiNotify::Error("Ouch!", "blabla");
    }
    if (ImGui::Button("Warning: no title, text"))
    {
        GuiNotify::Warning("", "blabla", 10);
    }
    if (ImGui::Button("Success: title, looooong text"))
    {
        GuiNotify::Success("That worked!", "blabla blabla blabla blablablablablablablablablablablablablablablablablablablabla blabla blabla blabla blabla blabla blabla blabla blablablabla blabla blabla blabla blabla blabla blabla blabla blabla blabla blabla blabla blabla blabla blabla blabla blabla blabla blabla blabla blablablabla blabla blabla blabla blabla blabla blabla blabla blabla blabla blabla blabla blabla blabla blabla blabla blabla blabla blabla blabla blabla");
    }
    if (ImGui::Button("Message: title, no text"))
    {
        GuiNotify::Message("message", "");
    }
    if (ImGui::Button("Message: title, text"))
    {
        GuiNotify::Message("message", "text");
    }
    if (ImGui::Button("Message: no title, text"))
    {
        GuiNotify::Message("", "message");
    }
    if (ImGui::Button("Warning: no title, no text"))
    {
        GuiNotify::Warning("", "");
    }
}

// ---------------------------------------------------------------------------------------------------------------------

void GuiWinExperiment::_DrawGuiWidgetMap()
{
    if (_map)
    {
        if (ImGui::Button("stop"))
        {
            _map = nullptr;
        }
        ImGui::SameLine();
        if (ImGui::Button("load"))
        {
            _map->SetSettings( GuiSettings::GetValue(_winName + ".map") );
        }
        ImGui::SameLine();
        if (ImGui::Button("save"))
        {
            GuiSettings::SetValue( _winName + ".map", _map->GetSettings() );
        }
    }
    else
    {
        if (ImGui::Button("start"))
        {
            _map = std::make_unique<GuiWidgetMap>();
        }
    }

    if (_map)
    {
        if (_map->BeginDraw())
        {
            _map->EndDraw();
        }
    }
}

/* ****************************************************************************************************************** */
