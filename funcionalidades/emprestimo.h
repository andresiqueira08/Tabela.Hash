#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H
#include "../src/tabela.h"
#define MAX_DATA 11 // "DD/MM/AAAA"

typedef struct Emprestimo {
    char isbn[20];
    int id;
    char data[MAX_DATA]; // Ex: "13/05/2025"
    int devolvido;     // 0 = não devolvido, 1 = devolvido
    float multa;
} Emprestimo;


void atualizarLivroNoArquivo(const char* isbn, Livro* livroAtualizado);
void realizarEmprestimo(const char* isbn, int idUsuario, const char* data);
void registrarLogEmprestimo(Usuario *usuario, Livro *livro);

#endif

