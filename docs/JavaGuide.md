## Getting Started Guide for Java Developers

If you come from a Java background and haven’t touched C++ in a while (or ever), this section will help you:

- Understand the C++ project layout and how it compares to a typical Java project
- Learn the CMake build workflow (analogy to Maven/Gradle)
- Pick up the core C++ language features used in this codebase

### 1. Project Layout Comparison

```text
Java:                            C++ (this project):
src/main/java/...                include/sud.hpp, include/option_pricing.hpp
src/main/resources/...           src/main.cpp
pom.xml / build.gradle           CMakeLists.txt (root & src)
```

• **Headers (`.hpp`)** declare interfaces and templates (like Java interfaces or class declarations).
• **Sources (`.cpp`)** contain implementations (like Java classes with method bodies).
• **`CMakeLists.txt`** serves as the build spec (similar to `pom.xml` or `build.gradle`).

### 2. CMake vs. Maven/Gradle

| Step                   | Java (Maven)              | C++ (CMake)                          |
|:-----------------------|:--------------------------|:-------------------------------------|
| Configure/dependencies | `mvn compile`             | `cmake ..`                           |
| Compile & link         | `mvn package`             | `cmake --build .`                    |
| Run tests              | `mvn test`                | (CTest or manual test executable)     |
| Execute application    | `java -jar target/app.jar`| `./option_pricing`                   |

### 3. Essential C++ Constructs

1. **Templates** (generic code):
   ```cpp
   template<typename T>
   using OptionData = std::tuple<T,T,T,T>;
   ```

2. **Type aliases** (`using`):
   ```cpp
   using ComputedData = std::tuple<V,V,V>;
   ```

3. **Tuples** (multiple return values):
   ```cpp
   return std::make_tuple(price, delta, gamma);
   ```

4. **Lambdas & callbacks** (`std::function`):
   ```cpp
   IAlgorithm<double> bs = [](auto od, double S) { /* ... */ };
   ```

5. **Inline/free functions** for small utilities:
   ```cpp
   inline double N(double x) { return 0.5*(1-std::erf(-x/√2)); }
   ```

6. **Thread safety** with `std::mutex` + `std::lock_guard` (vs Java `synchronized`):
   ```cpp
   static std::mutex m;
   std::lock_guard<std::mutex> lock(m);
   ```

### 4. IDE & Tooling

- **CLion**: IntelliJ-like C++ IDE—open the root folder, and it imports the CMake project automatically.
- **Command-line**: requires a C++17 compiler (`g++`/`clang++`) and CMake installed in your PATH.
- **.gitignore**: filters build artifacts, IDE settings, and temporary files so your repo stays clean.

With these points in mind, you’ll feel right at home extending and navigating this C++ project using patterns and workflows you already know from Java.

Happy coding!
