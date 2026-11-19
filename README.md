# Raytracer

An individual C++ ray tracer for the HETIC module *Veille, innovation et prospective* and the related software-engineering sessions.

## Milestone m1

Hand-in tag: **`m1`**. At that tag the project includes:

- Working `Scene` render of a shaded sphere on a floor (`make run` → `image.png`)
- Green tests (`make test`)
- ADRs and domain model under `docs/`

## Open in a Dev Container (Cursor / VS Code)

1. Install Docker Desktop.
2. Open this folder in Cursor.
3. Run **Dev Containers: Reopen in Container**.
4. In the container terminal:

```bash
make test
make run
```

## Build, test, and run

From the project root (host or container):

```bash
make build
make test
make run    # writes image.png
make clean
```

## Documentation

- [Domain model](docs/domain-model.md)
- [Architecture decision records](docs/adr/README.md)
- [AGENTS.md](AGENTS.md) — commands and rules for AI assistants
- [Discovery report — m0](docs/discovery/discovery-report.md)

## Course

- [Project brief](https://learn.glassworks.tech/raytracer/)
- [Milestones](https://learn.glassworks.tech/raytracer/milestones/)
