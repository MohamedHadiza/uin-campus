#include "uincampus/calculs.hpp"
#include "uincampus/regles.hpp"
#include "uincampus/saisie.hpp"
#include "uincampus/version.hpp"

#include <cstdlib>
#include <format>
#include <print>
#include <string>
#include <string_view>
#include <vector>

namespace {

void afficherLigne(std::string_view libelle, std::string_view valeur)
{
    std::println("{:<24}{:>20}", libelle, valeur);
}

} // namespace

int main(int argc, char* argv[])
{
    if (argc > 1 && std::string_view{argv[1]} == "--version") {
        std::println("uin-campus {}", uin::version());
        return EXIT_SUCCESS;
    }

    std::println("UIN-Campus {} — Relevé d'un étudiant\n", uin::version());

    const std::string nom = uin::lireTexte("Nom de l'étudiant : ");
    const int nbUE = uin::lireEntier("Nombre d'UE (1 à 30) : ", 1, 30);

    std::vector<double> notes;
    std::vector<double> coefficients;
    for (int i{1}; i <= nbUE; ++i) {
        notes.push_back(uin::lireNote(std::format("  Note de l'UE {} : ", i)));
        coefficients.push_back(static_cast<double>(
            uin::lireEntier(std::format("  Coefficient de l'UE {} : ", i), 1, 10)));
    }

    const double moyenneGenerale = uin::arrondir(uin::moyenne(notes, coefficients));
    const auto [mini, maxi, moyenneSimple, ecartType] = uin::calculerStatistiques(notes);
    const int validees = uin::compterValidees(notes);

    std::println("\n{:-<44}", "");
    afficherLigne("Étudiant", nom);
    afficherLigne("Moyenne pondérée", std::format("{:.2f}", moyenneGenerale));
    afficherLigne("Moyenne simple", std::format("{:.2f}", moyenneSimple));
    afficherLigne("Note min / max", std::format("{:.2f} / {:.2f}", mini, maxi));
    afficherLigne("Écart-type", std::format("{:.2f}", ecartType));
    afficherLigne("UE validées", std::format("{} / {}", validees, nbUE));
    afficherLigne("Mention", uin::libelle(uin::mentionPour(moyenneGenerale)));
    std::println("{:-<44}", "");

    return EXIT_SUCCESS;
}
