#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    char buscaNOC[10]; // Cria uma array de caracteres que será usada para a busca do NOC do país

    printf("Digite o NOC (ex: BRA, USA): "); // Pergunta ao usuário qual o NOC do país que será usado

    scanf("%s", buscaNOC); // Usuário digitará o NOC do país 

    float MulherPorHomem = 0; // Variável que armazena a razão das Atletas femininas pelos Atletas masculinos (Mulheres / Homem)

    for(int i = 0; buscaNOC[i]; i++) buscaNOC[i] = toupper(buscaNOC[i]); 
    // Loop feito para percorrer as palvras atrás de uma letra minúscula, que é transformada em maiúscula ( toupper )

    FILE *arquivo = fopen("results.csv", "r"); // Aqui cria um ponteiro do arquivo e usa o fopen para abrir o arquivo results.csv no modo leitura "r"
    if (!arquivo) { // Cria uma condicão caso o arquivo não seja aberto
        printf("Erro: Arquivo results.csv nao encontrado!\n"); // Sistema imprime essa mensagem de erro caso não seja aberto
        return 1;
    }

    char linha[2048]; // Usado para armazenar cada linha do arquivo, usando 2048 como limite 

    int homem = 0, mulher = 0; // contadores de medalhistas homens e mulheres 

    fgets(linha, sizeof(linha), arquivo);// pula a primeira linha do arquivo, preenchendo a varíavel linha com o cabeçalho, por isso está sendo usado uma única vez, será sobescrito no while

    while (fgets(linha, sizeof(linha), arquivo)) { // percorrerá o arquivo linha por linha até o final dele 
        int ano = atoi(linha); // conversão de texto para um inteiro usando o atoi
        
        if (ano >= 2008) { // condição para procurar só as olimpíadas mais recentes  
            
            if (strstr(linha, buscaNOC) != NULL) { // verifica se a linha que esta sendo percorrida contem o NOC, que o usuário digitou mais cedo por meio do String in String
                // se o programa procurar e achar nada, ele vai pra a próxima linha
               
                if (strstr(linha, "Gold") || strstr(linha, "Silver") || strstr(linha, "Bronze")) { // caso o NOC seja achado, cria uma condição para só atletas medalhistas, mesma lógica usado na busca pelo NOC, só que agora ele checa se o atleta conseguiu alguma medalha como a de bronze, prata ou ouro

                    if (strstr(linha, "Women") != NULL) { // Caso seja medalhista, cria uma condição para quem for mulher, que quando achada acrescentará uma unidade ao contador 

                        mulher++; // contador de mulher aumenta uma unidade quando achada Women na linha  

                    } else if (strstr(linha, "Men") != NULL) { // Caso seja medalhista, cria uma condição para quem for homem, que quando achada acrescentará uma unidade ao contador 

                        homem++; // contador de homem aumenta uma unidade quando achado Men na linha 
                    }
                }
            }
        }
    } // Fim do while

   if (homem > 0) { // condição para quando achar homem
   MulherPorHomem = (float)mulher / homem; // Deixando a variável MulherPorHomem como uma operação matemática, float para transformar o cálculo dos int em float 
    }

    printf("Homens e Mulheres Medalhistas de %s nas olimpíadas mais recentes", buscaNOC); // imprime a mensagem de onde vem os atletas 
    printf("Homens medalhistas: %d\n", homem); // mostra o total de homens medalhistas 
    printf("Mulheres medalhistas: %d\n", mulher); // mostra o toal de mulheres medalhistas 
    
    // mostra a conta de Mulher por Homem, usamos %.2lf para imprimir float com 2 casas decimais
    printf("Razao mulher por homem: %.2lf\n", MulherPorHomem);

    fclose(arquivo);
    return 0;
}
