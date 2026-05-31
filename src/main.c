#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ABELHAS 50
#define MAX_SENSORES 100

typedef struct {
    int id;
    char tipo[30]; 
    float valor; 
    int idAbelha; 
} Sensor;

typedef struct {
    int id;
    char nomePopular[40];
    char nomeCientifico[50];
    char regiao[30];
    float producaoMel; 
} Abelha;

Abelha abelhas[MAX_ABELHAS];
int qtdAbelhas = 0;

Sensor sensores[MAX_SENSORES];
int qtdSensores = 0;

void menuAbelhas();
void cadastrarAbelha();
void listarAbelhas();
void buscarAbelha();
void alterarAbelha();
void removerAbelha();

void menuSensores();
void cadastrarSensor();
void listarSensores();
void buscarSensorPorAbelha();
void alterarLeituraSensor();
void removerSensor();

void menuRelatorios();
void relatorioMediaMel();
void relatorioMediaTemperatura();
void relatorioQuantidadePorRegiao();

void menuGenetica();
void simularCruzamento();
void buscaAvancadaGenetica();

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
            case 1: menuAbelhas(); break;
            case 2: menuSensores(); break;
            case 3: menuRelatorios(); break;
            case 4: menuGenetica(); break;
            case 5: printf("Encerrando o sistema...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcao != 5);

    return 0;
}

void menuAbelhas() {
    int op;
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
    }
}

void menuSensores() {
    int op;
    printf("\n--- Submenu 2 - Gerenciar Sensores ---\n");
    printf("1. Cadastrar sensor\n2. Listar sensores\n3. Buscar por ID da abelha\n4. Alterar leitura\n5. Remover\n6. Voltar\n");
    printf("Escolha: ");
    scanf("%d", &op); getchar();

    switch(op) {
        case 1: cadastrarSensor(); break;
        case 2: listarSensores(); break;
        case 3: buscarSensorPorAbelha(); break;
        case 4: alterarLeituraSensor(); break;
        case 5: removerSensor(); break;
    }
}

void menuRelatorios() {
    int op;
    printf("\n--- Submenu 3 - Relatorios ---\n");
    printf("1. Media geral de producao de mel\n2. Media de temperatura dos sensores\n3. Quantidade de abelhas por regiao\n4. Voltar\n");
    printf("Escolha: ");
    scanf("%d", &op); getchar();

    switch(op) {
        case 1: relatorioMediaMel(); break;
        case 2: relatorioMediaTemperatura(); break;
        case 3: relatorioQuantidadePorRegiao(); break;
    }
}

void menuGenetica() {
    int op;
    printf("\n--- Submenu 4 - BeeGen (Genetica) ---\n");
    printf("1. Simular Cruzamento de Especies\n2. Busca Avancada por Caracteristicas\n3. Voltar\n");
    printf("Escolha: ");
    scanf("%d", &op); getchar();

    switch(op) {
        case 1: simularCruzamento(); break;
        case 2: buscaAvancadaGenetica(); break;
    }
}

void cadastrarAbelha() { printf("Funcao em desenvolvimento...\n"); }
void listarAbelhas() { printf("Funcao em desenvolvimento...\n"); }
void buscarAbelha() { printf("Funcao em desenvolvimento...\n"); }
void alterarAbelha() { printf("Funcao em desenvolvimento...\n"); }
void removerAbelha() { printf("Funcao em desenvolvimento...\n"); }

void cadastrarSensor() { printf("Funcao em desenvolvimento...\n"); }
void listarSensores() { printf("Funcao em desenvolvimento...\n"); }
void buscarSensorPorAbelha() { printf("Funcao em desenvolvimento...\n"); }
void alterarLeituraSensor() { printf("Funcao em desenvolvimento...\n"); }
void removerSensor() { printf("Funcao em desenvolvimento...\n"); }

void relatorioMediaMel() { printf("Funcao em desenvolvimento...\n"); }
void relatorioMediaTemperatura() { printf("Funcao em desenvolvimento...\n"); }
void relatorioQuantidadePorRegiao() { printf("Funcao em desenvolvimento...\n"); }

void simularCruzamento() { printf("Funcao em desenvolvimento...\n"); }
void buscaAvancadaGenetica() { printf("Funcao em development...\n"); }
