/*********************************************************************
 * CanInterfaceLinux
 *
 * Copyright (C) 2024 Marcel Maage
 *
 * This library is free software; you twai redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * LICENSE file for more details.
 */

#include "trainBoxMaerklin/CanInterfaceLinux.h"
#include <iostream>

CanInterfaceLinux::CanInterfaceLinux(twai_timing_config_t timingConfig, gpio_num_t txPin, gpio_num_t rxPin)
: m_timingConfig(timingConfig),
m_txPin(txPin),
m_rxPin(rxPin)
{
}

CanInterfaceLinux::~CanInterfaceLinux()
{
}

void CanInterfaceLinux::begin()
{

}

void CanInterfaceLinux::cyclic()
{
    /*
    Can::Message frame;
    while (receive(frame, 0))
    {
        notify(&frame);
    }
    errorHandling();
*/

}

bool CanInterfaceLinux::transmit(Can::Message &frame, uint16_t timeoutINms)
{
    return true;
}

bool CanInterfaceLinux::receive(Can::Message &frame, uint16_t timeoutINms)
{
    return true;
}

void CanInterfaceLinux::errorHandling()
{

}
