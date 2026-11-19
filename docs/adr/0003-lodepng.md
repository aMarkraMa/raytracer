# 0003. Encode PNG files with LodePNG

## Status

Accepted

## Context

`PngSaver` must write an `Image` to disk. Alternatives considered:

- **libpng** — industry standard, but needs system packages and more CMake glue.
- **stb_image_write** — single header, easy, less focused on PNG alone.
- **LodePNG** — two source files, zlib licence, no system dependency; can be pinned with CMake `FetchContent`.

## Decision

Use LodePNG, fetched and pinned to commit `7b2893e35891c0c85bee5595caafaf3c2044b409`, and call it from `PngSaver`.

## Consequences

- Positive: no OS package install; reproducible pin; fits a student project.
- Negative: another vendored dependency in the build tree; not a full imaging suite (only what we need for PNG out).
