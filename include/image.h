#pragma once

#include <color.h>
#include <spectrum.h>
#include <observer.h>

namespace spdi {
    class Image {
    public:
        Image(int width, int height, int num_wavelengths, colorama::Observer * observer);

        void set_pixel(int x, int y, const colorama::Spectrum& spectrum);
        void add_to_pixel(int x, int y, const colorama::Spectrum& spectrum);
        colorama::Spectrum get_pixel(int x, int y) const;

        // RGB 
        // RGB methods
        void set_pixel(int x, int y, double r, double g, double b);
        void add_to_pixel(int x, int y, double r, double g, double b);
        void add_to_pixel(int x, int y, const colorama::Color& color);
        void set_pixel(int x, int y, const colorama::Color& color);
        colorama::Color get_pixel_rgb(int x, int y) const;
        double max_value() const;
        void normalize();

        int width() const { return width_; }
        int height() const { return height_; }
        int num_wavelengths() const { return num_wavelengths_; }

    protected:
        int width_;
        int height_;
        int num_wavelengths_;
        int row_size_;
        std::vector<double> image_buffer_;
        colorama::Observer * observer_;
    };
}