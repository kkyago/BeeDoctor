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

#define MAX_SENSORES 50

typedef struct {
    int idSensor;
    int idAbelha;
    float temperatura;
    float umidade;
} Sensor;

Sensor sensores[MAX_SENSORES];
int qtdSensores = 0;
int proximoIdSensor = 1;

#define RESET    "\x1b[0m"
#define VERMELHO "\x1b[31m"
#define VERDE    "\x1b[32m"
#define AMARELO  "\x1b[33m"

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
float memel();
float relatoriosensores();
void abelhasPorRegiao();

void menuDiagnostico();
void realizardiagnostico();
void recomendarTratamento(float temp, float umid);

int main() {
    int opcao;

    do {
        printf("\n===== SISTEMA BEE MONITOR =====\n");
        printf("1. Gerenciar Abelhas\n");
        printf("2. Gerenciar Sensores\n");
        printf("3. Relatorios\n");
        printf("4. Desafio BeeDoctor (Diagnostico)\n"); 
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); 

        switch(opcao) {
            case 1: 
                menuAbelhas(); 
                break;
            case 2: 
                menuSensores(); 
                break;
            case 3: 
                menuRelatorios();
                break;
            case 4: 
                menuDiagnostico(); 
                break;
            case 5: 
                printf("Encerrando o sistema...\n"); 
                break;
            default: 
                printf(VERMELHO "Opcao invalida!" RESET "\n");
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
            default: printf(VERMELHO "Opcao invalida!" RESET "\n");
        }
    } while(op != 6); 
}

void cadastrarAbelha() {
    if (qtdAbelhas >= MAX_ABELHAS) {
        printf(VERMELHO "\nErro: Limite maximo de abelhas cadastradas atingido!" RESET "\n");
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

    printf(VERDE "\nAbelha cadastrada com sucesso!" RESET "\n");
}

void listarAbelhas() {
    if (qtdAbelhas == 0) {
        printf(AMARELO "\nNenhuma abelha cadastrada no sistema ate o momento." RESET "\n");
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
        printf(AMARELO "\nNenhuma abelha cadastrada no sistema." RESET "\n");
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
            printf(VERDE "\nAbelha Encontrada:" RESET "\n");
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
        printf(VERMELHO "\nNenhuma abelha encontrada com o nome \"%s\"." RESET "\n", termoBusca);
    }
}

void alterarAbelha() {
    if (qtdAbelhas == 0) {
        printf(AMARELO "\nNenhuma abelha cadastrada para alterar." RESET "\n");
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
        printf(VERMELHO "\nErro: Abelha com ID %d nao encontrada." RESET "\n", idBusca);
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

    printf(VERDE "\nDados alterados com sucesso!" RESET "\n");
}

void removerAbelha() {
    if (qtdAbelhas == 0) {
        printf(AMARELO "\nNenhuma abelha cadastrada para remover." RESET "\n");
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
        printf(VERMELHO "\nErro: Abelha com ID %d nao encontrada." RESET "\n", idBusca);
        return;
    }

    printf(AMARELO "Deseja realmente remover a abelha %s? (S/N): " RESET, abelhas[indiceEncontrado].nomePopular);
    scanf(" %c", &confirmacao);
    getchar();

    if (confirmacao == 'S' || confirmacao == 's') {
        for (int i = indiceEncontrado; i < qtdAbelhas - 1; i++) {
             abelhas[i] = abelhas[i + 1];
        }

        qtdAbelhas--;

        printf(VERDE "\nRegistro removido e vetor reorganizado com sucesso!" RESET "\n");
    } else {
        printf(AMARELO "\nOperacao cancelada." RESET "\n");
    }
}

void menuSensores() {
    int op;
    do {
        printf("\n--- GERENCIAR SENSORES ---\n");
        printf("1. Cadastrar sensor\n");
        printf("2. Listar sensores\n");
        printf("3. Buscar sensor por abelha\n");
        printf("4. Alterar leitura\n");
        printf("5. Remover sensor\n");
        printf("6. Voltar\n");
        printf("Opcao: ");

        scanf("%d", &op);
        getchar();

        switch(op) {
            case 1: cadastrarSensor(); break;
            case 2: listarSensores(); break;
            case 3: buscarSensorPorAbelha(); break;
            case 4: alterarLeituraSensor(); break;
            case 5: removerSensor(); break;
            case 6: printf("Voltando ao menu principal...\n"); break;
            default: printf(VERMELHO "Opcao invalida!" RESET "\n");
        }
    } while(op != 6);
}

void cadastrarSensor() {
    if (qtdSensores >= MAX_SENSORES) {
        printf(VERMELHO "\nLimite de sensores atingido!" RESET "\n");
        return;
    }

    int idAbelha;
    int existe = 0;

    printf("\n=== CADASTRAR SENSOR ===\n");
    printf("Informe o ID da abelha vinculada: ");
    scanf("%d", &idAbelha);
    getchar();

    for (int i = 0; i < qtdAbelhas; i++) {
        if (abelhas[i].id == idAbelha) {
            existe = 1;
            break;
        }
    }

    if (!existe) {
        printf(VERMELHO "\nErro: nao existe abelha com ID %d." RESET "\n", idAbelha);
        return;
    }

    sensores[qtdSensores].idSensor = proximoIdSensor++;
    sensores[qtdSensores].idAbelha = idAbelha;
    
    printf("Temperatura: ");
    scanf("%f", &sensores[qtdSensores].temperatura);

    printf("Umidade: ");
    scanf("%f", &sensores[qtdSensores].umidade);
    getchar();

    qtdSensores++;

    printf(VERDE "\nSensor cadastrado com sucesso!" RESET "\n");
}

void listarSensores() {
    if (qtdSensores == 0) {
        printf(AMARELO "\nNenhum sensor cadastrado." RESET "\n");
        return;
    }

    printf("\n=== LISTA DE SENSORES ===\n");

    for (int i = 0; i < qtdSensores; i++) {
        printf("\nSensor ID: %d\n", sensores[i].idSensor);
        printf("Abelha vinculada: %d\n", sensores[i].idAbelha);
        printf("Temperatura: %.2f C\n", sensores[i].temperatura);
        printf("Umidade: %.2f %%\n", sensores[i].umidade);
    }
}

void buscarSensorPorAbelha() {
    if (qtdSensores == 0) {
        printf(AMARELO "\nNenhum sensor cadastrado." RESET "\n");
        return;
    }

    int idAbelha;
    int encontrou = 0;

    printf("\nDigite o ID da abelha: ");
    scanf("%d", &idAbelha);
    getchar();

    for (int i = 0; i < qtdSensores; i++) {
        if (sensores[i].idAbelha == idAbelha) {
            printf("\nSensor ID: %d\n", sensores[i].idSensor);
            printf("Temperatura: %.2f C\n", sensores[i].temperatura);
            printf("Umidade: %.2f %%\n", sensores[i].umidade);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf(VERMELHO "\nNenhum sensor encontrado para essa abelha." RESET "\n");
    }
}

void alterarLeituraSensor() {
    if (qtdSensores == 0) {
        printf(AMARELO "\nNenhum sensor cadastrado." RESET "\n");
        return;
    }

    int idSensor;
    int indice = -1;

    printf("\nDigite o ID do sensor: ");
    scanf("%d", &idSensor);
    getchar();

    for (int i = 0; i < qtdSensores; i++) {
        if (sensores[i].idSensor == idSensor) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf(VERMELHO "\nSensor nao encontrado." RESET "\n");
        return;
    }

    printf("Nova temperatura: ");
    scanf("%f", &sensores[indice].temperatura);

    printf("Nova umidade: ");
    scanf("%f", &sensores[indice].umidade);
    getchar();

    printf(VERDE "\nLeituras atualizadas com sucesso!" RESET "\n");
}

void removerSensor() {
    if (qtdSensores == 0) {
        printf(AMARELO "\nNenhum sensor cadastrado." RESET "\n");
        return;
    }

    int idSensor;
    int indice = -1;

    printf("\nDigite o ID do sensor a remover: ");
    scanf("%d", &idSensor);
    getchar();

    for (int i = 0; i < qtdSensores; i++) {
        if (sensores[i].idSensor == idSensor) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf(VERMELHO "\nSensor nao encontrado." RESET "\n");
        return;
    }

    for (int i = indice; i < qtdSensores - 1; i++) {
        sensores[i] = sensores[i + 1];
    }

    qtdSensores--;

    printf(VERDE "\nSensor removido e vetor reorganizado com sucesso!" RESET "\n");
}

void menuRelatorios() {
    int opcao;
    do {
        printf("\n--- Submenu 3 - Relatorios ---\n");
        printf("1. Media geral de producao de mel\n");
        printf("2. Media de temperatura dos sensores\n");
        printf("3. Quantidade de abelhas por regiao\n");
        printf("4. Voltar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1: memel();             break;
            case 2: relatoriosensores(); break;
            case 3: abelhasPorRegiao();  break;
            case 4: printf("Voltando ao menu principal...\n"); break;
            default: printf(VERMELHO "Opcao invalida!" RESET "\n");
        }
    } while(opcao != 4);
}

float memel() {
    if (qtdAbelhas == 0) {
        printf(AMARELO "\nNenhuma abelha cadastrada." RESET "\n");
        return 0;
    }

    float somamel = 0;

    for (int i = 0; i < qtdAbelhas; i++) {
        somamel += abelhas[i].producaoMel;
    }

    float resultado = somamel / qtdAbelhas;

    printf("\n=== RELATORIO: MEDIA DE PRODUCAO DE MEL ===\n");
    printf("Total de abelhas:  %d\n", qtdAbelhas);
    printf("Soma total:        %.2f kg/mes\n", somamel);
    printf("Media geral:       " VERDE "%.2f kg/mes" RESET "\n", resultado);

    return resultado;
}

float relatoriosensores() {
    if (qtdSensores == 0) {
        printf(AMARELO "\nNenhum sensor cadastrado." RESET "\n");
        return 0;
    }

    float somadetemperatura = 0;

    for (int i = 0; i < qtdSensores; i++) {
        somadetemperatura += sensores[i].temperatura;
    }

    float media = somadetemperatura / qtdSensores;

    printf("\n=== RELATORIO: MEDIA DE TEMPERATURA ===\n");
    printf("Total de sensores:    %d\n", qtdSensores);
    printf("Media de temperatura: " VERDE "%.2f C" RESET "\n", media);

    return media;
}

void abelhasPorRegiao() {
    if (qtdAbelhas == 0) {
        printf(AMARELO "\nNenhuma abelha cadastrada." RESET "\n");
        return;
    }

    char regioes[MAX_ABELHAS][30];
    int contagens[MAX_ABELHAS];
    int totalRegioes = 0;

    for (int i = 0; i < qtdAbelhas; i++) {
        int encontrou = 0;

        for (int j = 0; j < totalRegioes; j++) {
            if (strcmp(regioes[j], abelhas[i].regiao) == 0) {
                contagens[j]++; 
                encontrou = 1;
                break;
            }
        }

        if (!encontrou) {
            strcpy(regioes[totalRegioes], abelhas[i].regiao);
            contagens[totalRegioes] = 1;
            totalRegioes++;
        }
    }

    printf("\n=== RELATORIO: ABELHAS POR REGIAO ===\n");
    printf("%-20s | %s\n", "Regiao", "Qtd de Abelhas");
    printf("--------------------------------\n");
    for (int i = 0; i < totalRegioes; i++) {
        printf("%-20s | " VERDE "%d" RESET "\n", regioes[i], contagens[i]);
    }
    printf("--------------------------------\n");
    printf("Total de regioes distintas: %d\n", totalRegioes);
}

void menuDiagnostico() {
    int op;
    do {
        printf("\n=== BEE DOCTOR ===\n");
        printf("1. Diagnosticar colonia\n");
        printf("2. Voltar\n");
        printf("Opcao: ");
        scanf("%d", &op);
        getchar();
        
        if(op == 1) realizardiagnostico();
    } while(op != 2);
}

void realizardiagnostico() {
    if(qtdAbelhas == 0) {
        printf(VERMELHO "\nNenhuma abelha cadastrada!" RESET "\n");
        return;
    }
    
    int id;
    float temp, umid;
    int encontrado = 0;
    
    printf("\nColonias disponiveis:\n");
    for(int i = 0; i < qtdAbelhas; i++) {
        printf("ID: %d - %s\n", abelhas[i].id, abelhas[i].nomePopular);
    }
    
    printf("\nDigite o ID da colonia: ");
    scanf("%d", &id);
    getchar();
    
    for(int i = 0; i < qtdSensores; i++) {
        if(sensores[i].idAbelha == id) {
            temp = sensores[i].temperatura;
            umid = sensores[i].umidade;
            encontrado = 1;
            break;
        }
    }
    
    if(!encontrado) {
        printf(AMARELO "\nSem sensor para esta colonia! Insira os dados manuais:" RESET "\n");
        printf("Digite temperatura: ");
        scanf("%f", &temp);
        printf("Digite umidade: ");
        scanf("%f", &umid);
        getchar();
    } else {
        printf("\nTemperatura: %.1fC | Umidade: %.1f%%\n", temp, umid);
    }
    
    printf("\n=== DIAGNOSTICO ===\n");
    
    if(temp < 32 || temp > 36) {
        printf(VERMELHO "ALERTA: Temperatura inadequada (ideal: 32-36C)" RESET "\n");
        if(temp < 32) printf("   -> Colonia muito fria\n");
        else printf("   -> Colonia muito quente\n");
    } else {
        printf(VERDE "Temperatura OK" RESET "\n");
    }
    
    if(umid < 50 || umid > 80) {
        printf(VERMELHO "ALERTA: Umidade inadequada (ideal: 50-80%%)" RESET "\n");
        if(umid < 50) printf("   -> Ambiente muito seco\n");
        else printf("   -> Ambiente muito umido\n");
    } else {
        printf(VERDE "Umidade OK" RESET "\n");
    }
    
    if((temp < 30 && umid > 80) || (temp > 35 && umid > 80)) {
        printf(VERMELHO "CRITICO: Combinacao de temperatura e umidade ruim!" RESET "\n");
    }
    
    if(temp >= 32 && temp <= 36 && umid >= 50 && umid <= 80) {
        printf(VERDE "\nCOLONIA SAUDAVEL!" RESET "\n");
    } else {
        printf(VERMELHO "\nNECESSITA ATENCAO!" RESET "\n");
    }
    
    recomendarTratamento(temp, umid);

    printf("\nPressione ENTER...");
    getchar();
}
void recomendarTratamento(float temp, float umid) {
    printf("\n=== RECOMENDACOES BEE DOCTOR ===\n");

    if (temp >= 32 && temp <= 36 && umid >= 50 && umid <= 80) {
        printf(VERDE "COLONIA SAUDAVEL" RESET "\n");
        printf("- Manter monitoramento periodico.\n");
        printf("- Continuar manejo atual.\n");
        printf("- Realizar inspecoes preventivas.\n");
    }

    if (temp < 32) {
        printf(AMARELO "PROBLEMA: TEMPERATURA BAIXA" RESET "\n");
        printf("- Melhorar isolamento da colmeia.\n");
        printf("- Evitar ventos fortes.\n");
        printf("- Monitorar temperatura diariamente.\n");
    }

    if (temp > 36) {
        printf(AMARELO "PROBLEMA: TEMPERATURA ELEVADA" RESET "\n");
        printf("- Instalar sombra sobre a colmeia.\n");
        printf("- Melhorar ventilacao.\n");
        printf("- Disponibilizar agua para resfriamento.\n");
    }

    if (umid < 50) {
        printf(AMARELO "PROBLEMA: BAIXA UMIDADE" RESET "\n");
        printf("- Verificar disponibilidade de agua.\n");
        printf("- Evitar exposicao excessiva ao sol.\n");
        printf("- Acompanhar as proximas leituras.\n");
    }

    if (umid > 80) {
        printf(AMARELO "PROBLEMA: UMIDADE ELEVADA" RESET "\n");
        printf("- Melhorar drenagem do local.\n");
        printf("- Aumentar ventilacao da colmeia.\n");
        printf("- Verificar possivel aparecimento de fungos.\n");
    }

    if ((temp < 30 && umid > 80) || (temp > 35 && umid > 80)) {
        printf(VERMELHO "ALERTA CRITICO" RESET "\n");
        printf("- Realizar inspecao urgente da colonia.\n");
        printf("- Corrigir temperatura e umidade imediatamente.\n");
        printf("- Avaliar riscos de doencas e perda da colonia.\n");
    }

    printf("\n=================================\n");
}