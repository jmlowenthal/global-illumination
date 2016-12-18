#include "TGAImageWriter.h"

bool TGAImageWriter::write(Image img) {
    char header[] = {
        0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        (char)(img.getWidth() & 0x00ff),  (char)(img.getWidth() >> 8),
        (char)(img.getHeight() & 0x00ff), (char)(img.getHeight() >> 8),
        24, 0
    };
    file.write(header, 18);
    
    char* data = new char[3 * img.getWidth() * img.getHeight()];
    int i = 0;
    for (int y = 0; y < img.getHeight(); ++y) {
        for (int x = 0; x < img.getWidth(); ++x) {
            data[i++] = img.getPixelB(x, y);
            data[i++] = img.getPixelG(x, y);
            data[i++] = img.getPixelR(x, y);
        }
    }
    file.write(data, 3 * img.getWidth() * img.getHeight());
}