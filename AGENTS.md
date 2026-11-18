# Agent notes

Short rules for AI assistants working in this repository.

## Build, run, and test

There is no root `Makefile` shortcut yet. Use CMake and CTest from the project root:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

- **Build:** `cmake -S . -B build` then `cmake --build build`
- **Test:** `ctest --test-dir build --output-on-failure`
- **Run:** no application executable yet; the library target is `raytracer`, and the current executable is the test binary `build/test_vector`

## Architecture decisions

- ADR documents live under `docs/adr/` (create that folder when the first ADR is added).
- Before changing build, developer tooling, or test configuration, read the related ADRs.
- Do not violate an **Accepted** ADR. To change a decision, write a new ADR with status **Proposed** and ask the user first.
- AI assistants must **not** set any ADR status to **Accepted**.

## Coding conventions (current)

- Private members use a `_` prefix (for example `_x`, `_origin`).
- Accessors omit a `get` prefix (for example `x()`, `origin()`).
- Headers and sources are split; keep beginner-friendly C++.
