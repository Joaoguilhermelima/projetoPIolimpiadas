#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() 
{
    FILE *f = fopen("results.csv", "r");
    char linha[1024];

    if (!f) {
        printf("Erro ao abrir arquivo\n");
        return 1;
    }

    fgets(linha, sizeof(linha), f); // Ignora o cabeçalho

    while (fgets(linha, sizeof(linha), f)) { // Lê cada linha do arquivo
        char *token = strtok(linha, ",");
        int coluna = 0;
        char sexo[10];
        char evento[100] = "";
        char noc[4];
        int ano;
        char medalha[10];

        while (token != NULL) {
             if (coluna == 0) {
                ano = atoi(token); // Armazenar ano. O atoi transforma string em inteiro
            }
            
            if (coluna == 4) { // Armazenar sexo
                strcpy(evento, token);
            } 
            
            if (coluna == 7) {
                strcpy(noc, token); // Armazenar NOC
            }

            if (coluna == 10) {
                strcpy(medalha, token); //Armazenar medalha
            }

            token = strtok(NULL, ",");
            coluna++;
        }

        if (strstr(evento, "Women") != NULL) {
                strcpy(sexo, "F");
                } else if (strstr(evento, "Men") != NULL) {
                strcpy(sexo, "M");
                } else {
                strcpy(sexo, "Desconhecido");
                }

        printf("%d, %s, %s, %s\n", ano, sexo, noc, medalha); // Imprime os dados extraídos

    }

    fclose(f);
    return 0;
}