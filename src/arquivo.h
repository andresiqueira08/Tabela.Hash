#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "tabela.h"
void atualizarLivroNaHash(Livro* livro);
void atualizarUsuarioNaHash(Usuario* usuario);
void salvarLivro(Livro* livro);
void salvarUsuario(Usuario* usuario);
void carregarLivros();
void carregarUsuarios();
void removerLivroDaHash(const char* isbn);
void removerUsuarioDaHash(int id);
void removerLivro(const char* isbnAlvo);
void removerUsuario(int idAlvo);
void atualizarLivro(const char* isbnAlvo);
void atualizarUsuario(int idAlvo);
#endif


