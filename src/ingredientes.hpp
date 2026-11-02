#ifndef INGREDIENTES_HPP
#define INGREDIENTES_HPP


#include <string>
using std::string;


typedef struct
{
    string nome;
    char simbolo;
    bool perecivel;
    bool requer_preparo;
    int validade_turnos;

} Ingrediente;

// Sem preparo e com quantidade infinita
inline const Ingrediente PAO{
    "Pao de cima", 'z', false, false, 0
};

inline const Ingrediente KETCHUP{
    "Ketchup", 'k', false, false, 0
};

inline const Ingrediente MOSTARDA{
    "Mostarda", 'm', false, false, 0
};

inline const Ingrediente PICLES{
    "Picles", 'p', false, false, 0
};

inline const Ingrediente ALFACE{
    "Alface", 'a', false, false, 0
};

// Com preparo, mas nao pereciveis
inline const Ingrediente QUEIJO_SUICO{
    "Queijo suico", 's', false, true, 0
};

inline const Ingrediente QUEIJO_CHEDDAR{
    "Queijo cheddar", 'q', false, true, 0
};

inline const Ingrediente CEBOLA{
    "Cebola", 'c', false, true, 0
};

inline const Ingrediente TOMATE{
    "Tomate", 't', false, true, 0
};

// Com preparo e pereciveis
inline const Ingrediente CARNE{
    "Carne", 'n', true, true, 3
};

inline const Ingrediente OVO_FRITO{
    "Ovo frito", 'o', true, true, 2
};

inline const Ingrediente BACON{
    "Bacon", 'b', true, true, 3
};


const Ingrediente *buscarIngrediente(char simbolo);

#endif