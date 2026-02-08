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

    int h = 0, m = 0; // contadores de medalhistas homens e mulheres 

    // Pula a primeira linha de títulos do arquivo
    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo)) { // percorre o arquivo linha por linha 
        int ano = atoi(linha); // ano para inteiro
        
        if (ano >= 2008) { // so dos olimpiadas mais recentes 
            
            if (strstr(linha, buscaNOC) != NULL) { // procura se o NOC do país está na linha 
               
                if (strstr(linha, "Gold") || strstr(linha, "Silver") || strstr(linha, "Bronze")) { // verifica se tem medalha 

                    if (strstr(linha, "Women") != NULL) { // se for mulher ele conta 

                        m++; // contador de mulher 

                    } else if (strstr(linha, "Men") != NULL) { // se for homem 

                        h++; // contador de homem
                    }
                }
            }
        }
    } // Fim do while

    // Calcula a razão (sem usar ++ para não alterar os contadores)
    if (h > 0) {
        MulherPorHomem = (float)m / h;
    }

    printf("\n--- RESULTADO PARA %s ---\n", buscaNOC);
    printf("Homens medalhistas: %d\n", h);
    printf("Mulheres medalhistas: %d\n", m);
    
    // Usamos %.2f para imprimir float com 2 casas decimais
    printf("Razao mulher por homem: %.2f\n", MulherPorHomem);

    fclose(arquivo);
    return 0;
}
