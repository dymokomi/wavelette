#include "image.h"

namespace spdi {
    Image::Image(int width, int height, int num_wavelengths, colorama::Observer * observer) 
        : width_(width), height_(height), num_wavelengths_(num_wavelengths), observer_(observer) {
        row_size_ = width_ * num_wavelengths_;
        image_buffer_ = std::vector<double>(width * height * num_wavelengths);
        std::fill(image_buffer_.begin(), image_buffer_.end(), 0.0f);
    }

    void Image::set_pixel(int x, int y, const colorama::Spectrum& spectrum) {
        int index = y * row_size_ + x * num_wavelengths_;
        for (int i = 0; i < num_wavelengths_; ++i) {
            image_buffer_[index + i] = spectrum[i];
        }
    }
    void Image::add_to_pixel(int x, int y, const colorama::Spectrum& spectrum) {
        int index = y * row_size_ + x * num_wavelengths_;
        for (int i = 0; i < num_wavelengths_; ++i) {
            image_buffer_[index + i] += spectrum[i];
        }
    }
    colorama::Spectrum Image::get_pixel(int x, int y) const {
        int index = y * row_size_ + x * num_wavelengths_;
        return colorama::Spectrum(image_buffer_.data() + index);
    }

    // RGB 
    // RGB methods
    void Image::set_pixel(int x, int y, double r, double g, double b) {
        set_pixel(x, y, colorama::Spectrum(colorama::Color(r, g, b)));
    }

    void Image::add_to_pixel(int x, int y, double r, double g, double b) {
        add_to_pixel(x, y, colorama::Spectrum(colorama::Color(r, g, b)));
    }

    void Image::add_to_pixel(int x, int y, const colorama::Color& color) {
        add_to_pixel(x, y, color.x(), color.y(), color.z());
    }

    void Image::set_pixel(int x, int y, const colorama::Color& color) {
        set_pixel(x, y, color.x(), color.y(), color.z());
    }

    colorama::Color Image::get_pixel_rgb(int x, int y) const {
        return get_pixel(x, y).to_rgb(observer_);
    }

    double Image::max_value() const {
        double max_value = 0.0f;
        for (const auto& value : image_buffer_) {
            max_value = std::max(max_value, value);
        }
        return max_value;
    }
    void Image::normalize() {
        double max_value = 0.0f;

        // Find the maximum value in the image
        for (const auto& value : image_buffer_) {
            max_value = std::max(max_value, value);
        }

        // Avoid division by zero
        if (max_value > 0.0f) {
            // Normalize all values
            for (auto& value : image_buffer_) {
                value /= max_value;
            }
        }
    }
}
