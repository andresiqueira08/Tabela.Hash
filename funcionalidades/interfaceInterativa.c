#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/tabela.h"
#include "../src/arquivo.h"
#include "historicoEmprestimo.h"
#include "emprestimo.h"
#include "consulta.h"
#include "relatorios.h"

void exibirMenu() {
    printf("\n=== Sistema de Biblioteca ===\n");
    printf("1 - Cadastrar Livro\n");
    printf("2 - Cadastrar Usuário\n");
    printf("3 - Consultar Livro\n");
    printf("4 - Consultar Usuário\n");
    printf("5 - Realizar Empréstimo\n");
    printf("6 - Registrar Devolução\n");
    printf("7 - Atualizar Livro\n");
    printf("8 - Atualizar Usuário\n");
    printf("9 - Remover Livro\n");
    printf("10 - Remover Usuário\n");
    printf("11 - Exibir Histórico de Empréstimos\n");
    printf("12 - Livros Mais Emprestados\n");
    printf("13 - Usuários Mais Ativos\n");
    printf("14 - Sair\n");
    printf("Escolha uma opção: ");
}

void interfaceInterativa() {
    int opcao;
    char isbn[MAX_STR], titulo[MAX_STR], autor[MAX_STR], nome[MAX_STR], email[MAX_STR], dataEmprestimo[11], telefone[15];
    int id, ano, copias, diasAtraso;

    while (1) {
        exibirMenu();
        scanf("%d", &opcao);
        getchar();  // Limpa o buffer

        switch (opcao) {
            case 1:
                printf("ISBN: ");
                fgets(isbn, MAX_STR, stdin);
                strtok(isbn, "\n");

                printf("Título: ");
                fgets(titulo, MAX_STR, stdin);
                strtok(titulo, "\n");

                printf("Autor: ");
                fgets(autor, MAX_STR, stdin);
                strtok(autor, "\n");

                printf("Ano: ");
                scanf("%d", &ano);
                printf("Número de cópias: ");
                scanf("%d", &copias);

                Livro* novoLivro = criarLivro(isbn, titulo, autor, ano, copias);
                inserirLivro(novoLivro);
                salvarLivro(novoLivro);
                printf("Livro cadastrado com sucesso!\n");
                break;

            case 2:
                printf("ID do Usuário: ");
                scanf("%d", &id);
                getchar();

                printf("Nome: ");
                fgets(nome, MAX_STR, stdin);
                strtok(nome, "\n");

                printf("Email: ");
                fgets(email, MAX_STR, stdin);
                strtok(email, "\n");

                printf("Telefone: ");
                fgets(telefone, 11, stdin);
                strtok(telefone, "\n");

                Usuario* novoUsuario = criarUsuario(id, nome, email, telefone);
                inserirUsuario(novoUsuario);
                salvarUsuario(novoUsuario);
                printf("Usuário cadastrado com sucesso!\n");
                break;

            case 3:
                printf("Digite o ISBN para consulta: ");
                fgets(isbn, MAX_STR, stdin);
                strtok(isbn, "\n");
                Livro* livro = buscarLivroPorISBN(isbn);
                if (livro) {
                    printf("Livro encontrado: %s - %s (%d cópias disponíveis)\n", livro->isbn, livro->titulo, livro->copias);
                } else {
                    printf("Livro não encontrado.\n");
                }
                break;

            case 4:
                printf("Digite o ID do usuário para consulta: ");
                scanf("%d", &id);
                Usuario* usuario = buscarUsuarioPorID(id);
                if (usuario) {
                    printf("Usuário encontrado: ID %d - %s\n", usuario->id, usuario->nome);
                } else {
                    printf("Usuário não encontrado.\n");
                }
                break;

            case 5:
                printf("Digite o ISBN do livro: ");
                fgets(isbn, MAX_STR, stdin);
                strtok(isbn, "\n");

                printf("Digite o ID do usuário: ");
                scanf("%d", &id);
                getchar();

                printf("Digite a data do empréstimo (DD/MM/AAAA): ");
                fgets(dataEmprestimo, 11, stdin);
                strtok(dataEmprestimo, "\n");

                realizarEmprestimo(isbn, id, dataEmprestimo);
                break;

            case 6:
                printf("Digite o ISBN do livro: ");
                fgets(isbn, MAX_STR, stdin);
                strtok(isbn, "\n");

                printf("Digite o ID do usuário: ");
                scanf("%d", &id);
                getchar();

                printf("Digite a data do empréstimo (DD/MM/AAAA): ");
                fgets(dataEmprestimo, 11, stdin);
                strtok(dataEmprestimo, "\n");

                printf("Digite a quantidade de dias de atraso: ");
                scanf("%d", &diasAtraso);

                registrarDevolucao(id, isbn, dataEmprestimo, diasAtraso);
                atualizarCopiasLivro(isbn, 1);
                break;

            case 7:
                printf("Digite o ISBN do livro para atualizar: ");
                fgets(isbn, MAX_STR, stdin);
                strtok(isbn, "\n");
                atualizarLivro(isbn);
                break;

            case 8:
                printf("Digite o ID do usuário para atualizar: ");
                scanf("%d", &id);
                atualizarUsuario(id);
                break;

            case 9:
                printf("Digite o ISBN do livro para remover: ");
                fgets(isbn, MAX_STR, stdin);
                strtok(isbn, "\n");
                removerLivro(isbn);
                break;

            case 10:
                printf("Digite o ID do usuário para remover: ");
                scanf("%d", &id);
                removerUsuario(id);
                break;

            case 11:
                exibirHistoricoEmprestimos();
                break;

            case 12:
                livrosMaisEmprestados();
                break;

            case 13:
                usuariosMaisAtivos();
                break;

            case 14:
                printf("Saindo...\n");
                return;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
}

