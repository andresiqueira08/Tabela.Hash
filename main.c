#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "src/tabela.h"
#include "src/arquivo.h"
#include "src/tabela.h"
#include "funcionalidades/emprestimo.h"
#include "funcionalidades/historicoEmprestimo.h"
#include "funcionalidades/relatorios.h"
#include "funcionalidades/consulta.h"
#include "funcionalidades/relatorios.h"
#include "funcionalidades/interfaceInterativa.h"
//Adição de tudo que foi trabalhado

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    iniciarTabelas();  // Inicializa tabelas hash
    carregarLivros();  // Carrega livros do arquivo
    carregarUsuarios(); // Carrega usuários do arquivo
    interfaceInterativa();  // Inicia o menu interativo
    return 0;
}
