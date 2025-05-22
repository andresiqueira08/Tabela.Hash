#ifndef BUSCA_H
#define BUSCA_H

#include "../src/tabela.h"
int compararStrings(const char* a, const char* b);

Livro* buscarLivroPorISBN(const char* isbn);
Livro* buscarLivroPorTitulo(const char* titulo);

Usuario* buscarUsuarioPorID(int id);
Usuario* buscarUsuarioPorNome(const char* nome);

#endif
