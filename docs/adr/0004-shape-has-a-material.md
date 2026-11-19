# 0004. A shape has a material

## Status

Accepted

## Context

Shading could live in several places. Alternatives considered:

- **Colour hardcoded in `trace`** — fastest to start, cannot vary per object.
- **Colour stored on the shape** — simple, but mixes geometry with appearance and blocks strategies such as Lambert vs flat.
- **Shape holds a `Material`** — geometry answers `hit`; appearance answers `shade` (Strategy), like `ImageSaver` / `PngSaver`.

## Decision

Every concrete `Shape` (`Sphere`, `Plane`) stores a reference to a `Material`. After `Scene::nearestHit`, `trace` calls `material->shade(normal, toLight)`.

## Consequences

- Positive: new materials do not change intersection code; new shapes do not change shaders.
- Negative: materials must outlive the shapes that refer to them (current design uses references owned by `main`); lifetime must stay clear.
