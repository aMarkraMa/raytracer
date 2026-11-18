# Discovery report

Research date: 17 November 2026. This report uses the course's fictional 2035 setting; the product comparison describes current documented offerings, not forecasts for 2035. The problem statement is based on the supplied brief and remains subject to confirmation in the client interview.

## Problem statement

A Los Angeles film studio needs dependable rendering for its films and changing production needs, but failures in tools that its staff cannot understand or maintain put delivery and long-term continuity at risk.

<!-- Basis: https://learn.glassworks.tech/raytracer/#the-problem ; not a claim obtained from an interview. -->

## Client interview summary

<!-- Intentionally left blank. Add only findings supported by real interview notes, grouped by theme. For each need, include the question, who asked it, the client's answer, and any separately labelled personal conclusion. Add open questions and contradictions after the thematic summary. -->

## State of the art

The comparison covers two commercial production renderers, one open-source production renderer and one open-source educational/reference renderer. The common criteria are maker, licence, dated software cost, rendering capabilities and integration or extension possibilities. These are documented capabilities, not results of a benchmark performed for this project.

| Solution | Maker | Licence | Pricing (date checked) | Capabilities | Sources |
|---|---|---|---|---|---|
| **Arnold** | Autodesk | Proprietary commercial software; subscription | **USD 430/year** or **USD 55/month**, as listed in the official US product-page FAQ; checked **2026-11-17**. These are subscription prices, not the cost of a complete render farm. | Monte Carlo ray tracing on CPU or GPU; indirect lighting, hair, volumes and motion blur. Integrations with content-creation applications, including Maya and 3ds Max; custom shaders and an extensible architecture. Extension access does not mean the renderer itself is open source. | [Product, features and pricing FAQ](https://www.autodesk.com/products/arnold/overview) |
| **RenderMan** | Pixar Animation Studios | Proprietary commercial software; a separate free non-commercial edition is offered | **USD 595 per licence**, including Tractor; **USD 250 per licence for annual maintenance renewal**. Checked **2026-11-17**. The free non-commercial edition is not the commercial studio licence. | Physically based lighting and materials, multi-bounce illumination, denoising, volumes, motion blur and resumable renders. XPU uses GPU resources; USD/Hydra integration and Tractor support production pipelines and render scheduling. | [Official store and licence options](https://renderman.pixar.com/store); [product capabilities](https://renderman.pixar.com/product) |
| **Cycles** | Blender project and contributors | Open source, **Apache 2.0** for the Cycles engine; this is the engine's licence, not a statement about every component of Blender | **USD 0 software licence fee** for the open-source engine; checked **2026-11-17**. Hardware, integration, operation and support still have costs. | Physically based production path tracing, shading nodes and GPU acceleration on compatible devices in Blender. Its source can also be integrated into other open-source or commercial applications. | [Cycles project and licence](https://www.cycles-renderer.org/); [Blender 4.5 LTS manual](https://docs.blender.org/manual/en/4.5/render/cycles/introduction.html) |
| **pbrt-v4** | Matt Pharr, Wenzel Jakob, Greg Humphreys and contributors | Open source, **Apache 2.0** for the main implementation; dependencies have their own notices | **USD 0 software licence fee** for the open-source implementation; checked **2026-11-17**. The accompanying fourth-edition book is readable online for free. Engineering and compute costs remain. | A C++ reference implementation linking rendering theory to code, with spectral rendering, materials, volume scattering and CPU rendering; its GPU path requires CUDA/OptiX. Useful for studying and modifying algorithms rather than assuming a ready-made studio workflow. | [Project and book](https://www.pbrt.org/); [implementation and hardware details](https://github.com/mmp/pbrt-v4); [licence file](https://github.com/mmp/pbrt-v4/blob/master/LICENSE.txt) |

Prices are the published USD amounts available on the check date. They are not converted into euros, do not establish tax treatment, and are not comparable total production budgets: a subscription, an initial licence plus maintenance, and a free source distribution have different cost structures. A studio estimate also needs concurrent rendering capacity, hardware, support, training and integration effort. In particular, no claim is made that a single commercial licence covers unlimited simultaneous renders.

The sources have different purposes. Vendor pages are useful for the vendor's advertised price and feature list, but claims of superior speed or quality need independent testing. Project documentation and licence files establish what is available for inspection and extension; they do not establish that our team could maintain it cheaply. The Cycles capability check uses a versioned manual so the reference stays identifiable.

**My conclusion:** producing convincing images is already a mature capability, available in both commercial and open-source tools. Physically based rendering has helped film workflows describe lighting and materials more consistently; pbrt is one documented link between that theory and practical implementations. Modern products also address integration and production operation, not just the colour of a pixel. [Background: pbrt](https://www.pbrt.org/)

Against the brief's need for long-term ownership, the commercial products leave the core implementation under vendor control. Cycles and pbrt offer source access, but access alone does not guarantee understandable architecture, suitable tests or a workflow that fits this studio. These are potential trade-offs inferred from the comparison, not failures reported by the client. Without the interview, there is no evidence that every existing solution is unsuitable. The unresolved decision is why adapting an existing renderer would be insufficient. For this course, a small C++ implementation can demonstrate understandable, testable behaviour; it should not be presented as a production replacement for these renderers before that has been established.

## What is ray tracing?

Ray tracing builds a two-dimensional image from a three-dimensional scene containing geometry, materials, lights and a camera, together with settings such as image size. For each pixel, the camera generates one or more rays into the scene. A ray has an origin and a direction: points on it can be written as `p(t) = origin + t × direction`. The renderer finds the nearest valid surface hit and uses its material, orientation and incoming light to estimate the colour seen along that ray; a ray that misses can see the environment. Further rays can test whether a light is blocked or follow reflection and transmission. Path tracing is a form of ray tracing that samples light paths to estimate contributions from multiple interactions, including indirect illumination. Averaging samples produces pixel values, which are converted into an image; additional samples usually reduce sampling noise but cost more computation. The output is an image for one camera view, and rendering successive scene states produces frames for animation. A basic tracer can start with spheres and direct lighting before attempting a full light-transport simulation.

**Sources** — checked 2026-11-17:

- **Starting resource:** Peter Shirley, Trevor David Black and Steve Hollasch, [*Ray Tracing in One Weekend*](https://raytracing.github.io/books/RayTracingInOneWeekend.html). Its progression from an image and a ray to intersections, materials and sampling makes the process concrete in C++.
- **Reference to return to:** Matt Pharr, Wenzel Jakob and Greg Humphreys, [*Physically Based Rendering*, fourth edition — Introduction](https://pbr-book.org/4ed/Introduction). It connects the physical model, algorithms and implementation when a simple tutorial no longer explains a design choice.

## What is C++?

C++ is a general-purpose language usually compiled into native machine code. It combines higher-level abstractions with control over object layout, lifetime and resource use. This makes it relevant to a renderer, where the same intersection and shading operations may run many times. C++ does not make an inefficient algorithm fast automatically. The requirement to use it comes from the course scenario; the scenario's claim that other languages have become proprietary is fictional.

### Programming paradigms

C++ supports several styles that can be combined in one program:

- **Procedural programming:** functions and control flow express computations such as intersecting a ray with a sphere. Python and JavaScript also support this approach.
- **Object-oriented programming:** classes encapsulate state and invariants; virtual functions allow different implementations to share an interface. Python and JavaScript/TypeScript also offer classes, although their object models differ from C++.
- **Generic programming:** templates express algorithms and containers for multiple types, with types checked when the template is instantiated. This differs from Python's usual runtime duck typing and TypeScript generics, whose type information does not remain as runtime JavaScript checks.
- **Functional techniques:** lambdas, callable objects and standard algorithms support passing behaviour to a function. As with Python and JavaScript, these techniques can complement mutable objects; using a lambda does not make a function pure.

Compared with Python and JavaScript, C++ generally exposes more decisions about concrete types, copying and memory ownership. TypeScript also checks types before execution, but that checking does not give JavaScript C++-style object lifetimes or ownership rules. For this project, these differences mean that the domain model should explain not only what an object represents but also who owns it and how long it remains valid. [Language background: Bjarne Stroustrup's FAQ](https://www.stroustrup.com/bs_faq.html)

### What to watch out for

In Python and JavaScript, the runtime normally reclaims unreachable managed objects. In C++, I need to design resource ownership explicitly. That does not mean scattering manual `new` and `delete` calls through the renderer: standard containers and resource-owning objects can release their resources automatically when their lifetime ends. The core guidelines recommend this RAII approach. [Resource-management guidance](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rr-raii)

The main traps to keep in mind are:

- **Lifetime and ownership:** a pointer or reference may outlive its target. Returning a reference to a local object or keeping a pointer into a vector after reallocation can leave an invalid reference. Prefer values and clear owners; use `std::unique_ptr` when dynamic exclusive ownership is needed.
- **Invalid operations:** uninitialised values, out-of-bounds access and signed integer overflow can cause undefined behaviour. A program compiling successfully does not prove that it is safe. Initialise data, check inputs and use compiler warnings and appropriate diagnostics.
- **Copying:** copying a large scene can be expensive, while copying a derived object into a base-class value loses the derived part. Use small value types freely and pass larger read-only objects by `const` reference when their lifetime permits it.
- **Resource cleanup:** file handles and other resources also need owners. Standard containers and RAII wrappers reduce the need for custom cleanup. If a class owns resources through such members, it can often follow the rule of zero and avoid custom copy, move and destruction code.
- **Numerical behaviour:** integer division can discard a fractional result, floating-point arithmetic has rounding error, and normalising a zero-length vector is invalid. Intersection calculations need tests for edge cases, including rays starting very close to surfaces.
- **Polymorphic destruction:** if an interface is used to delete derived objects through a base pointer, its destructor must be virtual. A smart pointer alone does not fix an incorrectly designed base class.

The proposed checks for later implementation are focused mathematical tests, small deterministic render cases, compiler warnings, and memory/undefined-behaviour diagnostics where supported. No such implementation checks have been performed for M0.

### Shaping the domain model

The starting model should use the rendering vocabulary directly. This is a preliminary design hypothesis, not an interview-validated architecture:

| Domain concept | Initial C++ representation and responsibility |
|---|---|
| Position, direction and colour | Small value types with clearly named operations. Positions and directions share coordinates but have different meanings; a point plus a direction makes sense, while adding two positions needs justification. |
| Ray and hit | A `Ray` contains its origin and direction. A `HitRecord` holds the intersection parameter, position, normal and a material reference or identifier. A miss should be represented explicitly rather than as an uninitialised record. |
| Camera | Converts image coordinates and camera settings into rays; it does not decide how a material scatters light. |
| Geometry and material | Geometry answers intersection questions; a material describes surface appearance. Compose them so the same shape can have different materials without creating a class for every shape/material combination. |
| Scene | Owns the objects and materials needed during a render. Non-owning references into it must not outlive it or be invalidated by later changes. |
| Renderer and image | The renderer coordinates sampling and lighting computations; the image stores pixel results. File output remains separate from intersection mathematics. |

I would begin with concrete types and ordinary functions, then introduce a small interface when multiple shapes genuinely need interchangeable intersection behaviour. C++ offers runtime polymorphism for that case and templates for compile-time variation; neither requires a deep inheritance tree. Small value types, explicit ownership and composition make individual calculations easier to test and changes easier to localise. A read-only scene during rendering would also reduce accidental mutation, although distribution and thread-safety decisions belong to later work. [Design guidance: C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)

**Sources** — checked 2026-11-17:

- **Starting resource:** [LearnCpp — Introduction to C/C++](https://www.learncpp.com/cpp-tutorial/introduction-to-cplusplus/) and its tutorial sequence. It provides a route from compiling a small program to functions, classes, references and ownership.
- **Language perspective:** [Bjarne Stroustrup's FAQ](https://www.stroustrup.com/bs_faq.html), especially its explanation of combining programming styles. This is background on the language's design, not a source for current popularity rankings.
- **Reference to return to:** [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines), particularly [R.1: RAII](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rr-raii), [R.20: ownership pointers](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rr-owner), [C.20: rule of zero](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-zero), and [C.35: base-class destructors](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-dtor-virtual). These are engineering recommendations rather than the normative language standard.
