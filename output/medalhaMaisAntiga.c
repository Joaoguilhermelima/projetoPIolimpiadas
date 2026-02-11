#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    char buscaNOC[10]; // armazena o país digitado pelo usuário em um array
    printf("Digite o NOC (ex: BRA, USA): "); // pergunta o NOC do país 
    scanf("%s", buscaNOC); // usuário digita o NOC do país

    for(int i = 0; buscaNOC[i]; i++) {
        buscaNOC[i] = toupper(buscaNOC[i]); // converte o texto digitado para maiúsculas
    } 

    FILE *arquivo = fopen("results.csv", "r"); // abre o aqrquivo no modo leitura 
    if (!arquivo) {
        printf("Erro: Arquivo results.csv nao encontrado!\n");
        return 1;
    }

    char linha[2048];
    char linhaMaisAntiga[2048]; // guarda os dados da primeira medalha
    int menorAno = 9999; // valor inicial alto para ser substituído pelo primeiro ano que achar
    int encontrou = 0; // flag para indicar se encontrou alguma medalha do país

    // Pula a primeira linha de títulos do arquivo
    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo)) { // percorre o arquivo linha por linha 
        int anoAtual = atoi(linha); // transforma o ano em inteiro

        if (strstr(linha, buscaNOC) != NULL) { // procura se o NOC do país está na linha 
            // verifica se tem medalha 
            if (strstr(linha, "Gold") || strstr(linha, "Silver") || strstr(linha, "Bronze")) { 
                
                // Se o ano desta linha for menor que o menor ano guardado até agora
                if (anoAtual < menorAno && anoAtual > 0) {
                    menorAno = anoAtual; // atualiza o menor ano
                    strcpy(linhaMaisAntiga, linha); // copia a linha para a variável de destaque
                    encontrou = 1;
                }
            }
        }
    } // Fim do while

    if (encontrou) {
        printf("Dados: %s", linhaMaisAntiga);
    } else {
        printf("\nNenhuma medalha encontrada para %s.\n", buscaNOC);
    }

    fclose(arquivo);
    return 0;
}