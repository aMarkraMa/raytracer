# Raytracer

An individual C++ ray tracer project for the HETIC module *Veille, innovation et prospective* and the associated software engineering courses.

The project explores how to build rendering software that developers can understand, test, maintain and extend. The course uses a fictional film studio in 2035 as its client; market research describes products available when the sources were checked, not predictions about 2035.

## Documentation

- [Discovery report — milestone m0](docs/discovery/discovery-report.md)
- [M0 submission checklist and course requirements — 中文](docs/discovery/m0-checklist.zh.md)
- [AGENTS.md](AGENTS.md) — build/test commands and rules for AI assistants (also via [CLAUDE.md](CLAUDE.md))

## Build and test

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Current status

The desk-research sections of the discovery report are drafted in English. The client interview section is intentionally blank until real interview notes are available. No renderer has been implemented or benchmarked at this stage.

The draft was prepared with AI assistance and references original sources. Before submission, the author should review the explanations, make them their own, and be able to explain them without notes, as required by the course.

## Course

- [Project brief](https://learn.glassworks.tech/raytracer/)
- [Milestones](https://learn.glassworks.tech/raytracer/milestones/)
- [Discovery report requirements](https://learn.glassworks.tech/raytracer/veille-perspective/discovery-report/)

The evaluated M0 artifact is `docs/discovery/discovery-report.md` at the Git tag `m0`. Creating these local files does not submit the assignment.
