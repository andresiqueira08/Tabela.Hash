#define MAX_TAM 100
#define MAX_STR 100
typedef struct Livro {
    char isbn[20];
    char titulo[MAX_STR];
    char autor[MAX_STR];
    int ano;
    int copias;
    struct Livro* prox; 
} Livro;
 
typedef struct Usuario {
    int id;
    char nome[MAX_STR];
    char email[MAX_STR];
    struct Usuario* prox;
} Usuario;
 

Livro* tabelaLivros[MAX_TAM];
Usuario* tabelaUsuarios[MAX_TAM];
void iniciarTabelas();