#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"
#include <string.h>

#define MAX 30

int precedencia(char c);
void converte_para_notacao_pos_fixa(char entrada[], char saida[]);
int resolve_expressao_pos_fixa(char s[]);
int resolve_operacao(char c, int aux2, int aux1); 


int main(int argc, char *argv[]) {
	char e[MAX], s[MAX];
	int resultado;
	
	printf ("Digite a expressao matematica: ");
	scanf("%s", e);

	converte_para_notacao_pos_fixa(e,s); // Converte a expresssao e em Pos-fixa e salva na string s
	
	printf("Expressao pos-fixa: %s\n", s); // Imprime a expressao Pos fixa
	
	resultado = resolve_expressao_pos_fixa(s); //Resolve a expressao pos fixa
	
	printf("Resultado da expressao pos-fixa: %i", resultado); // Imprime o resultado da expressao pos fixa
	
	return 0;
}

int precedencia(char c){
	if(c == '(')
	   return 0;
	if (c == '+' || c == '-')
	   return 1;
	if (c == '*' || c == '/') 
	   return 2;  
}

int resolve_expressao_pos_fixa(char s[MAX]){
	
	Pilha p2;
	inicializa_pilha(&p2, MAX);
	int i = 0;
	int aux1, aux2 = 0;
	int resultado;
	char c;
	
	while(s[i] != '\0'){
		c = s[i];
		
		if(isdigit(c)){
			aux1 = c - '0';
			empilha(&p2, aux1);
			
		}else
		if(c == '+' || c == '-' || c == '*' || c == '/'){ // se C é um operador
			desempilha(&p2, &aux2);
			desempilha(&p2, &aux1);
			resultado = 0;
			resultado = resolve_operacao(c, aux2, aux1);
			empilha(&p2, resultado);	
		}
		i++;
	}
	
	return resultado;
	desaloca_pilha(&p2);
}

int resolve_operacao(char c, int aux2, int aux1){
	switch (c) {
				case '+':
					return aux1 + aux2;
				break;
				case '-':
					return aux1 - aux2;
					break;
				case '*':
					return aux1 * aux2;
					break;
				case '/':
					return aux1 / aux2;
					break;
			}
}


void converte_para_notacao_pos_fixa(char entrada[], char saida[]){
	saida[0] = '\0';
	int deu_erro = 0;

	Pilha p;
	inicializa_pilha(&p, MAX);
	
	char c, auxc;
	int x = 0;
	int i = 0;
	while(entrada[i] != '\0' && !deu_erro){
		c = entrada[i]; 
		switch (c) {
			case '0':
  		    case '1':
    		case '2':
    		case '3':
    		case '4':
    		case '5':
    		case '6':
    		case '7':
    		case '8':
    		case '9':
				strncat(saida, &c, 1);
			break;
			case '(':
				empilha(&p, c);
			break;
			case ')':
				while ( le_topo(p, &x) != ERRO_PILHA_VAZIA && (x != '(')){
					desempilha(&p, &x);
					auxc = x;
					strncat(saida, &auxc, 1);
				}
				
				if (le_topo(p, &x) == ERRO_PILHA_CHEIA){
					printf ("Erro: ')' sem '('!");
					deu_erro = 1;
				} else {
					desempilha(&p, &x);
				}
			break;
			case '+':
			case '-':
			case '*':
			case '/':
				le_topo(p, &x);		
				if (pilha_vazia(p) == ERRO_PILHA_VAZIA || x == '(')
					empilha(&p, c);
				else {
					while(le_topo(p, &x) != ERRO_PILHA_VAZIA &&
					     precedencia(x) >= precedencia(c)) {
						desempilha(&p, &x);
						auxc = x;
						strncat(saida, &auxc, 1);
					}
					empilha(&p, c);
				}
			break;
			default:
				printf("Erro caractere inválido: c!");
				deu_erro = 1;
			break;
		}
	i++;
	}

    if(!deu_erro){
    	while((le_topo(p, &x) != ERRO_PILHA_VAZIA) && (x != '(')) {
    		desempilha(&p, &x);
    		auxc = x;
    		strncat(saida, &auxc, 1);
		}
		if (le_topo(p, &x) == ERRO_PILHA_VAZIA){
			auxc = '\0';
			strncat(saida, &auxc, 1);
		} else{
			printf ("Erro: '(' não foi fechado!");
		}
	}
}
