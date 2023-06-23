#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NOMES 1000
#define MAX_TAMANHO_NOME 100

int busca_binaria(char nomes[MAX_NOMES][MAX_TAMANHO_NOME], int n, char *inicio) {
    int esquerda = 0;
    int direita = n - 1;

    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        if (strncasecmp(nomes[meio], inicio, strlen(inicio)) == 0) {
            return meio;
        } else if (strcasecmp(nomes[meio], inicio) < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    return -1;
}

int encontrar_nomes(char *inicio, char resultado[MAX_NOMES][MAX_TAMANHO_NOME]) {
    FILE *fp = fopen("nomes.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir\n");
        return -1;
    }

    char nomes[MAX_NOMES][MAX_TAMANHO_NOME];
    int n = 0;
    while (fgets(nomes[n], MAX_TAMANHO_NOME, fp) != NULL) {
        nomes[n][strlen(nomes[n])-1] = '\0';
        n++;
    }
    fclose(fp);

    int indice = busca_binaria(nomes, n, inicio);
    if (indice == -1) {
        return 0;
    }

    int i = indice;
    int j = 0;
    while (i < n && strncasecmp(nomes[i], inicio, strlen(inicio)) == 0) {
        strncpy(resultado[j], nomes[i], MAX_TAMANHO_NOME);
        i++;
        j++;
    }

    return j;
}

void sequencia(char *seq) {
    printf("Sequencia de caracteres: ");
    fgets(seq, MAX_TAMANHO_NOME, stdin);
    seq[strlen(seq)-1] = '\0';

    for (int i = 0; i < strlen(seq); i++) {
        seq[i] = tolower(seq[i]);
    }
}

int main() {
    char seq[MAX_TAMANHO_NOME];
    char resultado[MAX_NOMES][MAX_TAMANHO_NOME];

    sequencia(seq);

    int n = encontrar_nomes(seq, resultado);

    if (n == 0) {
        printf("Nome nao encontrado\n");
    } else {
        for (int i = 0; i < n; i++) {
            printf("%s\n", resultado[i]);
        }
    }

    return 0;
}
