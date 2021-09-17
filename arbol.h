#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
typedef struct arbol A;
struct arbol
{
	int numero;
	A *hijo_izquierda;
	A *padre;
	A* hijo_derecha;
	int altura;
};
A* nodo_der_izq(A* inicio);
A* RIzquierda(A* raiz, int cual[2][50], int i);
A* RDerecha(A* raiz, int cual[2][50], int i);
void checa_repetidos(int*b,int num,A* inicio);
void revalida_altura(A* inicio, int num);
void checa_elimina(A** inicio);
short int Busca_nodo(A**raiz, int num);
void Checa_Balanceo(A** inicio, int cual[2][50], int* i,int *band);
void Balanceo(A* inicio, short int* num);
void Busca_fin(A*inicio,int num,int h);
short int inserta_dato(A **inicio,int num);
A* nodo_iz_der(A* inicio);
A* elimina_raiz(A** inicio);
///////////////////////////////////////////////////////////////////////////////////
void checa_repetidos(int *b, int num,A*inicio) {
	 if (inicio) {
		 if (inicio->numero == num) {
			 *b = 0;
		 }
			 if (inicio->hijo_derecha) {
				 if (inicio->hijo_derecha->numero == num) {
					 *b = 0;
				 }
			 checa_repetidos(b, num,inicio->hijo_derecha);
			 }
			 if (inicio->hijo_izquierda) {

				checa_repetidos(b, num,inicio->hijo_izquierda);
			 }
	 }
}
///////////////////////////////////////////////////////////////////////////////////
short int inserta_dato(A** inicio,int num)
{
	A *aux,*nuevo=NULL;
	//nuevo = NULL;
	aux = *inicio;
			if (!*inicio)
			{
				nuevo = (A*)malloc(sizeof(A));
				if (nuevo) {
				nuevo->altura = 0;
				nuevo->numero = num;
				nuevo->padre = NULL;
				nuevo->hijo_derecha = NULL;
				nuevo->hijo_izquierda = NULL;
				*inicio = nuevo;
				}
				else {
					return 0;
				}

			}
			else {
					Busca_fin(aux, num, 0);
			}
			return 1;
}
/////////////////////////////////////////////////////////////////////////////////////
void Busca_fin(A* inicio,int num,int h){
	if (inicio){
		if (inicio->numero >= num) {
			if (inicio->hijo_izquierda) {
				Busca_fin(inicio->hijo_izquierda, num, h + 1);
			}
			else {
				h++;
				inicio->hijo_izquierda = (A*)malloc(sizeof(A));
				if (inicio->hijo_izquierda) {
					inicio->hijo_izquierda->padre = inicio;
					inicio = inicio->hijo_izquierda;
					inicio->altura = h;
					inicio->hijo_derecha = NULL;
					inicio->hijo_izquierda = NULL;
					inicio->numero = num;
				}
			}
		}
		else {
			if (inicio->hijo_derecha) {
				Busca_fin(inicio->hijo_derecha, num, h + 1);
			}
			else {
				h++;
				inicio->hijo_derecha = (A*)malloc(sizeof(A));
				if (inicio->hijo_derecha) {
					inicio->hijo_derecha->padre = inicio;
					inicio = inicio->hijo_derecha;
					inicio->altura = h;
					inicio->hijo_derecha = NULL;
					inicio->hijo_izquierda = NULL;
					inicio->numero = num;
				}
			}
		}
	}
}
/// ///////////////////////////////////////////////////////////////////
void Checa_Balanceo(A** inicio,int cual[2][50],int *i,int*band)
{
	A* cambio = NULL, * aux2 = NULL, *aux3;;
	short int alt1 = 0, alt2 = 0;
	int fact_eq;
	aux3 =*inicio;
	if (aux3) {
	if(aux3->hijo_izquierda)
	Balanceo(aux3->hijo_izquierda, &alt1);
	else
		alt1 = aux3->altura;
	if (aux3->hijo_derecha)
		Balanceo(aux3->hijo_derecha, &alt2);
	else
		alt2 = aux3->altura;
	fact_eq = alt1 - alt2;
	printf("\nalt 1= %d\nalt 2=%d\nFactor = %d", alt1, alt2, fact_eq);
	if (fact_eq <= -2 || fact_eq >= 2){
*band = 1;
		cual[1][*i] = (*inicio)->numero;
			if (fact_eq <= -2) {//desbalance derecha
				*inicio = RIzquierda((*inicio),cual,*i);
			}
			else {//desbalance izquierda
					*inicio = RDerecha((*inicio),cual,*i);
			}
			aux2 = *inicio;
			revalida_altura(aux2, aux2->altura - 1);
			*i = *i + 1;
		}
	else {
		if((*inicio)->hijo_derecha)
		Checa_Balanceo(&(*inicio)->hijo_derecha,cual,&*i,&*band);
		if ((*inicio)->hijo_izquierda)
			Checa_Balanceo(&(*inicio)->hijo_izquierda,cual,&*i,&*band);
	}
	}
}
//////////////////////////////////////////////////
A* nodo_der_izq(A* inicio) {   
	if (inicio) {
		if (inicio->hijo_izquierda) {
			return(nodo_der_izq(inicio->hijo_izquierda));
		}
		else
			return inicio;
	}
}
//////////////////////////////////////////////////
A* RIzquierda(A* raiz,int cual[2][50],int i) {
	A* nuevaR;
	nuevaR = nodo_der_izq(raiz->hijo_derecha);
	if (nuevaR == raiz->hijo_derecha) {
		cual[0][i] = 1;
		nuevaR->hijo_izquierda = raiz;
		if (raiz->padre) {
			nuevaR->padre = raiz->padre;
			if(raiz->padre->hijo_derecha==raiz) {
				raiz->padre->hijo_derecha = nuevaR;
			}
			else {
				raiz->padre->hijo_izquierda = nuevaR;
			}
		}
		else {
			nuevaR->padre = NULL;
		}
		raiz->hijo_derecha = NULL;
		raiz->padre = nuevaR;
	}
	else {
		cual[0][i] = 2;
		nuevaR->hijo_izquierda = raiz;
		nuevaR->padre->hijo_izquierda = nuevaR->hijo_derecha;
		if (nuevaR->hijo_derecha) {
			nuevaR->hijo_derecha->padre = nuevaR->padre;
		}
		if (raiz->padre) {
			nuevaR->padre = raiz->padre;
			nuevaR->hijo_derecha = raiz->hijo_derecha;
			nuevaR->hijo_derecha->padre = nuevaR;
			if (raiz->padre->hijo_derecha == raiz) {
				raiz->padre->hijo_derecha = nuevaR;
			}
			else {
				raiz->padre->hijo_izquierda = nuevaR;
			}
		}
		else {
			nuevaR->hijo_derecha = raiz->hijo_derecha;
			nuevaR->hijo_derecha->padre = nuevaR;
			nuevaR->padre = NULL;
		}
		raiz->hijo_derecha = NULL;
		raiz->padre = nuevaR;
	}
	return nuevaR;
}
//////////////////////////////////////////////////
A* RDerecha(A* raiz,int cual[2][50],int i) {
	A* nuevaR;
	nuevaR = nodo_iz_der(raiz->hijo_izquierda);
	if (nuevaR == raiz->hijo_izquierda) {
		cual[0][i] = 3;
			nuevaR->hijo_derecha = raiz;
			if (raiz->padre) {
				nuevaR->padre = raiz->padre;
				if (raiz->padre->hijo_derecha == raiz) {
					raiz->padre->hijo_derecha = nuevaR;
				}
				else {
					raiz->padre->hijo_izquierda = nuevaR;
				}
			}
			else {
				nuevaR->padre = NULL;
			}
			raiz->hijo_izquierda = NULL;
	raiz->padre = nuevaR;
	}
	else {
		cual[0][i] = 4;
		nuevaR->hijo_derecha = raiz;
			nuevaR->padre->hijo_derecha = nuevaR->hijo_izquierda;
			if (nuevaR->hijo_izquierda) {
				nuevaR->hijo_izquierda->padre = nuevaR->padre;
			}
		if (raiz->padre) {
			nuevaR->padre = raiz->padre;
			nuevaR->hijo_izquierda = raiz->hijo_izquierda;
			nuevaR->hijo_izquierda->padre = nuevaR;
			if (raiz->padre->hijo_derecha == raiz) {
				raiz->padre->hijo_derecha = nuevaR;
			}
			else {
				raiz->padre->hijo_izquierda = nuevaR;
			}
		}
		else {
			nuevaR->hijo_izquierda = raiz->hijo_izquierda;
			nuevaR->hijo_izquierda->padre = nuevaR;
			nuevaR->padre = NULL;
		}
		raiz->hijo_izquierda = NULL;
		raiz->padre = nuevaR;
	}

	return nuevaR;
}
/////////////////////////////////////////////////////////////////////////////////////
void Balanceo(A* inicio, short int *num) {
	if (inicio) {
		if (inicio->hijo_derecha||inicio->hijo_izquierda) {
			if (inicio->hijo_izquierda) {
				Balanceo(inicio->hijo_izquierda, &*num);
			}
			else {
					Balanceo(inicio->hijo_derecha, &*num);
			}
		}
		else {
			if (inicio->altura > *num) {
				*num = inicio->altura;
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////////
A* elimina_raiz(A**inicio){
	A* aux,*bye;
	if ((*inicio)->hijo_izquierda) {
		aux = nodo_iz_der((*inicio)->hijo_izquierda);
		if ((*inicio)->hijo_derecha) {

			aux->hijo_derecha = (*inicio)->hijo_derecha;
			aux->hijo_derecha->padre = aux;
		}
		else {
			aux->padre = NULL;
			aux->altura = 0;
			free(*inicio);
			return aux;
		}

		if (aux->hijo_izquierda) {
			if ((*inicio) != aux->padre) {
				aux->padre->hijo_derecha = aux->hijo_izquierda;
				aux->hijo_izquierda->padre = aux->padre;
			}
			aux->hijo_izquierda->altura = aux->altura;
		}
		else {
			bye = aux->padre;
			bye->hijo_derecha = NULL;
		}
			if ((*inicio)->hijo_izquierda != aux) {
				aux->hijo_izquierda = (*inicio)->hijo_izquierda;
			}

			*inicio = NULL;
		free(*inicio);
		aux->altura = 0;
		aux->padre = NULL;
		return aux;
	}
	else {
		aux = (*inicio)->hijo_derecha;
		aux->padre = NULL;
		aux->altura = 0;
		*inicio = NULL;
		free(*inicio);
		return aux;
	}
}
// ///////////////////////////////////////////////////////////////////////////
short int Busca_nodo(A**raiz,int num) {
	A* inicio;
	inicio = *raiz;;
	if (inicio) {
		if (inicio->numero == num) {
			if (!inicio->padre) {
				if (inicio->padre == NULL&&!inicio->hijo_derecha&&!inicio->hijo_izquierda)
				{
					return -1;
				}
				else {
					return -2;
				}
			}
			else {
				checa_elimina(&inicio);
			}
			
			return 1;
		}
		else {
			if (inicio->numero < num) {
				Busca_nodo(&inicio->hijo_derecha, num);
			}
			else {
				Busca_nodo(&inicio->hijo_izquierda, num);
			}
		}
	}
	else {
		return 0;
	}
}
///////////////////////////////////////////////////////////////////////////////
void checa_elimina(A **inicio) {
	A* aux,*dad;
	aux = *inicio;
	if (aux->padre){
		if( !aux->hijo_derecha&&!aux->hijo_izquierda) {	// hoja
			dad = aux->padre;
			if (dad->hijo_derecha == aux) {						//hoja derecha
				dad->hijo_derecha = NULL;
				free(aux);
			}
			else {															//hoja izquierda
				dad->hijo_izquierda = NULL;
				free(aux);
			}
		}
		else {
			if (aux->hijo_izquierda) {								//si existe hijo izquierda
				dad = nodo_iz_der(aux->hijo_izquierda);
				if (dad == aux->hijo_izquierda) {
					dad->padre = aux->padre;
					if (aux->padre->hijo_izquierda == aux)
						aux->padre->hijo_izquierda = dad;
					else
						aux->padre->hijo_derecha = dad;
					dad->altura = aux->altura;
					dad->hijo_derecha = aux->hijo_derecha;
					if (dad->hijo_derecha) {
						dad->hijo_derecha->padre = dad;
					}
					aux = NULL;
					free(aux);
				}
				else{
				if (aux->padre->hijo_izquierda == aux)
					aux->padre->hijo_izquierda = dad;
				else
					aux->padre->hijo_derecha = dad;
				if (dad->hijo_izquierda) {
					dad->hijo_izquierda->padre = dad->padre;
					dad->hijo_izquierda->altura = dad->altura;
					dad->padre->hijo_derecha = dad->hijo_izquierda;
				}
				else {
					dad->padre->hijo_derecha = NULL;
				}
				dad->hijo_derecha = aux->hijo_derecha;
				if(dad->hijo_derecha)
				dad->hijo_derecha->padre = dad;
				if (aux->hijo_izquierda != dad) {
					dad->hijo_izquierda = aux->hijo_izquierda;
					dad->hijo_izquierda->padre = dad;
				}
				dad->altura = aux->altura;
				dad->padre = aux->padre;
				aux = NULL;
				free(aux);
				}


			}
			else {															//No existe hijo izquierda
				dad = aux->padre;
				if (dad->hijo_derecha == aux) {
					dad->hijo_derecha = aux->hijo_derecha;
				}
				else {
					dad->hijo_izquierda = aux->hijo_derecha;
				}
				aux->hijo_derecha->padre = dad;
				aux->hijo_derecha->altura = aux->altura;
				aux = NULL;
				free(aux);
			}
			
		}
	}
}
/// ////////////////////////////////////////////////////////////////////
void revalida_altura(A* inicio,int num) {
	if (inicio) {
		inicio->altura = num;
		if (inicio->hijo_izquierda) {	
			revalida_altura(inicio->hijo_izquierda, inicio->altura + 1);
		}
		if (inicio->hijo_derecha) {
			revalida_altura(inicio->hijo_derecha, inicio->altura + 1);
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
A* nodo_iz_der(A* inicio) {
	if (inicio) {
		if (inicio->hijo_derecha) {
			return(nodo_iz_der(inicio->hijo_derecha));
		}
		else
			return inicio;
	}
}
///////////////////////////////////////////////////////////////////////////////
#endif