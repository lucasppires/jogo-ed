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