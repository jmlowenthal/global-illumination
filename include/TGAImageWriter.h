#pragma once

#ifndef TGAIMAGEWRITER_H
#define TGAIMAGEWRITER_H

#include "ImageWriter.h"
#include <fstream>
#include <string>

class TGAImageWriter : public ImageWriter {
private:
    std::ofstream file;

public:
    TGAImageWriter(std::string filename) : file(filename) {};
    virtual bool write(Image img);
};

#endif