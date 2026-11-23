#ifndef FILMES_H
#define FILMES_H

typedef struct {
    int codigo;
    char nome[50];
    char genero[30];
    int ano;
    float nota;
} Filme;

Filme *criarFilme(void);
void liberarFilme(Filme *filme);

void cadastroFilmes(void);
void deletarFilmes(void);
void listarFilmes(void);
void buscarFilmes(void);
void relatorioFilmes(void);

#endif