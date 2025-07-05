<b>Projeto Final: Sistema de Acervo Pessoal de Livros <br></b>
![LibraryReadingGIF](https://github.com/user-attachments/assets/f21629c7-721f-4dd4-bea0-c8eb7dca8f4c)


1. Descrição do Sistema:

Este projeto foi desenvolvido como trabalho final para a disciplina de Linguagem de Programação do curso de Tecnologia em Análise e Desenvolvimento de Sistemas da Fatec Arthur de Azevedo.
O objetivo foi criar um sistema de linha de comando para gerenciar um acervo pessoal de livros, aplicando conceitos de estruturas de dados, manipulação de arquivos e boas práticas de desenvolvimento de software. 
O programa permite cadastrar, alterar, consultar e listar livros, com todas as informações salvas de forma persistente em um arquivo de formato CSV.

2. Funcionalidades Implementadas:

O sistema possui um menu principal que dá acesso às seguintes funcionalidades:

Visualizar Listagem Completa: Exibe todos os livros cadastrados no acervo com seus respectivos detalhes. Os códigos de Gênero, Status e Progresso de Leitura são convertidos para textos descritivos para facilitar a leitura (ex: exibe 'Suspense/Terror' em vez do código '2').
Inserir Cadastro de Livro: Permite adicionar um novo livro ao acervo. O sistema realiza a validação dos dados inseridos para garantir a consistência das informações.
Alterar Cadastro de Livro: Permite modificar as informações de um livro já existente, que é localizado por seu código ISBN.
Buscar Livro: Realiza buscas no acervo por código ISBN, título ou autor.
Listar Livros por Filtro: Permite filtrar a exibição dos livros por Gênero, Avaliação, Status ou Progresso de Leitura.

3. Estrutura de Dados: Struct Livro

A principal estrutura de dados utilizada para representar um livro no sistema é a struct Livro, definida da seguinte forma:

typedef struct {
    char codigoISBN[100];
    char titulo[100];
    char autor[100];
    int genero;
    int avaliacao;
    float valor;
    int status;
    int progressoLeitura;
    char observacoes[100];
} Livro;


4. Requisitos Técnicos Atendidos:

O projeto foi desenvolvido atendendo aos seguintes requisitos técnicos definidos na especificação do trabalho:

- Persistência de Dados em CSV: O programa salva e carrega todos os dados de um arquivo no formato CSV. As informações são carregadas na inicialização (inicializa()) e salvas a cada alteração ou ao final da execução (salvarDados()), garantindo que os dados não sejam perdidos.
- Alocação Dinâmica de Memória: Cada registro de livro é alocado dinamicamente na memória usando a função malloc, otimizando o uso de recursos do sistema.
- Vetor de Ponteiros para Structs: Um vetor global de ponteiros para a 'struct Livro' é utilizado para gerenciar o acervo, permitindo um gerenciamento flexível dos registros.
- Modularização do Código: O código-fonte é organizado de forma modular em arquivos de cabeçalho (.h) e de implementação (.c), separando as definições, a lógica principal e as funções de manipulação de dados.
- Tratamento de Erros de Arquivo: Foram implementadas verificações para erros durante a abertura, leitura e escrita do arquivo CSV, garantindo a consistência e a robustez do programa.

5. Como Compilar e Executar:

Este README.md serve como guia de instruções do projeto, conforme solicitado.

1.  Pré-requisitos: É necessário ter um compilador C (como GCC/MinGW) instalado no sistema.
2.  Arquivos: Os arquivos 'main.c', 'acervopessoal.c' e 'acervopessoal.h' devem estar no mesmo diretório.
3.  Compilação: Abra um terminal no diretório dos arquivos e execute o comando: gcc main.c acervopessoal.c -o acervo_pessoal
4.  Execução: Para rodar o programa, use o comando correspondente ao seu sistema operacional:
	Windows: .\acervo_pessoal.exe
	Linux/macOS: ./acervo pessoal
5.  Para carregar o arquivo CSV, tenha-o salvo em alguma pasta do seu diretório e defina este caminho no arquivo de cabeçalho 'acervopessoal.h'. Verifique a edição do local de pasta de acordo com seu sistema operacional. Exemplo do Windows:

	#define NOME_ARQUIVO "C:\\temp\\ws-clion\\AcervoPessoalLivros\\livros.csv" //Local e nome do arquivo

6. Ambiente de Desenvolvimento: 

CLion 2024.3.2
Projeto desenvolvido e testado no compilador GCC (MinGW 64-bit) em ambiente Windows.

7. Autores:👨‍🦰👨‍🦰👧👧👧👧

Este projeto foi desenvolvido em equipe pelos seguintes alunos:

Davi Esteves Arcanjo de Oliveira<br>
Flavia Benegas https://github.com/Flaviabenegas <br>
João Vitor Guimarães de Moraes da Silva<br>
Marilia dos Santos Silva https://github.com/marilia141194 <br>
Milena Acuio de Arruda<br>
Millena Souza de Aguiar.
