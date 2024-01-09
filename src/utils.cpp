//
// Created by Gianni on 9/01/2024.
//

#include "utils.hpp"

uint32_t get_max_refresh_rate()
{
    DEVMODE dev_mode;
    memset(&dev_mode, 0, sizeof(DEVMODE));
    dev_mode.dmSize = sizeof(DEVMODE);

    if (EnumDisplaySettings(nullptr, ENUM_CURRENT_SETTINGS, &dev_mode) == TRUE)
        return dev_mode.dmDisplayFrequency;
    else
        throw std::runtime_error("get_max_refresh_rate() - Failed to retrieve monitor refresh rate\n");
}