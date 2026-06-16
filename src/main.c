#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ABELHAS 50
#define MAX_SENSORES 100

#define RESET    "\x1b[0m"
#define VERMELHO "\x1b[31m"
#define VERDE    "\x1b[32m"
#define AMARELO  "\x1b[33m"
#define ROXO     "\x1b[35m"

//struct que define o tipo Abelha, agrupando todos os dados de uma abelha em uma unica estrutura
typedef struct {
    int id;
    char nomePopular[40];
    char nomeCientifico[50];
    char regiao[30];
    float producaoMel;
} Abelha;

//vetor global que armazena todas as abelhas cadastradas, com capacidade maxima definida por MAX_ABELHAS
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

float lerFloatValido();

//funcao principal, ponto de entrada do programa
int main() {
    int opcao;

    do {
        system("cls"); //limpa a tela a cada iteracao para manter a interface organizada
        printf("\n" ROXO "===== SISTEMA BEE MONITOR =====" RESET "\n");
        printf("1. Gerenciar Abelhas\n");
        printf("2. Gerenciar Sensores\n");
        printf("3. Relatorios\n");
        printf("4. Diagnosticos\n");
        printf("5. Sair\n");
        printf("opcao: ");
        scanf("%d", &opcao);
        getchar(); //consome o '\n' que sobra no buffer apos o scanf, evitando que o proximo fgets leia uma linha vazia

        if (opcao == 1) menuAbelhas();
        else if (opcao == 2) menuSensores();
        else if (opcao == 3) menuRelatorios();
        else if (opcao == 4) menuDiagnostico();
        else if (opcao == 5) {
            printf(VERDE "Saindo...\n" RESET);
        }
        else {
            printf(VERMELHO "opcao invalida\n" RESET);
            printf("\nPressione ENTER para continuar...");
            getchar();
        }

    } while (opcao != 5); //o loop continua ate o usuario digitar 5 para sair

    return 0;
}

//submenu de abelhas que chama as funcoes do CRUD
void menuAbelhas() {
    int op;
    do {
        system("cls");
        printf("\n" ROXO "--- Abelhas ---" RESET "\n");
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
        else {
            printf(VERMELHO "opcao invalida\n" RESET);
            printf("\nPressione ENTER para continuar...");
            getchar();
        }

    } while (op != 6);
}

//funcao para cadastrar uma nova abelha no vetor global
void cadastrarAbelha() {
    system("cls");
    //verifica se o vetor ja atingiu o limite
    if (qtdAbelhas >= MAX_ABELHAS) {
        printf(VERMELHO "Nao da pra cadastrar mais abelhas\n" RESET);
        printf("\nPressione ENTER para voltar...");
        getchar();
        return;
    }

    printf("\n" ROXO "=== CADASTRAR ABELHA ===" RESET "\n");

    //atribui o proximo ID disponivel a nova abelha e ja incrementa o contador
    abelhas[qtdAbelhas].id = proximoIdAbelha;
    proximoIdAbelha++;
    printf("id: %d\n", abelhas[qtdAbelhas].id);

    printf("Nome popular: ");
    //fgets e usado aqui pois aceita espacos no meio do texto
    fgets(abelhas[qtdAbelhas].nomePopular, 40, stdin);
    //strcspn substitui o "\n" que o fgets coloca no final da string por "\0" caractere nulo
    abelhas[qtdAbelhas].nomePopular[strcspn(abelhas[qtdAbelhas].nomePopular, "\n")] = '\0';

    printf("Nome cientifico: ");
    fgets(abelhas[qtdAbelhas].nomeCientifico, 50, stdin);
    abelhas[qtdAbelhas].nomeCientifico[strcspn(abelhas[qtdAbelhas].nomeCientifico, "\n")] = '\0';

    printf("Regiao: ");
    fgets(abelhas[qtdAbelhas].regiao, 30, stdin);
    abelhas[qtdAbelhas].regiao[strcspn(abelhas[qtdAbelhas].regiao, "\n")] = '\0';

    printf("Producao de mel (kg/mes): ");
    abelhas[qtdAbelhas].producaoMel = lerFloatValido(); //garante que so sera aceito um numero valido

    //no final de tudo incrementa a variavel da proxima abelha
    qtdAbelhas++;

    printf(VERDE "Cadastrado!\n" RESET);
    printf("\nPressione ENTER para voltar...");
    getchar();
}

//percorre o vetor das abelhas e imprime os dados de todas as abelhas cadastradas
void listarAbelhas() {
    system("cls");
    //verifica se ha abelhas antes de tentar listar, evitando exibir uma lista vazia sem aviso
    if (qtdAbelhas == 0) {
        printf(AMARELO "Nenhuma abelha cadastrada\n" RESET);
        printf("\nPressione ENTER para voltar...");
        getchar();
        return;
    }

    printf("\n" ROXO "=== LISTA DE ABELHAS ===" RESET "\n");

    //loop que percorre o vetor
    for (int i = 0; i < qtdAbelhas; i++) {
        printf("\nID: %d\n", abelhas[i].id);
        printf("Nome popular: %s\n", abelhas[i].nomePopular);
        printf("Nome cientifico: %s\n", abelhas[i].nomeCientifico);
        printf("Regiao: %s\n", abelhas[i].regiao);
        printf("Mel: %.2f kg/mes\n", abelhas[i].producaoMel);
        printf("---\n");
    }

    printf("Total: %d\n", qtdAbelhas);
    printf("\nPressione ENTER para voltar...");
    getchar();
}

void buscarAbelha() {
    system("cls");
    if (qtdAbelhas == 0) {
        printf(AMARELO "sem abelhas cadastradas\n" RESET);
        printf("\nPressione ENTER para voltar...");
        getchar();
        return;
    }

    char nome[40];
    int achou = 0; //var que diz se pelo menos uma abelha foi achada, 0 = falso

    printf("\n" ROXO "=== BUSCAR ABELHA ===" RESET "\n");
    printf("nome popular pra buscar: ");
    fgets(nome, 40, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    //percorre o vetor
    for (int i = 0; i < qtdAbelhas; i++) {
        //strcmp compara as duas strings e retorna 0 se forem identicas
        if (strcmp(abelhas[i].nomePopular, nome) == 0) {
            printf(VERDE "\nachei:\n" RESET);
            printf("ID: %d\n", abelhas[i].id);
            printf("Nome popular: %s\n", abelhas[i].nomePopular);
            printf("Nome cientifico: %s\n", abelhas[i].nomeCientifico);
            printf("Regiao: %s\n", abelhas[i].regiao);
            printf("Mel: %.2f kg/mes\n", abelhas[i].producaoMel);
            printf("---\n");
            achou = 1; //var 1 = indica que encontrou ao menos uma abelha
        }
    }

    if (achou == 0) {
        printf(VERMELHO "Nao tem nenhuma abelha com esse nome\n" RESET);
    }
    printf("\nPressione ENTER para voltar...");
    getchar();
}

//permite alterar os dados da abelha
void alterarAbelha() {
    system("cls");
    if (qtdAbelhas == 0) {
        printf(AMARELO "Sem abelhas pra alterar\n" RESET);
        printf("\nPressione ENTER para voltar...");
        getchar();
        return;
    }

    int id;
    int pos = -1; //var que vai guardar o indice da abelha no vetor, -1 = ainda nao foi encontrada

    printf("\n" ROXO "=== ALTERAR ABELHA ===" RESET "\n");
    printf("ID da abelha pra alterar: ");
    scanf("%d", &id);
    getchar();

    //procura o id da abelha que foi digitado
    for (int i = 0; i < qtdAbelhas; i++) {
        if (abelhas[i].id == id) {
            pos = i; //armazena indice na variavel
            break;
        }
    }

    //se pos ainda for -1 depois da busca é pq nenhuma abelha com o id foi achada
    if (pos == -1) {
        printf(VERMELHO "ID %d nao existe\n" RESET, id);
        printf("\nPressione ENTER para voltar...");
        getchar();
        return;
    }

    printf("Alterando abelha %d\n", id);

    //sobrescreve os dados da abelha encontrada
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

    printf(VERDE "Alterado com sucesso\n" RESET);
    printf("\nPressione ENTER para voltar...");
    getchar();
}

//remove a abelha e o sensor dela
void removerAbelha() {
    system("cls");
    if (qtdAbelhas == 0) {
        printf(AMARELO "sem abelhas pra remover\n" RESET);
        printf("\nPressione ENTER para voltar...");
        getchar();
        return;
    }

    int id;
    int pos = -1;
    char conf; //var de confirmação

    printf("\n" ROXO "=== REMOVER ABELHA ===" RESET "\n");
    printf("ID da abelha pra remover: ");
    scanf("%d", &id);
    getchar();

    //busca o ID da abelha digitada
    for (int i = 0; i < qtdAbelhas; i++) {
        if (abelhas[i].id == id) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf(VERMELHO "Nao tem ID %d cadastrado\n" RESET, id);
        printf("\nPressione ENTER para voltar...");
        getchar();
        return;
    }

    printf(AMARELO "Tem certeza que quer remover %s? (S/N): " RESET, abelhas[pos].nomePopular);
    scanf(" %c", &conf);
    getchar();

    if (conf == 'S' || conf == 's') {
        //deleta sensores que o idabelha é igual ao id digitado pelo user
        for (int i = 0; i < qtdSensores; i++) {
            if (sensores[i].idAbelha == id) {
                //desloca todos os sensores seguintes uma posicao para a esquerda, sobrescrevendo o sensor removido
                for (int j = i; j < qtdSensores - 1; j++) {
                    sensores[j] = sensores[j + 1];
                }
                qtdSensores--; //reduz a var em 1 apos remover do vetor
                i--;
            }
        }

        //desloca todas as abelhas uma posicao para a esquerda, fechando o buraco no vetor
        for (int i = pos; i < qtdAbelhas - 1; i++) {
            abelhas[i] = abelhas[i + 1];
        }

        qtdAbelhas--;

        printf(VERDE "Abelha e sensores vinculados removidos!\n" RESET);
    } else {
        printf(AMARELO "Cancelado\n" RESET);
    }
    printf("\nPressione ENTER para voltar...");
    getchar();
}

void menuSensores() {
    int op;
    do {
        system("cls");
        printf("\n" ROXO "--- GERENCIAR SENSORES ---" RESET "\n");
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
            default: {
                printf(VERMELHO "Opcao invalida!" RESET "\n");
                printf("\nPressione ENTER para continuar...");
                getchar();
            }
        }
    } while(op != 6);
}

void cadastrarSensor() {
    system("cls");
    if (qtdSensores >= MAX_SENSORES) {
        printf(VERMELHO "\nLimite de sensores atingido!" RESET "\n");
        printf("\nPressione ENTER para voltar...");
        getchar();
        return;
    }

    int idAbelha;
    int existe = 0;
    int tipo;

    printf("\n" ROXO "=== CADASTRAR SENSOR ===" RESET "\n");

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
        printf("\nPressione ENTER para voltar...");
        getchar();
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
        printf("\nPressione ENTER para voltar...");
        getchar();
        return;
    }

    sensores[qtdSensores].idSensor = proximoIdSensor++;
    sensores[qtdSensores].idAbelha = idAbelha;
    sensores[qtdSensores].tipo = tipo;

    printf("Valor da leitura: ");
    sensores[qtdSensores].valor = lerFloatValido();

    qtdSensores++;

    printf(VERDE "Sensor cadastrado com sucesso!\n" RESET);
    printf("\nPressione ENTER para voltar...");
    getchar();
}

void listarSensores() {
    system("cls");
    if (qtdSensores == 0) {
        printf(AMARELO "\nNenhum sensor cadastrado.\n" RESET);
        printf("\nPressione ENTER para voltar...");
        getchar();
        return;
    }

    printf("\n" ROXO "=== LISTA DE SENSORES ===" RESET "\n");

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
    printf("\nPressione ENTER para voltar...");
    getchar();
}

void buscarSensorPorAbelha() {
    system("cls");
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
    printf("\nPressione ENTER para voltar...");
    getchar();
}

void alterarLeituraSensor() {
    system("cls");
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
        printf("\nPressione ENTER para voltar...");
        getchar();
        return;
    }

    printf("Nova leitura: ");
    sensores[indice].valor = lerFloatValido();

    printf(VERDE "Leitura updated!\n" RESET);
    printf("\nPressione ENTER para voltar...");
    getchar();
}

void removerSensor() {
    system("cls");
    if (qtdSensores == 0) {
        printf(AMARELO "\nNenhum sensor cadastrado." RESET "\n");
        printf("\nPressione ENTER para voltar...");
        getchar();
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
        printf("\nPressione ENTER para voltar...");
        getchar();
        return;
    }

    for (int i = indice; i < qtdSensores - 1; i++) {
        sensores[i] = sensores[i + 1];
    }

    qtdSensores--;

    printf(VERDE "\nSensor removido e vetor reorganizado com sucesso!" RESET "\n");
    printf("\nPressione ENTER para voltar...");
    getchar();
}

void menuRelatorios() {
    int opcao; //variavel que recebera o que se deseja
    do {
        system("cls");
        printf("\n" ROXO "--- Submenu 3 - Relatorios ---" RESET "\n");
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
            default: {
                printf(VERMELHO "Opcao invalida!" RESET "\n");
                printf("\nPressione ENTER para continuar...");
                getchar();
            }
        }
    } while(opcao != 4);
}

float memel() {
    system("cls");
    //caso não haja sensores de temperatura cadastrados
    if (qtdAbelhas == 0) {
        printf(AMARELO "\nNenhuma abelha cadastrada." RESET "\n");
        printf("\nPressione ENTER para voltar...");
        getchar();
        return 0;
    }

    float somamel = 0; //inicialização de variavel

    for (int i = 0; i < qtdAbelhas; i++) {
        somamel += abelhas[i].producaoMel;
        //enquanto i for menor que a quantidade de abelhas cadastradas, a variavel somamel ira armazenar toda a produção de mel da comeia
    }
// a variavel resultado recebera a divisão do somatorio total de mel pela quantidade de abelhas da comeia
    float resultado = somamel / qtdAbelhas;

    printf("\n" ROXO "=== RELATORIO: MEDIA DE PRODUCAO DE MEL ===" RESET "\n");
    printf("Total de abelhas:  %d\n", qtdAbelhas);
    printf("Soma total:        %.2f kg/mes\n", somamel);
    printf("Media geral:       " VERDE "%.2f kg/mes" RESET "\n", resultado);

    printf("\nPressione ENTER para voltar...");
    getchar();
    return resultado;
}

float relatoriosensores() {
    system("cls");
    float soma = 0;//inicializando a soma das temperaturas
    int quantidade = 0;//inicializando a quantidade de sensores existentes na comeia

    for (int i = 0; i < qtdSensores; i++) {
//enquanto i for menor que a quantidade de sensores, a variavel soma recebera o valor acumulado da temperatura dos sensores
        if (sensores[i].tipo == 1) {
            soma += sensores[i].valor;
            quantidade++;// aqui será contabilizado a quantidade de sensores existentes
        }
    }
//caso não haja sensores de temperatura cadastrados
    if (quantidade == 0) {
        printf(AMARELO "Nao existem sensores de temperatura.\n" RESET);
        printf("\nPressione ENTER para voltar...");
        getchar();
        return 0;
    }
//a variavel media recebera a divisão da soma total das temperaturas sobre a quantidade de sensores
    float media = soma / quantidade;

    printf("\nMedia de temperatura: %.2f C\n", media);

    printf("\nPressione ENTER para voltar...");
    getchar();
    return media;
}

void abelhasPorRegiao() {
    system("cls");
	//caso não haja regiões cadastradas
    if (qtdAbelhas == 0) {
        printf(AMARELO "\nNenhuma abelha cadastrada." RESET "\n");
        printf("\nPressione ENTER para voltar...");
        getchar();
        return;
        //função do tipo void, não ha nada há frente do return
    }

    char regioes[MAX_ABELHAS][30];//nome e quantidade de regiões cadastradas
    int contagens[MAX_ABELHAS];//variavel contadora para quantidade de abelhas por região
    int totalRegioes = 0;//inicializando variavel

    for (int i = 0; i < qtdAbelhas; i++) { // 
        int encontrou = 0;//inicializando variavel encontrou 

        for (int j = 0; j < totalRegioes; j++) {
            if (strcmp(regioes[j], abelhas[i].regiao) == 0)//compara se a região da abelha já foi cadastrada
			 {
                contagens[j]++; //aumenta a quantidade de abelhas na região j
                encontrou = 1;//evita de cadstrar a mesma região novamente
                break;
            }
        }

        if (encontrou==0) {//como o primeiro valor de j sera 0, ele executara essa parte
            strcpy(regioes[totalRegioes], abelhas[i].regiao);
            contagens[totalRegioes] = 1;//vetor contagens na posição da quantidade de regiões encontradas
            totalRegioes++; //incrementação na variavel e mostra a quantidade de regiões distintas
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
    printf("\nPressione ENTER para voltar...");
    getchar();
}

void menuDiagnostico() {
    int op;
    do {
        system("cls");
        printf("\n" ROXO "=== BEE DOCTOR ===" RESET "\n");
        printf("1. Diagnosticar colonia\n");
        printf("2. Voltar\n");
        printf("Opcao: ");
        scanf("%d", &op);
        getchar();
        
        if(op == 1) realizardiagnostico();
    } while(op != 2);
}

void realizardiagnostico() {
    system("cls");
    if(qtdAbelhas == 0) {
        printf(VERMELHO "\nNenhuma abelha cadastrada!" RESET "\n");
        printf("\nPressione ENTER para voltar...");
        getchar();
        return;
    }
    
    int id;
    float temp = 0, umid = 0;
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
    
    printf("\n" ROXO "=== DIAGNOSTICO ===" RESET "\n");
    
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

    printf("\nPressione ENTER para voltar...");
    getchar();
}

void recomendarTratamento(float temp, float umid) {
    printf("\n" ROXO "=== RECOMENDACOES BEE DOCTOR ===" RESET "\n");

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

    printf("=================================\n");
}

//funcao que garante que o usuario so consiga inserir um numero float valido, evitando travamento do programa
float lerFloatValido() {
    float valor;
    char c;

    //o loop continua enquanto o scanf nao conseguir ler um float valido, o scanf retorna o numero de itens lidos com sucesso; se nao for 1, a entrada foi invalida
    while (scanf("%f", &valor) != 1) {
        printf(VERMELHO "Digite apenas numeros: " RESET);
        //descarta todos os caracteres invalidos que sobraram no buffer ate encontrar '\n' ou fim de arquivo
        while ((c = getchar()) != '\n' && c != EOF);
    }
    getchar();
    return valor;
}