#ifndef PROJETO_H_INCLUDED
#define PROJETO_H_INCLUDED

typedef struct paciente Paciente;
typedef struct heap Heap;
Heap* heap_cria (int nmax);
void heap_libera (Heap* h);
int heap_vazia (Heap* h);
void heap_insere (Heap* h, Paciente* p);
int verifica(Heap* h);
Paciente* cria_paciente(int pri, char* nome, char sexo, int idade, float peso, float imc, float altura, char* situacao);
int prioridade(float imc);
Paciente* retira_paciente(Heap* h);
void imprime_dados(Paciente* p);
void imprime_situacao(Paciente* p);
void Arquiva_situacao(Paciente* p);
Paciente* busca_paciente(Heap* h, char* nome);
char* classe_imc(int priori,float imc);

#endif // PROJETO_H_INCLUDED
