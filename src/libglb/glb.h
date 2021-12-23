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

#ifndef __GLB_H
#define __GLB_H

#include "encoder.h"

#include <string>
#include <map>
#include <vector>
#include <memory>

typedef struct _glb_file_header {
    uint32_t flags;
    uint32_t offset;
    uint32_t length;
    char filename[16];
} GlbFileHeader;

class File {
public:
    File(const File &file);
    File(uint32_t length);
    virtual ~File() = default;

    char *getContent() const;
    uint32_t getLength() const;
    bool saveToFile(const std::string &filename);

private:
    uint32_t length;
    std::unique_ptr<char[]> content;
};

class Glb {
public:
    Glb(const std::string &path, Encoder &encoder);
    virtual ~Glb() = default;

    bool load();
    bool existsFile(const std::string& filename);
    std::vector<std::string> getFiles();
    File fetchFile(const std::string &filename);

private:
    Encoder &encoder;
    std::string path;
    GlbFileHeader readFileHeader(uint32_t index, std::ifstream &file);
    void decodeContent(char *content, uint32_t length, const char *key, uint32_t keyPosition);
    std::map<std::string, GlbFileHeader> fat;
};

#endif // __GLB_H
