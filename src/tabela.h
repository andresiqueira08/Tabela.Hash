#define MAX_TAM 100
#define MAX_STR 100

typedef struct Livro {
    char isbn[20];
    char titulo[MAX_STR];
    char autor[MAX_STR];
    int ano;
    int copias;
    int totalEmprestimos;
    struct Livro* prox; 
} Livro;
 
typedef struct Usuario {
    int id;
    char nome[MAX_STR];
    char email[MAX_STR];
    struct Usuario* prox;
} Usuario;
 

Livro* tabelaLivros[MAX_TAM]; //Criando Tabela Hash para Livros.
Usuario* tabelaUsuarios[MAX_TAM]; // Criando Tabela Hash para Usuarios.
void iniciarTabelas();
Livro* criarLivro(const char* isbn, const char* titulo, const char* autor, int ano, int copias);
Usuario* criarUsuario(int id, const char* nome, const char* email);
int hashLivro(const char* isbn);
int hashUsuario(int id);
void inserirLivro(Livro* livro);
void inserirUsuario(Usuario* usuario);

