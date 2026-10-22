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
├── src             # Project source code
├── include         # Header files
└── Makefile
```

### 2. Setup

To clone the project along with its dependencies, use the --recursive flag to automatically fetch the libft submodule:

```Bash
git clone --recursive git@github.com:fiaudfiz/fract-ol
```

## Usage

### Compilation

Two versions are available:

```bash
make simd        # SIMD (AVX2) version  -> ./fractol_simd
make threads     # multithreaded version -> ./fractol_threads
```

Running `make` alone only prints the available targets.

### Launch

Run the program with the name of the desired fractal:

```bash
./fractol_simd mandelbrot
./fractol_simd julia
./fractol_simd burningship
./fractol_simd celtic
./fractol_simd tricorn
```

The threaded version takes the same arguments:

```bash
./fractol_threads mandelbrot
```

### Other targets

| Command | Description |
|---|---|
| `make debug_simd` / `make debug_threads` | `-O0 -g3` with ASan + UBSan |
| `make prof_simd` / `make prof_threads` | `-pg` for gprof (also usable with perf) |
| `make perf_simd` / `make perf_threads` | Symbols + frame pointers for `perf`, without `-pg` |
| `make re_simd` / `make re_threads` | `fclean` + rebuild |
| `make clean` / `make fclean` | Remove objects / binaries |

Each variant has its own object directory (`obj/<version>-<variant>/`) and its own binary (`fractol_simd_debug`, `fractol_threads_perf`, ...), so builds never mix.

### Profiling

```bash
make perf_threads
perf record -F 999 -e cycles:u --call-graph fp ./fractol_threads_perf mandelbrot
perf report --no-children
```

For gprof (single-threaded SIMD version only):

```bash
make prof_simd
./fractol_simd_prof mandelbrot      # quit normally to write gmon.out
gprof ./fractol_simd_prof gmon.out | less
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
