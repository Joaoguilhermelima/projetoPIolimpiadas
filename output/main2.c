#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    int totalMedalhas;
} Edicao;

int encontraEdicao(Edicao edicoes[], int qntdEdicoes, char nome[]) {
    for(int i = 0; i < qntdEdicoes; i++) {
        if(strcmp(edicoes[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

int main() 
{
    FILE *arquivo = fopen("results.csv", "r");
    if(!arquivo) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char linha[1024];
    Edicao edicoes[200];
    int totalEdicoes = 0;
    char paises[5][10];

    printf("Digite os 5 países que deseja: \n");
    for(int i = 0; i < 5; i++) {
        scanf("%s", paises[i]);
    }

    fgets(linha,sizeof(linha), arquivo); // pula o cabeçalho

    while(fgets(linha, sizeof(linha), arquivo)) {
        char *token = strtok(linha, ",");
        int coluna = 0;

        int ano = 0;
        char pais[50] = "";
        char medalha[10] = "";

        while (token != NULL) {
            if(coluna == 0) {
                ano = atoi(token);
            }

            if(coluna == 6) {
                strcpy(pais, token);
            }

            if(coluna == 10) {
                strcpy(medalha, token);
            }

            token = strtok(NULL, ",");
            coluna++;
        }

        int valido = 0;
        for (int i = 0; i < 5; i++) {
            if (strcmp(paises[i], pais) == 0) {
            valido = 1;
            }
        }

        if (valido && strlen(medalha) > 0) {
            char edicaoNome[50];
            sprintf(edicaoNome, "%d", ano);

            int indiceEdicao = encontraEdicao(edicoes, totalEdicoes, edicaoNome);

            if(indiceEdicao == -1) {
                strcpy(edicoes[totalEdicoes].nome, edicaoNome);
                edicoes[totalEdicoes].totalMedalhas = 1;
                totalEdicoes++;
            } else {
                edicoes[indiceEdicao].totalMedalhas++;
            }
        }
    }

    fclose(arquivo);

    for(int i = 0; i < totalEdicoes; i++) {
        for(int j = 0; j < totalEdicoes - i - 1; j++) {
            if(edicoes[j].totalMedalhas < edicoes[j + 1].totalMedalhas) {
                Edicao temporaria = edicoes[j];
                edicoes[j] = edicoes[j + 1];
                edicoes[j + 1] = temporaria;
            }
        }
    }

    printf("\nTop 3 edições em que os países escolhidos ganharam mais medalhas:\n");

    for(int i = 0; i < 3 && i < totalEdicoes; i++) {
        printf("%d° lugar: %d medalhas em %s\n", i + 1, edicoes[i].totalMedalhas, edicoes[i].nome);
    }
}   