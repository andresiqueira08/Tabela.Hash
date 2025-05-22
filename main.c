#include <stdio.h>
#include <stdlib.h>
#include "src/tabela.h"
#include "src/arquivo.h"
#include "src/tabela.h"
#include "funcionalidades/emprestimo.h"
#include "funcionalidades/historicoEmprestimo.h"
#include "funcionalidades/relatorios.h"
#include "funcionalidades/consulta.h"
#include "funcionalidades/relatorios.h"
#include "funcionalidades/interfaceInterativa.h"

int main() {
    iniciarTabelas();  // Inicializa tabelas hash
    carregarLivros();  // Carrega livros do arquivo
    carregarUsuarios(); // Carrega usuários do arquivo
    interfaceInterativa();  // Inicia o menu interativo
    return 0;
}
