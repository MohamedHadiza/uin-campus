#pragma once

#include "uincampus/regles.hpp"

#include <span>

namespace uin {

/// Indicateurs statistiques d'une série de notes.
struct Statistiques {
    double minimum{};
    double maximum{};
    double moyenne{};
    double ecartType{};
};

/// Somme des valeurs.
[[nodiscard]] double somme(std::span<const double> valeurs);

/// Moyenne arithmétique.
/// @pre notes n'est pas vide
[[nodiscard]] double moyenne(std::span<const double> notes);

/// Moyenne pondérée par les coefficients.
/// @pre notes n'est pas vide, même taille que coefficients, somme des coefficients > 0
[[nodiscard]] double moyenne(std::span<const double> notes, std::span<const double> coefficients);

/// Minimum, maximum, moyenne et écart-type.
/// @pre notes n'est pas vide
[[nodiscard]] Statistiques calculerStatistiques(std::span<const double> notes);

/// Nombre de notes supérieures ou égales au seuil.
[[nodiscard]] int compterValidees(std::span<const double> notes, double seuil = seuilValidation);

/// Arrondi au nombre de décimales demandé.
[[nodiscard]] double arrondir(double valeur, int decimales = 2);

} // namespace uin
