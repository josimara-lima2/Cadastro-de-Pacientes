#include <stdio.h>
#include <stdlib.h>
#include "Menu_interativo.h"
#include "projeto.h"
#include <math.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#define T_OPCAO1 "Cadastrar paciente"
#define T_OPCAO2 "Listar pacientes"
#define T_OPCAO3 "Buscar paciente"
#define T_OPCAO4 "Sair"

#define T_SUB_OPCAO1 "Imprimir dados na tela"
#define T_SUB_OPCAO2 "Salvar os dados em arquivo"
#define T_SUB_OPCAO3 "Voltar"

#define OPCAO1 '1'
#define OPCAO2 '2'
#define OPCAO3 '3'
#define OPCAO4 '4'

#define SUB_OPCAO1 '1'
#define SUB_OPCAO2 '2'
#define SUB_OPCAO3 '3'

#define N_SUB_OPCAO 3
#define N_OPCAO 4

#define N 100
int main()
{

    Heap* h= heap_cria(N);
    char entrada[71];
    char* result;
    int opcao, sub_op;
    int idade, priori;
    char nome[71];
    char linha[201];
    char nome1[71];
    char sexo;
    char* situ = (char*) malloc(41*sizeof(char));
    float peso, altura, imc;
    Paciente* p;


    FILE* e= fopen("entrada.txt","at");
    FILE* s= fopen("saida.txt","at");
    do
    {
        Apresenta_menu(N_OPCAO,OPCAO1,T_OPCAO1,T_OPCAO2,T_OPCAO3,T_OPCAO4);
        opcao= Le_opcao(OPCAO1 + N_OPCAO - 1, OPCAO1);

        switch(opcao)
        {
        case OPCAO1:
            printf("Voce escolheu a opcao de cadastramento. Informe os dados a seguir e cuidaremos do resto:\n");
            printf("Nome: ");
            scanf("%s",nome);
            printf("Sexo (F)/(M): ");
            scanf(" %c",&sexo);
            printf("Idade: ");
            scanf("%d",&idade);
            printf("Peso (KG): ");
            scanf("%f",&peso);
            printf("Altura (m) ");
            scanf("%f",&altura);
            imc=(peso/(altura*altura));
            priori = prioridade(imc);
            situ = classe_imc(priori,imc);
            p= cria_paciente(priori,nome,sexo,idade,peso,imc,altura,situ);
            heap_insere(h,p);
            fprintf(e, "%s\t%c\t%d\t%.2f\t%.2f\n",nome,sexo,idade,peso,altura);
            printf("%.2f\n",imc);
            fprintf(s,"%s\t%.2f\t%s\n",nome,imc,situ);
            assert(verifica(h));
            Limpa_Buffer();
            break;
        case OPCAO2:
            do
            {
                Apresenta_menu(N_SUB_OPCAO,SUB_OPCAO1,T_SUB_OPCAO1,T_SUB_OPCAO2, T_SUB_OPCAO3);
                sub_op = Le_opcao(SUB_OPCAO1 + N_SUB_OPCAO - 1, SUB_OPCAO1);

                switch(sub_op)
                {
                case SUB_OPCAO1:
                    fclose(e);
                    fclose(s);
                    printf("Informe o nome do arquivo de entrada:\n");
                    scanf("%s",entrada);
                    e = fopen(entrada,"rt");
                    remove("saida.txt");
                    rewind(e);
                    if(e==NULL)
                        exit(1);
                    while(fgets(linha,201,e)!=NULL)
                    {
                        sscanf(linha,"%70[^\t]\t%c\t%d\t%f\t%f\n",nome,&sexo,&idade,&peso,&altura);
                        imc=(peso/(altura*altura));
                        priori = prioridade(imc);
                        situ = classe_imc(priori,imc);
                        p= cria_paciente(priori,nome,sexo,idade,peso,imc,altura,situ);
                        heap_insere(h,p);
                        assert(verifica(h));
                    }
                    while(!heap_vazia(h))
                    {
                        p = retira_paciente(h);
                        imprime_situacao(p);
                        Arquiva_situacao(p);
                        assert(verifica(h));
                    }


                    break;

                case SUB_OPCAO2:
                    fclose(e);
                    fclose(s);
                    printf("Informe o nome do arquivo de entrada:\n");
                    scanf("%s",entrada);
                    e = fopen(entrada,"rt");
                    remove("saida.txt");
                    rewind(e);

                    while(fgets(linha,201,e)!=NULL)
                    {
                        sscanf(linha,"%70[^\t]\t%c\t%d\t%f\t%f\n",nome,&sexo,&idade,&peso,&altura);
                        imc=(peso/(altura*altura));
                        priori = prioridade(imc);
                        situ = classe_imc(priori,imc);
                        p= cria_paciente(priori,nome,sexo,idade,peso,imc,altura,situ);
                        heap_insere(h,p);
                        assert(verifica(h));
                    }
                    while(!heap_vazia(h))
                    {
                        p = retira_paciente(h);
                        Arquiva_situacao(p);
                        assert(verifica(h));
                    }

                    fclose(e);
                    Limpa_Buffer();
                    break;
                case SUB_OPCAO3:
                    break;
                }
            }
            while(sub_op != SUB_OPCAO3);
            break;
        case OPCAO3:
            printf("Informe o nome do paciente a ser buscado:\n");
            scanf("%70[^\n]s",nome1);
            e = fopen("entrada.txt","rt");
            while(fgets(linha,201,e)!=NULL)
            {
                sscanf(linha,"%70[^\t]\t%c\t%d\t%f\t%f\n",nome,&sexo,&idade,&peso,&altura);
                imc=(peso/(altura*altura));
                priori = prioridade(imc);
                situ = classe_imc(priori,imc);
                p= cria_paciente(priori,nome,sexo,idade,peso,imc,altura,situ);
                heap_insere(h,p);
                assert(verifica(h));
            }

            p = busca_paciente(h,nome1);
            if(p != NULL)
            {
                imprime_dados(p);
            }
            else
            {
                fclose(e);
                printf("Nome nao encontrado na lista de pacientes!\n");
            }
            fclose(e);
            Limpa_Buffer();
            break;
        case OPCAO4:
            break;
        }
    }
    while(opcao != OPCAO4);

    return 0;
}
