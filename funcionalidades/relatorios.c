#include <stdio.h>
#include <stdlib.h>
#include "../src/arquivo.h"
#include "../src/tabela.h"
#include "historicoEmprestimo.h"
int contarLivros() {
    FILE* f = fopen("C:\\Users\\LORENA\\estrutura.de.dados\\tabelaHash\\dados\\livros.dat", "rb");
    if (!f) return 0; // Se o arquivo não existir, retorna 0

    int total = 0;
    Livro livro;
    while (fread(&livro, sizeof(Livro), 1, f)) {
        if (livro.ativo) { // Conta apenas livros ativos
            total++;
        }
    }
    fclose(f);
    return total;
}
void livrosMaisEmprestados() {
    printf("\n--- Livros mais emprestados ---\n");

    Livro livros[MAX_TAM];
    int total = contarLivros(livros); // Implementar essa função para ler todos os livros do arquivo

    // Ordenar (bubble sort)
    for (int i = 0; i < total - 1; i++) {
        for (int j = i + 1; j < total; j++) {
            if (livros[j].emprestimos > livros[i].emprestimos) {
                Livro temp = livros[i];
                livros[i] = livros[j];
                livros[j] = temp;
            }
        }
    }

    for (int i = 0; i < total && i < 5; i++) {
        printf("%s - %s (%d empréstimos)\n", livros[i].isbn, livros[i].titulo, livros[i].emprestimos);
    }
}
int contarUsuarios() {
    FILE* f = fopen("C:\\Users\\LORENA\\estrutura.de.dados\\tabelaHash\\dados\\usuarios.dat", "rb");
    if (!f) return 0; // Se o arquivo não existir, retorna 0

    int total = 0;
    Usuario usuario;
    while (fread(&usuario, sizeof(Usuario), 1, f)) {
        if (usuario.ativo) { // Conta apenas usuários ativos
            total++;
        }
    }
    fclose(f);
    return total;
}

void usuariosMaisAtivos() {
    printf("\n--- Usuários mais ativos ---\n");

    Usuario usuarios[MAX_TAM];
    int total = contarUsuarios(usuarios); 

    // Ordenar
    for (int i = 0; i < total - 1; i++) {
        for (int j = i + 1; j < total; j++) {
            if (usuarios[j].emprestimos > usuarios[i].emprestimos) {
                Usuario temp = usuarios[i];
                usuarios[i] = usuarios[j];
                usuarios[j] = temp;
            }
        }
    }

    for (int i = 0; i < total && i < 5; i++) {
        printf("ID %d - %s (%d empréstimos)\n", usuarios[i].id, usuarios[i].nome, usuarios[i].emprestimos);
    }
}

void exibirHistoricoEmprestimos() {
    printf("\n--- Histórico de empréstimos ---\n");
    FILE *log = fopen("dados/emprestimos.log", "r");
    if (!log) {
        printf("Nenhum empréstimo registrado.\n");
        return;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), log)) {
        printf("%s", linha);
    }
    fclose(log);
}
