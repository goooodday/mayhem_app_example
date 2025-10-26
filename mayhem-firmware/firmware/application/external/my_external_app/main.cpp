/*
 * Copyright (C) 2023 Bernd Herzog
 *
 * This file is part of PortaPack.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include "my_external_app.hpp"

namespace ui::external_app::my_external_app {
void initialize_app(ui::NavigationView& nav) {
    nav.push<NewExternalAppView>();
}
}  // namespace ui::external_app::ui_new_external_app

extern "C" {

__attribute__((section(".external_app.app_my_external_app.application_information"), used)) application_information_t _application_information_ui_new_external_app = {
    /*.memory_location = */ (uint8_t*)0x00000000,
    /*.externalAppEntry = */ ui::external_app::my_external_app::initialize_app,
    /*.header_version = */ CURRENT_HEADER_VERSION,
    /*.app_version = */ VERSION_MD5,
    /*.app_name = */ "NewExternalApp",
    /*.bitmap_data = */ {
        0x54,
        0x15,
        0x54,
        0x15,
        0xFF,
        0x7F,
        0xFC,
        0x1F,
        0xFF,
        0x7F,
        0xCC,
        0x19,
        0xAF,
        0x7A,
        0x6C,
        0x1B,
        0xEF,
        0x7B,
        0xEC,
        0x1B,
        0xFF,
        0x7F,
        0xFC,
        0x1F,
        0xFF,
        0x7F,
        0x54,
        0x15,
        0x54,
        0x15,
        0x00,
        0x00,
    },
    /*.icon_color = */ ui::Color::cyan().v,
    /*.menu_location = */ app_location_t::DEBUG,
    /*.desired_menu_position = */ -1,
    /*.m4_app_tag = portapack::spi_flash::image_tag_none */ {0, 0, 0, 0},
    /*.m4_app_offset = */ 0x00000000,  // will be filled at compile time
};
}
