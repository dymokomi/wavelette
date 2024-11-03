#pragma once

#include <vector>
#include <cstdio>
#include <string>
#include <observer.h>
#include <spectrum.h>
#include "image.h"
namespace spdi {

    class SPDImage : public Image {
    public:
        SPDImage(int width, int height, int num_wavelengths, colorama::Observer * observer) ;

        static SPDImage load(const char* filename, colorama::Observer * obs);
        void save(const char* filename, double gamma = 2.2, double exposure = 1.0);
        
        void save_spectrum(const char* filename);
        void load_spectrum(const char* filename);

        void set_pixel(int x, int y, const colorama::Spectrum& spectrum);
        colorama::Spectrum uv_value(double u, double v) const;

        double exposure_ = 1.0f;
        double gamma_ = 2.2f;
        int samples_ = 1024;
        int depth_ = 1;
        int light_source_ = 0;
        int observer_type_ = 0;
        int spectrum_type_ = 0;
        int render_mode_ = 0;
 
    };
}
