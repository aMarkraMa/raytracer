#pragma once

#include "io/image_saver.h"

class PngSaver : public ImageSaver {
public:
    void save(Image& image) override;
};
