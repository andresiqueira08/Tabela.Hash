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
    for (int x = 0; isbn[x] != '\0'; x++) {
        soma += isbn[x];
    }
    return soma % MAX_TAM;
}

int hashUsuario(int id) {
    return id % MAX_TAM;
}

Livro* criarLivro(const char* isbn, const char* titulo, const char* autor, int ano, int copias){
    Livro* novo = (Livro*)malloc(sizeof(Livro));
    //Definir isbn
    int y = 0;
    while (isbn[y] != '\0' && y < MAX_STR - 1) {
        novo->isbn[y] = isbn[y];
        y++;
    }
    novo->isbn[y] = '\0';

    //Definir título
    int z = 0;
    while (titulo[z] != '\0' && z < MAX_STR - 1) {
        novo->titulo[z] = titulo[z];
        z++;
    }
    novo->titulo[z] = '\0';

    //Definir autor
    int j = 0;
    while (autor[j] != '\0' && j < MAX_STR - 1) {
        novo->autor[j] = autor[j];
        j++;
    }
    novo->autor[j] = '\0';

    novo -> ano = ano;
    novo -> copias = copias;
    novo -> prox = NULL;
    return novo;
}


Usuario* criarUsuario(int id, const char* nome, const char* email){
    Usuario* novo = (Usuario*)malloc(sizeof(Usuario));
    novo -> id = id;
    int index = 0;
    while(nome[index] != '\0' && index < MAX_STR - 1){
        novo ->nome[index] = nome[index];
        index++;
    }
    novo -> nome[index] = '\0';

    int a = 0;
    while(email[a] != '\0' && a < MAX_STR - 1){
        novo ->email[a] = email[a];
        a++;
    }
    novo -> email[a] = '\0';
    novo -> prox = NULL;
    return novo; 
}

//Funções para inserir Livro e Usuário na tabela, solucionando colisões

void inserirLivro(Livro* livro){
    int p = hashLivro(livro->isbn); // Posição na tabela
    livro -> prox = tabelaLivros[p]; // O novo livro aponta para o primeiro da lista
    tabelaLivros[p] = livro; // Insere o livro na frente da lista
}

void inserirUsuario(Usuario* usuario){
    int i = hashUsuario(usuario -> id);
    usuario -> prox = tabelaUsuarios[i];
    tabelaUsuarios[i] = usuario;
}