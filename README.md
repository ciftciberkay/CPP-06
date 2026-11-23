*This project has been created as part of the 42 curriculum by beciftci.*

# CPP-06 · C++ casts

Type conversion, pointer serialization, and runtime type identification. Each exercise has its own Makefile.

## Exercises

| Directory | Exercise | Focus |
| --- | --- | --- |
| [ex00](./ex00) | Scalar conversion | Convert a string representation into scalar types. |
| [ex01](./ex01) | Serialization | Round-trip a pointer through an integer representation. |
| [ex02](./ex02) | Runtime identification | Identify derived classes through a base pointer or reference. |

## Build and run

Run these commands from the repository root with a C++98 compatible compiler and Make.

```sh
make -C ex00
./ex00/convert 42
```

To build another exercise, pass its directory to `make -C`.
