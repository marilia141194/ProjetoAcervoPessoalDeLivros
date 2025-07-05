#include "acervopessoal.h"

//VARIÁVEIS GLOBAIS
Livro* acervo[MAX_LIVROS]; //Vetor global de ponteiros para as structs.
int totalLivros = 0; //Contador total de livros cadastrados.

//Função principal que inicia o programa.
int main() {
    setlocale(LC_NUMERIC, "C"); //Define formato decimal com ponto (.) em vez de vírgula (,)
    inicializa(); //Carregar os dados do arquivo CSV.
    menuPrincipal(); //Exibir o menu principal para o usuário.
    liberarMemoria(); //Liberar a memória alocada.
    return 0;
}

//Carregar os dados dos livros do arquivo CSV para a memória.
void inicializa() {
    FILE* arquivo = fopen(NOME_ARQUIVO, "r");
    if (arquivo == NULL) {
        printf("Arquivo de dados nao encontrado. Iniciando com acervo vazio.\n");
        return;
    }

    char linha[512]; //Buffer para armazenar cada linha
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (totalLivros >= MAX_LIVROS) {
            printf("Aviso: Limite maximo de livros atingido (%d). Alguns livros podem nao ter sido carregados.\n", MAX_LIVROS);
            break;
        }

        //Remover a quebra de linha que o fgets lê no final da string, importante para o strtok funcionar corretamente.
        linha[strcspn(linha, "\r\n")] = 0;

        //Alocar a memória para o novo livro
        acervo[totalLivros] = (Livro*)malloc(sizeof(Livro));
        if (acervo[totalLivros] == NULL) {
            printf("Erro critico: Falha ao alocar memoria.\n");
            break;
        }

        char *token;
        int campo_atual = 1;

        //Pegar o primeiro 'token' antes do delimitador ';', ou seja, vai separar cada campo por ';'.
        token = strtok(linha, ";");

        while (token != NULL) {
            //Atribuir o token a cada campo correspondente da struct.
            switch (campo_atual) {
                case 1: strcpy(acervo[totalLivros]->codigoISBN, token); break;
                case 2: strcpy(acervo[totalLivros]->titulo, token); break;
                case 3: strcpy(acervo[totalLivros]->autor, token); break;
                case 4: acervo[totalLivros]->genero = atoi(token); break; //atoi: converter string para inteiro
                case 5: acervo[totalLivros]->avaliacao = atoi(token); break; //atoi: converter string para inteiro
                case 6: acervo[totalLivros]->valor = atof(token); break; //atof: converter string para float
                case 7: acervo[totalLivros]->status = atoi(token); break; //atoi: converter string para inteiro
                case 8: acervo[totalLivros]->progressoLeitura = atoi(token); break; //atoi: converter string para inteiro
                case 9: strcpy(acervo[totalLivros]->observacoes, token); break;
            }
            //Pegar o próximo 'token' antes do delimitador ';'.
            token = strtok(NULL, ";");
            campo_atual++;
        }

        //Caso o campo de observações ficar vazio, o loop termina com campo_atual = 9.
        //Então tem que limpar o campo para não ter lixo de memória.
        if (campo_atual <= 9) {
            strcpy(acervo[totalLivros]->observacoes, "");
        }
        //Incrementar o contador de livros.
        totalLivros++;
    }

    fclose(arquivo);
    //Primeira mensagem para o usuário antes do menu principal, avisando que carregou a listagem.
    printf("Acervo carregado com sucesso! Total de %d livros.", totalLivros);
}

//Função para salvar todos os dados do acervo da memória para o arquivo CSV.
//Para garantir consistência, o arquivo é completamente reescrito.
void salvarDados() {
    FILE* arquivo = fopen(NOME_ARQUIVO, "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar arquivo! Verifique as permissoes da pasta.\n");
        return;
    }

    for (int i = 0; i < totalLivros; i++) {
        fprintf(arquivo, "%s;%s;%s;%d;%d;%.2f;%d;%d;%s\n",
                acervo[i]->codigoISBN,
                acervo[i]->titulo,
                acervo[i]->autor,
                acervo[i]->genero,
                acervo[i]->avaliacao,
                acervo[i]->valor,
                acervo[i]->status,
                acervo[i]->progressoLeitura,
                acervo[i]->observacoes);
    }
    fclose(arquivo);
}

//Função para liberar a memória alocada dinamicamente para cada livro.
void liberarMemoria() {
    for (int i = 0; i < totalLivros; i++) {
        free(acervo[i]);
    }
}

// Função para exibir o menu principal e direcionar o usuário para as funções.
void menuPrincipal() {
    int opcao;
    do {
        printf("\n----------------------------------------------");
        printf("\n--- ACERVO DE LIVROS PESSOAL ---\n");
        printf("1 - Visualizar Listagem Completa dos Livros\n");
        printf("2 - Inserir Cadastro de Livro\n");
        printf("3 - Alterar Cadastro de Livro\n");
        printf("4 - Buscar Livro por...\n");
        printf("5 - Listar Livros por...\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); //Limpar o buffer do teclado para evitar problemas com leituras de strings futuras.

        switch (opcao) {
            case 1: listagemCompleta(); break;
            case 2: inserirCadastro(); break;
            case 3: alterarCadastro(); break;
            case 4: consultarLivro(); break;
            case 5: listarLivros(); break;
            case 0:
                printf("Salvando dados e saindo...\n");
                salvarDados(); //Salvar os dados antes de sair.
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);
}