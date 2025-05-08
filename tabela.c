#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela.h"
#define MAX_TAM 100
#define MAX_STR 100
 
void inicializarTabelas() {
    for (int i = 0; i < MAX_TAM; i++) {
        tabelaLivros[i] = NULL;
        tabelaUsuarios[i] = NULL;
    }
}
int hash(char* isbn) {
    int soma = 0;
    for (int i = 0; isbn[i] != '\0'; i++) {
        soma += isbn[i];
    }
    return soma % MAX_TAM;
}

Livro* criarLivro(char* isbn, char* titulo, char* autor, int ano, int copias){
    Livro* novo = (Livro*)malloc(sizeof(Livro));
    strcpy(novo->isbn, isbn);
    strcpy(novo-> titulo, titulo);
    strcpy(novo->autor, autor);
    novo -> ano = ano;
    novo -> copias = copias;
    novo -> prox = NULL;
    return novo;
}