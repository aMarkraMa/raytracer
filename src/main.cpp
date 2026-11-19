#include <iostream>
#include <memory>

#include "colour/colour.h"
#include "geometry/plane.h"
#include "geometry/sphere.h"
#include "io/png_saver.h"
#include "material/flat_shader.h"
#include "material/lambert_shader.h"
#include "math/vector.h"
#include "render/camera.h"
#include "scene/scene.h"

int main() {
    const int width = 400;
    const int height = 300;

    Camera camera(Vector(0.0, 0.0, 0.0));

    LambertShader red(Colour(1.0, 0.0, 0.0));
    FlatShader grey(Colour(0.8, 0.8, 0.8));

    Scene scene(Vector(-1.0, 1.0, -1.0).normalised());
    scene.add(std::make_unique<Sphere>(Vector(0.0, 0.0, 9.0), 5.0, red));
    scene.add(std::make_unique<Plane>(Vector(0.0, -5.0, 0.0), Vector(0.0, 1.0, 0.0), grey));

    Image image = camera.render(scene, width, height);

    PngSaver saver;
    const std::string outputPath = "image.png";
    saver.save(image, outputPath);

    std::cout << "Wrote " << outputPath << " (" << width << "x" << height << ")\n";
    return 0;
}
