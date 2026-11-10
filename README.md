# UIN-Campus

Système de gestion académique de l'UIN, développé en **C++23** dans le cadre du cours de Programmation Orientée Objet en C++ moderne.

Le projet est construit progressivement, chapitre après chapitre (« fil rouge » du cours).

## Fonctionnalités actuelles

- Calcul de la moyenne d'un étudiant à partir de ses notes
- Attribution d'une mention (Ajourné, Passable, Assez bien, Bien, Très bien)
- Décision de validation (seuil à 10/20)
- Saisie robuste : les entrées invalides (lettres, valeurs hors barème) sont refusées et redemandées, la virgule décimale est acceptée (`12,5`)

## Prérequis

| Outil | Version minimale |
|---|---|
| Compilateur C++23 (GCC ou Clang) | GCC 14 ou Clang 18 |
| CMake | 3.25 |
| Ninja | 1.11 |
| Git | 2.x |

Environnement de développement utilisé : Ubuntu 24.04, VS Code avec clangd.

## Construction et exécution

```bash
git clone https://github.com/MohamedHadiza/uin-campus.git
cd uin-campus
cmake --preset debug
cmake --build --preset debug
./build/debug/uin-campus
```

Deux configurations sont disponibles :

- `debug` : sans optimisation, avec AddressSanitizer et UBSan pour détecter les erreurs mémoire
- `release` : optimisée

```bash
cmake --preset release
cmake --build --preset release
./build/release/uin-campus
```

## Exemple d'exécution

```text
UIN-Campus 0.1.0 — Calcul de la moyenne d'un étudiant

Nom de l'étudiant : Moussa Adamou
Nombre de notes (1 à 30) : 3
  Note 1 : 12,5
  Note 2 : 14
  Note 3 : 9.5

----------------------------------------
Étudiant                  Moussa Adamou
Nombre de notes                       3
Moyenne                           12.00
Mention                      Assez bien
Décision                         Validé
----------------------------------------
```

## Structure du projet

```text
uin-campus/
├── include/uincampus/    En-têtes publics
│   ├── version.hpp
│   ├── regles.hpp        Barème, seuil de validation, mentions
│   └── saisie.hpp        Saisie robuste (texte, entier, note)
├── src/                  Implémentations
│   ├── version.cpp
│   ├── regles.cpp
│   └── saisie.cpp
├── app/
│   └── main.cpp          Programme principal
├── tests/                Tests (à venir)
├── docs/                 Documentation (à venir)
├── CMakeLists.txt
└── CMakePresets.json
```

La logique métier est regroupée dans la bibliothèque `uincampus_core` ; l'application `uin-campus` s'appuie sur elle.

## Qualité du code

- Compilation avec `-Wall -Wextra -Wpedantic -Wshadow -Wconversion` : aucun avertissement toléré
- Formatage automatique avec `clang-format` (fichier `.clang-format`)
- Analyse statique avec `clang-tidy` (fichier `.clang-tidy`)


## Construction

    cmake --preset debug
    cmake --build --preset debug
    ./build/debug/uin-campus
