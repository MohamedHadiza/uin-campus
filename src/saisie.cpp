#include "uincampus/saisie.hpp"

#include "uincampus/regles.hpp"

#include <iostream>
#include <sstream>

namespace uin {

namespace { // espace de noms anonyme : fonctions internes à ce fichier (chapitre 4)

// Affiche l'invite puis lit une ligne. Renvoie false si l'entrée est fermée.
bool lireLigne(std::string_view invite, std::string& ligne)
{
    std::cout << invite;
    return static_cast<bool>(std::getline(std::cin, ligne));
}

bool estEntierStrict(const std::string& texte, int& valeur)
{
    std::istringstream flux{texte};
    char reste{};
    return (flux >> valeur) && !(flux >> reste);
}

bool estReelStrict(std::string texte, double& valeur)
{
    for (char& c : texte) {
        if (c == ',') { c = '.'; }
    }
    std::istringstream flux{texte};
    char reste{};
    return (flux >> valeur) && !(flux >> reste);
}

} // namespace

std::string lireTexte(std::string_view invite)
{
    std::string ligne;
    lireLigne(invite, ligne);
    return ligne;
}

int lireEntier(std::string_view invite, int min, int max)
{
    std::string ligne;
    while (lireLigne(invite, ligne)) {
        int valeur{};
        if (!estEntierStrict(ligne, valeur)) {
            std::cout << "  Saisie invalide : entrez un nombre entier.\n";
        } else if (valeur < min || valeur > max) {
            std::cout << "  La valeur doit être comprise entre " << min << " et " << max << ".\n";
        } else {
            return valeur;
        }
    }
    return min; // fin d'entrée : valeur de repli (sera remplacée par une exception au chapitre 15)
}

double lireNote(std::string_view invite)
{
    std::string ligne;
    while (lireLigne(invite, ligne)) {
        double note{};
        if (!estReelStrict(ligne, note)) {
            std::cout << "  Saisie invalide : entrez un nombre (ex. 12.5 ou 12,5).\n";
        } else if (!estNoteValide(note)) {
            std::cout << "  La note doit être comprise entre " << noteMin << " et " << noteMax
                      << ".\n";
        } else {
            return note;
        }
    }
    return noteMin;
}

} // namespace uin
