#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "projeto.h"

#define pai(i) (((i)-1)/2)
#define esq(i) (2*(i)+1)
#define dir(i) (2*(i)+2)


struct paciente
{
    int pri;
    char nome[71];
    int idade;
    float peso;
    float imc;
    float altura;
    char sexo;
    char situacao[71];
};
struct heap
{
    Paciente **v;
    int n;
    int nmax;
};

Heap* heap_cria (int nmax)
{
    Heap* h= (Heap*) malloc(sizeof(Heap));
    h->n=0;
    h->nmax=nmax;
    h->v= (Paciente**) malloc(h->nmax*sizeof(Paciente*));

    return h;
}

void heap_libera (Heap* h)
{
    int i;
    for(i=0; i < h->n; i++)
    {
        free(h->v[i]);
    }
    free(h->v);
    free(h);
}

int heap_vazia (Heap* h)
{
    if(h->n==0)
        return 1;
    else
        return 0;
}
static void troca(Heap* h, int i, int j)
{
    Paciente* temp = (Paciente*) malloc (sizeof(Paciente));

    temp->pri = h->v[i]->pri;
    temp->imc = h->v[i]->imc;
    temp->peso = h->v[i]->peso;
    temp->altura =h->v[i]->altura;
    temp->sexo = h->v[i]->sexo;
    temp->idade = h->v[i]->idade;
    strcpy(temp->nome, h->v[i]->nome);
    strcpy(temp->situacao, h->v[i]->situacao);

    h->v[i]->pri = h->v[j]->pri;
    h->v[i]->imc = h->v[j]->imc;
    h->v[i]->peso = h->v[j]->peso;
    h->v[i]->altura = h->v[j]->altura;
    h->v[i]->sexo = h->v[j]->sexo;
    h->v[i]->idade = h->v[j]->idade;
    strcpy(h->v[i]->nome,h->v[j]->nome);
    strcpy(h->v[i]->situacao,h->v[j]->situacao);

    h->v[j]->pri = temp->pri;
    h->v[j]->imc = temp->imc;
    h->v[j]->peso = temp->peso;
    h->v[j]->altura= temp->altura;
    h->v[j]->sexo = temp->sexo;
    h->v[j]->idade = temp->idade;
    strcpy(h->v[j]->nome,temp->nome);
    strcpy(h->v[j]->situacao,temp->situacao);
}



static void sobe(Heap*h, int i)
{
    while(i>0)
    {
        int p= pai(i);
        if(h->v[p]->pri > h->v[i]->pri)
            break;
        troca(h,i,p);
        i=p;
    }
}
void heap_insere (Heap* h, Paciente* p)
{
    if(h->n < h->nmax)
    {
        h->v[h->n++] = p;
        sobe(h,h->n-1);
    }
}

static void desce(Heap* h, int i)
{
    int c= esq(i);
    while(c<h->n)
    {
        int c2 = dir(i);
        if(c2 < h->n && h->v[c2]->pri > h->v[c]->pri)
            c=c2;
        if(h->v[c]->pri < h->v[i]->pri)
            break;
        troca(h,i,c);
        i=c;
        c=esq(i);
    }
}

int verifica(Heap* h)
{
    int i;
    for(i=0; i < h->n/2; ++i)
    {
        int e = esq(i);
        int d = dir(i);
        if(h->v[e]->pri > h->v[i]->pri)
            return 0;
        if(d < h->n && h->v[d]->pri > h->v[i]->pri)
            return 0;
    }
    return 1;
}


Paciente* cria_paciente(int pri, char* nome, char sexo,int idade, float peso, float imc, float altura, char* situacao)
{
    Paciente* novo = (Paciente*) malloc(sizeof(Paciente));
    if(novo==NULL)
    {
        exit(1);
    }
    novo->pri = pri;
    novo->idade = idade;
    novo->peso = peso;
    novo->altura = altura;
    novo->sexo = sexo;
    novo->imc = imc;
    strcpy( novo->nome,nome);
    strcpy( novo->situacao,situacao);
    return novo;
}
// funça
int prioridade(float imc)
{
    int p;
    if(imc < 16.0)
    {
        p = 4;
    }
    else if(imc >=16.0 && imc <= 16.99)
    {
        p = 3;
    }
    else if(imc >= 17.0 && imc <= 18.49)
    {
        p=2;
    }
    else if(imc >= 18.5 && imc <= 24.99)
    {
        p=1;
    }
    else if(imc >= 25.0 && imc <= 29.99)
    {
        p=2;
    }
    else if(imc >= 30.0 && imc <= 34.99)
    {
        p=3;
    }
    else if(imc >= 35.0 && imc <= 39.49)
    {
        p=4;
    }
    else
    {
        p=5;
    }
    return p;
}

Paciente* retira_paciente(Heap* h)
{
    Paciente* p = h->v[0];
    h->v[0]= h->v[--h->n];
    desce(h,0);
    return p;
}

void imprime_dados(Paciente* p)
{
    printf(" %s\t%c\t%d\t%.2f\t%.2f\t%.2f\t%s\n\n", p->nome,p->sexo,p->idade, p->peso, p->altura,p->imc,p->situacao);
}

void imprime_situacao(Paciente* p)
{
    printf("%s\t%.2f\t%s\n\n",p->nome,p->imc,p->situacao);
}

void Arquiva_situacao(Paciente* p)
{
    FILE* arq = fopen("saida.txt","at");
    fprintf(arq,"%s\t%.2f\t%s\n",p->nome, p->imc,p->situacao,p->situacao);
    fclose(arq);
}
Paciente* busca_paciente(Heap* h, char* nome)
{
    int i;
    for(i=0; i < h->nmax; i++)
    {
        if(strcmp(h->v[i]->nome,nome)== 0)
        {
            return h->v[i];
        }
    }
    return NULL;
}

char* classe_imc(int priori,float imc)
{
    char *classe = (char*) malloc(41*sizeof(char));
    if(priori == 1)
    {
        strcpy(classe,"Peso normal");
    }
    else if(priori==2)
    {
        if(imc >= 17.0 && imc <= 18.49)
        {
            strcpy(classe,"Baixo peso");
        }
        else
        {
            strcpy(classe,"Sobrepeso");
        }
    }
    else if(priori==3)
    {
        if(imc>=16.0 && imc<=16.99)
        {
            strcpy(classe,"Baixo peso grave");
        }
        else
        {
            strcpy(classe,"Obesidade grau I");
        }
    }
    else if(priori==4)
    {
        if(imc<16)
        {
            strcpy(classe,"Baixo peso muito grave");
        }
        else
        {
            strcpy(classe,"Obesidade grau II");
        }
    }
    else
    {
        strcpy(classe,"Obesidade grau III(Obesidade Morbida)");
    }
    return classe;
}
