# Pathogen

**Pathogen** is a top-down 2D game developed in C++ for the Stop Killing Games Community Jam with the theme **"Limited Lifetime."**
https://itch.io/jam/stop-killing-games-game-jam

---

## Built With

- **GLFW** — windowing and input
- **GLAD** — OpenGL loader
- **C++20**
- No external engine — all rendering and logic is custom-built

---

## Building

### Requirements

- CMake 3.20+
- Any compiler with C++20 support

### Instructions

```bash
	git clone https://github.com/GitBoss12291/Pathogen.git
	cd pathogen
	cmake -B build -G "[Your C++ Compiler]" -A x64
	cmake --build build --config Release
```

### Note

I am fairly new to programming in C++, so this may not build without using Visual Studio 17 2022 compiler.

---

## Description

You play as a parasitic organism with a limited time to infect, evolve, and survive. Inspired by the cell stage of *Spore*,
the gameplay emphasizes fast-paced survival, absorption mechanics, and environmental hazards.

The goal is to survive just long enough to grow, and with each generation, you gain momentum for the next.

### How to Play