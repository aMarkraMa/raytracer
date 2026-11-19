#include <iostream>
#include <memory>

#include "colour/colour.h"
#include "geometry/plane.h"
#include "geometry/sphere.h"
#include "io/png_saver.h"
#include "material/lambert_shader.h"
#include "math/vector.h"
#include "render/camera.h"
#include "render/image.h"
#include "scene/scene.h"

int main() {
    const unsigned int width = 400;
    const unsigned int height = 300;
    const double screenWidth = 2.0;

    Image image(width, height);
    Camera camera(Vector(0.0, 0.0, -3.0));

    LambertShader red(Colour(0.9, 0.2, 0.2));
    LambertShader grey(Colour(0.7, 0.7, 0.7));

    Scene scene(Vector(5.0, 5.0, -5.0));
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 0.0), 1.0, red));
    scene.add(std::make_unique<Plane>(Vector(0.0, -1.0, 0.0), Vector(0.0, 1.0, 0.0), grey));

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            Ray ray = camera.rayThroughPixel(x, y, width, height, screenWidth);
            Colour colour = camera.trace(ray, scene);
            image.setPixel(x, y, colour);
        }
    }

    PngSaver saver;
    const std::string outputPath = "output.png";
    saver.save(image, outputPath);

    std::cout << "Wrote " << outputPath << " (" << width << "x" << height << ")\n";
    return 0;
}
