#ifndef INGREDIENTES_HPP
#define INGREDIENTES_HPP


#include <string>
#include "cores.hpp"
using std::string;
using namespace cores;


typedef struct
{
    string nome;
    char simbolo;
    bool perecivel;
    bool requer_preparo;
    int validade_turnos;
    const char* cor;

} Ingrediente;

// Sem preparo e com quantidade infinita
inline const Ingrediente PAO{
    "Pao de cima", 'z', false, false, 0, LARANJA
};

inline const Ingrediente KETCHUP{
    "Ketchup", 'k', false, false, 0, VERMELHO
};

inline const Ingrediente MOSTARDA{
    "Mostarda", 'm', false, false, 0, AMARELO
};

inline const Ingrediente PICLES{
    "Picles", 'p', false, false, 0, VERDE
};

inline const Ingrediente ALFACE{
    "Alface", 'a', false, false, 0, VERDE_CLARO
};

// Com preparo, mas nao pereciveis
inline const Ingrediente QUEIJO_SUICO{
    "Queijo suico", 's', false, true, 0, AMARELO_CLARO
};

inline const Ingrediente QUEIJO_CHEDDAR{
    "Queijo cheddar", 'q', false, true, 0, AMARELO,
};

inline const Ingrediente CEBOLA{
    "Cebola", 'c', false, true, 0, CINZA
};

inline const Ingrediente TOMATE{
    "Tomate", 't', false, true, 0, VERMELHO_CLARO
};

// Com preparo e pereciveis
inline const Ingrediente CARNE{
    "Carne", 'n', true, true, 3, MARROM
};

inline const Ingrediente OVO_FRITO{
    "Ovo frito", 'o', true, true, 3, BRANCO
};

inline const Ingrediente BACON{
    "Bacon", 'b', true, true, 3, MAGENTA
};


const Ingrediente *buscarIngrediente(char simbolo);

#endif