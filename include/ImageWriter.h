#pragma once

#ifndef IMAGEWRITER_H
#define IMAGEWRITER_H

#include "Image.h"

class ImageWriter {
public:
    virtual bool write(Image img) = 0;
};

#endif