#include <iostream>
using namespace std;

#define MAX_NODO 10 // Quantidades de nos do grafo

int longestPath(int node);
int verificarPath(int cam[], int tam, int node);
int path[MAX_NODO];
				    			 //0,1,2,3,4,5,6,7,8,9
int matrix[MAX_NODO][MAX_NODO] = {{0,1,0,0,0,1,0,0,0,0},//0
								  {1,0,0,0,1,0,0,0,0,0},//1
								  {0,0,0,1,0,0,0,1,0,0},//2
								  {0,0,1,0,1,0,1,1,0,0},//3
								  {0,1,0,1,0,1,0,0,0,0},//4
								  {1,0,0,1,1,0,0,0,1,0},//5
								  {0,0,0,1,0,0,0,1,0,1},//6
								  {0,0,1,1,0,0,1,0,0,1},//7
								  {0,0,0,0,0,1,0,0,0,0},//8
								  {0,0,0,0,0,0,1,1,0,0},//9
								  };


// int matrix[MAX_NODO][MAX_NODO] = {{0,1,1,0},
// 							  	  {1,0,0,1},
// 					              {1,0,0,0},
// 					              {0,1,0,0}
// 					          };

//Função para verificar se um determinado Nó ja foi visitado.
int verificarPath(int cam[], int tam, int node){
	int i;
	if(tam == 0)
		return 1;

	for(i=0; i<tam; i++){
		if(cam[i] == node)
			return 0;
	}
	return 1;

}


int longestPath(int node){
	int cam[MAX_NODO], tam=0,max=0, dest, i;
	//Inicializa um vetor com valor -1
	for(i=0; i<MAX_NODO; i++)
		cam[i] = -1;

	dest = 0;
	while(1){
		if(matrix[node][dest] == 1){//Verifica se existe uma aresta entre nodo e dest
			if(verificarPath(cam, tam, dest) == 1){//Caso exista uma aresta, verifica se o destino já está no caminho
				cam[tam] = node;//salva os nodos que foram visitados
				node = dest;
				tam++;
				if(tam == MAX_NODO - 1){//Verifica se já foi encontrado um caminho de tamanho maximo
					for(i=0; i<tam; i++){
						path[i] = cam[i];
					}
					path[i] = dest;
					return tam ;
				}
				dest=0;
				continue;
			}
		}
		dest++;
		if(dest >= MAX_NODO){//verifica se o tamanho maximo da matriz ja foi alcançado, para então realizar o backtracking
			if(tam>max){//verifica se na execução atual foi encontrado um caminho maior
				for(i=0; i<tam; i++)
					path[i] = cam[i];
				path[i] = node;
				max = tam;
			}
			tam--; //realização do backtracking
			dest = node;
			node = cam[tam];

			dest++;//contiunação de onde parou
		}
		if(tam < 0){//caso o tamanho do vetor seja negativo, é dito que todas as possibilidades ja foram testadas
			return max;
		}
	}
}

int main(void){
	int x, tam, i;

	while(1){
		cout << "Digite um no para realizar a busca do caminho mais longo, caso deseje parar, digite -1: ";
		cin >> x;
		if(x == -1)
			break;

		tam = longestPath(x);

		cout <<"Tamanho do caminho mais longo: "<< tam << "  Origem: " << path[0] <<"\n"<< "Caminho: ";

		for(i=1; i<=tam; i++){
			if(i == tam)
				cout <<" "<< path[i];
				//printf("%d\n", path[i]);
			else
				cout <<" "<< path[i];
				//printf("%d -> ", path[i]);
		}
		cout << "\n";

	}
	return 0;
}
