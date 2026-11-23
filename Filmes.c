#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Filmes.h"
    
// Funções dos menus
    Filme *criarFilme(void){
        return malloc(sizeof(Filme));
    }

    void liberarFilme(Filme *filme){
        free(filme);
    }

    void cadastroFilmes(){
        Filme *filme = criarFilme();
        FILE *arquivo;

        if (filme == NULL){
            printf("Erro ao alocar memória para o filme.\n");
            return;
        }

        printf("\n================(Cadastro de Filme)================\n");
        printf("NUNCA COLOQUE ; , ACENTOS E CARACTERES ESPECIAIS!\n");
        printf("Informe o código do filme: \n"); 
        scanf("%d", &filme->codigo);
        // Uso de comandos do <string.h> para melhorar a formatação dos nomes e gêneros
        printf("Informe o nome do filme: \n"); 
        scanf(" ");
        fgets(filme->nome, sizeof(filme->nome), stdin);
        filme->nome[strcspn(filme->nome, "\n")] = '\0';
        printf("Informe o gênero do filme: \n"); 
        scanf(" ");
        fgets(filme->genero, sizeof(filme->genero), stdin);
        filme->genero[strcspn(filme->genero, "\n")] = '\0';

        printf("Informe o ano do filme: \n"); 
        scanf("%d", &filme->ano);
        printf("Informe a nota do filme: \n"); 
        scanf("%f", &filme->nota);

        printf("Iniciando cadastro...\n");
        
        arquivo = fopen("filmes.txt", "a");

        // Ver se o arquivo está abrindo
        if (arquivo == NULL){
            printf("Erro ao abrir o arquivo!!\n");
            liberarFilme(filme);
            return;
        }

        // Escrever no arquivo
        fprintf(arquivo, "%d;%s;%s;%d;%.1f\n", filme->codigo, filme->nome, filme->genero, filme->ano, filme->nota);
        fclose(arquivo);
        liberarFilme(filme);
        printf("Filme cadastrado!!");
        int opcao = 0;
        printf("\n==============================================\n");
        printf("Deseja cadastrar mais filmes? Sim[1] ou Não[2]\n");
        scanf("%d", &opcao);
        if (opcao == 1){
            cadastroFilmes();
        }else if (opcao == 2){
            return;
        }else{
            printf("Opção Inválida.");
        }
    }
    
    void deletarFilmes(){
        // Usa um arquivo temporário pra reescrever tudo sem uma linha
        FILE *arquivo = fopen("filmes.txt", "r");
        FILE *temporario = fopen("filmes_temp.txt", "w");

        // Variaveis para achar as coisas no arquivo
        char linha[150];
        Filme filme;
        int codigoInformado;
        int encontrado = 0;

        // Ver se os arquivos estão abrindo normal
        if (arquivo == NULL){
            printf("Erro ao abrir o arquivo!!\n");
            return;
        }

        if (temporario == NULL){
            printf("Erro ao abrir arquivo temporario!!\n");
            fclose(arquivo);
            return;
        }
        printf("\n===============(DELETAR FILMES)===============\n");
        printf("Informe o código do filme a ser deletado: ");
        scanf("%d", &codigoInformado);

        // Procura a linha e passa as outras para o outro arquivo
        while (fgets(linha, sizeof(linha), arquivo) != NULL){
            sscanf(linha, "%d;%49[^;];%29[^;];%d;%f", &filme.codigo, filme.nome, filme.genero, &filme.ano, &filme.nota);

            if (filme.codigo == codigoInformado){
                encontrado = 1;
            }
            else{
            fprintf(temporario, "%d;%s;%s;%d;%.1f\n", filme.codigo, filme.nome, filme.genero, filme.ano, filme.nota);
            }
        }

        fclose(arquivo);
        fclose(temporario);

        // caso encontrar as coisas reescreve tudo no outro aquivo e já renomeia.
        if (encontrado){
            remove("filmes.txt");
            rename("filmes_temp.txt", "filmes.txt");
            printf("Filme deletado.\n");
        }
        else{
            remove("filmes_temp.txt");
            printf("Codigo nao encontrado.\n");
        }

        int opcao = 0;
        printf("\n==============================================\n");
        printf("Deseja deletar mais filmes? Sim[1] ou Não[2]\n");
        scanf("%d", &opcao);
        if (opcao == 1){
            deletarFilmes();
        }else if (opcao == 2){
            return;
        }else{
            printf("Opção Inválida.");
        }
    }

    void listarFilmes(){
        FILE *arquivo = fopen("filmes.txt", "r");
        char linha[150];
        Filme filme;

        // Ver se o arquivo está abrindo
        if (arquivo == NULL){
            printf("Erro ao abrir o arquivo!");
            return;
        }
        printf("\n===============(LISTAR FILMES)===============\n");
        while (fgets(linha, sizeof(linha), arquivo) != NULL){
            // Variaveis para achar as coisas no arquivo
            sscanf(linha, "%d;%49[^;];%29[^;];%d;%f", &filme.codigo, filme.nome, filme.genero, &filme.ano, &filme.nota);

            printf("\n=========\nCódigo: %d\nNome: %s\nGênero: %s\nAno: %d\nNota: %.1f", filme.codigo, filme.nome, filme.genero, filme.ano, filme.nota);
        }
        printf("\n=========\n");

        fclose(arquivo);

        return;
    }

    void buscarFilmes(){
        FILE *arquivo = fopen("filmes.txt", "r");
        char linha[150];
        Filme filme;
        char nomeInformado[50];
        int codigoInformado;
        int encontrado = 0;

        // Ver se o arquivo está abrindo
        if (arquivo == NULL){
            printf("Erro ao abrir o arquivo!");
            return;
        }

        int busca = 0;
        printf("\n===============(BUSCAR FILMES)===============\n");
        printf("NUNCA COLOQUE ;!\n");
        printf("Deseja buscar por nome(1) ou código(2)? \n");
        scanf("%d", &busca);

        if (busca == 1){
            printf("Digite o nome do filme: \n");
            printf("Caso esteja com problemas para digitar o nome, use a busca por Código.\n");
            scanf(" ");
            // Funções do <string.h> para melhorar a busca
            fgets(nomeInformado, sizeof(nomeInformado), stdin);
            nomeInformado[strcspn(nomeInformado, "\n")] = '\0';

            while (fgets(linha, sizeof(linha), arquivo) != NULL){
                int campos = sscanf(linha, "%d;%49[^;];%29[^;];%d;%f", &filme.codigo, filme.nome, filme.genero, &filme.ano, &filme.nota);

                if (campos != 5)
                    continue;

                if (strcmp(filme.nome, nomeInformado) == 0)
                {
                    encontrado = 1;
                    printf("\n=========\nCódigo: %d\nNome: %s\nGênero: %s\nAno: %d\nNota: %.1f\n", filme.codigo, filme.nome, filme.genero, filme.ano, filme.nota);
                    fclose(arquivo);
                    return;
                }
            }
        }else if (busca == 2){
            printf("Digite o código do filme: ");
            scanf("%d", &codigoInformado);
            while (fgets(linha, sizeof(linha), arquivo) != NULL){
                int campos = sscanf(linha, "%d;%49[^;];%29[^;];%d;%f", &filme.codigo, filme.nome, filme.genero, &filme.ano, &filme.nota);

                if (campos != 5)
                    continue;

                if (filme.codigo == codigoInformado)
                {
                    encontrado = 1;
                    printf("\n=========\nCódigo: %d\nNome: %s\nGênero: %s\nAno: %d\nNota: %.1f\n=========\n", filme.codigo, filme.nome, filme.genero, filme.ano, filme.nota);
                    fclose(arquivo);
                    return;
                }
            }
        }else{
            printf("Opção inválida, escolha 1 ou 2.\n");
        }

        if (encontrado != 1){
            printf("Filme não encontrado!");
            fclose(arquivo);
            return;
        }
        int opcao = 0;
        printf("\n==============================================\n");
        printf("Deseja buscar mais filmes? Sim[1] ou Não[2]");
        scanf("%d", &opcao);
        if (opcao == 1){
            buscarFilmes();
        }else if (opcao == 2){
            return;
        }else{
            printf("Opção Inválida.");
        }
    }

    void relatorioFilmes(){
        FILE *arquivo = fopen("filmes.txt", "r");
        char linha[150];
        Filme filme;
        Filme maiorFilme = {0, "", "", 0, -1.0f};
        Filme menorFilme = {0, "", "", 0, 100.0f};
        char textoNota[20];
        int acumulador = 0;
        float media;
        float acumuladorNotas = 0.0f;


        // Ver se o arquivo está abrindo
        if (arquivo == NULL){
            printf("Erro ao abrir o arquivo!");
            return;
        }

        // Percorre as linhas do arquivo
        while (fgets(linha, sizeof(linha), arquivo) != NULL){
            int campos = sscanf(linha, "%d;%49[^;];%29[^;];%d;%19[^;\n]", &filme.codigo, filme.nome, filme.genero, &filme.ano, textoNota);

            // Verifica se os campos estão na quantidade certa.
            if (campos != 5)
            {
                continue;
            }
            // Para caso no arquivo as notas estejam com vírgula
            for (int i = 0; textoNota[i] != '\0'; i++)
            {
                if (textoNota[i] == ',')
                {
                    textoNota[i] = '.';
                }
            }

            filme.nota = strtof(textoNota, NULL);
            
            // Acumula as notas e a quatidade delas
            acumulador += 1;
            acumuladorNotas += filme.nota;

            // Atribui e atualiza o filme com a maior e a menor nota.
            if (filme.nota > maiorFilme.nota){
                maiorFilme = filme;
            }
            if (filme.nota < menorFilme.nota){
                menorFilme = filme;
            }
        }

        if (acumulador == 0){
                printf("Nenhum filme cadastrado.\n");
                fclose(arquivo);
                return;
            }

        // Mostra os resultados
        media = acumuladorNotas/acumulador;
        printf("\n===============(RELATÓRIO)===============\n");
        printf("A média das notas é %.1f\n", media);
        printf("A maior nota é %.1f de %s\n", maiorFilme.nota, maiorFilme.nome);
        printf("A menor nota é %.1f de %s\n", menorFilme.nota, menorFilme.nome);
        fclose(arquivo);
        return;
    }