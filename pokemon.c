#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pokemon.h"
#include "jogador.h"

/* Pokemon functions */
/* Function to create a Pokemon */

int converter_tipo(const char *texto, TipoPokemon *tipo) {
    if (strcmp(texto, "eletrico") == 0 || strcmp(texto, "elétrico") == 0) {
        *tipo = ELETRICO;
    } else if (strcmp(texto, "agua") == 0 || strcmp(texto, "água") == 0) {
        *tipo = AGUA;
    } else if (strcmp(texto, "fogo") == 0) {
        *tipo = FOGO;
    } else if (strcmp(texto, "gelo") == 0) {
        *tipo = GELO;
    } else if (strcmp(texto, "pedra") == 0) {
        *tipo = PEDRA;
    } else {
        return 0;
    }

    return 1;
}

int ler_pokemon(FILE *arquivo, Pokemon *pokemon) {
    char tipo_texto[TAM_NOME];

    if (fscanf(arquivo, "%99s %d %d %d %99s",
               pokemon->nome,
               &pokemon->ataque,
               &pokemon->defesa,
               &pokemon->vida,
               tipo_texto) != 5) {
        return 0;
    }

    if (!converter_tipo(tipo_texto, &pokemon->tipo)) {
        return 0;
    }

    return 1;
}

const char *tipo_para_texto(TipoPokemon tipo) {
    switch (tipo) {
        case ELETRICO:
            return "elétrico";
        case AGUA:
            return "água";
        case FOGO:
            return "fogo";
        case GELO:
            return "gelo";
        case PEDRA:
            return "pedra";
        default:
            return "desconhecido";
    }
}

void imprimir_pokemon(const Pokemon *pokemon) {
    if (pokemon == NULL) {
        return;
    }

    printf("%s %d %d %d %s\n",
           pokemon->nome,
           pokemon->ataque,
           pokemon->defesa,
           pokemon->vida,
           tipo_para_texto(pokemon->tipo));
}

/* Function to free a Pokemon */
void liberar_pokemon(Pokemon *pokemon) {
    if (pokemon != NULL) {
        free(pokemon);
    }
}
