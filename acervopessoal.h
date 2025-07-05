//Este arquivo contém definições de constantes, a estrutura Livro e os protótipos
//das funções utilizadas para gerenciar o acervo pessoal de livros.

#ifndef ACERVOPESSOAL_H
#define ACERVOPESSOAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

//CONSTANTES
#define MAX_LIVROS 500 //Limite máximo de livros no acervo.
#define MAX_STR 100 //Tamanho máximo para strings.
#define NOME_ARQUIVO "C:\\temp\\ws-clion\\AcervoPessoalLivros\\livros.csv" //Local e nome do arquivo.

//ESTRUTURA DE DADOS
//Definir a estrutura para armazenar os dados de um livro.
typedef struct {
    char codigoISBN[MAX_STR]; //Código ISBN do livro.
    char titulo[MAX_STR]; //Campo 2: Título do livro.
    char autor[MAX_STR]; //Campo 3: Autor do livro.
    int genero; //Campo 4: Gênero do livro (1 a 8).
    int avaliacao; //Campo 5: Avaliação pessoal (0 a 5).
    float valor; //Campo 6: Valor de aquisição do livro.
    int status; //Campo 7: Status do livro (1 a 4).
    int progressoLeitura; //Campo 8: Progresso da leitura (1 a 3).
    char observacoes[MAX_STR]; //Campo 9: Observações gerais.
} Livro;

//PROTOTIPAGEM DAS FUNÇÕES
//Funções de persistência (main.c).
void inicializa();
void salvarDados();
void liberarMemoria();

//Função do menu principal (main.c).
void menuPrincipal();

//Funções de gerenciamento do acervo (acervopessoal.c).
void listagemCompleta();
void inserirCadastro();
void alterarCadastro();
void consultarLivro();
void listarLivros();

//Função auxiliar de validação (acervopessoal.c).
int validarCadastro(Livro* livro);

//Funções de conversão (acervopessoal.c)
const char* getGeneroString(int codigo);
const char* getStatusString(int codigo);
const char* getProgressoString(int codigo);

//Função auxiliar para comparação sem diferenciação de maiúsculas/minúsculas.
void strToLower(char* str);

#endif //ACERVOPESSOAL_H