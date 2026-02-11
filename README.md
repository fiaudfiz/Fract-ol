# 🌀 Fract-ol - Infinite Fractal Explorer
## 📖 Présentation

Fract-ol est un moteur de rendu graphique en temps réel développé en C. Ce projet explore le monde fascinant des ensembles récursifs et de la dynamique complexe à travers la manipulation de pixels avec la MiniLibX.

L'objectif est de générer des fractales mathématiquement précises avec une navigation fluide (zoom, déplacement) et une gestion dynamique des couleurs.
##🎨 Fractales disponibles

Le projet supporte plusieurs types de sets, des plus classiques aux plus exotiques :

    Mandelbrot : L'ensemble classique basé sur zn+1​=zn2​+c.

    Julia : Des variations infinies selon la position de la souris ou des paramètres fixes.

    Burning Ship : Une fractale particulière générant une forme de navire en feu via zn+1​=(∣Re(zn​)∣+i∣Im(zn​)∣)2+c.

    Celtic : Une variante élégante de Mandelbrot avec des structures en forme de nœuds.

    Tricorn : Également connue sous le nom de Mandelbar, utilisant le conjugué de z.

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
