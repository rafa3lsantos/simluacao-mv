#include <iostream>
#include <vector>
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
    
}

int main() {

    tabela_paginas[0].frame_fisico = 5;
    tabela_paginas[0].bit_valid = 1;

    return 0;
}