#include <stdio.h>
#include <stdlib.h>
#include "tabela.h"
#include "arquivo.h"

void salvarLivro(Livro* livro) {
    FILE* f = fopen("usuarios.dat", "ab"); // a = adicionar, b = binário
    if (f == NULL) {
        printf("Erro ao abrir usuarios.dat\n");
        return;
    }

    fwrite(livro, sizeof(livro), 1, f);
    fclose(f);
}

void salvarUsuario(Usuario* usuario) {
    FILE* f = fopen("usuarios.dat", "ab"); 
    if (f == NULL) {
        printf("Erro ao abrir usuarios.dat\n");
        return;
    }

    fwrite(usuario, sizeof(Usuario), 1, f);
    fclose(f);
}
// Funções para carregar os dados do arquivo binário de volta para a tabela hash quando o programa inicia.
void carregarLivros() {
    FILE* f = fopen("livros.dat", "rb"); // r = leitura
    if (f == NULL) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }

    Livro livro;
    while (fread(&livro, sizeof(Livro), 1, f)) {
        Livro* novoLivro = criarLivro(livro.isbn, livro.titulo, livro.autor, livro.ano, livro.copias);
        inserirLivro(novoLivro);
    }
    fclose(f);
}

void carregarUsuarios() {
    FILE* f = fopen("usuarios.dat", "rb"); 
    if (f == NULL) {
        printf("Nenhum usuário cadastrado.\n");
        return;
    }

    Usuario usuario;
    while (fread(&usuario, sizeof(Usuario), 1, f)) {
        Usuario* novoUsuario = criarUsuario(usuario.id, usuario.nome, usuario.email);
        inserirUsuario(novoUsuario);
    }
    fclose(f);
}