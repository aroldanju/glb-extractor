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

#include "glb.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <sstream>

File::File(const File &file)  :
    length(file.length),
    content(nullptr)
{
    this->content = std::make_unique<char[]>(length);
    memcpy(this->content.get(), file.content.get(), length);
}

File::File(uint32_t length) :
    length(length),
    content(nullptr)
{
    this->content = std::make_unique<char[]>(length);
}

char *File::getContent() const  {
    return this->content.get();
}

uint32_t File::getLength() const  {
    return this->length;
}

bool File::saveToFile(const std::string &filename)    {
    std::ofstream file(filename, std::ios_base::out | std::ios_base::binary);
    if (!file.is_open()) {
        return false;
    }

    file.write(this->content.get(), this->length);

    file.close();

    return true;
}

Glb::Glb(const std::string &path, Encoder &encoder) :
    encoder(encoder),
    path(path)
{
}

GlbFileHeader Glb::readFileHeader(uint32_t index, std::ifstream &file)    {
    GlbFileHeader header;

    file.read((char*)&header, sizeof(GlbFileHeader));
    this->encoder.reset(1);
    this->encoder.decode((char*)&header, sizeof(GlbFileHeader));

    return header;
}

bool Glb::existsFile(const std::string& filename)    {
    return this->fat.find(filename) != this->fat.end();
}

bool Glb::load() {

    std::string lastFilename = "";
    int i = 0;
    uint32_t fileLength = 0;
    uint32_t offset = 0;
    int fileIndex = 0;

	// std::cout << "[Glb::load]: Loading GLB file '" << filename << "'..." << std::endl;

    std::ifstream file(this->path.c_str(), std::ios_base::in);
    if (!file.is_open()) {
        return false;
    }

    file.seekg(0, std::ios_base::end);
    fileLength = file.tellg();
    file.seekg(0, std::ios_base::beg);

    do {
        GlbFileHeader header = readFileHeader(i++, file);

        if (i == 1) {
            // First entry of FAT: number of files
            continue;
        }

        // File with no name: extension of last read file
        if (std::string(header.filename).length() == 0) {
            std::stringstream extensionFilename;
            extensionFilename << lastFilename << "_" << fileIndex++;
            strcat(header.filename, extensionFilename.str().c_str());
        }
        else {
            lastFilename = std::string(header.filename);
            fileIndex = 0;
        }

        this->fat.insert(
            std::pair<std::string, GlbFileHeader>(
                std::string(header.filename), header
            )
        );

        // std::cout << "Filename #" << i << ": " << std::string(header.filename) << " at " << header.offset << " with " << header.length << " bytes" << std::endl;

        offset = header.offset;

    } while (offset != fileLength);

    file.close();

    return true;
}

std::vector<std::string> Glb::getFiles() {
    std::vector<std::string> files;

    for (auto& file : this->fat) {
        files.push_back(file.first);
    }

    return files;
}

File Glb::fetchFile(const std::string &filename) {
    auto fatFile = this->fat.find(filename);

    if (fatFile == this->fat.end()) {
        throw std::exception();
    }

    std::ifstream glbFile(this->path, std::ios_base::in);
    if (!glbFile.is_open())    {
        throw std::exception();
    }

    File file(fatFile->second.length);
    glbFile.seekg(fatFile->second.offset, std::ios_base::beg);
    glbFile.read(file.getContent(), fatFile->second.length);

    if (fatFile->second.flags == 1) {
        this->encoder.reset(1);
        this->encoder.decode(file.getContent(), fatFile->second.length);
    }

    glbFile.close();

    return file;
}
