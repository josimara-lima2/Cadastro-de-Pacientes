#ifndef MENU_INTERATIVO_H_INCLUDED
#define MENU_INTERATIVO_H_INCLUDED

void Limpa_Buffer(void);
int Le_opcao(int max_valor, int min_valor);
int Le_inteiro(void);
void Apresenta_menu(int num_itens, int min_op, ...);
char* Le_string();

#endif // MENU_INTERATIVO_H_INCLUDED
