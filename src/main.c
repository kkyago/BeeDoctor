#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ABELHAS 50
#define MAX_SENSORES 100

#define RESET    "\x1b[0m"
#define VERMELHO "\x1b[31m"
#define VERDE    "\x1b[32m"
#define AMARELO  "\x1b[33m"

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

typedef struct {
    int idSensor;
    int idAbelha;
    int tipo;
    float valor;
} Sensor;

Sensor sensores[MAX_SENSORES];
int qtdSensores = 0;
int proximoIdSensor = 1;

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

void salvarDados();
void carregarDados();
float lerFloatValido();

int main() {
    carregarDados();

    int opcao;

    do {
        printf("\n===== SISTEMA BEE MONITOR =====\n");
        printf("1. Gerenciar Abelhas\n");
        printf("2. Gerenciar Sensores\n");
        printf("3. Relatorios\n");
        printf("4. Diagnosticos\n");
        printf("5. Sair\n");
        printf("opcao: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) menuAbelhas();
        else if (opcao == 2) menuSensores();
        else if (opcao == 3) menuRelatorios();
        else if (opcao == 4) menuDiagnostico();
        else if (opcao == 5) {
            salvarDados();
            printf(VERDE "salvando e saindo...\n" RESET);
        }
        else printf(VERMELHO "opcao invalida\n" RESET);

    } while (opcao != 5);

    return 0;
}

void menuAbelhas() {
    int op;
    do {
        printf("\n--- Abelhas ---\n");
        printf("1. Cadastrar\n");
        printf("2. Listar\n");
        printf("3. Buscar por nome\n");
        printf("4. Alterar\n");
        printf("5. Remover\n");
        printf("6. Voltar\n");
        printf("Opcao: ");
        scanf("%d", &op);
        getchar();

        if (op == 1) cadastrarAbelha();
        else if (op == 2) listarAbelhas();
        else if (op == 3) buscarAbelha();
        else if (op == 4) alterarAbelha();
        else if (op == 5) removerAbelha();
        else if (op == 6) printf("Voltando...\n");
        else printf(VERMELHO "opcao invalida\n" RESET);

    } while (op != 6);
}

void cadastrarAbelha() {
    if (qtdAbelhas >= MAX_ABELHAS) {
        printf(VERMELHO "Nao da pra cadastrar mais abelhas\n" RESET);
        return;
    }

    printf("\n=== CADASTRAR ABELHA ===\n");

    abelhas[qtdAbelhas].id = proximoIdAbelha;
    proximoIdAbelha++;
    printf("id: %d\n", abelhas[qtdAbelhas].id);

    printf("Nome popular: ");
    fgets(abelhas[qtdAbelhas].nomePopular, 40, stdin);
    abelhas[qtdAbelhas].nomePopular[strcspn(abelhas[qtdAbelhas].nomePopular, "\n")] = '\0';

    printf("Nome cientifico: ");
    fgets(abelhas[qtdAbelhas].nomeCientifico, 50, stdin);
    abelhas[qtdAbelhas].nomeCientifico[strcspn(abelhas[qtdAbelhas].nomeCientifico, "\n")] = '\0';

    printf("Regiao: ");
    fgets(abelhas[qtdAbelhas].regiao, 30, stdin);
    abelhas[qtdAbelhas].regiao[strcspn(abelhas[qtdAbelhas].regiao, "\n")] = '\0';

    printf("Producao de mel (kg/mes): ");
    abelhas[qtdAbelhas].producaoMel = lerFloatValido();

    qtdAbelhas++;
    salvarDados();

    printf(VERDE "Cadastrado!\n" RESET);
}

void listarAbelhas() {
    if (qtdAbelhas == 0) {
        printf(AMARELO "Nenhuma abelha cadastrada\n" RESET);
        return;
    }

    printf("\n=== LISTA DE ABELHAS ===\n");

    for (int i = 0; i < qtdAbelhas; i++) {
        printf("\nID: %d\n", abelhas[i].id);
        printf("Nome popular: %s\n", abelhas[i].nomePopular);
        printf("Nome cientifico: %s\n", abelhas[i].nomeCientifico);
        printf("Regiao: %s\n", abelhas[i].regiao);
        printf("Mel: %.2f kg/mes\n", abelhas[i].producaoMel);
        printf("---\n");
    }

    printf("Total: %d\n", qtdAbelhas);
}

void buscarAbelha() {
    if (qtdAbelhas == 0) {
        printf(AMARELO "sem abelhas cadastradas\n" RESET);
        return;
    }

    char nome[40];
    int achou = 0;

    printf("\n=== BUSCAR ABELHA ===\n");
    printf("nome popular pra buscar: ");
    fgets(nome, 40, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < qtdAbelhas; i++) {
        if (strcmp(abelhas[i].nomePopular, nome) == 0) {
            printf(VERDE "\nachei:\n" RESET);
            printf("ID: %d\n", abelhas[i].id);
            printf("Nome popular: %s\n", abelhas[i].nomePopular);
            printf("Nome cientifico: %s\n", abelhas[i].nomeCientifico);
            printf("Regiao: %s\n", abelhas[i].regiao);
            printf("Mel: %.2f kg/mes\n", abelhas[i].producaoMel);
            printf("---\n");
            achou = 1;
        }
    }

    if (achou == 0) {
        printf(VERMELHO "Nao tem nenhuma abelha com esse nome\n" RESET);
    }
}

void alterarAbelha() {
    if (qtdAbelhas == 0) {
        printf(AMARELO "Sem abelhas pra alterar\n" RESET);
        return;
    }

    int id;
    int pos = -1;

    printf("\n=== ALTERAR ABELHA ===\n");
    printf("ID da abelha pra alterar: ");
    scanf("%d", &id);
    getchar();

    //percorre o vetor procurando a abelha
    for (int i = 0; i < qtdAbelhas; i++) {
        if (abelhas[i].id == id) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf(VERMELHO "ID %d nao existe\n" RESET, id);
        return;
    }

    printf("Alterando abelha %d\n", id);

    printf("Novo nome popular: ");
    fgets(abelhas[pos].nomePopular, 40, stdin);
    abelhas[pos].nomePopular[strcspn(abelhas[pos].nomePopular, "\n")] = '\0';

    printf("Novo nome cientifico: ");
    fgets(abelhas[pos].nomeCientifico, 50, stdin);
    abelhas[pos].nomeCientifico[strcspn(abelhas[pos].nomeCientifico, "\n")] = '\0';

    printf("Nova regiao: ");
    fgets(abelhas[pos].regiao, 30, stdin);
    abelhas[pos].regiao[strcspn(abelhas[pos].regiao, "\n")] = '\0';

    printf("Nova producao de mel: ");
    abelhas[pos].producaoMel = lerFloatValido();

    salvarDados();
    printf(VERDE "Alterado com sucesso\n" RESET);
}

void removerAbelha() {
    if (qtdAbelhas == 0) {
        printf(AMARELO "sem abelhas pra remover\n" RESET);
        return;
    }

    int id;
    int pos = -1;
    char conf;

    printf("\n=== REMOVER ABELHA ===\n");
    printf("ID da abelha pra remover: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < qtdAbelhas; i++) {
        if (abelhas[i].id == id) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf(VERMELHO "Nao tem ID %d cadastrado\n" RESET, id);
        return;
    }

    printf(AMARELO "Tem certeza que quer remover %s? (S/N): " RESET, abelhas[pos].nomePopular);
    scanf(" %c", &conf);
    getchar();

if (conf == 'S' || conf == 's') {

    // Remove todos os sensores vinculados a essa abelha
    for (int i = 0; i < qtdSensores; i++) {

        if (sensores[i].idAbelha == id) {

            for (int j = i; j < qtdSensores - 1; j++) {
                sensores[j] = sensores[j + 1];
            }

            qtdSensores--;
            i--;
        }
    }

    // empurra tudo uma posicao pra tras para nao ficar buraco no vetor
    for (int i = pos; i < qtdAbelhas - 1; i++) {
        abelhas[i] = abelhas[i + 1];
    }

    qtdAbelhas--;

    salvarDados();

    printf(VERDE "Abelha e sensores vinculados removidos!\n" RESET);
    
    } else {
        printf(AMARELO "Cancelado\n" RESET);
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
    int tipo;

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
        printf(VERMELHO "Abelha nao encontrada!\n" RESET);
        return;
    }

    printf("\nTipo do sensor:\n");
    printf("1 - Temperatura\n");
    printf("2 - Umidade\n");
    printf("3 - Luminosidade\n");
    printf("Opcao: ");
    scanf("%d", &tipo);
    getchar();

    if(tipo < 1 || tipo > 3) {
        printf(VERMELHO "Tipo invalido!\n" RESET);
        return;
    }

    sensores[qtdSensores].idSensor = proximoIdSensor++;
    sensores[qtdSensores].idAbelha = idAbelha;
    sensores[qtdSensores].tipo = tipo;

    printf("Valor da leitura: ");
    sensores[qtdSensores].valor = lerFloatValido();

    qtdSensores++;

    salvarDados();

    printf(VERDE "Sensor cadastrado com sucesso!\n" RESET);
}

void listarSensores() {
    if (qtdSensores == 0) {
        printf(AMARELO "\nNenhum sensor cadastrado.\n" RESET);
        return;
    }

    printf("\n=== LISTA DE SENSORES ===\n");

    for (int i = 0; i < qtdSensores; i++) {

        printf("\nSensor ID: %d\n", sensores[i].idSensor);
        printf("Abelha vinculada: %d\n", sensores[i].idAbelha);

        if (sensores[i].tipo == 1)
            printf("Tipo: Temperatura\n");
        else if (sensores[i].tipo == 2)
            printf("Tipo: Umidade\n");
        else
            printf("Tipo: Luminosidade\n");

        printf("Leitura: %.2f\n", sensores[i].valor);
    }
}

void buscarSensorPorAbelha() {
    int idAbelha;
    int encontrou = 0;

    printf("Digite o ID da abelha: ");
    scanf("%d", &idAbelha);
    getchar();

    for (int i = 0; i < qtdSensores; i++) {

        if (sensores[i].idAbelha == idAbelha) {

            printf("\nSensor ID: %d\n", sensores[i].idSensor);

            if (sensores[i].tipo == 1)
                printf("Tipo: Temperatura\n");
            else if (sensores[i].tipo == 2)
                printf("Tipo: Umidade\n");
            else
                printf("Tipo: Luminosidade\n");

            printf("Leitura: %.2f\n", sensores[i].valor);

            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf(VERMELHO "Nenhum sensor encontrado.\n" RESET);
    }
}

void alterarLeituraSensor() {
    int idSensor;
    int indice = -1;

    printf("ID do sensor: ");
    scanf("%d", &idSensor);
    getchar();

    for (int i = 0; i < qtdSensores; i++) {
        if (sensores[i].idSensor == idSensor) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf(VERMELHO "Sensor nao encontrado!\n" RESET);
        return;
    }

    printf("Nova leitura: ");
    sensores[indice].valor = lerFloatValido();

    salvarDados();

    printf(VERDE "Leitura atualizada!\n" RESET);
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
    salvarDados();

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

    float soma = 0;
    int quantidade = 0;

    for (int i = 0; i < qtdSensores; i++) {

        if (sensores[i].tipo == 1) {
            soma += sensores[i].valor;
            quantidade++;
        }
    }

    if (quantidade == 0) {
        printf(AMARELO "Nao existem sensores de temperatura.\n" RESET);
        return 0;
    }

    float media = soma / quantidade;

    printf("\nMedia de temperatura: %.2f C\n", media);

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
        if (sensores[i].tipo == 1)
        temp = sensores[i].valor;

        if (sensores[i].tipo == 2)
        umid = sensores[i].valor;
            encontrado = 1;
            break;
        }
    }
    
    if(!encontrado) {
        printf(AMARELO "\nSem sensor para esta colonia! Insira os dados manuais:" RESET "\n");
        printf("Digite temperatura: ");
        temp = lerFloatValido(); 
        printf("Digite umidade: ");
        umid = lerFloatValido(); 
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

void salvarDados() {
    FILE *arq = fopen("dados_sistema.dat", "wb");
    if (arq == NULL) {
        return;
    }

    //salva as abelhas
    fwrite(&qtdAbelhas, sizeof(int), 1, arq);
    fwrite(&proximoIdAbelha, sizeof(int), 1, arq);
    fwrite(abelhas, sizeof(Abelha), qtdAbelhas, arq);

    //salva os sensores
    fwrite(&qtdSensores, sizeof(int), 1, arq);
    fwrite(&proximoIdSensor, sizeof(int), 1, arq);
    fwrite(sensores, sizeof(Sensor), qtdSensores, arq);

    fclose(arq);
}

void carregarDados() {
    FILE *arq = fopen("dados_sistema.dat", "rb");
    if (arq == NULL) {
        return; //se nao tem arquivo nao faz nada
    }

    fread(&qtdAbelhas, sizeof(int), 1, arq);
    fread(&proximoIdAbelha, sizeof(int), 1, arq);
    fread(abelhas, sizeof(Abelha), qtdAbelhas, arq);

    fread(&qtdSensores, sizeof(int), 1, arq);
    fread(&proximoIdSensor, sizeof(int), 1, arq);
    fread(sensores, sizeof(Sensor), qtdSensores, arq);

    fclose(arq);
}

float lerFloatValido() {
    float valor;
    char c;

    //fica tentando ate o usuario digitar um numero
    while (scanf("%f", &valor) != 1) {
        printf(VERMELHO "Digite apenas numeros: " RESET);
        while ((c = getchar()) != '\n' && c != EOF);
    }
    getchar();
    return valor;
}
