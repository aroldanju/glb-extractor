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

#include "glbencoder.h"

GlbEncoder::GlbEncoder(const char *key, uint32_t length) :
    Encoder(key, length)
{
}


void GlbEncoder::encode(char *data, uint32_t length)    {
    // TODO
}

void GlbEncoder::decode(char *data, uint32_t length)    {
    unsigned char previousByte = this->key[this->position];

    for (int i = 0; i < length; i++) {
        unsigned char encodedByte = data[i];

    	unsigned char byte = encodedByte - this->key[this->position++];
    	if (this->position >= this->length) {
            this->position = 0;
    	}

    	byte -= previousByte;
    	byte &= 0xff;

    	data[i] = byte;

    	previousByte = encodedByte;
    }
}
