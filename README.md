# GameEngine
Game Engine based on Hazel engine.

# TODO :

## Components
* Entrypoint
* Application Layer
* Window Layer
* Renderer
* Render API abstraction
* Debugging support
* Scripting language
* Memory Systems 
    * Detect leaks, tagging, ...
* Entity-Component System
* Physics
* File I/O, VFS
* Build system, asets
* Audio
* AI
* Profiling tools
...

## Render API(API/platform specific)
* Render Context
* Swap Chain
* Framebuffer
* Vertex Buffer
* Index Buffer
* Texture
* Shader
* States
* Pipelines
* Render passes

## Renderer (API/platfprm agnostic)
* 2D & 3D Renderer
    * Forward, deferred etc.
* Scene Graph
* Sorting
* Culling
* Materials
* LOD
* Animation
* Camera
* VFX
* PostFX
* Other things
    * reflections, ambient occlusion, ...

## 2D Renderer 
* `Renderer2D::BeginScene()`
* `Renderer2D::DrawQuad(pos, size, color, texture)`
* Batch renderer    
    * 100k quads , 60fps, w/ textures, 
* Texture Atlas, 100-200 textures
* Animation
* UI - Layouts, aspect ratio,  
* PostFx - Particles, HDR, Blur, LUT

## 2D Game
* Interaction
* Sripting - Lua
* ECS(Entity Component System)/CGO (Composable Game Objects) 
    * *Player*
        * *Transform*
        * *Renderer*
        * *Script*


