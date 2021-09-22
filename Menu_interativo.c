#include<stdarg.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/****************************************************************
* Fun��o: Limpa_Buffer();                                       *
* Par�metros: Nenhum;                                           *
* Descri��o: L� e descarta caracteres da entrada;               *
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
* Fun��o: Le_opcao();                                           *
* Par�metros:                                                   *
* max_valor, min_valor;                                         *
* Descri��o: L� e valida a op��o escolhida;                     *
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
* Fun��o: Le_inteiro();                                        *
* Par�metros: Nenhum;                                           *
* Descri��o: L� um inteiro informado pelo usu�rio;              *
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
* Fun��o: Apresenta_menu();                                      *
* Par�metros: num_itens, min_op;                                 *
* Descri��o: Apresenta menu de op��es com um n�mero indeterminado*
* Retorno: Void.                                                 *
*****************************************************************/

void Apresenta_menu(int num_itens, int min_op, ...)
{
    int i;
    va_list argumentos; //inicializa lista de argumentos variaveis;
    va_start(argumentos,min_op); //l� cada argumento e imprime na tela;

    for(i=0; i < num_itens; ++i)
    {
        printf("%c-%s\n",min_op++, va_arg(argumentos, char*));
    }
    va_end(argumentos);
}
/*****************************************************************
* Fun��o: Le_string();                                           *
* Par�metros: Nenhum;                                            *
* Descri��o: L� uma cadeia de caracteres;                        *
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
