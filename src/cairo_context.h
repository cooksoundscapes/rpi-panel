#pragma once
#include <cairo/cairo.h>
#include <cstdlib>
#include <cstring>
#include <iostream>

class Pencil {
public:
    cairo_t* cr;
    cairo_surface_t* surface;
    unsigned char* data;
    int width, height;

    Pencil(int w, int h) : width{w}, height{h} {}

    void beginDrawing() {
        auto format = CAIRO_FORMAT_A8;
        int stride = cairo_format_stride_for_width(format, width);
        data = (unsigned char*) malloc(stride * height);
        memset(data, 0, stride * height);
        std::cout << "size of data: " << stride*height << '\n';
        surface = cairo_image_surface_create_for_data(data, format, width, height, stride);
    }

    unsigned char* endDrawing() {
        cairo_surface_flush(surface);
        return data;
    }

    void drawText(std::string text) const {
        
    }

    // testing functions
    void testCircle() {
        cr = cairo_create(surface);
        cairo_set_source_rgb(cr, 0xFF, 0xFF, 0xFF);
        cairo_move_to(cr, 10, 10);
        cairo_arc(cr, 10, 10, 10, 0, 180);
        cairo_fill(cr);
    }
};