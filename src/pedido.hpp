#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include "listaenc.hpp"

struct Pedido  //cada pedido tem um codigo e uma receita(composta por varios ingredientes encadeados)
{
    int cod;
    ListaEnc receita;
};

struct Cliente 
{
    int id;
    int paciencia_restante;
    const Pedido *pedido_cliente = nullptr;
};

#endif