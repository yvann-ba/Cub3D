# 🎮 Cub3D

### What is Cub3D
Cub3D was a project where we had to make a mini 3D game engine in C. We used raycasting to simulate a first-person view in a maze. The goal was to render walls, handle player movement, and add textures to make it look more realistic. It all starts from a basic 2D map, but gives the illusion of depth, kind of like Wolfenstein 3D

### What is MinilibX
MiniLibX is a small graphics library used to create windows, display images, and handle keyboard/mouse events on Linux and macOS. In Cub3D, it allows for managing 2D/3D graphics rendering and user interaction for the game engine. It's essential for displaying textures and handling player movements in real-time.

## video

## How to use it :
#### (Works only on Mac or Linux) ⚠️

```bash
# Clone the repository
git clone https://github.com/Lilien86/Cube_3d.git

# Navigate to the project directory
cd Cub_3d

# Pull minilibx_linux
wget https://cdn.intra.42.fr/document/document/25837/minilibx-linux.tgz

# Compresse minilibx folder
tar -xpf minilibx-linux.tgz

# Compile minilibx
cd minilibx-linux && make && cd..

# Build the project using Make
make

# Run cub and choice you map, after enjoy (:
./cub3D ./map/*
```

## File.cub format 🌟
1. Valid characters: Use 0 (empty space), 1 (walls), and N, S, E, W (player starting position).
2. Enclosed by walls: The map must be surrounded by walls (1).
3. There must be only one starting position.
4. Rectangular shape: All rows must have the same number of columns.
5. No gaps: The map cannot have any undefined areas inside.

## Sources
- Lodev blog (https://lodev.org/cgtutor/raycasting.html)
- Javidx9 video (https://youtu.be/NbSee-XM7WA?si=Lg1NyZL-PhpnAZ3W)
- Kofybrek devlog (https://youtu.be/LUYxLjic0Bc?si=3DYxCFdwpMbKbsay)
