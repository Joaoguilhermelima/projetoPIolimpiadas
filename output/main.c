#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    char buscaNOC[10]; // armazena o país digitado pelo usuário

    printf("Digite o NOC (ex: BRA, USA): "); // pergunta o NOC do país 

    scanf("%s", buscaNOC); // usuário digita o NOC do país

    float MulherPorHomem = 0; // divisão de mulheres por homens do NOC

    for(int i = 0; buscaNOC[i]; i++) buscaNOC[i] = toupper(buscaNOC[i]); // converte o texto digitado para maiúsculas 

    FILE *arquivo = fopen("results.csv", "r"); // abre o aqrquivo no modo leitura 
    if (!arquivo) {
        printf("Erro: Arquivo results.csv nao encontrado!\n");
        return 1;
    }

    char linha[2048];

    int homem = 0, mulher = 0; // contadores de medalhistas homens e mulheres 

    // pula a primeira linha de títulos do arquivo
    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo)) { // percorre o arquivo linha por linha 
        int ano = atoi(linha); // ano para inteiro
        
        if (ano >= 2008) { // so dos olimpiadas mais recentes 
            
            if (strstr(linha, buscaNOC) != NULL) { // procura se o NOC do país está na linha 
               
                if (strstr(linha, "Gold") || strstr(linha, "Silver") || strstr(linha, "Bronze")) { // verifica se tem medalha 

                    if (strstr(linha, "Women") != NULL) { // se for mulher ele conta 

                        mulher++; // contador de mulher 

                    } else if (strstr(linha, "Men") != NULL) { // se for homem 

                        homem++; // contador de homem
                    }
                }
            }
        }
    } // Fim do while

    // Calcula a razão (sem usar ++ para não alterar os contadores)
    if (homem > 0) {
        MulherPorHomem = (float)mulher / homem;
    }

    printf("\n--- RESULTADO PARA %s ---\n", buscaNOC);
    printf("Homens medalhistas: %d\n", homem);
    printf("Mulheres medalhistas: %d\n", mulher);
    
    // Usamos %.2lf para imprimir float com 2 casas decimais
    printf("Razao mulher por homem: %.2lf\n", MulherPorHomem);

    fclose(arquivo);
    return 0;
}
