Trabalho: BeeDoctor – Diagnostico de Colonias de Abelhas sem Ferrao

Integrantes: Yago Rangel, Igor Leal, Matheus Barbosa, Marcio Victor, Davi Borges

Disciplina: Algoritmos e Programacao I

Professora: Dra. Alcilene Dalilia de Sousa

Descricao:
Sistema de cadastro e monitoramento de abelhas sem ferrao e sensores ambientais
associados. O BeeDoctor permite gerenciar colonias de abelhas, vincular sensores de
temperatura, umidade e luminosidade a cada colonia, gerar relatorios de producao de
mel e realizar diagnosticos automaticos de saude da colonia com base nas leituras dos
sensores, emitindo alertas e recomendacoes de tratamento quando os parametros estao
fora do ideal.

Compilacao:
    gcc src/main.c -o beedoctor

Execucao:
  Windows:
    beedoctor.exe
  Linux:
    ./beedoctor

Bugs conhecidos:
    - Nao ha persistencia em arquivo; os dados se perdem ao encerrar o programa.
    - A busca de abelha por nome eh case sensitive (diferencia maiusculas de minusculas).
    - System clear só funciona em dispositivos rodando o Windows.
