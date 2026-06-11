void menuRelatorios() {
    int opção;
    do {
        printf("\n--- Submenu 3 - Relatorios ---\n");
        printf("1. Media geral de producao de mel\n");
        printf("2. Media de temperatura dos sensores\n");
        printf("3. Quantidade de abelhas por regiao\n");
        printf("4. Voltar\n");
        printf("Opcao: ");
        scanf("%d", &opção);
        getchar();

        switch(opção) {
            case 1: memel();           break;
            case 2: relatoriosensores(); break;
            case 3: abelhasPorRegiao(); break;
            case 4: printf("Voltando ao menu principal...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while(opção != 4);
}


float memel() {
    if (qtdAbelhas == 0) {
        printf("\nNenhuma abelha cadastrada.\n");
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
    printf("Media geral:       %.2f kg/mes\n", resultado);

    return resultado;
}


float relatoriosensores() {
    if (qtdSensores == 0) {
        printf("\nNenhum sensor cadastrado.\n");
        return 0;
    }

    float somadetemperatura = 0;


    for (int i = 0; i < qtdSensores; i++) {
        somadetemperatura += sensores[i].temperatura;
    }

    float media = somadetemperatura / qtdSensores;

    printf("\n=== RELATORIO: MEDIA DE TEMPERATURA ===\n");
    printf("Total de sensores:    %d\n", qtdSensores);
    printf("Media de temperatura: %.2f C\n", media);

    return media;
}


void abelhasPorRegiao() {
    if (qtdAbelhas == 0) {
        printf("\nNenhuma abelha cadastrada.\n");
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
        printf("%-20s | %d\n", regioes[i], contagens[i]);
    }
    printf("--------------------------------\n");
    printf("Total de regioes distintas: %d\n", totalRegioes);
}
