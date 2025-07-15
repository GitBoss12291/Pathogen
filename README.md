# Pathogen

**Pathogen** is a top-down 2D game developed in C++ for the 
[Stop Killing Games Community Jam](https://itch.io/jam/stop-killing-games-game-jam) with the theme **"Limited Lifetime."**

---

## Built With

- **GLFW** - windowing and input
- **GLAD** - OpenGL loader
- **GLM**  - OpenGL math library
- **C++20**
- No external engine - all rendering and logic is custom-built

---

## Building

### Requirements

- CMake 3.20+
- A compiler with full C++20 support

### Instructions

```bash
	git clone https://github.com/GitBoss12291/Pathogen.git
	cd Pathogen
	cmake -B build -G "[Your C++ Compiler]" -A x64
	cmake --build build --config Release
```

### Note

This project was developed using Visual Studio 2022 on Windows. Other compilers may work, but are not tested yet.

---

## Description

You play as a parasitic organism with a limited time to infect, evolve, and survive. Inspired by the cell stage of *Spore*,
the gameplay emphasizes fast-paced survival, absorption mechanics, and environmental hazards.

The goal is to survive just long enough to grow, and with each generation, you gain momentum for the next.

### How to Play

- **WASD** Movement

## License

MIT - See ==['LICENSE.txt'](LICENSE.txt)==

---

## Author

Made by [GitBoss12291](https://github.com/GitBoss12291)
Created for the [Stop Killing Games Community Jam](https://itch.io/jam/stop-killing-games-game-jam) -- July 2025
