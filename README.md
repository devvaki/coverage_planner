# Coverage Planning in 2D Space

## Table of Contents
- [Overview](#-overview)
- [Features](#-features)
- [Demo](#-demo)
- [Tech Stack](#-tech-stack)
- [How it Works](#-how-it-works)
- [Build Instructions](#-build-instructions)
- [Project Structure](#-project-structure)
- [Future Enhancements](#-future-enhancements)
- [Author](#-author)

## Overview
This project focuses on implementing an efficient 2D coverage planning algorithm. 
It uses **Boustrophedon decomposition** to divide the map into sweepable sub-regions and leverages **A\*** path planning to generate optimal transitions between them. 
The system processes an occupancy grid (with `0` representing free space and `100` for obstacles), ensuring complete coverage with minimal overlap and optimized path length. All path planning and coverage behaviors are visualized in real time using **OpenCV**, making it easier to validate performance across both convex and non-convex obstacles. 
The implementation is modular, written in modern C++ (C++17), and designed to be easily extensible for future integration.

## Features
- 2D occupancy grid parsing and map generation  
- Boustrophedon decomposition for cellular coverage  
- A\* search for inter-region traversal  
- Real-time path and coverage visualization using OpenCV  
- Handles both convex and non-convex obstacles  
- Modular structure for easy extension

## Demo
[demo_video.webm](https://github.com/user-attachments/assets/20c67d84-d5bf-4ff1-970b-7996b68483a1)

## Tech Stack

- **C++17** – Core implementation  
- **OpenCV** – Visualization and map handling  
- **CMake** – Build system  
- **STL** – Data structures and algorithms

## How it Works

1. **Map Input**  
   A 2D occupancy grid is generated, where `0` represents free space and `100` represents obstacles.

2. **Cell Decomposition**  
   The map is scanned column by column to detect connected free-space regions using **boustrophedon decomposition** logic.

3. **Coverage Path Generation**  
   Within each decomposed region, the algorithm follows a **column-wise sweeping pattern**, moving from top to bottom in one column, then bottom to top in the next — repeating this vertically across the region.

4. **Inter-Region Transition**  
   **A\*** path planning is used to connect the end of one region’s sweep to the start of the next with minimal travel distance.

5. **Visualization**  
   The entire coverage path and movement visualization is rendered in real time using **OpenCV**, clearly showing region traversal and transitions.

## Build Instructions
### Prerequisites
- C++ compiler with C++17 support
- CMake >= 3.10
- OpenCV (>= 4.x recommended)

### Project Structure
![layout](https://github.com/user-attachments/assets/a9656db4-6adf-492e-8639-8b12839f51f2)

### Build & Run
Open a terminal and run:

```bash
# Clone the repository
git clone https://github.com/devvaki/Coverage-Planning-in-2D-space.git
cd Coverage-Planning-in-2D-space

# Create and enter build directory
mkdir build && cd build

# Generate build files with CMake
cmake ..

# Compile the project
make

# Run the coverage planner
./coverage_planner
```

---

### Build Notes

- If OpenCV is not found automatically, you may need to set the path manually:
  ```bash
  cmake -DOpenCV_DIR=/path/to/opencv ..
  ```

- To verify OpenCV is installed:
  ```bash
  pkg-config --modversion opencv4
  ```
  
## Future Enhancements

1. ROS2 integration for real robot deployment
2. Dynamic obstacle handling
3. GUI for interactive map creation
4. Multi-agent coverage support
