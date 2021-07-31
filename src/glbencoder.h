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

#ifndef __GLBENCODER_H
#define __GLBENCODER_H

#include "encoder.h"

class GlbEncoder : public Encoder {
public:
    GlbEncoder(const char *key, uint32_t length);
    virtual ~GlbEncoder() = default;

    void encode(char *data, uint32_t length) override;
    void decode(char *data, uint32_t length) override;
};

#endif // __GLBENCODER_H
