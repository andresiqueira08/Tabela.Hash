#ifndef TABELA_H
#define TABELA_H


#define MAX_TAM 101 // Números primos tendem a diminuir colisões na tabela Hash
#define MAX_STR 100

typedef struct Livro {
    char isbn[20];
    char titulo[MAX_STR];
    char autor[MAX_STR];
    int ano;
    int copias;
    int ativo; //1 = ativo
    int emprestimos;
    struct Livro* prox; 
} Livro;
 
typedef struct Usuario {
    int id;
    char nome[MAX_STR];
    char email[MAX_STR];
    char telefone[15];
    int ativo;
    int emprestimos;
    struct Usuario* prox;
} Usuario;
 

Livro* tabelaLivros[MAX_TAM]; //Criando Tabela Hash para Livros.
Usuario* tabelaUsuarios[MAX_TAM]; // Criando Tabela Hash para Usuarios.
void iniciarTabelas();
Livro* criarLivro(const char* isbn, const char* titulo, const char* autor, int ano, int copias);
Usuario* criarUsuario(int id, const char* nome, const char* email, const char* telefone);
int hashLivro(const char* isbn);
int hashUsuario(int id);
void inserirLivro(Livro* livro);
void inserirUsuario(Usuario* usuario);

#endif // TABELA_H
