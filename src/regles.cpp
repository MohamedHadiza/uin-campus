#include "uincampus/regles.hpp"

namespace uin {

Mention mentionPour(double moyenne)
{
    // Chaque seuil franchi fait monter d'un rang : 0 seuil -> Ajourne, 4 seuils -> TresBien.
    int rang{0};
    for (double seuil : seuilsMentions) {
        if (moyenne >= seuil) {
            ++rang;
        }
    }
    return static_cast<Mention>(rang);
}

std::string_view libelle(Mention mention)
{
    using enum Mention;
    switch (mention) {
    case Ajourne:
        return "Ajourné";
    case Passable:
        return "Passable";
    case AssezBien:
        return "Assez bien";
    case Bien:
        return "Bien";
    case TresBien:
        return "Très bien";
    }
    return "Inconnue";
}

} // namespace uin
