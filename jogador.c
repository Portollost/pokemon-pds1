#include "jogador.h"
#include "pokemon.h"
#include <stdlib.h>


Jogador *criar_jogador(int quantidade) {
    Jogador *jogador;

    if (quantidade < 1 || quantidade > MAX_POKEMONS) {
        return NULL;
    }

    jogador = malloc(sizeof(Jogador));
    if (jogador == NULL) {
        return NULL;
    }

    jogador->equipe = malloc(quantidade * sizeof(Pokemon));
    if (jogador->equipe == NULL) {
        free(jogador);
        return NULL;
    }

    jogador->quantidade = quantidade;
    jogador->atual = 0;

    return jogador;
}

void liberar_jogador(Jogador *jogador) {
    if (jogador != NULL) {
        free(jogador->equipe);
        free(jogador);
    }
}