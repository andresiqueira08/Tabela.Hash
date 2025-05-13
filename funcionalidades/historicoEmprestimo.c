#include "historicoEmprestimo.h"
#include <stdio.h>
#include <stdlib.h>
void registrarHistorico(HistoricoEmprestimo* historico) {
    FILE* f = fopen("dados/historico_emprestimos.dat", "ab");
    if (f==NULL){
        printf("Erro ao abrir o arquivo de histórico!\n");
        return;
    }
    fwrite(historico, sizeof(HistoricoEmprestimo), 1, f);
    fclose(f);
}

void mostrarHistorico() {
    FILE* f = fopen("dados/historico_emprestimos.dat", "rb");
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
