#include <stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct { //Obter dados dos atletas
    int ano;
    char sexo[2];
    char noc[4];
    char medalha[10];
} Atleta;

int guardarDados(FILE *arquivo, Atleta *atletas) { //Função para guardar os dados dos atletas. Fica mais fácil de usar
    char linha[1024];
    
    if (fgets(linha, sizeof(linha), arquivo) == NULL) {
        return 0;
    }

        char *token = strtok(linha, ",");
        int coluna = 0;
        char evento[100] = "";

        while (token != NULL) {
             if (coluna == 0) {
                atletas->ano = atoi(token); // Armazenar ano. O atoi transforma string em inteiro
            }
            
            if (coluna == 4) { // Armazenar sexo
                strcpy(evento, token);
            } 
            
            if (coluna == 7) {
                strcpy(atletas->noc, token); // Armazenar NOC
            }

            if (coluna == 10) {
                strcpy(atletas->medalha, token); //Armazenar medalha
            }

            token = strtok(NULL, ",");
            coluna++;
        }

        if (strstr(evento, "Women") != NULL) {
            strcpy(atletas->sexo, "F");
        } else if (strstr(evento, "Men") != NULL) {
            strcpy(atletas->sexo, "M");
        } else {
            strcpy(atletas->sexo, "NA");
        }  
    return 1;
}

int main() 
{
    FILE *arquivo = fopen("results.csv", "r");

    if (!arquivo) {
        printf("Erro ao abrir arquivo\n");
        return 1;
    }

    char linha[1024];
    fgets(linha, sizeof(linha), arquivo);
    Atleta atletas;

    while(guardarDados(arquivo, &atletas)) {
        printf("%d %s %s %s\n", atletas.ano, atletas.sexo, atletas.noc, atletas.medalha);
    }

    fclose(arquivo);
    return 0;
}