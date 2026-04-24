# MyTetrisQT

Un clone de Tetris developpe en QT/C++.

## Apercu

Le jeu est compose de:

- Une logique metier en C++ (`TetrisGame`, `TetrisBoard`, `Tetromino`)
- Une interface en QML (`App.qml`, `Main.qml`)
- Une integration QML/C++ via `QML_ELEMENT` et enregistrement de type Qt

Le plateau principal est en 10x20, avec panneau `HOLD`, panneau `NEXT`, score, niveau et lignes.

## Fonctionnalites

- Deplacement gauche/droite
- Rotation de la piece (avec wall-kick basique: `0, -1, +1, -2, +2`)
- Soft drop et hard drop
- Ghost piece
- Systeme Hold (1 utilisation max par tour de piece)
- Effacement des lignes
- Score et progression de niveau
- Pause / reprise
- Ecran de game over + bouton rejouer

## Regles de score

Points de base par lignes effacees (multiplies par le niveau):

- 1 ligne: 100
- 2 lignes: 300
- 3 lignes: 500
- 4 lignes: 800

Bonus de descente:

- Soft drop: `+1` par case
- Hard drop: `+2` par case

Progression:

- Le niveau augmente de 1 toutes les 10 lignes
- Vitesse de chute: `max(33 ms, 800 - (niveau - 1) * 40)`

## Controles

- `Fleche gauche`: deplacer a gauche
- `Fleche droite`: deplacer a droite
- `Fleche haut`: rotation
- `Fleche bas`: soft drop
- `Espace`: hard drop
- `C` ou `Shift`: hold piece
- `P` ou `Echap`: pause / reprise



## Structure du projet

- `main.cpp`: point d'entree Qt, chargement du module QML
- `tetrisgame.h/.cpp`: boucle de jeu, score, niveau, hold, spawn, collisions haut niveau
- `tetrisboard.h/.cpp`: representation de grille, verrouillage, clear lines, ghost Y
- `tetromino.h/.cpp`: definitions des pieces, rotations, couleurs, aleatoire
- `App.qml`: fenetre principale
- `Main.qml`: interface utilisateur et gestion des entrees clavier
- `Constants.qml`: constantes d'UI
- `CMakeLists.txt`: configuration CMake/Qt

## Architecture (resume)

1. `TetrisGame` pilote le gameplay et expose des `Q_PROPERTY` vers QML.
2. `TetrisBoard` maintient la grille verrouillee et valide les placements.
3. `Main.qml` affiche la grille fusionnee (`cells`) + fantome (`ghost`) et relaye les controles clavier.

## Limites actuelles

- Generateur de pieces aleatoire simple (`rand`) et non pas un systeme "7-bag"
- Wall-kick simplifie (pas de SRS complet)
- Pas de sauvegarde de meilleur score

## Idees d'amelioration

- Passer a un randomizer 7-bag
- Implementer SRS complet pour des rotations plus fideles
- Ajouter effets visuels/sons (line clear, lock, game over)
- Ajouter persistance du high score
- Adapter l'UI a plusieurs resolutions

## Prerequis pour build sans QT Creator 

- Qt 6.8+ (module `Qt6::Quick`)
- CMake 3.16+

## Build et execution (Linux)

Depuis la racine du projet:

```bash
cmake -S . -B build
cmake --build build -j
./build/appMyTetrisQT
```
