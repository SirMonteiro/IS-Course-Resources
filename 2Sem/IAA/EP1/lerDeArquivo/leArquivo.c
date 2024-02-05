#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILENAME 256 /* tamanho máximo de um nome de arquivo*/

int main(int argc, char *argv[])
{
    /* argc é o número de argumentos (na verdade palavras) passados na linha de comando na chamada do programa */
    /* incluindo a chamada do programa */
    if (argc != 3)
    {
        printf("Este programa exige dois argumentos: TAL e TAL\n"); /* COMPLETAR */
        exit(1);
    }

    printf("%s ", argv[0]);
    printf("%s ", argv[1]);
    printf("%s\n", argv[2]);

    /* argv[0] tem a chamada do programa */
    /* argv[i] tem os argumentos passados (para i > 0) armazenados na forma de string */
    /* se precisar convertê-los para outro tipo de dado, por ex int, precisa fazer a conversão para esse tipo de dado */
    /* ex: usando a função atoi - note para isso vai precisar de outros include's ... */
    /* COMPLETAR */

    /* se o segundo argumento  for o nome de um arquivo, e você precisa abri-lo: */
    char filename[MAX_FILENAME] = "";
    strcpy(filename, argv[2]);       /* copia conteúdo de argv[2] para filename */
    FILE *fp = fopen(filename, "r"); /* abre arquivo em modo somente leitura */
    if (fp == NULL)
    {
        fprintf(stderr, "Não foi possível abrir o arquivo %s\n", filename);
        return -1;
    }
    /* lendo algo do arquivo, por ex um inteiro, seguido de um char */
    int inteiroLido;
    fscanf(fp, "%d", &inteiroLido);
    /* conferindo se li certo */
    printf("%d\n", inteiroLido);

    /* se você for ler char's, para o compilador um char pode ser espaço em branco, newline, etc */
    char char1, char2, char3;
    fscanf(fp, "%c", &char1);
    fscanf(fp, "%c", &char2);
    fscanf(fp, "%c", &char3);
    /* conferindo se li certo */
    printf("char1=%c; char2=%c; char3=%c;\n", char1, char2, char3);
    /* também dá para ler char's usando getchar() - pesquisem!!! */

    /* dá para ler outros tipos de dados também: floats, bools, etc */
}