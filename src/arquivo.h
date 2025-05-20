#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "tabela.h"

void salvarLivro(Livro* livro);
void salvarUsuario(Usuario* usuario);
void carregarLivros();
void carregarUsuarios();
void removerLivro(const char* isbnAlvo);
void removerUsuario(int idAlvo);
void atualizarLivro(const char* isbnAlvo);
void atualizarUsuario(int idAlvo);
#endif


