#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emprestimo.h"
#include "consulta.h"
#include <time.h>

void atualizarLivroNoArquivo(const char* isbn, Livro* livroAtualizado) {
    FILE* f = fopen("C:\\Users\\LORENA\\estrutura.de.dados\\tabelaHash\\dados\\livros.dat", "r+b");
    if (f == NULL) {
        printf("Erro ao abrir arquivo de livros para atualização.\n");
        return;
    }

    Livro livro;
    while (fread(&livro, sizeof(Livro), 1, f)) {
        if (strcmp(livro.isbn, isbn) == 0) {
            // Retorna para posição correta antes de reescrever
            fseek(f, -sizeof(Livro), SEEK_CUR);
            fwrite(livroAtualizado, sizeof(Livro), 1, f);
            printf("Livro atualizado no arquivo! ISBN: %s\n", isbn);
            break;
        }
    }

    fclose(f);
}


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
    livro -> emprestimos++;
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

    FILE* f = fopen("C:\\Users\\LORENA\\estrutura.de.dados\\tabelaHash\\dados\\emprestimos.dat", "ab");
    if (f == NULL) {
        printf("Erro ao abrir arquivo de empréstimos.\n");
        return;
    }
    fwrite(&emp, sizeof(Emprestimo), 1, f);
    fclose(f);
    atualizarLivroNoArquivo(isbn,livro);

    printf("Empréstimo realizado!\n");

}

void registrarLogEmprestimo(Usuario *usuario, Livro *livro) {
    FILE *log = fopen("dados/emprestimos.log", "a");
    if (!log) {
        printf("Erro ao abrir o log de empréstimos.\n");
        return;
    }

    time_t agora = time(NULL);
    struct tm *t = localtime(&agora);

    fprintf(log, "[%02d/%02d/%d %02d:%02d] ID: %d - Nome: %s - ISBN: %s - Título: %s\n",
        t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
        t->tm_hour, t->tm_min,
        usuario->id, usuario->nome,
        livro->isbn, livro->titulo);

    fclose(log);
}
