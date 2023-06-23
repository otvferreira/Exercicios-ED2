#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TIMES 12
#define MAX_NOME_TIME 100

typedef struct {
    char nome[MAX_NOME_TIME];
    int vitorias;
    int empates;
    int derrotas;
    int pontos;
    int saldo_gols;
    int gols_pro;
    int gols_contra;
} Time;

int ler_arquivo(Time* arr) {
    FILE* arquivo = fopen("dados.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    int num_times = 0;

    while (!feof(arquivo)) {
        char nome_time_1[MAX_NOME_TIME], nome_time_2[MAX_NOME_TIME];
        int gols_time_1, gols_time_2;

        fscanf(arquivo, "%s %dX%d %s", nome_time_1, &gols_time_1, &gols_time_2, nome_time_2);

        int time_1_existe = -1, time_2_existe = -1;
        for (int i = 0; i < num_times; i++) {
            if (strcmp(arr[i].nome, nome_time_1) == 0) {
                time_1_existe = i;
            }
            if (strcmp(arr[i].nome, nome_time_2) == 0) {
                time_2_existe = i;
            }
        }

        if (time_1_existe == -1) {
            strcpy(arr[num_times].nome, nome_time_1);
            arr[num_times].pontos = 0;
            arr[num_times].vitorias = 0;
            arr[num_times].empates = 0;
            arr[num_times].derrotas = 0;
            arr[num_times].gols_pro = 0;
            arr[num_times].gols_contra = 0;
            arr[num_times].saldo_gols = 0;
            time_1_existe = num_times;
            num_times++;
        }

        if (time_2_existe == -1) {
            strcpy(arr[num_times].nome, nome_time_2);
            arr[num_times].pontos = 0;
            arr[num_times].vitorias = 0;
            arr[num_times].empates = 0;
            arr[num_times].derrotas = 0;
            arr[num_times].gols_pro = 0;
            arr[num_times].gols_contra = 0;
            arr[num_times].saldo_gols = 0;
            time_2_existe = num_times;
            num_times++;
        }

        if (gols_time_1 > gols_time_2) {
            arr[time_1_existe].vitorias++;
            arr[time_1_existe].pontos += 3;
            arr[time_2_existe].derrotas++;
        } else if (gols_time_2 > gols_time_1) {
            arr[time_2_existe].vitorias++;
            arr[time_2_existe].pontos += 3;
            arr[time_1_existe].derrotas++;
        } else {
            arr[time_1_existe].pontos++;
            arr[time_2_existe].pontos++;
            arr[time_1_existe].empates++;
            arr[time_2_existe].empates++;
        }

        arr[time_1_existe].gols_pro += gols_time_1;
        arr[time_1_existe].gols_contra += gols_time_2;
        arr[time_1_existe].saldo_gols += gols_time_1 - gols_time_2;
        arr[time_2_existe].gols_pro += gols_time_2;
        arr[time_2_existe].gols_contra += gols_time_1;
        arr[time_2_existe].saldo_gols += gols_time_2 - gols_time_1;
    }

    fclose(arquivo);

    return num_times;
}

void mostrar_times(Time* arr, int num_times) {
    printf("TIME\t\tPTOS\tVIT\tEMP\tDRT\tSG\tGP\tGC\n");

    for (int i = 0; i < num_times; i++) {
        printf("%s\t\t", arr[i].nome);
        printf("%d\t", arr[i].pontos);
        printf("%d\t", arr[i].vitorias);
        printf("%d\t", arr[i].empates);
        printf("%d\t", arr[i].derrotas);
        printf("%d\t", arr[i].saldo_gols);
        printf("%d\t", arr[i].gols_pro);
        printf("%d\n", arr[i].gols_contra);
    }
}

void ordenar_times(Time* arr, int num_times) {
    Time temp;

    for (int i = 0; i < num_times - 1; i++) {
        for (int j = 0; j < num_times - i - 1; j++) {
            if (arr[j].pontos < arr[j + 1].pontos) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            } else if (arr[j].pontos == arr[j + 1].pontos) {
                if (arr[j].vitorias > arr[j + 1].vitorias) {
                    temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                } else if (arr[j].vitorias == arr[j + 1].vitorias) {
                    if (arr[j].saldo_gols > arr[j + 1].saldo_gols) {
                        temp = arr[j];
                        arr[j] = arr[j + 1];
                        arr[j + 1] = temp;
                    }
                }
            }
        }
    }
}

int main() {
    Time times[MAX_TIMES];
    int num_times;

    num_times = ler_arquivo(times);

    ordenar_times(times, num_times);
    mostrar_times(times, num_times);

    return 0;
}

