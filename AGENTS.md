# Agent notes

Short rules for AI assistants working in this repository.

## Build, run, and test

Prefer the Makefile from the project root (including inside the Dev Container):

```bash
make build
make run
make test
make clean
```

These wrap:

```bash
cmake -S . -B build
cmake --build build
./build/raytracer          # writes image.png
ctest --test-dir build --output-on-failure
rm -rf build
```

## Documents

- Domain model: `docs/domain-model.md`
- ADRs: `docs/adr/` — read related ADRs before changing build tools, PNG encoding, shape/material design, or scene ownership.
- Do not violate an **Accepted** ADR. To change a decision, write a new ADR with status **Proposed** and ask the user first.
- AI assistants must **not** set any ADR status to **Accepted**.

## Coding conventions

- Private members use a `_` prefix (for example `_x`, `_origin`).
- Accessors omit a `get` prefix (for example `x()`, `origin()`).
- Headers and sources are split; keep beginner-friendly C++.
