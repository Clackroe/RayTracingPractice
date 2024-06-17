# Raytracer Practice
This is my first attempt at creating a raytracing "engine" or renderer. The code in this repo is based on the book [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html). 
I attempted to throw my own styles and methologies where I could, but the renderer is largely very similar to the one in the book. However, the code in this repository was all written by me and me only. 

Some places where I changed the architecture:
1.  Multithreaded Renderer
   *  While still slow, the renderer will attempt to spread the work among as many cores/threads as it can
3.  Camera Architecture
  * I am unsure if I like my method more than the book's, but I am sure it could be improved. I find the code in its current state a little messy.

This project uses CMake, build as usual. (Written and tested on Linux, other platforms are not garunteed)

Here are the results of the final renderer, enjoy!

1200x675 | 
Max Depth: 50 |
Samples Per Pixel: 500
![image](https://github.com/Clackroe/RayTracingPractice/assets/65436489/5d537986-c030-4d5b-be0f-bb5b3fb6f06a)
