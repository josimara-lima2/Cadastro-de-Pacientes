#include<stdarg.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/****************************************************************
* Função: Limpa_Buffer();                                       *
* Parâmetros: Nenhum;                                           *
* Descrição: Lê e descarta caracteres da entrada;               *
* Retorno: void.                                                *
****************************************************************/

void Limpa_Buffer(void)
{
    int vl; //Valor Lido;
    do
    {
        vl= getchar();
    }
    while((vl != '\n') && (vl != EOF));
}

/****************************************************************
* Função: Le_opcao();                                           *
* Parâmetros:                                                   *
* max_valor, min_valor;                                         *
* Descrição: Lê e valida a opção escolhida;                     *
* Retorno: inteiro.                                             *
****************************************************************/

int Le_opcao(int max_valor, int min_valor)
{
    int opcao;

    while(1)
    {
        printf("Informe sua opcao:\n");
        opcao= getchar();
        if(opcao>=min_valor && opcao<=max_valor)
        {
            Limpa_Buffer();
            break;
        }
        else
        {
            printf("Opcao invalida!\n");
            Limpa_Buffer();
        }
    }
    return opcao;
}

/****************************************************************
* Função: Le_inteiro();                                        *
* Parâmetros: Nenhum;                                           *
* Descrição: Lê um inteiro informado pelo usuário;              *
* Retorno: inteiro.                                             *
****************************************************************/

int Le_inteiro(void)
{
    int inteiro, num_vl;
    num_vl= scanf("%d", &inteiro);
    while(num_vl == 0)
    {
        Limpa_Buffer();
        printf("Entrada incorreta! Informe um valor inteiro:\n");
        num_vl = scanf("%d",&inteiro);
    }
    Limpa_Buffer();
    return inteiro;
}

/*****************************************************************
* Função: Apresenta_menu();                                      *
* Parâmetros: num_itens, min_op;                                 *
* Descrição: Apresenta menu de opções com um número indeterminado*
* Retorno: Void.                                                 *
*****************************************************************/

void Apresenta_menu(int num_itens, int min_op, ...)
{
    int i;
    va_list argumentos; //inicializa lista de argumentos variaveis;
    va_start(argumentos,min_op); //lê cada argumento e imprime na tela;

    for(i=0; i < num_itens; ++i)
    {
        printf("%c-%s\n",min_op++, va_arg(argumentos, char*));
    }
    va_end(argumentos);
}
/*****************************************************************
* Função: Le_string();                                           *
* Parâmetros: Nenhum;                                            *
* Descrição: Lê uma cadeia de caracteres;                        *
* Retorno: Char*.                                                *
*****************************************************************/

char* Le_string()
{
    char aux[121];
    printf("Digite uma linha de texto: ");
    scanf(" %s",aux);
    int n = strlen(aux);
    char* string = (char*) malloc((n+1)*sizeof(char));
    strcpy(string,aux);
    Limpa_Buffer();

    return string;
}
