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

#include <iostream>
#include <sstream>
#include "glbencoder.h"
#include "glb.h"

using namespace std;

int main(int argc, char* argv[]) {
    cout << "GLB Extractor - GLB files extractor of Raptor - Call of the shadows DOS game." << endl;

    string glbFilename, outputDirectory = ".", encoderKey = "32768GLB";
    bool listFiles = false;
    stringstream ss;

    if (argc < 2) {
        cout << "usage: " << argv[0] << " GLB_FILE [options]" << endl;
        cout << "Options: " << endl;
        cout << "  --output dir ... Extract files in the specified directory." << endl;
        cout << "  --list ......... List files from GLB file. This option disable the exporting." << endl;
        cout << "  --key .......... Set the encoder key." << endl;
        cout << "  By default: --output " << outputDirectory << " --key " << encoderKey << endl;
        cout << endl;
        return 0;
    }

    glbFilename = string(argv[1]);

    for (int i = 2; i < argc; i++) {
        if (string(argv[i]) == "--output") {
            if (argc >= i + 1) {
                outputDirectory = string(argv[i + 1]);
                i++;
            }
            else {
                cout << "--output option need a parameter" << endl;
            }
        }
        else if (string(argv[i]) == "--list") {
            listFiles = true;
        }
        else if (string(argv[i]) == "--key") {
            if (argc >= i + 1) {
                encoderKey = string(argv[i + 1]);
                i++;
            }
            else {
                cout << "--key option need a parameter" << endl;
            }
        }
    }

    GlbEncoder glbEncoder(encoderKey.c_str(), encoderKey.length());
    Glb glb(glbFilename, glbEncoder);

    if (!glb.load())    {
        cout << "Error loading '" << glbFilename << "' GLB file." << endl;
        return 1;
    }

    for (auto& filename : glb.getFiles()) {
        if (listFiles) {
            cout << filename << endl;
        }
        else {
            try {
                File file = glb.fetchFile(filename);

                stringstream ss;
                ss << outputDirectory << "/" << filename;

                file.saveToFile(ss.str());
            }
            catch (exception &ex) {
                cout << "Error fetching file '" << filename << "'" << endl;
            }
        }
    }

    return 0;
}
