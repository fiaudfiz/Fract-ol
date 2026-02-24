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

## ⚙️ Installation & Dépendances

Ce projet nécessite deux bibliothèques externes situées dans le dossier libs/.
### 1. Arborescence requise
Plaintext
.
├── libs
│   ├── libft       # Ma bibliothèque C personnalisée
│   └── minilibx    # Bibliothèque graphique de 42
├── srcs            # Code source du projet
├── includes        # Headers
└── Makefile

### 2. Configuration

Pour cloner le projet avec ses dépendances (si tu utilises des submodules) ou les ajouter manuellement :
Bash

mkdir libs
# Ajouter ma libft custom
git clone git@github.com:fiaudfiz/libft.git libs/libft
# Ajouter la minilibx (version Linux ou MacOS selon ton poste)
# git clone [URL_MINILIBX] libs/minilibx

## 🚀 Utilisation

    Compilation :
    Bash

make

Lancement : Exécute le programme avec le nom de la fractale souhaitée :
Bash

    ./fractol mandelbrot
    ./fractol julia
    ./fractol burningship
    ./fractol celtic
    ./fractol tricorn

### ⌨️ Commandes & Contrôles

    Souris : Molette pour un Zoom/Unzoom précis sur le curseur.

    Clavier :

        Flèches / WASD : Se déplacer dans le plan complexe.

        C : Changer la palette de couleurs (Color Shifting).

        R : Reset la vue par défaut.

        ESC : Quitter proprement le programme.

### 🛠️ Défis Techniques

    Optimisation du rendu : Gestion des itérations pour garder un framerate fluide malgré la complexité mathématique.

    Interactivité : Mapping des coordonnées de l'écran (pixels) vers le plan complexe (nombres réels et imaginaires).

    Hooks MiniLibX : Gestion propre des événements clavier et souris pour éviter les fuites de mémoire et les plantages.

    Note : Ce projet respecte strictement la Norme 42 et a été testé pour garantir l'absence totale de fuites mémoire (Valgrind approved).
