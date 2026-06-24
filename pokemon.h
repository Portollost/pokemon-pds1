#include <stdio.h>

#ifndef POKEMON_H
#define POKEMON_H

#define MAX_POKEMONS 100
#define TAM_NOME 100

typedef enum {
    ELETRICO,
    AGUA,
    FOGO,
    GELO,
    PEDRA
} TipoPokemon;

typedef struct {
    char nome[TAM_NOME];
    int ataque;
    int defesa;
    int vida;
    TipoPokemon tipo;
} Pokemon;

int ler_pokemon(FILE *arquivo, Pokemon *pokemon);
const char *tipo_para_texto(TipoPokemon tipo);
void imprimir_pokemon(const Pokemon *pokemon);
#endif