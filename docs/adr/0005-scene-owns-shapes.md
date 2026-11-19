# 0005. The scene owns its shapes through unique_ptr

## Status

Accepted

## Context

A scene holds several shapes of different concrete types. Alternatives considered:

- **Non-owning pointers / references into `main`** — works while everything is stack-allocated in `main`; breaks when shapes are loaded from a file later.
- **`std::vector<Shape>` by value** — impossible: `Shape` is abstract and sizes differ.
- **`std::vector<std::unique_ptr<Shape>>`** — one owner, polymorphic storage, destruction with the scene.

## Decision

`Scene` stores `std::vector<std::unique_ptr<Shape>>` and `add` takes `std::unique_ptr<Shape>` (moved in). `nearestHit` picks the hit with the smallest positive `t`.

## Consequences

- Positive: clear ownership; ready for future file-loaded scenes; polymorphism via `Shape`.
- Negative: callers must use `std::make_unique` and `std::move`; copying a `Scene` is not trivial.
