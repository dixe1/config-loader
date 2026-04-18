# ConfigLoader
<p align="left">
<img src="https://badgen.net/badge/icon/Windows/4E4E4E?icon=windows&label=&labelColor=4E4E4E" alt="Windows">
<img src="https://badgen.net/badge/icon/Linux/4E4E4E?icon=linux&label=&labelColor=4E4E4E" alt="Windows">
<img src="https://badgen.net/badge/icon/macOS/4E4E4E?icon=apple&label=&labelColor=4E4E4E" alt="Windows">
</p>

<p>
<img src="https://img.shields.io/badge/language-C++-00599C?logo=c%2B%2B" alt="C++">
<img src="https://img.shields.io/badge/build-CMake-3eae2b?logo=cmake&logoColor=white" alt="CMake">
<img src="https://img.shields.io/badge/license-MIT-green" alt="License: MIT">
</p>

A simple C++23 library for loading configuration files in a key-value format.

## Requirements

- CMake 3.20 or newer
- Compiler with C++23 support

## Building

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

The library will be built as a static library (`ConfigLoader.a` / `ConfigLoader.lib`).

## Config File Format

```ini
# This is a comment
name = John
age = 21
temperature = 36.6
debug = true
path = /home/user/data   # inline comments work too
```

**Rules:**
- Comments start with `#`
- Key-value separator is `=`
- Whitespace around keys and values is ignored
- Supported types: `long long`, `double`, `bool`, `string`

## Usage

### Using constructor:

```cpp
#include "ConfigLoader.h"

int main()
{
    ConfigLoader cfg("config.ini");

    long long age  = cfg.get<long long>("age");
    double temp    = cfg.get<double>("temperature");
    bool debug     = cfg.get<bool>("debug");
    std::string s  = cfg.get<std::string>("name");
}
```

### Using static `load()`:

```cpp
auto config = ConfigLoader::load("config.ini");
```

Returns `std::unordered_map<std::string, std::any>`.

## API

| Method | Description |
|--------|-------------|
| `ConfigLoader(filePath)` | Constructor – loads the config file |
| `getValue(key)` | Returns the value for a key as `std::any` |
| `get<T>(key)` | Returns the value cast to type `T` |
| `load(filePath)` | Static – loads the file and returns a config map |
| `getConfig()` | Returns the internal config map as `const` reference |

## Error Handling

- If the file does not exist, `load()` prints an error to `stderr` and returns an empty map.
- If the key does not exist, `getValue()` prints a message and returns an empty `std::any`.
- `get<T>()` will throw `std::bad_any_cast` if the type does not match — wrap it in a `try/catch`.

### Validating the loaded config

**Using constructor:**
```cpp
ConfigLoader cfg("config.ini");

if (cfg.getConfig().empty())
{
    // handle error
}
```

**Using static `load()`:**
```cpp
auto config = ConfigLoader::load("config.ini");

// load() returns an empty map if the file was not found
if (config.empty())
{
    // handle error
}
```
