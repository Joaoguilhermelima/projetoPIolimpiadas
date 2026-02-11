#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { //struct para armazenar o ano e a quantidade de medalhas
    char ano[50];       
    int totalMedalhas;
} Edicao;

int encontraEdicao(Edicao edicoes[], int qntdEdicoes, char nome[]) { //função que serve pra encontrar a edição das olimpíadas
    for(int i = 0; i < qntdEdicoes; i++) { 
        if(strcmp(edicoes[i].ano, nome) == 0) { 
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

    char paises[5][10]; //armazenar os países que o usuário deseja consultar
    printf("Digite os 5 NOCs que deseja (ex: BRA USA FRA CHN GER): \n");
    for(int i = 0; i < 5; i++) {
        scanf("%s", paises[i]); //lê os países escolhidos
    }

    for(int p = 0; p < 5; p++) {//esse for percorre os países escolhidos para consultar as edições com mais medalhas, armazenando cada dado ao seu país
        Edicao edicoes[200];
        int totalEdicoes = 0;
        char linha[1024];

        rewind(arquivo); //volta para o início do arquivo toda vez que chegar no final. Essencial porque precisamos ler o arquivo 5 vezes, uma pra cada país.
        fgets(linha, sizeof(linha), arquivo); 

        while(fgets(linha, sizeof(linha), arquivo)) {
            linha[strcspn(linha, "\r\n")] = 0;//remove o \n do final da linha, caso exista
            
            char copiaLinha[1024];
            strcpy(copiaLinha, linha);

            char *token = strtok(copiaLinha, ",");//token para "acabar" com as vírgulas do arquivo
            int coluna = 0;
            char anoLido[50] = "";
            char paisLido[50] = "";
            char medalhaLida[50] = "";

            while (token != NULL) {//percorre cada coluna para armazenar o ano, país e medalha
                if(coluna == 0) { 
                    strcpy(anoLido, token);
                }

                if(coluna == 4) { 
                    strcpy(medalhaLida, token); 
                }

                if(coluna == 7) { 
                    strcpy(paisLido, token);
                }    
                
                token = strtok(NULL, ",");
                coluna++;
            }

            if (strcmp(paises[p], paisLido) == 0 && strcmp(medalhaLida, "NA") != 0 && strlen(medalhaLida) > 1) {//verifica se o país da linha é igual ao país que o usuário deseja consultar e se a medalha não é "NA" 
                int indiceEdicao = encontraEdicao(edicoes, totalEdicoes, anoLido);

                if(indiceEdicao == -1) {
                    strcpy(edicoes[totalEdicoes].ano, anoLido); 
                    edicoes[totalEdicoes].totalMedalhas = 1;
                    totalEdicoes++;
                } else {
                    edicoes[indiceEdicao].totalMedalhas++;
                }
            }
        } // fim do While

        for(int i = 0; i < totalEdicoes; i++) {// bubble sort para ordenar as edições pela quantidade de medalhas
            for(int j = 0; j < totalEdicoes - i - 1; j++) {
                if(edicoes[j].totalMedalhas < edicoes[j + 1].totalMedalhas) {
                    Edicao temporaria = edicoes[j];
                    edicoes[j] = edicoes[j + 1];
                    edicoes[j + 1] = temporaria;
                }
            }
        }

        printf("\n TOP 5: %s\n", paises[p]);
        if(totalEdicoes == 0) {
            printf("Nenhum dado encontrado para este pais.\n");//caso o país não tenha conquistado nenhuma medalha
        } else {
            for(int i = 0; i < 5 && i < totalEdicoes; i++) {
                printf("%d lugar: %s - %d medalhas em %s\n", i + 1, paises[p], edicoes[i].totalMedalhas, edicoes[i].ano);
            }
        }
    } //fim do for de países

    fclose(arquivo);
    return 0;
}