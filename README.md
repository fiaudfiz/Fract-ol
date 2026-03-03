#  Fract-ol - Infinite Fractal Explorer - @42

*This project has been created as part of the 42 curriculum by miouali.*

##  Description

Fract-ol is a real-time fractal renderer built in C. This project delves into the fascinating world of converging sequences and complex dynamics, leveraging the MiniLibX for direct pixel manipulation.

The goal is to generate mathematically accurate fractals based on the study of complex sequence limits. The engine features smooth navigation (zooming, panning) and dynamic color mapping to visualize the rate of divergence.

## Available Fractals

The project supports several types of sets, from the most classic to the more exotic:

    Mandelbrot: The classic set based on the convergence of the sequence : 
        z₀ = 0
        zₙ₊₁ = zₙ² + c
    
    Julia: Infinite variations depending on mouse position or fixed parameters:
        z₀ = pixel
        zₙ₊₁ = zₙ² + c,  c = fixed constant

    Burning Ship: A unique fractal generating a ship-like shape via the sequence:
        z₀ = 0
        zₙ₊₁ = (|Re(zₙ)| + i·|Im(zₙ)|)² + c

    Celtic: An elegant Mandelbrot variant featuring knot-like structures :
        z₀ = 0
        zₙ₊₁ = |Re(zₙ²)| + i·Im(zₙ²) + c

    Tricorn: Also known as the Mandelbar, uses the complex conjugate z̄:
        z₀ = 0
        zₙ₊₁ = z̄ₙ² + c

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
