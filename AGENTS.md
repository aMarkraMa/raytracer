# Agent notes

Short rules for AI assistants working in this repository.

## Build, run, and test

From the project root, prefer the Makefile shortcuts:

```bash
make build
make run
make test
make clean
```

These wrap the underlying CMake commands:

```bash
cmake -S . -B build
cmake --build build
./build/raytracer
ctest --test-dir build --output-on-failure
rm -rf build
```

- **Build:** `make build`
- **Run:** `make run` (writes `output.png` in the project root)
- **Test:** `make test`
- **Clean:** `make clean` (removes only the local `build/` directory)

## Architecture decisions

- ADR documents live under `docs/adr/` (create that folder when the first ADR is added).
- Before changing build, developer tooling, or test configuration, read the related ADRs.
- Do not violate an **Accepted** ADR. To change a decision, write a new ADR with status **Proposed** and ask the user first.
- AI assistants must **not** set any ADR status to **Accepted**.

## Coding conventions (current)

- Private members use a `_` prefix (for example `_x`, `_origin`).
- Accessors omit a `get` prefix (for example `x()`, `origin()`).
- Headers and sources are split; keep beginner-friendly C++.
