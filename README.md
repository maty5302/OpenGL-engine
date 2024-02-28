# OpenGL engine

This is a project on the essentials of computer graphics. It's mostly written in C++ and OpenGL and it's a simple and old render engine

Citation from my university:

> The course aims to introduce students to the basics of computer graphics. To gain an overview of the basic principles of 2D and especially
> 3D computer graphics. During the semester, students will learn the basic principles of the graphics card and the display chain.
> The basic algorithms used in computer graphics will be presented step by step. The result will be a project on which students will demonstrate
> the knowledge they have gained, which will allow them to display a 3D scene, move the camera, objects, adjust lights, colors, textures,
> add shadows, transparency, normal maps, etc. to the scene.

There are 3 testing scenes:

- Scene 1 - Main scene

- Scene 2 - Checking stacking of transformations

- Scene 3 - Testing Blinn-phong shader

# Demo

![demo.gif](demo.gif)

# Instalation

For running this project and successfully compiling it, you need to have headers for these packages in the folder `lib` which needs to be outside of the project folder. Also you need to have at least VS2022 with C++ support downloaded.

Headers needed:
```
glm
glfw
glew
assimp
soil (for textures)
```
### Assimp

**Needs to be downloaded and compiled by CMAKE for VS2022 and put into the folder Debug/Release, depending on where you compiling the project.** -*Release is set, so better use it*

### Soil 
Soil should be downloaded in the project by Nuget packages. If not just search for Soil2. It should be compatible with VS2022.

## Running on Linux

Of course, the project can be compiled on Linux but I haven't made CMAKE yet. You must do it on your own :)  Packages needed are:
```
glfw3 3.3
OpenGL
GLEW
glm
assimp
```

# Usage and controls

Just run a compiled program it's that simple.

### Movement

<kbd>W</kbd> - Move forward

<kbd>S</kbd> - Move backwards

<kbd>A</kbd> - Move left

<kbd>D</kbd> - Move Right

### Other

<kbd> MOUSE LEFT</kbd> - Lock/unlock camera

<kbd> MOUSE RIGHT</kbd> - Plant/remove tree function

<kbd> E</kbd> - Changing action of <kbd> MOUSE RIGHT</kbd>

<kbd> Esc</kbd> - Closing application

<kbd>1</kbd> <kbd>2</kbd> <kbd>3</kbd> - Changing scene
