#include "historicoEmprestimo.h"
#include "../src/tabela.h"
#include <time.h> // Biblioteca auxiliar para calcular multa
#include <stdio.h>
#include <stdlib.h>

void registrarHistorico(HistoricoEmprestimo* historico) {
    FILE* f = fopen("../dados/historico_emprestimos.dat", "ab");
    if (f==NULL){
        printf("Erro ao abrir o arquivo de histórico!\n");
        return;
    }
    fwrite(historico, sizeof(HistoricoEmprestimo), 1, f);
    fclose(f);
}

void mostrarHistorico() {
    FILE* f = fopen("../dados/historico_emprestimos.dat", "rb");
    if (!f) {
        printf("Erro ao abrir o arquivo de histórico!\n");
        return;
    }

    HistoricoEmprestimo historico;
    while (fread(&historico, sizeof(HistoricoEmprestimo), 1, f)) {
        printf("Usuário ID: %d, ISBN: %s, Empréstimo: %s, Devolução: %s, Multa: %.2f\n",
               historico.idUsuario, historico.isbn, historico.dataEmprestimo,
               historico.dataDevolucao, historico.multa);
    }

    fclose(f);
}

void registrarDevolucao(int idUsuario, char* isbn, char* dataEmprestimo, int diasAtraso) {
    HistoricoEmprestimo historico;

    historico.idUsuario = idUsuario;
    strcpy(historico.isbn, isbn);
    strcpy(historico.dataEmprestimo, dataEmprestimo);

    obterDataAtual(historico.dataDevolucao, sizeof(historico.dataDevolucao));
    historico.multa = calcularMulta(diasAtraso);

    registrarHistorico(&historico);

    printf("Devolução registrada com sucesso!\n");
    printf("Data: %s | Multa: R$ %.2f\n", historico.dataDevolucao, historico.multa);
}

void atualizarCopiasLivro(const char* isbn, int delta) {
    FILE* f = fopen("dados/livros.dat", "r+b"); // leitura + escrita binária
    if (!f) {
        printf("Erro ao abrir livros.dat para atualização.\n");
        return;
    }

    Livro livro;
    while (fread(&livro, sizeof(Livro), 1, f)) {
        if (strcmp(livro.isbn, isbn) == 0) {
            livro.copias += delta;

            // Retorna o cursor para a posição correta antes de reescrever
            fseek(f, -sizeof(Livro), SEEK_CUR);
            fwrite(&livro, sizeof(Livro), 1, f);
            fclose(f);
            printf("Número de cópias do livro ISBN %s atualizado para %d.\n", isbn, livro.copias);
            return;
        }
    }

    fclose(f);
    printf("Livro com ISBN %s não encontrado para atualização.\n", isbn);
}

void obterDataAtual(char* buffer, int tamanho) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(buffer, tamanho, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

// cálculo da multa (R$2 por dia de atraso)
float calcularMulta(int diasAtraso) {
    float valorPorDia = 2.00;
    if (diasAtraso > 0) {
        return diasAtraso * valorPorDia;
    } 
    else {
        return 0.0;
    }
}

// Função principal para registrar a devolução no histórico
void registrarDevolucao(int idUsuario, char* isbn, char* dataEmprestimo, int diasAtraso) {
    HistoricoEmprestimo historico;

    historico.idUsuario = idUsuario;
    strcpy(historico.isbn, isbn);
    strcpy(historico.dataEmprestimo, dataEmprestimo);

    obterDataAtual(historico.dataDevolucao, sizeof(historico.dataDevolucao));
    historico.multa = calcularMulta(diasAtraso);

    registrarHistorico(&historico);

    printf("Devolução registrada com sucesso!\n");
    printf("Data: %s | Multa: R$ %.2f\n", historico.dataDevolucao, historico.multa);
}