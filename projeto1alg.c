//cliente do Problema do Caixeiro Vaijante.

/*
    No Problema do Caixeiro Viajante precisamos optar pela escolha
    mais eficiente de um caixeiro viajante ir em todas as cidades possíveis 
    no menor custo possível de distância. 

    A leitura será feita por um programa externo:
    CIDADE A | CIDADE B | Distância 
        1         2           3
        1         3           4
        1         4           2
        2         1           5
        ...

        então, a n-enésima cidade A, onde estamos no momento, irá para o resto das
        outras cidades (n-1 cidades possíveis). Este é um problema de análise combinatória
        com a relação do menor custo das distâncias.

    Além disso, escolhe-se no programa qual será a cidade de origem.

    Precisa-se no final do programa mostrar a rota e o custo.
*/

// Pensei em primeiro qual seria a melhor estrutura para abordar esse problema?
// Pilha (sequencial ou encadeada) ou Lista Duplamente Encadeada.
// melhor optar pela pilha encadeada primeiro.