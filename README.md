# Coverage Planning in 2D Space
## Table of Contents
- [Overview](#-overview)
- [Features](#-features)
- [Demo](#-demo)
- [Tech Stack](#-tech-stack)
- [How it Works](#-how-it-works)
- [Build Instructions](#-build-instructions)
- [Sample Maps](#-sample-maps)
- [Project Structure](#-project-structure)
- [Future Enhancements](#-future-enhancements)
- [Author](#-author)

## Overview
This project focuses on implementing an efficient 2D coverage planning algorithm. 
It uses **Boustrophedon decomposition** to divide the map into sweepable sub-regions and leverages **A\*** path planning to generate optimal transitions between them. 
The system processes an occupancy grid (with `0` representing free space and `100` for obstacles), ensuring complete coverage with minimal overlap and optimized path length. All path planning and coverage behaviors are visualized in real time using **OpenCV**, making it easier to validate performance across both convex and non-convex obstacles. 
The implementation is modular, written in modern C++ (C++17), and designed to be easily extensible for future integration.
