# Option Pricing C++ Project

Bootstrap for implementing code snippets from Duffy's *Financial Instrument Pricing Using C++*.

### Quick Start
1. `mkdir build && cd build`
2. `cmake .. && cmake --build .`
3. `ctest -V`

## Requirements

- CMake >= 3.15
- C++17 compatible compiler

## Building

```bash
mkdir -p build && cd build
cmake ..
cmake --build .
```

## CLion

Open this directory in CLion (File > Open) to import the CMake project.

## Overview

This project bootstraps the code examples from Duffy's *Financial Instrument Pricing Using C++*. It provides:

- **Core interfaces** (`include/sud.hpp`):
  - `OptionData<T>`: a tuple `<K, T, r, σ>` representing option parameters.
  - `ComputedData<T>`: a tuple `<V, Δ, Γ>` representing the computed price and sensitivities.
  - `IAlgorithm<T>`: a type-safe callable for pricing algorithms.
  - `SUD<T,Source,Sink>`: a policy-based "System Under Discussion" that wires a source, algorithm, and sink.

- **Demo application** (`src/main.cpp`): call and put pricing demo using `SUD`, `Processing`, `Input`, and `Output`.

You can implement your own `Source`/`Sink`, write any pricing algorithm (e.g. Black‑Scholes), and hook them up via `SUD` for end-to-end execution.

## Project Structure

```
. ├── CMakeLists.txt        # top-level CMake configuration
  ├── include/
  │   ├── sud.hpp          # core templates and interfaces
  │   └── option_pricing.hpp # domain logic (Black‑Scholes formulas)
  ├── src/
  │   ├── CMakeLists.txt   # builds all .cpp files in this folder
  │   └── main.cpp         # application entry-point (demo runner)
  ├── tests/
  │   ├── CMakeLists.txt   # tests build rules
  │   └── test_option_pricing.cpp # unit tests for pricing routines
  └── README.md            # project documentation
``` 

## Example Usage

Below is a minimal sketch of how to plug in a source, algorithm, and sink:

```cpp
#include "sud.hpp"

struct MySource {
    OptionData<double> getData() { /* read/write input... */ }
};

struct MySink {
    void SendData(const ComputedData<double>& x) { /* output data... */ }
    void end() { /* cleanup... */ }
};

int main() {
    // Black‑Scholes pricing lambda
    IAlgorithm<double> blackScholes = [](const OptionData<double>& od, double S) {
        double V = /* ... */;
        double delta = /* ... */;
        double gamma = /* ... */;
        return ComputedData<double>{V, delta, gamma};
    };

    SUD<double, MySource, MySink> app(blackScholes);
    app.run(100.0 /* spot price */);
    return 0;
}
```

## Running the Demo

After building (see **Building**), from the `build` directory run:

```bash
./option_pricing
```

You should see the call price + sensitivities followed by the put price + sensitivities, for example:

```text
(2.13337,0.372483,0.0420428)
end
(5.84628,-0.372483,0.0420428)
end
```

## Running Unit Tests

After building (see **Building**), from the `build` directory run:

```bash
ctest -V
```

This will execute the `option_pricing` unit tests (normal PDF/CDF checks and basic call/put pricing validations).

For a detailed introduction, see [docs/JavaGuide.md](docs/JavaGuide.md).

## License

This project is licensed under the MIT License. Pricing formulas are provided for educational purposes only and should not be used in production without proper validation.
