# 0001. Use a Dev Container for the build and test environment

## Status

Accepted

## Context

The project must build and run tests the same way on different machines (macOS, Linux, CI later). Alternatives considered:

- **Install tools only on the host** — simple at first, but versions of CMake, compilers and libraries drift between students and graders.
- **A full VM** — reproducible, but heavy for a small C++ ray tracer.
- **A Dev Container** — a Dockerfile-based environment opened from Cursor/VS Code, with CMake and a C++ toolchain preinstalled.

## Decision

Provide a Dev Container under `.devcontainer/` so `make build`, `make test` and `make run` use the same Linux toolchain wherever the project is opened.

## Consequences

- Positive: graders and classmates can reproduce `make test` without matching the author's laptop setup.
- Negative: first open needs Docker and a container download; some host-only workflows are unused inside the container.
