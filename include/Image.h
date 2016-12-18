#pragma once

#ifndef IMAGE_H
#define IMAGE_H

class Image {
private:
    char** data;
    int width, height;

public:
    Image(int w, int h) : width(w), height(h) {
        data = new char*[w];
        for (int i = 0; i < w; ++i) {
            data[i] = new char[h * 3];
        }
    }

    int getWidth() {
        return width;
    }

    int getHeight() {
        return height;
    }

    char getPixelR(int x, int y) {
        return data[x][y * 3];
    }

    void setPixelR(int x, int y, char v) {
        data[x][y * 3] = v;
    }

    char getPixelG(int x, int y) {
        return data[x][y * 3 + 1];
    }

    void setPixelG(int x, int y, char v) {
        data[x][y * 3 + 1] = v;
    }

    char getPixelB(int x, int y) {
        return data[x][y * 3 + 2];
    }

    void setPixelB(int x, int y, char v) {
        data[x][y * 3 + 2] = v;
    }
};

#endif