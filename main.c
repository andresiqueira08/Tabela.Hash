#include <stdio.h>
#include <stdlib.h>
#include "src/tabela.h"
#include "src/arquivo.h"
#include "funcionalidades/emprestimo.h"
#include "funcionalidades/historicoEmprestimo.h"
#include "funcionalidades/consulta.h"

int main() {
    FILE* f = NULL;
    int opcao;
 
    do {
        printf("\n--- Menu ---\n");
        printf("1. Cadastrar livro\n");
        printf("2. Cadstrar Usuario\n");
        printf("3. Buscar l por codigo\n");
        printf("4. Atualizar produto\n");
        printf("5. Remover produto\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: cadastrar_produto(f); break;
            case 2: listar_produtos(f); break;
            case 3: buscar_produto(f); break;
            case 4: atualizar_produto(f); break;
            case 5: remover_produto(f); break;
            case 6: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 6);
 
    return 0;
}
