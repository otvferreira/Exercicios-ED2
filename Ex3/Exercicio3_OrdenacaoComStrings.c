#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE_ROW 100
#define NUM_ROWS 1000

void mostrar_nomes(char arr[][SIZE_ROW]){
    for(int j = 0; j < NUM_ROWS; j++){
        printf("%s", arr[j]);
    }
    printf("\n\n");
}

void trocar(char arr[][SIZE_ROW], int i, int j){
    char temp[SIZE_ROW];

    strcpy(temp, arr[i]);
    strcpy(arr[i], arr[j]);
    strcpy(arr[j], temp);
}

void bubble_sort(char arr[][SIZE_ROW]){
    for(int i = 0; i < (NUM_ROWS - 1); i++){
        for(int j = 0; j < (NUM_ROWS - i - 1); j++){
            if(strcmp(arr[j], arr[j+1]) > 0){
                trocar(arr, j, j+1);
            }
        }
    }
}

void selection_sort(char arr[][SIZE_ROW]){
    for(int i = 0; i < (NUM_ROWS - 1); i++){
        for(int j = i + 1; j < NUM_ROWS; j++){
            if(strcmp(arr[i], arr[j]) > 0){
                trocar(arr, i, j);
            }
        }
    }
}

void insertion_sort(char arr[][SIZE_ROW]){
    int j = 0;
    char *key;
    for(int i = 1; i < NUM_ROWS; i++){
        strcpy(key, arr[i]);
        for(j = i - 1; j >= 0 && (strcmp(arr[j], key) > 0); j--){
            strcpy(arr[j + 1], arr[j]);
        }
        strcpy(arr[j + 1], key);
    }
}

void merge(char arr[][SIZE_ROW], int inicio, int meio, int fim){
    int size_left = meio - inicio + 1;
    int size_right = fim - meio;

    char left[size_left][SIZE_ROW];
    char right[size_right][SIZE_ROW];

    int i, j, k;

    for(i = 0; i < size_left; i++){
        strcpy(left[i], arr[inicio + i]);
    }
    for(j = 0; j < size_right; j++){
        strcpy(right[j], arr[meio + 1 + j]);
    }

    i = 0;
    j = 0;
    k = inicio;

    while(i < size_left && j < size_right){
        if(strcmp(left[i], right[j]) <= 0){
            strcpy(arr[k], left[i]);
            i++;
        }else{
            strcpy(arr[k], right[j]);
            j++;
        }
        k++;
    }

    while(i < size_left){
        strcpy(arr[k], left[i]);
        i++;
        k++;
    }

    while(j < size_right){
        strcpy(arr[k], right[j]);
        j++;
        k++;
    }
}

void merge_sort(char arr[][SIZE_ROW], int inicio, int fim){
    if(inicio < fim){
        int meio = (inicio + fim) / 2;
        merge_sort(arr, inicio, meio);
        merge_sort(arr, (meio + 1), fim);
        merge(arr, inicio, meio, fim);
    }
}

int main(){
    char nome_arquivo[] = "nomes2.txt";
    char nomes[NUM_ROWS][SIZE_ROW];

    FILE* arquivo = fopen(nome_arquivo, "r");

    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    int i = 0;
    while(!feof(arquivo)){
        fgets(nomes[i], SIZE_ROW, arquivo);
        i++;
    }

    fclose(arquivo);

    int op = 0;

    do {
        printf("Escolha qual metodo de ordenacao deseja usar:\n\n");
        printf("1: Bubble Sort\n");
        printf("2: Selection Sort\n");
        printf("3: Insertion Sort\n");
        printf("4: Merge Sort\n");
        printf("5: Sair\n");
        scanf("%d", &op);

        switch (op) {
            case 1:
                bubble_sort(nomes);
                mostrar_nomes(nomes);
                break;
            case 2:
                selection_sort(nomes);
                mostrar_nomes(nomes);
                break;
            case 3:
                insertion_sort(nomes);
                mostrar_nomes(nomes);
                break;
            case 4:
                merge_sort(nomes, 0, NUM_ROWS - 1);
                mostrar_nomes(nomes);
                break;
            case 5:
                break;
            default:
                printf("Opcao invalida!\n\n");
                break;
        }
    } while (op != 5);

    return 0;
}
