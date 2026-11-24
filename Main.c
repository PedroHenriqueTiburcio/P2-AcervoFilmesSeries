#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "Filmes.h"

int main(void){
    // Para permitir os Acentos e a Formatação Numérica corretamente
    setlocale(LC_ALL, "pt_BR.UTF-8");
    setlocale(LC_NUMERIC, "C");
    int opcao;

    do{
        printf("\n==========(SELECIONE SUA OPÇÃO)===========\n");
        printf("1 - Cadastrar\n");
        printf("2 - Listar\n");
        printf("3 - Buscar\n");
        printf("4 - Deletar\n");
        printf("5 - Relatorio\n");
        printf("0 - Sair\n\n");

        printf("Escolha sua opção: ");
        if (scanf("%d", &opcao) != 1){
            int caractere;
            while ((caractere = getchar()) != '\n' && caractere != EOF){}
            if (caractere == EOF){
                break;
            }
            printf("Opção inválida.\n");
            continue;
        }

        switch (opcao){
            case 1: cadastroFilmes(); break;
            case 2: listarFilmes(); break;
            case 3: buscarFilmes(); break;
            case 4: deletarFilmes(); break;
            case 5: relatorioFilmes(); break;
            case 0: printf("Encerrando programa..."); break;
            default: printf("Opcao invalida.\n");
        }
    }while (opcao != 0);
    
    return 0;
}