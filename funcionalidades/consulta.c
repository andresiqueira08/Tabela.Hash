#include <stdio.h>
#include <stdlib.h>
#include "consulta.h"

//Função usada para auxiliar a busca na tabela Hash
int compararStrings(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            return 0; //As strings são diferentes
        }
        i++;
    }
    return a[i] == b[i]; 
}

Livro* buscarLivroPorISBN(const char* isbn){
    int chave = hashLivro((char*)isbn);
    Livro* buscando = tabelaLivros[chave];
    while(buscando != NULL){
        if(compararStrings(buscando->isbn, isbn)){
            return buscando; //Se os isbn do livro atual e do que estamos procurando fore, iguais, retorna-se ao ponteiro do livro
        }
        buscando = buscando ->prox;
    }
    return NULL;

}

//Necessário varrer toda tabela Hash, pois título não é uma chave
Livro* buscarLivroPorTitulo(const char* titulo){
    for(int i = 0; i < MAX_TAM; i ++){
        Livro* buscando = tabelaLivros[i];
        while(buscando != NULL){
            if(compararStrings(buscando->titulo, titulo)){
                return buscando;
            }
            buscando = buscando ->prox;
        }
    }
}
Usuario* buscarUsuarioPorID(int id){
    int chave = hashUsuario(id);
    Usuario* buscando = tabelaUsuarios[chave];
    while(buscando != NULL){
        if(buscando->id == id){
            return buscando;
        }
        buscando = buscando -> prox;
    }
    return NULL;
}

Usuario* buscarUsuarioPorNome(const char* nome) {
    for (int i = 0; i < MAX_TAM; i++) {
        Usuario* buscando = tabelaUsuarios[i];
        while (buscando != NULL) {
            if (compararStrings(buscando->nome, nome)) {
                return buscando;
            }
            buscando = buscando->prox;
        }
    }
    return NULL;
}

