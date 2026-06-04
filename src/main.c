#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ABELHAS 50

typedef struct {
    int id;
    char nomePopular[40];
    char nomeCientifico[50];
    char regiao[30];
    float producaoMel; 
} Abelha;

Abelha abelhas[MAX_ABELHAS];
int qtdAbelhas = 0;
int proximoIdAbelha = 1;

void menuAbelhas();
void cadastrarAbelha();
void listarAbelhas();
void buscarAbelha();
void alterarAbelha();
void removerAbelha();

int main() {
    int opcao;

    do {
        printf("\n===== SISTEMA BEE MONITOR =====\n");
        printf("1. Gerenciar Abelhas\n");
        printf("2. Gerenciar Sensores\n");
        printf("3. Relatorios\n");
        printf("4. Desafio BeeGen (Genetica)\n"); 
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); 

        switch(opcao) {
            case 1: 
                menuAbelhas(); 
                break;
            case 2: 
                printf("\nOpcao em desenvolvimento pelo Membro 2...\n"); 
                break;
            case 3: 
                printf("\nOpcao em desenvolvimento pelo Membro 3...\n"); 
                break;
            case 4: 
                printf("\nOpcao em desenvolvimento pelos Membros 4 e 5...\n"); 
                break;
            case 5: 
                printf("Encerrando o sistema...\n"); 
                break;
            default: 
                printf("Opcao invalida!\n");
        }
    } while(opcao != 5);

    return 0;
}

void menuAbelhas() {
    int op;
    do {
        printf("\n--- Submenu 1 - Gerenciar Abelhas ---\n");
        printf("1. Cadastrar abelha\n2. Listar todas\n3. Buscar por nome popular\n4. Alterar dados\n5. Remover\n6. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op); getchar();
        
        switch(op) {
            case 1: cadastrarAbelha(); break;
            case 2: listarAbelhas(); break;
            case 3: buscarAbelha(); break;
            case 4: alterarAbelha(); break;
            case 5: removerAbelha(); break;
            case 6: printf("Voltando ao menu principal...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while(op != 6); 
}

void cadastrarAbelha() {
    if (qtdAbelhas >= MAX_ABELHAS) {
        printf("\nErro: Limite maximo de abelhas cadastradas atingido!\n");
        return;
    }

    printf("\n=== CADASTRAR NOVA ABELHA ===\n");

    abelhas[qtdAbelhas].id = proximoIdAbelha;
    proximoIdAbelha++;
    printf("ID gerado automaticamente: %d\n", abelhas[qtdAbelhas].id);

    printf("Digite o nome popular: ");
    fgets(abelhas[qtdAbelhas].nomePopular, 40, stdin);
    abelhas[qtdAbelhas].nomePopular[strcspn(abelhas[qtdAbelhas].nomePopular, "\n")] = '\0';

    printf("Digite o nome cientifico: ");
    fgets(abelhas[qtdAbelhas].nomeCientifico, 50, stdin);
    abelhas[qtdAbelhas].nomeCientifico[strcspn(abelhas[qtdAbelhas].nomeCientifico, "\n")] = '\0';

    printf("Digite a regiao: ");
    fgets(abelhas[qtdAbelhas].regiao, 30, stdin);
    abelhas[qtdAbelhas].regiao[strcspn(abelhas[qtdAbelhas].regiao, "\n")] = '\0';

    printf("Digite a producao media de mel (kg/mes): ");
    scanf("%f", &abelhas[qtdAbelhas].producaoMel);
    getchar(); 

    qtdAbelhas++;

    printf("\nAbelha cadastrada com sucesso!\n");
}

void listarAbelhas() {
    if (qtdAbelhas == 0) {
        printf("\nNenhuma abelha cadastrada no sistema ate o momento.\n");
        return;
    }

    printf("\n=== LISTA DE ABELHAS CADASTRADAS ===\n");
    printf("----------------------------------------------------------------------\n");
    printf("%-4s | %-15s | %-20s | %-15s | %-10s\n", "ID", "Nome Popular", "Nome Cientifico", "Regiao", "Prod. Mel");
    printf("----------------------------------------------------------------------\n");

    for (int i = 0; i < qtdAbelhas; i++) {
        printf("%-4d | %-15s | %-20s | %-15s | %-10.2f kg/mes\n", 
               abelhas[i].id, 
               abelhas[i].nomePopular, 
               abelhas[i].nomeCientifico, 
               abelhas[i].regiao, 
               abelhas[i].producaoMel);
    }
    printf("----------------------------------------------------------------------\n");
    printf("Total de registros: %d\n", qtdAbelhas);
}

void buscarAbelha() {
    if (qtdAbelhas == 0) {
        printf("\nNenhuma abelha cadastrada no sistema.\n");
        return;
    }

    char termoBusca[40];
    int encontrado = 0;

    printf("\n=== BUSCAR ABELHA POR NOME POPULAR ===\n");
    printf("Digite o nome popular para buscar: ");
    fgets(termoBusca, 40, stdin);
    termoBusca[strcspn(termoBusca, "\n")] = '\0'; 

    for (int i = 0; i < qtdAbelhas; i++) {
        if (strcmp(abelhas[i].nomePopular, termoBusca) == 0) {
            printf("\nAbelha Encontrada:\n");
            printf("ID: %d\n", abelhas[i].id);
            printf("Nome Popular: %s\n", abelhas[i].nomePopular);
            printf("Nome Cientifico: %s\n", abelhas[i].nomeCientifico);
            printf("Regiao: %s\n", abelhas[i].regiao);
            printf("Producao de Mel: %.2f kg/mes\n", abelhas[i].producaoMel);
            printf("---------------------------\n");
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("\nNenhuma abelha encontrada com o nome \"%s\".\n", termoBusca);
    }
}

void alterarAbelha() {
    if (qtdAbelhas == 0) {
        printf("\nNenhuma abelha cadastrada para alterar.\n");
        return;
    }

    int idBusca;
    int indiceEncontrado = -1;

    printf("\n=== ALTERAR DADOS DA ABELHA ===\n");
    printf("Digite o ID da abelha que deseja alterar: ");
    scanf("%d", &idBusca);
    getchar(); 

    for (int i = 0; i < qtdAbelhas; i++) {
        if (abelhas[i].id == idBusca) {
            indiceEncontrado = i;
            break;
        }
    }

    if (indiceEncontrado == -1) {
        printf("\nErro: Abelha com ID %d nao encontrada.\n", idBusca);
        return;
    }

    printf("\nEditando a abelha de ID %d:\n", idBusca);

    printf("Novo Nome Popular (Atual: %s): ", abelhas[indiceEncontrado].nomePopular);
    fgets(abelhas[indiceEncontrado].nomePopular, 40, stdin);
    abelhas[indiceEncontrado].nomePopular[strcspn(abelhas[indiceEncontrado].nomePopular, "\n")] = '\0';

    printf("Novo Nome Cientifico (Atual: %s): ", abelhas[indiceEncontrado].nomeCientifico);
    fgets(abelhas[indiceEncontrado].nomeCientifico, 50, stdin);
    abelhas[indiceEncontrado].nomeCientifico[strcspn(abelhas[indiceEncontrado].nomeCientifico, "\n")] = '\0';

    printf("Nova Regiao (Atual: %s): ", abelhas[indiceEncontrado].regiao);
    fgets(abelhas[indiceEncontrado].regiao, 30, stdin);
    abelhas[indiceEncontrado].regiao[strcspn(abelhas[indiceEncontrado].regiao, "\n")] = '\0';

    printf("Nova Producao Media de Mel (Atual: %.2f): ", abelhas[indiceEncontrado].producaoMel);
    scanf("%f", &abelhas[indiceEncontrado].producaoMel);
    getchar(); 

    printf("\nDados alterados com sucesso!\n");
}

void removerAbelha() {
    if (qtdAbelhas == 0) {
        printf("\nNenhuma abelha cadastrada para remover.\n");
        return;
    }

    int idBusca;
    int indiceEncontrado = -1;
    char confirmacao;

    printf("\n=== REMOVER REGISTRO DE ABELHA ===\n");
    printf("Digite o ID da abelha que deseja remover: ");
    scanf("%d", &idBusca);
    getchar(); 

    for (int i = 0; i < qtdAbelhas; i++) {
        if (abelhas[i].id == idBusca) {
            indiceEncontrado = i;
            break;
        }
    }

    if (indiceEncontrado == -1) {
        printf("\nErro: Abelha com ID %d nao encontrada.\n", idBusca);
        return;
    }

    printf("Deseja realmente remover a abelha %s? (S/N): ", abelhas[indiceEncontrado].nomePopular);
    scanf("%c", &confirmacao);
    getchar();

    if (confirmacao == 'S' || confirmacao == 's') {
        for (int i = indiceEncontrado; i < qtdAbelhas - 1; i++) {
            abelhas[i] = abelhas[i + 1];
        }

        qtdAbelhas--;

        printf("\nRegistro removido e vetor reorganizado com sucesso!\n");
    } else {
        printf("\nOperacao cancelada.\n");
    }
}