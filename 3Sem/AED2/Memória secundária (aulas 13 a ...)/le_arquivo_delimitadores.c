#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE  128
#define MAX_FIELD 64

/* aloca um string e retorna seu endereço */
char* readLine(FILE* fp) {

    char* line = (char*) malloc(sizeof(char) * MAX_LINE);
    if (line == NULL) {
        fprintf(stderr, "Erro de alocação de memória na função readLine\n");
        exit(1);
    }

    int length = MAX_LINE;
    int count = 0;
    char ch = fgetc (fp);
    while ((ch != '\n') && (ch != EOF)) { /* aqui entra a informação do delimitador de registro */ 
        /* se meu string line já estiver cheio, realoca-o para um maior */      
        if (count == length) {
            length += MAX_LINE;
            line = realloc(line, length);
            if (line == NULL) {
                fprintf(stderr, "Erro de alocação de memória na função readLine\n");
                exit(1);
            }
        }
        line[count] = ch;
        count++;
        ch = fgetc(fp);
    }
    if (ch == EOF) return NULL;
    line[count] = '\0';
    return line;
}

/* lê o primeiro substring de buffer que começa na posição i 
   e termina antes do delimitador delim ou '\0' (fim de buffer);
   aloca um string e retorna seu endereço */
char* readField(char* buffer, int* i, char delim) {
 
    char* field = (char*) malloc(sizeof(char) * MAX_FIELD);
    if (field == NULL) {
        fprintf(stderr, "Erro de alocação de memória na função readField\n");
        exit(1);
    }

    int length = MAX_FIELD;
    int count = 0;

    /* se já acabou o registro retorna NULL*/
    if (buffer[*i] == '\0') return NULL;    

    /* senão lê até o delimitador de campo ou fim do buffer */
    while ((buffer[*i] != delim) && (buffer[*i] != '\0')) { /* aqui entra a informação do delimitador de field !!! */
        if (count == length) {
            length += MAX_FIELD;
            field = realloc(field, length);
            if (field == NULL) {
                fprintf(stderr, "Erro de alocação de memória na função readField\n");
                exit(1);
            }
        }
        field[count] = buffer[*i];
        count++;
        (*i)++;
    }
    field[count] = '\0';
    return field;

}

/* Assume-se que o arquivo tem um registro por linha, ou seja, delimitador de registros = '\n' */
int main (void)
{
    char filename[] = "planilha_alunos.csv";
    FILE* fp = fopen(filename, "r"); /* abre arquivo em modo somente leitura */ 
    if (fp == NULL){
        fprintf(stderr, "Não foi possível abrir o arquivo %s", filename);
        return -1;
    }  

    char* registro;
    char* campo;
    int pos; /* posição no registro na qual deve começar o próximo campo */

    registro = readLine(fp); 
    free(registro); /* descarta linha de cabeçalho */
    while (registro = readLine(fp)){
        /*  lê campos do registro */

        /* primeiro lê NrUSP -  primeiro substring de registro */
        pos = 0;
        campo = readField(registro, &pos, ',');
        printf("NrUSP: %s\n", campo);
        free(campo);

        /* lê Curso */
        pos++; /* na leitura anterior terminou no delimitador */
        campo = readField(registro, &pos, ',');
        printf("Curso: %s\n", campo);
        free(campo);

        /**************   COMPLETAR !!!!  ************/

        free(registro); /* alocado dentro de readLine */
    }

    fclose(fp);
}

