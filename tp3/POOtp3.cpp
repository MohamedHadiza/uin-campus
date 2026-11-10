
#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <format>
#include <iostream>
#include <print>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

enum class Mention { Ajourne, Passable, AssezBien, Bien, TresBien };

constexpr std::size_t nbMentions = 5;
constexpr int nbEtudiantsMin = 1;
constexpr int nbEtudiantsMax = 200;
constexpr double noteMin = 0.0;
constexpr double noteMax = 20.0;
constexpr double seuilValidation = 10.0;

Mention mentionPour(double note)
{
    if (note < seuilValidation) { return Mention::Ajourne; }
    if (note < 12.0) { return Mention::Passable; }
    if (note < 14.0) { return Mention::AssezBien; }
    if (note < 16.0) { return Mention::Bien; }
    return Mention::TresBien;
}

std::string_view libelle(Mention m)
{
    using enum Mention;
    switch (m) {
        case Ajourne:   return "Ajourné";
        case Passable:  return "Passable";
        case AssezBien: return "Assez bien";
        case Bien:      return "Bien";
        case TresBien:  return "Très bien";
    }
    return "Inconnue";
}

// Entier strict : toute la ligne doit être un entier.
int lireEntier(std::string_view invite, int min, int max)
{
    while (true) {
        std::cout << invite;
        std::string ligne;
        if (!std::getline(std::cin, ligne)) {
            return min; // fin d'entrée : valeur de repli
        }
        std::istringstream flux{ligne};
        int valeur{};
        char reste{};
        if (!(flux >> valeur) || (flux >> reste)) {
            std::cout << "  Saisie invalide : entrez un nombre entier.\n";
        } else if (valeur < min || valeur > max) {
            std::cout << "  La valeur doit être comprise entre " << min << " et " << max << ".\n";
        } else {
            return valeur;
        }
    }
}

// Note dans [0 ; 20], virgule ou point décimal accepté.
double lireNote(std::string_view invite)
{
    while (true) {
        std::cout << invite;
        std::string ligne;
        if (!std::getline(std::cin, ligne)) {
            return noteMin; // fin d'entrée : valeur de repli
        }
        std::ranges::replace(ligne, ',', '.');
        std::istringstream flux{ligne};
        double note{};
        char reste{};
        if (!(flux >> note) || (flux >> reste)) {
            std::cout << "  Saisie invalide : entrez un nombre (ex. 12.5 ou 12,5).\n";
        } else if (note < noteMin || note > noteMax) {
            std::cout << "  La note doit être comprise entre 0 et 20.\n";
        } else {
            return note;
        }
    }
}

int main()
{
    std::cout << "Nom de l'UE : ";
    std::string ue;
    std::getline(std::cin, ue);

    const int nb = lireEntier(
        std::format("Nombre d'étudiants ({} à {}) : ", nbEtudiantsMin, nbEtudiantsMax),
        nbEtudiantsMin, nbEtudiantsMax);

    std::vector<double> notes;
    notes.reserve(static_cast<std::size_t>(nb));
    for (int i{1}; i <= nb; ++i) {
        notes.push_back(lireNote(std::format("Note de l'étudiant {} : ", i)));
    }

    double minimum{noteMax};
    double maximum{noteMin};
    double somme{0.0};
    int admis{0};
    std::array<int, nbMentions> repartition{};

    for (double n : notes) {
        minimum = std::min(minimum, n);
        maximum = std::max(maximum, n);
        somme += n;
        if (n >= seuilValidation) { ++admis; }
        ++repartition[static_cast<std::size_t>(mentionPour(n))];
    }

    const double taille = static_cast<double>(notes.size());
    const double moyenne = somme / taille;

    double sommeEcarts{0.0};
    for (double n : notes) {
        sommeEcarts += (n - moyenne) * (n - moyenne);
    }
    const double ecartType = std::sqrt(sommeEcarts / taille);

    std::println("\nStatistiques — {} ({} étudiants)", ue, nb);
    std::println("{:-<58}", "");
    std::println("{:<18}: {:6.2f}", "Note minimale", minimum);
    std::println("{:<18}: {:6.2f}", "Note maximale", maximum);
    std::println("{:<18}: {:6.2f}", "Moyenne", moyenne);
    std::println("{:<18}: {:6.2f}", "Écart-type", ecartType);
    std::println("{:<18}: {:6} ({:.1f} %)", "Admis", admis,
                 100.0 * static_cast<double>(admis) / taille);

    std::println("\nRépartition par mention");
    for (std::size_t i{0}; i < nbMentions; ++i) {
        const auto m = static_cast<Mention>(i);
        std::println("{:<12} {} ({})", libelle(m),
                     std::string(static_cast<std::size_t>(repartition[i]), '*'),
                     repartition[i]);
    }
}