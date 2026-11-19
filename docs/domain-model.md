# Domain model

This model matches the code at milestone **m1**. It is the vocabulary of the renderer, not a full UML dump of every helper.

## Core concepts

| Concept | Responsibility | Main types |
|---|---|---|
| **Vector** | 3D direction or displacement; arithmetic, length, normalisation, dot product | `math::` / `Vector` |
| **Colour** | RGB intensity in `[0, 1]` | `Colour` |
| **Ray** | Half-line: origin + direction; `at(t)` gives a point | `Ray` |
| **Hit** | Nearest intersection in front of the ray: `t`, point, unit normal, material | `HitInfo` |
| **Shape** | Anything that can answer `hit(ray)` | abstract `Shape` |
| **Sphere** | Ball: centre, radius, material | `Sphere` |
| **Plane** | Infinite plane: point, normal, material | `Plane` |
| **Material** | How a surface turns normal + light direction into a colour | abstract `Material` |
| **Flat / Lambert** | Constant colour vs diffuse (n·L) shading | `FlatShader`, `LambertShader` |
| **Scene** | Owns shapes, stores `toLight`, finds `nearestHit` | `Scene` |
| **Camera** | Turns pixels into rays; `trace` and `render` a scene | `Camera` |
| **Image** | Width × height grid of colours; `setPixel` | `Image` |
| **ImageSaver** | Strategy to write an image to disk | `ImageSaver`, `PngSaver` |

## Relationships

```text
Camera --trace/render--> Scene
Scene  --owns *--> Shape
Shape  --hit--> HitInfo
HitInfo --uses--> Material
Sphere / Plane --are--> Shape
FlatShader / LambertShader --are--> Material
Camera --produces--> Image
PngSaver --saves--> Image
```

- **Geometry vs appearance:** a shape knows *where* it is hit; its material knows *how it looks*.
- **Scene vs camera:** the scene is the world (objects + light direction); the camera asks what is seen along each ray.
- **Dependency inversion:** `trace` / `render` depend on `Scene` and `Shape`, not on `Sphere` or `Plane`. Concrete shapes are chosen in `main`.

## Rendering loop (m1)

1. For each pixel, the camera builds a `Ray`.
2. `Scene::nearestHit` asks every shape and keeps the smallest `t > 0`.
3. If there is no hit, the pixel is black.
4. If there is a hit, `material->shade(normal, toLight)` yields the colour.
5. `PngSaver` writes the image (m1: `image.png`).

## Deliberate limits at m1

- One directional light (`toLight`), no point-light falloff in the shader API used by `trace`.
- No shadows (a floor hit does not test occlusion toward the light).
- Materials are referenced from shapes and currently created in `main` (lifetime must outlive the scene's shapes).
