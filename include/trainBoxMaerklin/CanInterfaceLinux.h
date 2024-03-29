/*********************************************************************
 * CanInterfaceLinux
 *
 * Copyright (C) 2024 Marcel Maage
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * LICENSE file for more details.
 */

#pragma once

#include "trainBoxMaerklin/CanInterface.h"

class CanInterfaceLinux : public CanInterface
{
public:
    CanInterfaceLinux(char* interface);
    virtual ~CanInterfaceLinux();

    void begin() override;

    void cyclic();

    bool transmit(Can::Message &frame, uint16_t timeoutINms) override;

    bool receive(Can::Message &frame, uint16_t timeoutINms) override;

private:
    void errorHandling();
};
