#  Fract-ol - Infinite Fractal Explorer - @42

*This project has been created as part of the 42 curriculum by miouali.*

##  Description

Fract-ol is a real-time fractal renderer built in C. This project delves into the fascinating world of converging sequences and complex dynamics, leveraging the MiniLibX for direct pixel manipulation.

The goal is to generate mathematically accurate fractals based on the study of complex sequence limits. The engine features smooth navigation (zooming, panning) and dynamic color mapping to visualize the rate of divergence.

## Available Fractals

The project supports several types of sets, from the most classic to the more exotic:

    Mandelbrot: The classic set based on the convergence of the sequence zn+1​=zn2​+c.

    Julia: Infinite variations depending on mouse position or fixed parameters, studying the limit of the sequence based on z0​.

    Burning Ship: A unique fractal generating a ship-like shape via the sequence zn+1​=(∣Re(zn​)∣+i∣Im(zn​)∣)2+c.

    Celtic: An elegant Mandelbrot variant featuring knot-like structures.

    Tricorn: Also known as the Mandelbar, it uses the complex conjugate of z to determine its divergence pattern.

## Instructions

This project relies on two internal libraries located in the libs/ folder.

### 1. Project Structure

```Plaintext
.
├── libs
│   ├── libft       # Custom C library (submodule)
│   └── minilibx    # 42 Graphical library (included)
├── srcs            # Project source code
├── includes        # Header files
└── Makefile
```

### 2. Setup

To clone the project along with its dependencies, use the --recursive flag to automatically fetch the libft submodule:

```Bash
git clone --recursive git@github.com:fiaudfiz/fract-ol
```
##  Usage

###    Compilation :
```bash
make
```
###    Launch
Run the program with the name of the desired fractal:

```Bash
    ./fractol mandelbrot
    ./fractol julia
    ./fractol burningship
    ./fractol celtic
    ./fractol tricorn
```

### Controls & Navigation

    Mouse: Use the Scroll Wheel for precise Zooming/Unzooming centered on the cursor.

    Keyboard:

    Arrows / WASD: Move across the complex plane.

    C: Cycle through different color palettes (Color Shifting). 
    
    R: Reset to the default view.

    ESC: Exit the program cleanly.

##    Resources

* **The Mandelbrot Set**  : [Mandelbrot Set](https://en.wikipedia.org/wiki/Mandelbrot_set)
* **Julia Set** : [Julia Set](https://en.wikipedia.org/wiki/Julia_set)
* **Mini Lib X**  : [Mini Lib X doc](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html)
* **Fractal**  : [Fractal](https://en.wikipedia.org/wiki/Fractal)
