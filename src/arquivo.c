#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela.h"
#include "arquivo.h"
void atualizarLivroNaHash(Livro* livro) {
    if (livro == NULL) {
        printf("Erro: Livro inválido.\n");
        return;
    }

    int chave = hashLivro(livro->isbn);
    Livro* buscando = tabelaLivros[chave];

    while (buscando != NULL) {
        if (strcmp(buscando->isbn, livro->isbn) == 0) {
            // Atualiza os campos com os novos valores
            strcpy(buscando->titulo, livro->titulo);
            strcpy(buscando->autor, livro->autor);
            buscando->ano = livro->ano;
            buscando->copias = livro->copias;
            printf("Livro ISBN %s atualizado na tabela hash.\n", livro->isbn);
            return;
        }
        buscando = buscando->prox;
    }

    printf("Livro com ISBN %s não encontrado na tabela hash.\n", livro->isbn);
}
void atualizarUsuarioNaHash(Usuario* usuario) {
    if (usuario == NULL) {
        printf("Erro: Usuário inválido.\n");
        return;
    }

    int chave = hashUsuario(usuario->id);
    Usuario* buscando = tabelaUsuarios[chave];

    while (buscando != NULL) {
        if (buscando->id == usuario->id) {
            // Atualiza os campos com os novos valores
            strcpy(buscando->nome, usuario->nome);
            strcpy(buscando->email, usuario->email);
            printf("Usuário ID %d atualizado na tabela hash.\n", usuario->id);
            return;
        }
        buscando = buscando->prox;
    }

    printf("Usuário com ID %d não encontrado na tabela hash.\n", usuario->id);
}
void salvarLivro(Livro* livro) {
    FILE* f = fopen("C:\\Users\\LORENA\\estrutura.de.dados\\tabelaHash\\dados\\livros.dat", "ab"); // a = adicionar, b = binário
    if (f == NULL) {
        printf("Erro ao abrir livros.dat\n");
        return;
    }

    fwrite(livro, sizeof(Livro), 1, f);
    fclose(f);
}

void salvarUsuario(Usuario* usuario) {
    FILE* f = fopen("C:\\Users\\LORENA\\estrutura.de.dados\\tabelaHash\\dados\\usuarios.dat", "ab"); 
    if (f == NULL) {
        printf("Erro ao abrir usuarios.dat\n");
        return;
    }

    fwrite(usuario, sizeof(Usuario), 1, f);
    fclose(f);
}
// Funções para carregar os dados do arquivo binário de volta para a tabela hash quando o programa inicia.
void carregarLivros() {
    FILE* f = fopen("C:\\Users\\LORENA\\estrutura.de.dados\\tabelaHash\\dados\\livros.dat", "rb");
    if (f == NULL) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }

    Livro livro;
    while (fread(&livro, sizeof(Livro), 1, f)) {
        if (livro.ativo) {  // <- Só carrega se estiver ativo
            Livro* novoLivro = criarLivro(livro.isbn, livro.titulo, livro.autor, livro.ano, livro.copias);
            inserirLivro(novoLivro);
        }
    }
    fclose(f);
}


void carregarUsuarios() {
    FILE* f = fopen("C:\\Users\\LORENA\\estrutura.de.dados\\tabelaHash\\dados\\usuarios.dat", "rb");
    if (f == NULL) {
        printf("Nenhum usuário cadastrado.\n");
        return;
    }

    Usuario usuario;
    while (fread(&usuario, sizeof(Usuario), 1, f)) { 
        if (usuario.ativo) {  
            Usuario* novoUsuario = criarUsuario(usuario.id, usuario.nome, usuario.email, usuario.telefone);
            
            if (novoUsuario != NULL) { 
                inserirUsuario(novoUsuario);
            } else {
                printf("Erro ao criar usuário: ID %d\n", usuario.id);
            }
        }
    }
    fclose(f);
}
void removerUsuarioDaHash(int id) {
    int chave = hashUsuario(id);
    Usuario* atual = tabelaUsuarios[chave];
    Usuario* anterior = NULL;

    while (atual != NULL) {
        if (atual->id == id) {
            // Remove o usuário da lista encadeada
            if (anterior == NULL) {
                tabelaUsuarios[chave] = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            printf("Usuário ID %d removido da tabela hash.\n", id);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }

    printf("Usuário com ID %d não encontrado na tabela hash.\n", id);
}
void removerLivroDaHash(const char* isbn) {
    int chave = hashLivro(isbn);
    Livro* atual = tabelaLivros[chave];
    Livro* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->isbn, isbn) == 0) {
            // Remove o livro da lista encadeada
            if (anterior == NULL) {
                tabelaLivros[chave] = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            printf("Livro ISBN %s removido da tabela hash.\n", isbn);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }

    printf("Livro com ISBN %s não encontrado na tabela hash.\n", isbn);
}
//Algoritmo que remove os livro e os usuários de maneira lógica, sem apagá-los fisicamente
void removerLivro(const char* isbnAlvo) {
    FILE* f = fopen("C:\\Users\\LORENA\\estrutura.de.dados\\tabelaHash\\dados\\livros.dat", "rb+"); //r = leitura, + = leitura e escrita
    if (f == NULL) {
        printf("Erro ao abrir livros.dat\n");
        return;
    }

    Livro livro;
    while (fread(&livro, sizeof(Livro), 1, f)) {
        if (livro.ativo && strcmp(livro.isbn, isbnAlvo) == 0){ //strcmp para comparar strings
            livro.ativo = 0;
            fseek(f, -sizeof(Livro), SEEK_CUR); // volta uma posição no arquivo
            fwrite(&livro, sizeof(Livro), 1, f);
            printf("Livro removido com sucesso.\n");

            //Remover da tabela hash em memória
            removerLivroDaHash(isbnAlvo); 
            fclose(f);
            return;
        }
    }

    printf("Livro não encontrado ou já removido.\n");
    fclose(f);
}
void removerUsuario(int idAlvo) {
    FILE* f = fopen("C:\\Users\\LORENA\\estrutura.de.dados\\tabelaHash\\dados\\usuarios.dat", "rb+");
    if (f == NULL) {
        printf("Erro ao abrir usuarios.dat\n");
        return;
    }

    Usuario usuario;
    while (fread(&usuario, sizeof(Usuario), 1, f)) {
        if (usuario.ativo && usuario.id == idAlvo) {
            usuario.ativo = 0;
            fseek(f, -sizeof(Usuario), SEEK_CUR);
            fwrite(&usuario, sizeof(Usuario), 1, f);
            printf("Usuário removido com sucesso.\n");

            // Opcional: remover da hash em memória
            removerUsuarioDaHash(idAlvo);
            fclose(f);
            return;
        }
    }

    printf("Usuário não encontrado ou já removido.\n");
    fclose(f);
}
void atualizarLivro(const char* isbnAlvo) {
    FILE* f = fopen("C:\\Users\\LORENA\\estrutura.de.dados\\tabelaHash\\dados\\livros.dat", "rb+");
    if (f == NULL) {
        printf("Erro ao abrir livros.dat\n");
        return;
    }

    Livro livro;
    while (fread(&livro, sizeof(Livro), 1, f)) {
        if (livro.ativo && strcmp(livro.isbn, isbnAlvo) == 0) {
            printf("Livro encontrado. Informe os novos dados:\n");

            printf("Novo título: ");
            getchar(); // Limpa buffer
            fgets(livro.titulo, sizeof(livro.titulo), stdin);
            livro.titulo[strcspn(livro.titulo, "\n")] = '\0';

            printf("Novo autor: ");
            fgets(livro.autor, sizeof(livro.autor), stdin);
            livro.autor[strcspn(livro.autor, "\n")] = '\0';

            printf("Novo ano: ");
            scanf("%d", &livro.ano);

            printf("Nova quantidade de cópias: ");
            scanf("%d", &livro.copias);

            // Reposiciona o ponteiro para atualizar no mesmo local
            fseek(f, -sizeof(Livro), SEEK_CUR);
            fwrite(&livro, sizeof(Livro), 1, f);
            fclose(f);

            // Atualiza na tabela hash 
            atualizarLivroNaHash(&livro);
            printf("Livro atualizado com sucesso.\n");
            return;
        }
    }

    printf("Livro com ISBN %s não encontrado.\n", isbnAlvo);
    fclose(f);
}
void atualizarUsuario(int idAlvo) {
    FILE* f = fopen("C:\\Users\\LORENA\\estrutura.de.dados\\tabelaHash\\dados\\usuarios.dat", "rb+");
    if (f == NULL) {
        printf("Erro ao abrir usuarios.dat\n");
        return;
    }

    Usuario usuario;
    while (fread(&usuario, sizeof(Usuario), 1, f)) {
        if (usuario.ativo && usuario.id == idAlvo) {
            printf("Usuário encontrado. Informe os novos dados:\n");

            printf("Novo nome: ");
            getchar();
            fgets(usuario.nome, sizeof(usuario.nome), stdin);
            usuario.nome[strcspn(usuario.nome, "\n")] = '\0';

            printf("Novo e-mail: ");
            fgets(usuario.email, sizeof(usuario.email), stdin);
            usuario.email[strcspn(usuario.email, "\n")] = '\0';
            //fseek para sobreescrever
            fseek(f, -sizeof(Usuario), SEEK_CUR);
            fwrite(&usuario, sizeof(Usuario), 1, f);
            fclose(f);

            atualizarUsuarioNaHash(&usuario); 
            printf("Usuário atualizado com sucesso.\n");
            return;
        }
    }

    printf("Usuário com ID %d não encontrado.\n", idAlvo);
    fclose(f);
}
