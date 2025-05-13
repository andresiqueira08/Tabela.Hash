#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emprestimo.h"

void realizarEmprestimo(const char* isbn, int id, const char* data){
    Livro* livro = buscarLivroPorISBN(isbn);
    Usuario* usuario = buscarUsuarioPorID(id);

    if (livro == NULL) {
        printf("Livro com ISBN %s não encontrado.\n", isbn);
        return;
    }
    if (usuario == NULL) {
        printf("Usuário com ID %d não encontrado.\n", id);
        return;
    }
    if(livro->copias <= 0){
        printf("Este livro não possui cópias suficientes para ser emprestado.\n");
        return;
    }

    livro->copias--; //Diminuir número de cópias ao emprestar livro

    // Criar o emprestimo
    Emprestimo emp;
    //Copiar dados isbn, id, data e devolvido para a struct de emprestimo
    //loop para ler todos o carcteres da array de caracteres(String)
    int i = 0;
    while (isbn[i] != '\0' && i < 19) {
        emp.isbn[i] = isbn[i]; i++;//copiar o valor de isbn para o campo isbn da estrutura Emprestimo (emp.isbn).
     }
    emp.isbn[i] = '\0';
    emp.id = id;

    i = 0;
    while (data[i] != '\0' && i < 10) {
        emp.data[i] = data[i]; i++;
    }
    emp.data[i] = '\0';

    emp.devolvido = 0;

    FILE* f = fopen("dados/emprestimos.dat", "ab");
    if (f == NULL) {
        printf("Erro ao abrir arquivo de empréstimos.\n");
        return;
    }
    fwrite(&emp, sizeof(Emprestimo), 1, f);
    fclose(f);

    printf("Empréstimo realizado!\n");

}
