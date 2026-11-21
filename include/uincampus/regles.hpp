#pragma once

#include <array>
#include <string_view>

namespace uin {

/// Bornes du barème et seuil de validation d'une UE.
inline constexpr double noteMin = 0.0;
inline constexpr double noteMax = 20.0;
inline constexpr double seuilValidation = 10.0;

/// Mentions attribuées selon la moyenne.
enum class Mention { Ajourne, Passable, AssezBien, Bien, TresBien };

/// Seuils d'accès aux mentions Passable, Assez bien, Bien et Très bien.
inline constexpr std::array seuilsMentions{10.0, 12.0, 14.0, 16.0};

static_assert(seuilsMentions.size() == 4, "Un seuil par mention au-dessus d'Ajourné");
static_assert(seuilsMentions[0] == seuilValidation,
              "La mention Passable commence au seuil de validation");

/// Une note est valide si elle appartient à [noteMin ; noteMax].
constexpr bool estNoteValide(double note)
{
    return note >= noteMin && note <= noteMax;
}

/// Mention correspondant à une moyenne.
Mention mentionPour(double moyenne);

/// Libellé affichable d'une mention.
std::string_view libelle(Mention mention);

} // namespace uin
