#include "ingredientes.hpp"

#include <string>
using std::string;

const Ingrediente *buscarIngrediente(char simbolo)
{
    switch (simbolo)
    {
        case 'n':
            return &CARNE;
        case 'z':
            return &PAO;
        case 'k':
            return &KETCHUP;
        case 'm':
            return &MOSTARDA;
        case 'p':
            return &PICLES;
        case 'a':
            return &ALFACE;
        case 's':
            return &QUEIJO_SUICO;
        case 'q':
            return &QUEIJO_CHEDDAR;
        case 'c':   
            return &CEBOLA;
        case 't':
            return &TOMATE;
        case 'o':
            return &OVO_FRITO;
        case 'b':
            return &BACON;
        default:
            return nullptr;

    }
}

int conta_turnos_ingrediente(const Ingrediente *ingrediente)  //para estipular a paciencia de cada cliente, precisamos contar quantos turnos cada ingrediente leva, no minimo. para ser adicionado
{

    if (ingrediente->requer_preparo == true)
    {
        return 2; //se precisa de preparo, sao 2 turnos, o de preparo e o de adicionar
    }
    else
    {
        return 1; //se nao precisa, so 1 turno para adicionar
    }


}
