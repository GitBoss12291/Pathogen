# Pathogen

**Pathogen** is a top-down 2D game developed in C++ for the 
[Stop Killing Games Community Jam](https://itch.io/jam/stop-killing-games-game-jam), with the theme **"Limited Lifetime."**

---

## Table of Contents

- [Built With](#built-with)
- [How to Build](#how-to-build)
- [Description](#description)
- [How to Play](#how-to-play)
- [License](#license)
- [Author](#author)

---

## Built With

- **GLFW** - windowing and input
- **GLAD** - OpenGL loader
- **GLM**  - Math Library for OpenGL
- **STBI** - Image loading Library
- **STBIW** - Image write Library
- **STBTT** - Font loading Library
- **Nlohmann JSON** JSON Serialization library
- **C++20**
- No external engine - all rendering and logic is custom-built

---

## How to Build

### Requirements

- CMake 3.50+
- A compiler with full C++20 support

### Instructions

```bash
	git clone https://github.com/GitBoss12291/Pathogen.git
	cd Pathogen
	cmake -B build -G "[Your C++ Compiler]" -A x64
	cmake --build build --config Release
```

>This project was developed using Visual Studio 2022 on Windows. Other compilers may work, but are not tested yet.

---

## Description

You play as a parasitic organism with a limited time to infect, evolve, and survive. Inspired by the cell stage of *Spore*,
the gameplay emphasizes fast-paced survival, absorption mechanics, and environmental hazards.

The goal is to survive just long enough to grow, and with each generation, you gain momentum for the next.

### How to Play

- **WASD** Movement
- Avoid threats, absorb other cells, and evolve by collecting new parts
- Make your cell your own with the cell editor 

---

## License

MIT - See [LICENSE.txt](LICENSE.txt)

---

## Author

Made by [GitBoss12291](https://github.com/GitBoss12291)
Created for the [Stop Killing Games Community Jam](https://itch.io/jam/stop-killing-games-game-jam) -- July 2025
