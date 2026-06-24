#ifndef JOGADOR_H
#define JOGADOR_H

#include "pokemon.h"

typedef struct {
    Pokemon *equipe;
    int quantidade;
    int atual;
} Jogador;

Jogador *criar_jogador(int quantidade);
void liberar_jogador(Jogador *jogador);


#endif