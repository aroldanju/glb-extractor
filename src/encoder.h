/*
 *  GLB extractor - GLB files extractor of Raptor - Call of the shadows game.
 *  Copyright (C) 2021  A. Roldán
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __ENCODER_H
#define __ENCODER_H

#include <cstdint>
#include <memory>

class Encoder {
public:
    Encoder(const char *key, uint32_t length, uint32_t position = 0);
    virtual ~Encoder() = default;

    void reset(uint32_t position = 0);

    virtual void encode(char *data, uint32_t length) = 0;
    virtual void decode(char *data, uint32_t length) = 0;

protected:
    uint32_t position;
    uint32_t length;
    std::unique_ptr<char[]> key;
};

#endif // __ENCODER_H
