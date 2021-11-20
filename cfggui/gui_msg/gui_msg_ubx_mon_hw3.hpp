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

#ifndef __GUI_MSG_UBX_MON_HW3_HPP__
#define __GUI_MSG_UBX_MON_HW3_HPP__

#include <memory>

#include "imgui.h"
#include "gui_msg.hpp"

/* ***** UBX-MON-HW3 renderer *************************************************************************************** */

class GuiMsgUbxMonHw3 : public GuiMsg
{
    public:
        GuiMsgUbxMonHw3(std::shared_ptr<Receiver> receiver = nullptr, std::shared_ptr<Logfile> logfile = nullptr);

        bool Render(const std::shared_ptr<Ff::ParserMsg> &msg, const FfVec2 &sizeAvail) final;

    private:

        static const std::vector<StatusFlags> _rtcFlags;
        static const std::vector<StatusFlags> _xtalFlags;
        static const std::vector<StatusFlags> _safebootFlags;

};

/* ****************************************************************************************************************** */
#endif // __GUI_MSG_UBX_MON_HW3_HPP__
