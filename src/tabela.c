#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela.h"

//Iniciar tabela apontar para NULL
void iniciarTabelas() {
    for (int i = 0; i < MAX_TAM; i++) {
        tabelaLivros[i] = NULL;
        tabelaUsuarios[i] = NULL;
    }
}
//Funções Hash básica para modularizar o isbn e atribuir a chave(isbn,id) ao indice da tabela
//"const" para declarar char como constante, ou seja, para seu valor original não ser alterado
int hashLivro(const char* isbn) {
    int soma = 0;
    for (int i = 0; isbn[i] != '\0'; i++) {
        soma += isbn[i];
    }
    return soma % MAX_TAM;
}

int hashUsuario(int id) {
    return id % MAX_TAM;
}

Livro* criarLivro(const char* isbn, const char* titulo, const char* autor, int ano, int copias){
    Livro* novo = (Livro*)malloc(sizeof(Livro));
    //Definir isbn
    int i = 0;
    while (isbn[i] != '\0' && i < MAX_STR - 1) {
        novo->isbn[i] = isbn[i];
        i++;
    }
    novo->isbn[i] = '\0';

    //Definir título
    i = 0;
    while (titulo[i] != '\0' && i < MAX_STR - 1) {
        novo->titulo[i] = titulo[i];
        i++;
    }
    novo->titulo[i] = '\0';

    //Definir autor
    i = 0;
    while (autor[i] != '\0' && i < MAX_STR - 1) {
        novo->autor[i] = autor[i];
        i++;
    }
    novo->autor[i] = '\0';

    novo -> ano = ano;
    novo -> copias = copias;
    novo -> prox = NULL;
    return novo;
}


Usuario* criarUsuario(int id, const char* nome, const char* email){
    Usuario* novo = (Usuario*)malloc(sizeof(Usuario));
    novo -> id = id;
    int i = 0;
    while(nome[i] != '\0' && i < MAX_STR - 1){
        novo ->nome[i] = nome[i];
        i++;
    }
    novo -> nome[i] = '\0';
    int i = 0;
    while(email[i] != '\0' && i < MAX_STR - 1){
        novo ->email[i] = email[i];
        i++;
    }
    novo -> email[i] = '\0';
    novo -> prox = NULL;
    return novo; 
}

//Funções para inserir Livro e Usuário na tabela, solucionando colisões

void inserirLivro(Livro* livro){
    int i = hashLivro(livro->isbn); // Posição na tabela
    livro -> prox = tabelaLivros[i]; // O novo livro aponta para o primeiro da lista
    tabelaLivros[i] = livro; // Insere o livro na frente da lista
}

void inserirUsuario(Usuario* usuario){
    int i = hashUsuario(usuario -> id);
    usuario -> prox = tabelaUsuarios[i];
    tabelaUsuarios[i] = usuario;
}