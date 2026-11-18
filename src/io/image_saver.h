#pragma once

#include "render/image.h"

class ImageSaver {
public:
    virtual ~ImageSaver() = default;
    virtual void save(Image& image) = 0;
};
