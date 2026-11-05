#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include "listaenc.hpp"

struct Pedido {
    int cod;
    ListaEnc receita;
};

struct Cliente
{
    int id;
    int paciencia_restante;
};

#endif