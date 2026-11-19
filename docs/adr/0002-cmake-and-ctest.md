# 0002. Build with CMake and run tests with CTest

## Status

Accepted

## Context

We need a standard way to compile the library, the app, and the tests. Alternatives considered:

- **Raw Makefiles only** — fine for a tiny demo, but hard to grow (dependencies such as LodePNG, multiple test binaries).
- **CMake + CTest** — common for C++ courses and integrates FetchContent and `ctest`.
- **Meson / Bazel** — powerful, but extra learning cost for this module.

A root `Makefile` still wraps the common commands (`make build|test|run|clean`) for a familiar entry point.

## Decision

Use CMake (C++17) as the build system and CTest to run the test executables. Keep a thin Makefile that calls CMake/CTest.

## Consequences

- Positive: clear targets for library, app and tests; FetchContent can pin third-party code.
- Negative: students must learn a little CMake; the generated `build/` directory must stay out of git.
