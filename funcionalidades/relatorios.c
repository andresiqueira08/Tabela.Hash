#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/arquivo.h"
#include "../src/tabela.h"
#include "historicoEmprestimo.h"

int contarLivros(Livro livros[]) {
    FILE* f = fopen("C:\\Users\\LORENA\\estrutura.de.dados\\tabelaHash\\dados\\livros.dat", "rb");
    if (!f) return 0; // Arquivo não existe, retorna 0

    int total = 0;
    while (fread(&livros[total], sizeof(Livro), 1, f)) {
        if (livros[total].ativo) { // Conta apenas livros ativos
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
    int trocou = 0;
    for (int j = 0; j < total - i - 1; j++) {
        if (livros[j].emprestimos < livros[j + 1].emprestimos) {
            Livro temp = livros[j];
            livros[j] = livros[j + 1];
            livros[j + 1] = temp;
            trocou = 1;
        }
    }
    if (!trocou) break; // Se não houve troca, já está ordenado
}

    for (int i = 0; i < total && i < 5; i++) {
        printf("%s - %s (%d empréstimos)\n", livros[i].isbn, livros[i].titulo, livros[i].emprestimos);
    }
}
int contarUsuarios(Usuario usuarios[]) {
    FILE* f = fopen("C:\\Users\\LORENA\\estrutura.de.dados\\tabelaHash\\dados\\usuarios.dat", "rb");
    if (!f) return 0; 

    int total = 0;
    while (fread(&usuarios[total], sizeof(Usuario), 1, f)) {
        if (usuarios[total].ativo) { 
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
        if(strlen(usuarios[i].nome) > 0 && usuarios[i].id > 0){
        printf("ID %d - %s\n", usuarios[i].id, usuarios[i].nome);
    }
}
}
void exibirHistoricoEmprestimos() {
    printf("\n--- Histórico de Empréstimos ---\n");

    FILE *log = fopen("C:\\Users\\LORENA\\estrutura.de.dados\\tabelaHash\\dados\\emprestimos.dat", "r");
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