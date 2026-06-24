#include <stdio.h>

#include "pokemon.h"
#include "jogador.h"

#define ARQUIVO_ENTRADA "entrada.txt"
#define ARQUIVO_SAIDA "saida.txt"

int calcular_dano(const Pokemon *atacante, const Pokemon *defensor) {
    int dano;

    if ((atacante->tipo == ELETRICO && defensor->tipo == AGUA) ||
        (atacante->tipo == AGUA && defensor->tipo == FOGO) ||
        (atacante->tipo == FOGO && defensor->tipo == GELO) ||
        (atacante->tipo == GELO && defensor->tipo == PEDRA) ||
        (atacante->tipo == PEDRA && defensor->tipo == ELETRICO)) {
        dano = atacante->ataque * 120 / 100 - defensor->defesa;
    } else if ((atacante->tipo == ELETRICO && defensor->tipo == PEDRA) ||
               (atacante->tipo == AGUA && defensor->tipo == ELETRICO) ||
               (atacante->tipo == FOGO && defensor->tipo == AGUA) ||
               (atacante->tipo == GELO && defensor->tipo == FOGO) ||
               (atacante->tipo == PEDRA && defensor->tipo == GELO)) {
        dano = atacante->ataque * 80 / 100 - defensor->defesa;
    } else {
        dano = atacante->ataque - defensor->defesa;
    }

    return dano > 0 ? dano : 1;
}

void turno(Jogador *atacante, Jogador *defensor, FILE *saida) {
    Pokemon *pokemon_atacante = &atacante->equipe[atacante->atual];
    Pokemon *pokemon_defensor = &defensor->equipe[defensor->atual];
    int dano = calcular_dano(pokemon_atacante, pokemon_defensor);

    pokemon_defensor->vida -= dano;

    if (pokemon_defensor->vida <= 0) {
        fprintf(saida, "%s venceu %s\n",
                pokemon_atacante->nome, pokemon_defensor->nome);
        defensor->atual++;
    }
}

int main(void) {
    FILE *entrada = fopen(ARQUIVO_ENTRADA, "r");
    FILE *saida;
    Jogador *jogador1 = NULL;
    Jogador *jogador2 = NULL;
    Jogador *vencedor;
    int quantidade1;
    int quantidade2;
    int vez_jogador1 = 1;
    int primeiro = 1;

    if (entrada == NULL) {
        fprintf(stderr, "Erro ao abrir %s.\n", ARQUIVO_ENTRADA);
        return 1;
    }

    saida = fopen(ARQUIVO_SAIDA, "w");
    if (saida == NULL) {
        fprintf(stderr, "Erro ao criar %s.\n", ARQUIVO_SAIDA);
        fclose(entrada);
        return 1;
    }

    if (fscanf(entrada, "%d %d", &quantidade1, &quantidade2) != 2) {
        fprintf(stderr, "Erro ao ler as quantidades dos jogadores.\n");
        fclose(entrada);
        fclose(saida);
        return 1;
    }

    jogador1 = criar_jogador(quantidade1);
    jogador2 = criar_jogador(quantidade2);
    if (jogador1 == NULL || jogador2 == NULL) {
        fprintf(stderr, "Erro ao criar os jogadores.\n");
        liberar_jogador(jogador1);
        liberar_jogador(jogador2);
        fclose(entrada);
        fclose(saida);
        return 1;
    }

    for (int i = 0; i < jogador1->quantidade; i++) {
        if (!ler_pokemon(entrada, &jogador1->equipe[i])) {
            fprintf(stderr, "Erro ao ler Pokemon do jogador 1.\n");
            liberar_jogador(jogador1);
            liberar_jogador(jogador2);
            fclose(entrada);
            fclose(saida);
            return 1;
        }
    }

    for (int i = 0; i < jogador2->quantidade; i++) {
        if (!ler_pokemon(entrada, &jogador2->equipe[i])) {
            fprintf(stderr, "Erro ao ler Pokemon do jogador 2.\n");
            liberar_jogador(jogador1);
            liberar_jogador(jogador2);
            fclose(entrada);
            fclose(saida);
            return 1;
        }
    }
    fclose(entrada);

    while (jogador1->atual < jogador1->quantidade &&
           jogador2->atual < jogador2->quantidade) {
        if (vez_jogador1) {
            turno(jogador1, jogador2, saida);
        } else {
            turno(jogador2, jogador1, saida);
        }

        vez_jogador1 = !vez_jogador1;
    }

    vencedor = jogador1->atual >= jogador1->quantidade ? jogador2 : jogador1;
    fprintf(saida, "Jogador %d venceu\n", vencedor == jogador1 ? 1 : 2);
    fprintf(saida, "Pokemon sobreviventes:\n");

    for (int i = vencedor->atual; i < vencedor->quantidade; i++) {
        fprintf(saida, "%s%s", i == vencedor->atual ? "" : " ",
                vencedor->equipe[i].nome);
    }

    fprintf(saida, "\nPokemon derrotados:\n");
    for (int i = 0; i < jogador1->atual; i++) {
        fprintf(saida, "%s%s", primeiro ? "" : " ", jogador1->equipe[i].nome);
        primeiro = 0;
    }
    for (int i = 0; i < jogador2->atual; i++) {
        fprintf(saida, "%s%s", primeiro ? "" : " ", jogador2->equipe[i].nome);
        primeiro = 0;
    }
    fprintf(saida, "\n");

    liberar_jogador(jogador1);
    liberar_jogador(jogador2);
    fclose(saida);
    return 0;
}
