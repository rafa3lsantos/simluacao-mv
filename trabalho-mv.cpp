#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
#define TAMANHO_MEMORIA_FISICA 1024
#define TAMANHO_PAGINA 64
#define TAMANHO_TLB 4
#define NUMERO_DE_PAGINAS 32        
#define NUMERO_DE_SEGMENTOS 5

typedef struct {
    int frame_fisico;
    int bit_valid;
    int bit_dirty;
} PaginacaoTabelaEntrada;

typedef struct {
    int base;
    int limite;
    int valida;
} SegmentacaoTabelaEntrada;

typedef struct {
    int pagina_virtual;
    int frame_fisico;
    int valid;
    int tempo_uso;
} TlbEntrada;

int memoria_fisica[TAMANHO_MEMORIA_FISICA];
PaginacaoTabelaEntrada tabela_paginas[NUMERO_DE_PAGINAS];   // A Tabela de Páginas
SegmentacaoTabelaEntrada tabela_segmentos[NUMERO_DE_SEGMENTOS]; // A Tabela de Segmentos
TlbEntrada tlb[TAMANHO_TLB];

void inicializar() {

    for(int i = 0; i < NUMERO_DE_PAGINAS; i++) { // para indicarmos que nao existe nada alocado na RAM
        tabela_paginas[i].bit_valid = 0;
    }

    for(int i = 0; i < NUMERO_DE_SEGMENTOS; i++) { 
        tabela_segmentos[i].valida = 0;
    }

    for(int i = 0; i < TAMANHO_MEMORIA_FISICA; i++) { // loop para colocar um byte aleatorio em cada posicao do vetor 
        memoria_fisica[i] = i % 255; 
        // cout << memoria_fisica[i] << endl;
    }

    //testes
    tabela_paginas[2].bit_valid = 1;
    tabela_paginas[2].frame_fisico = 4;

    tabela_paginas[5].bit_valid = 1;
    tabela_paginas[5].frame_fisico = 10;

    tabela_segmentos[0].valida = 1;
    tabela_segmentos[0].base = 0; 
    tabela_segmentos[0].limite = 500;
    tabela_segmentos[1].valida = 1;
    tabela_segmentos[1].base = 800;
    tabela_segmentos[1].limite = 100;

}

void traduzir_paginacao(int endereco_virtual) {
    int pagina = 0, offset = 0, endereco_fisico = 0;

    pagina = endereco_virtual / TAMANHO_PAGINA;
    offset = endereco_virtual % TAMANHO_PAGINA;

    if (pagina >= NUMERO_DE_PAGINAS) {
        cout << "Pagina invalida (fora do limite da tabela)" << endl;
        return;
    }

    if(tabela_paginas[pagina].bit_valid == 0) {
        cout << "PAGE FAULT! A pagina " << pagina << " nao esta na RAM" << endl;
        return;
    }

    endereco_fisico = (tabela_paginas[pagina].frame_fisico * TAMANHO_PAGINA) + offset;

    cout << "Pagina Valida! Esta no Frame " << tabela_paginas[pagina].frame_fisico << endl;
    cout << "ENDERECO FISICO CALCULADO: " << endereco_fisico << endl;
    cout << "Valor na Memoria: " << memoria_fisica[endereco_fisico] << endl;

}

void traduzir_segmentacao(int segmento, int offset) {
    int endereco_fisico = 0;

    if(segmento >= NUMERO_DE_SEGMENTOS) {
        cout << "Segmento invalido!" << endl;
        return;
    }

    if(tabela_segmentos[segmento].valida == 0) {
        cout << "Segmento nao foi carregado na RAM!" << endl;
        return;
    }

    if(offset >= tabela_segmentos[segmento].limite) {
        cout << "Segmentation fault!" << endl;
        cout << "Voce tentou acessar " << offset << ", mas o limite eh " << tabela_segmentos[segmento].limite << endl;
        return;
    }

    endereco_fisico = tabela_segmentos[segmento].base + offset;

    cout << "Segmento Valido! Base no endereco " << tabela_segmentos[segmento].base << endl;
    cout << "ENDERECO FISICO CALCULADO: " << endereco_fisico << endl;
    cout << "Valor na Memoria: " << memoria_fisica[endereco_fisico] << endl;
}

int main() {
    srand(time(NULL));
    inicializar();
    
    int opcao;

    cout << "Escolha: " << endl << "1 - Paginacao " << endl << "2 - Segmentacao" << endl;
    cin >> opcao;
    while(opcao < 1 or opcao > 2) {
        cout << "Opcao invalida! Tente novamente" << endl;
        cin >> opcao;
    }

    if(opcao == 1) {
        int endereco_virtual;

        cout << "Insira o endereco virtual a ser acessado : " << endl;
        cin >> endereco_virtual;

        traduzir_paginacao(endereco_virtual);
    } else {
        int segmento, offset;

        cout << "Insira o segmento: " << endl;
        cin >> segmento;

        cout << "Insira o offset: " << endl; 
        cin >> offset;

        traduzir_segmentacao(segmento, offset);
    }

    return 0;
}