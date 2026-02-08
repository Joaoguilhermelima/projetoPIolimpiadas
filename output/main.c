#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() 
{
    FILE *f = fopen("results.csv", "r");
    
    if (!f) {
        printf("Erro ao abrir arquivo\n");
        return 1;
    }

    char linha[1024];
    fgets(linha, sizeof(linha), f); // Ignora cabeçalho

    while (fgets(linha, sizeof(linha), f)) { //Lê as linhas do arquivo
        char *token = strtok(linha, ",");
        int coluna = 0;

        char sexo[15];
        char evento[100] = "";
        char noc[4] = "";
        int ano = 0;
        char medalha[20] = "";

        while (token != NULL) {

            if (coluna == 0) { // Armazenar o ano
                ano = atoi(token);
            }

            if (coluna == 3) { // Armazenar o evento para colocar o sexo depois
                strcpy(evento, token);
            }

            if (coluna == 7) { // Armazenar o NOC
                strcpy(noc, token);
            }

            if (coluna == 10) { // Armazenar a medalha
                strcpy(medalha, token);
            }

            token = strtok(NULL, ",");
            coluna++;
        }

        if (strstr(evento, "Women") != NULL)
            strcpy(sexo, "F");
        else if (strstr(evento, "Men") != NULL)
            strcpy(sexo, "M");
        else
            strcpy(sexo, "NA");

        printf("%d, %s, %s, %s\n", ano, sexo, noc, medalha);
    }

    fclose(f);
    return 0;
}