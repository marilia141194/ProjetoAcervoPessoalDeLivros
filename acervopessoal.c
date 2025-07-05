#include "acervopessoal.h"

//Declaração de que as variáveis globais existem em outro arquivo.
extern Livro* acervo[];
extern int totalLivros;

//Função para converter os gêneros dos livros - de números de 1 a 8 para saídas em strings.
const char* getGeneroString(int codigo) {
    switch (codigo) {
        case 1: return "Romance";
        case 2: return "Suspense/Terror";
        case 3: return "Fantasia";
        case 4: return "Ficcao Cientifica";
        case 5: return "HQ/Manga";
        case 6: return "Tecnicos/Didaticos";
        case 7: return "Autoajuda";
        case 8: return "Outros";
        default: return "Desconhecido";
    }
}

//Função para converter os status dos livros - de números de 1 a 4 para saídas em strings.
const char* getStatusString(int codigo) {
    switch (codigo) {
        case 1: return "Disponivel";
        case 2: return "Doado";
        case 3: return "Emprestado";
        case 4: return "Inativado";
        default: return "Desconhecido";
    }
}

//Função para converter os progressos de leitura - de números de 1 a 3 para saídas em strings.
const char* getProgressoString(int codigo) {
    switch (codigo) {
        case 1: return "Lido";
        case 2: return "Lendo";
        case 3: return "Nao lido";
        default: return "Desconhecido";
    }
}

 //Função para imprimir os detalhes de um único livro de forma formatada.
void imprimirLivro(Livro* livro) {
    printf("\n----------------------------------------------\n");
    printf("ISBN: %s\n", livro->codigoISBN);
    printf("Titulo: %s\n", livro->titulo);
    printf("Autor: %s\n", livro->autor);
    printf("Genero: %s\n", getGeneroString(livro->genero));
    printf("Avaliacao: %d\n", livro->avaliacao);
    printf("Valor: R$ %.2f\n", livro->valor);
    printf("Status: %s\n", getStatusString(livro->status));
    printf("Progresso: %s\n", getProgressoString(livro->progressoLeitura));
    printf("Observacoes: %s\n", livro->observacoes);
}

//Função para imprimir a listagem completa de todos os livros cadastrados no acervo.
//Utilizada na primeira opção do menu principal.
void listagemCompleta() {
    if (totalLivros == 0) {
        printf("\nNenhum livro cadastrado no acervo.\n");
        return;
    }

    printf("\n--- LISTAGEM COMPLETA DOS LIVROS ---");
    //Contar a quantidade total de livros e calcular o valor total em R$ do acervo.
    float valorTotal = 0;
    for (int i = 0; i < totalLivros; i++) {
        imprimirLivro(acervo[i]);
        valorTotal += acervo[i]->valor;
    }
    printf("\n----------------------------------------------");

    //Mostrar a quantidade total de livros e o valor total em R$ do acervo.
    printf("\nQuantidade total de livros: %d\n", totalLivros);
    printf("Valor total do acervo: R$ %.2f\n", valorTotal);
}

//Função para validar se todos os campos "string" estão preenchidos, se os campos numéricos estão no intervalo esperado,
//e se o campo 'observações' está preenchido caso o 'status' seja 3 (obrigatório).
//Utilizada na inserção de novos livros e na alteração de livros.
int validarCadastro(Livro* livro) {
    if (strlen(livro->codigoISBN) < 2) {
        printf("Erro: ISBN nao pode estar vazio.\n");
        return 0;
    }
    if (strlen(livro->titulo) < 2) {
        printf("Erro: Titulo nao pode estar vazio.\n");
        return 0;
    }
    if (strlen(livro->autor) < 2) {
        printf("Erro: Autor nao pode estar vazio.\n");
        return 0;
    }
    if (livro->genero < 1 || livro->genero > 8) {
        printf("Erro: Genero invalido. Deve ser entre 1 e 8.\n");
        return 0;
    }
    if (livro->avaliacao < 0 || livro->avaliacao > 5) {
        printf("Erro: Avaliacao invalida. Deve ser entre 0 e 5.\n");
        return 0;
    }
    if (livro->valor < 0) {
        printf("Erro: Valor do livro nao pode ser negativo.\n");
        return 0;
    }
    if (livro->status < 1 || livro->status > 4) {
        printf("Erro: Status invalido. Deve ser entre 1 e 4.\n");
        return 0;
    }
    if (livro->progressoLeitura < 1 || livro->progressoLeitura > 3) {
        printf("Erro: Progresso de leitura invalido. Deve ser entre 1 e 3.\n");
        return 0;
    }
    if (livro->status == 3 && strlen(livro->observacoes) < 2) {
        printf("Erro: Observacoes sao obrigatorias para livros emprestados.\n");
        return 0;
    }
    return 1;
}

//Função para solicitar os dados de um novo livro e inserir no acervo.
//Utilizada na segunda opção do menu principal.
void inserirCadastro() {
    if (totalLivros >= MAX_LIVROS) {
        printf("Erro: Acervo de livros esta cheio.\n");
        return;
    }

    Livro novoLivro;
    printf("\n--- INSERIR NOVO LIVRO ---\n");
    printf("Digite o ISBN: ");
    fgets(novoLivro.codigoISBN, MAX_STR, stdin);
    strtok(novoLivro.codigoISBN, "\n");

    printf("Digite o Titulo: ");
    fgets(novoLivro.titulo, MAX_STR, stdin);
    strtok(novoLivro.titulo, "\n");

    printf("Digite o Autor: ");
    fgets(novoLivro.autor, MAX_STR, stdin);
    strtok(novoLivro.autor, "\n");

    printf("Digite o Genero (1.romance, 2.suspense/terror, 3.fantasia, "
        "4.ficcao cientifica, 5.HQ/manga, 6.tecnicos/didaticos, 7.autoajuda, 8.outros): ");
    scanf("%d", &novoLivro.genero);

    printf("Digite a Avaliacao (0-5): ");
    scanf("%d", &novoLivro.avaliacao);

    printf("Digite o Valor (ex: 29.99): ");
    scanf("%f", &novoLivro.valor);

    printf("Digite o Status (1.disponivel, 2.doado, 3.emprestado, 4.inativado): ");
    scanf("%d", &novoLivro.status);

    printf("Digite o Progresso de Leitura (1.lido, 2.lendo, 3.nao lido): ");
    scanf("%d", &novoLivro.progressoLeitura);
    getchar();

    printf("Digite as Observacoes (obrigatorio se emprestado): ");
    fgets(novoLivro.observacoes, MAX_STR, stdin);
    strtok(novoLivro.observacoes, "\n");

    //Validar os dados antes de inserir.
    if (validarCadastro(&novoLivro)) {
        acervo[totalLivros] = (Livro*)malloc(sizeof(Livro));
        *acervo[totalLivros] = novoLivro; //Copiar os dados para a memória alocada.
        totalLivros++;
        salvarDados(); //Salvar as alterações a cada inserção.
        printf("\nLivro cadastrado com sucesso!\n");
        imprimirLivro(&novoLivro); //Imprimir livro automaticamente
    } else {
        printf("\nFalha no cadastro. Verifique os dados inseridos.\n");
    }
}

//Função para alterar os dados de um livro existente no acervo.
//Utilizada na terceira opção do menu principal.
void alterarCadastro() {
    char isbnBusca[MAX_STR];
    printf("\nDigite o ISBN do livro que deseja alterar: ");
    fgets(isbnBusca, MAX_STR, stdin);
    isbnBusca[strcspn(isbnBusca, "\n")] = 0; //Remove a quebra de linha

    int indice = -1;
    for (int i = 0; i < totalLivros; i++) {
        if (strcmp(acervo[i]->codigoISBN, isbnBusca) == 0) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("Livro com ISBN '%s' nao encontrado.\n", isbnBusca);
        return;
    }

    //Buffer temporário para ler todas as entradas do usuário como string.
    char buffer[MAX_STR];

    printf("\n--- ALTERANDO LIVRO: %s ---\n", acervo[indice]->titulo);
    printf("Se quiser manter o valor atual, apenas pressione Enter.\n\n");

    printf("Novo ISBN (atual: %s): ", acervo[indice]->codigoISBN);
    fgets(buffer, MAX_STR, stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Remove a quebra de linha
    if (strlen(buffer) > 0) { // Se o usuário digitou algo...
        strcpy(acervo[indice]->codigoISBN, buffer); // ...atualiza o campo.
    }

    printf("Novo Titulo (atual: %s): ", acervo[indice]->titulo);
    fgets(buffer, MAX_STR, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        strcpy(acervo[indice]->titulo, buffer);
    }

    printf("Novo Autor (atual: %s): ", acervo[indice]->autor);
    fgets(buffer, MAX_STR, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        strcpy(acervo[indice]->autor, buffer);
    }

    printf("Novo Genero (atual: %s) (1.romance, 2.suspense/terror, 3.fantasia, 4.ficcao cientifica, \n5.HQ/manga, 6.tecnicos/didaticos, 7.autoajuda, 8.outros): ", getGeneroString(acervo[indice]->genero));
    fgets(buffer, MAX_STR, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        acervo[indice]->genero = atoi(buffer); // atoi converte string para inteiro
    }

    printf("Nova Avaliacao (atual: %d): ", acervo[indice]->avaliacao);
    fgets(buffer, MAX_STR, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        acervo[indice]->avaliacao = atoi(buffer);
    }

    printf("Novo Valor (atual: %.2f): ", acervo[indice]->valor);
    fgets(buffer, MAX_STR, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        acervo[indice]->valor = atof(buffer); // atof converte string para float
    }

    printf("Novo Status (atual: %s) (1.disponivel, 2.doado, 3.emprestado, 4.inativado): ", getStatusString(acervo[indice]->status));
    fgets(buffer, MAX_STR, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        acervo[indice]->status = atoi(buffer);
    }

    printf("Novo Progresso de Leitura (atual: %s) (1.lido, 2.lendo, 3.nao lido): ", getProgressoString(acervo[indice]->progressoLeitura));
    fgets(buffer, MAX_STR, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        acervo[indice]->progressoLeitura = atoi(buffer);
    }

    printf("Novas Observacoes (atuais: %s): ", acervo[indice]->observacoes);
    fgets(buffer, MAX_STR, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
    if (strlen(buffer) > 0) {
        strcpy(acervo[indice]->observacoes, buffer);
    } else {
        //Se o usuário apagar as observações, o campo fica vazio, mas só se o livro não estiver emprestado.
        if (acervo[indice]->status != 3) {
            strcpy(acervo[indice]->observacoes, "");
        }
    }

    //Validar os dados após todas as possíveis alterações.
    //Passar o ponteiro para o livro original que foi modificado.
    if (validarCadastro(acervo[indice])) {
        salvarDados(); //Salvar as alterações no arquivo CSV.
        printf("\nCadastro alterado com sucesso!\n");
        imprimirLivro(acervo[indice]); //Mostrar o conteúdo final.
    } else {
        printf("\nFalha na alteracao. Verifique os dados inseridos.\n");
    }
}

//Função para tornar as funções de consultarLivro e listarLivro para "case-insensitive" (sem diferença entre maiúsculas e minúsculas).
void strToLower(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

//Função para buscar um livro por ISBN, Título ou Autor.
//Utilizada na quarta opção do menu principal.
void consultarLivro() {
    int opcao;
    char termoBusca[MAX_STR];
    printf("\n--- BUSCAR LIVRO POR ---\n");
    printf("1 - Codigo ISBN\n");
    printf("2 - Titulo\n");
    printf("3 - Autor\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    getchar();

    //Pedir o termo para a listagem.
    printf("Digite o termo de busca: ");
    fgets(termoBusca, MAX_STR, stdin);
    strtok(termoBusca, "\n");

    int encontrados = 0;
    printf("\n--- RESULTADOS DA BUSCA ---\n");

    char termoLower[MAX_STR];
    strcpy(termoLower, termoBusca);
    strToLower(termoLower);
    for (int i = 0; i < totalLivros; i++) {
        int achou = 0;
        char campoLower[MAX_STR];
        switch (opcao) {
            case 1:
                strcpy(campoLower, acervo[i]->codigoISBN);
                strToLower(campoLower);
                if (strcmp(campoLower, termoLower) == 0) achou = 1;
                break;
            case 2:
                strcpy(campoLower, acervo[i]->titulo);
                strToLower(campoLower);
                if (strstr(campoLower, termoLower) != NULL) achou = 1;
                break;
            case 3:
                strcpy(campoLower, acervo[i]->autor);
                strToLower(campoLower);
                if (strstr(campoLower, termoLower) != NULL) achou = 1;
                break;
            default:
                printf("Opcao invalida.\n");
            return;
        }
        //Imprimir o livro encontrado com o critério do usuário.
        if (achou) {
            imprimirLivro(acervo[i]);
            encontrados++;
        }
    }
    //Se não encontrou nenhum livro com o critério do usuário.
    if (encontrados == 0) {
        printf("Nenhum livro encontrado com o termo '%s'.\n", termoBusca);
    }
}

//Função para listar livros filtrando por Gênero, Avaliação, Status ou Progresso.
//Utilizada na quinta opção do menu principal.
void listarLivros() {
    int opcao;
    printf("\n--- LISTAR LIVROS POR ---\n");
    printf("1 - Genero (1.romance, 2.suspense/terror, 3.fantasia, "
        "4.ficcao cientifica, 5.HQ/manga, 6.tecnicos/didaticos, 7.autoajuda, 8.outros): \n");
    printf("2 - Avaliacao (0 a 5): \n");
    printf("3 - Status (1.disponivel, 2.doado, 3.emprestado, 4.inativado): \n");
    printf("4 - Progresso de Leitura (1.lido, 2.lendo, 3.nao lido): \n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    getchar();

    int filtro;
    int encontrados = 0;

    //Pedir o critério específico para a listagem.
    switch(opcao) {
        case 1: printf("Digite o genero (1-8): "); scanf("%d", &filtro); break;
        case 2: printf("Digite a avaliacao (0-5): "); scanf("%d", &filtro); break;
        case 3: printf("Digite o status (1-4): "); scanf("%d", &filtro); break;
        case 4: printf("Digite o progresso (1-3): "); scanf("%d", &filtro); break;
        default: printf("Opcao invalida.\n"); return;
    }

    printf("\n--- RESULTADOS DA LISTAGEM ---");
    for (int i = 0; i < totalLivros; i++) {
        int achou = 0;
        switch (opcao) {
            case 1: if (acervo[i]->genero == filtro) achou = 1; break;
            case 2: if (acervo[i]->avaliacao == filtro) achou = 1; break;
            case 3: if (acervo[i]->status == filtro) achou = 1; break;
            case 4: if (acervo[i]->progressoLeitura == filtro) achou = 1; break;
        }
        //Imprimir os livros encontrados com o critério do usuário.
        if (achou) {
            imprimirLivro(acervo[i]);
            encontrados++;
        }
    }
    //Se não encontrou nenhum livro com o critério do usuário.
    if (encontrados == 0) {
        printf("Nenhum livro encontrado com este criterio.\n");
    }
}