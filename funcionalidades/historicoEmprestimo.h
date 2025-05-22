#ifndef HISTORICO_H
#define HISTORICO_H
#define MAX_STR 100

// Estrutura para armazenar histórico de empréstimos
typedef struct {
    int idUsuario;
    char isbn[20];
    char dataEmprestimo[11];  // formato: DD/MM/AAAA
    char dataDevolucao[11];   // formato: DD/MM/AAAA
    float multa;              
} HistoricoEmprestimo;

void registrarHistorico(HistoricoEmprestimo* historico);
void mostrarHistorico();
void atualizarCopiasLivro(const char* isbn, int delta);
void registrarDevolucao(int idUsuario, char* isbn, char* dataEmprestimo, int diasAtraso);
void obterDataAtual(char* buffer, int tamanho);
float calcularMulta(int diasAtraso);



#endif
