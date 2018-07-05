#include <iostream>
using namespace std;

#define MAX_NODO 20 // Quantidades de nos do grafo

int longestPath(int node);
int verificarPath(int cam[], int tam, int node);
int path[MAX_NODO];
int pesoPath = 0;

//Matrizes de Testes

//Matriz 3x3
// int matrix[MAX_NODO][MAX_NODO] = {{0,2,0},//0
// 								  {3,0,2},//1
// 								  {0,3,0},//2
// 								  };


// //Matriz 10x10
// 				    			 //0,1,2,3,4,5,6,7,8,9
// int matrix[MAX_NODO][MAX_NODO] = {{0,2,1,0,0,0,0,0,0,0},//0
// 								  {2,0,2,5,0,0,0,0,0,0},//1
// 								  {1,2,0,3,6,5,0,0,0,0},//2
// 								  {0,5,3,0,2,0,1,0,0,10},//3
// 								  {0,0,6,2,0,8,0,4,0,0},//4
// 								  {0,0,5,0,8,0,0,6,0,9},//5
// 								  {0,0,0,1,0,0,0,3,7,5},//6
// 								  {0,0,0,0,4,6,3,0,0,0},//7
// 								  {0,0,0,0,0,0,7,0,0,3},//8
// 								  {0,0,0,10,0,9,5,0,3,0},//9
// 								  };


//Matriz 15x15
				    			 // 00,01,02,03,04,05,06,07,08,09,10,11,12,13,14
// int matrix[MAX_NODO][MAX_NODO] = {{ 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,15},//0
// 								  { 2, 0, 2, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//1
// 								  { 1, 2, 0, 3, 6, 5, 0, 0, 0, 0, 0, 0, 0, 0,10},//2
// 								  { 0, 5, 3, 0, 2, 0, 1, 0, 0,10, 0 ,0 ,0, 0, 0},//3
// 								  { 0, 0, 6, 2, 0, 8, 0, 4, 0, 0, 0, 0, 0, 0, 0},//4
// 								  { 0, 0, 5, 0, 8, 0, 0, 6, 0, 9, 0, 0, 7, 0, 0},//5
// 								  { 0, 0, 0, 1, 0, 0, 0, 3, 7, 5, 0, 0, 0, 0, 0},//6
// 								  { 0, 0, 0, 0, 4, 6, 3, 0, 0, 0, 3, 0, 0, 0, 0},//7
// 								  { 0, 0, 0, 0, 0, 0, 7, 0, 0, 3, 5, 7, 0,10, 0},//8
// 								  { 0, 0, 0,10, 0, 9, 5, 0, 3, 0, 1, 4, 0, 0, 9},//9
// 								  { 0, 0, 0, 0, 0, 0, 0, 3, 5, 1, 0, 0, 0, 5, 0},//10
// 								  { 0, 0, 0, 0, 0, 0, 0, 0, 7, 4, 0, 0, 5, 0, 0},//11
// 								  { 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 5, 0, 1, 4},//12
// 								  { 0, 0, 0, 0, 0, 0, 0, 0,10, 0, 5, 0, 1, 0, 3},//13
// 								  {15, 0,10, 0, 0, 0, 0, 0, 0, 9, 0, 0, 4, 3, 0},//14
// 								  };



//Matriz 20x20
				    			 //00,01,02,03,04,05,06,07,08,09,10,11,12,13,14,15,16,17,18,19
int matrix[MAX_NODO][MAX_NODO] = {{ 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,15,15,15,15,15,15},//0
								  { 2, 0, 2, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//1
								  { 1, 2, 0, 3, 6, 5, 0, 0, 0, 0, 0, 0, 0, 0,10,10,10,10,10,10},//2
								  { 0, 5, 3, 0, 2, 0, 1, 0, 0,10, 0 ,0 ,0, 0, 0, 0, 0, 0, 0, 0},//3
								  { 0, 0, 6, 2, 0, 8, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//4
								  { 0, 0, 5, 0, 8, 0, 0, 6, 0, 9, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0},//5
								  { 0, 0, 0, 1, 0, 0, 0, 3, 7, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},//6
								  { 0, 0, 0, 0, 4, 6, 3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0},//7
								  { 0, 0, 0, 0, 0, 0, 7, 0, 0, 3, 5, 7, 0,10, 0, 0, 0, 0, 0, 0},//8
								  { 0, 0, 0,10, 0, 9, 5, 0, 3, 0, 1, 4, 0, 0, 9, 9, 9, 9, 9, 9},//9
								  { 0, 0, 0, 0, 0, 0, 0, 3, 5, 1, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0},//10
								  { 0, 0, 0, 0, 0, 0, 0, 0, 7, 4, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0},//11
								  { 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 5, 0, 1, 4, 4, 4, 4, 4, 4},//12
								  { 0, 0, 0, 0, 0, 0, 0, 0,10, 0, 5, 0, 1, 0, 3, 3, 3, 3, 3, 3},//13
								  {15, 0,10, 0, 0, 0, 0, 0, 0, 9, 0, 0, 4, 3, 0, 4, 0, 0, 0, 0},//14
								  {15, 0,10, 0, 0, 0, 0, 0, 0, 9, 0, 0, 4, 3, 4, 0, 8, 0, 0, 0},//15
								  {15, 0,10, 0, 0, 0, 0, 0, 0, 9, 0, 0, 4, 3, 0, 8, 0,12, 0, 0},//16
								  {15, 0,10, 0, 0, 0, 0, 0, 0, 9, 0, 0, 4, 3, 0, 0,12, 0,16, 0},//17
								  {15, 0,10, 0, 0, 0, 0, 0, 0, 9, 0, 0, 4, 3, 0, 0, 0,16, 0,20},//18
								  {15, 0,10, 0, 0, 0, 0, 0, 0, 9, 0, 0, 4, 3, 0, 0, 0, 0,20, 0},//19
								  };


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
	int cam[MAX_NODO], tam=0,max=0, dest, i, peso=0;
	//Inicializa um vetor com valor -1
	for(i=0; i<MAX_NODO; i++)
		cam[i] = -1;

	dest = 0;
	while(1){
		if(matrix[node][dest] > 0){//Verifica se existe uma aresta entre nodo e dest
			if(verificarPath(cam, tam, dest) == 1){//Caso exista uma aresta, verifica se o destino já está no caminho
				peso += matrix[node][dest];

				cam[tam] = node;//salva os nodos que foram visitados
				node = dest;
				tam++;
	
				dest=0;
				continue;
			}
		}
		dest++;
		do{
			if(dest >= MAX_NODO){//verifica se o tamanho maximo da matriz ja foi alcançado, para então realizar o backtracking
				if(peso>pesoPath){//verifica se na execução atual foi encontrado um caminho maior
					for(i=0; i<tam; i++)
						path[i] = cam[i];
					path[i] = node;
					max = tam;
					pesoPath = peso;
				}
				tam--; //realização do backtracking
				dest = node;
				node = cam[tam];
				peso -= matrix[node][dest];
				
				dest++;
			}
		}while(dest >= MAX_NODO);

		if(tam < 0){//caso o tamanho do vetor seja negativo, é dito que todas as possibilidades ja foram testadas
			return max;
		}
	}
}

int main(void){
	int x, tam, i;
	clock_t t_inicial, t_final;
   	double tempo_gasto;


	while(1){
		cout << "Digite um no para realizar a busca do caminho mais longo, caso deseje parar, digite -1: ";
		cin >> x;
		if(x == -1)
			break;

		t_inicial = clock();
		tam = longestPath(x);
		t_final = clock();

		tempo_gasto = ( (double) (t_final - t_inicial) ) / CLOCKS_PER_SEC;
		cout <<"Tempo gasto:"<<  tempo_gasto << "s\n";

		cout <<"Tamanho do caminho mais longo: "<< tam << "\n";

		if(tam > 0){
			cout << "Origem: " << path[0] <<"\n"<< "Caminho: ";
			for(i=1; i<=tam; i++){
				if(i == tam)
					cout <<" "<< path[i] << "\n";
				else
					cout <<" "<< path[i] << "->";
			}
			cout << "Peso do caminho encontrado = " << pesoPath << "\n";
		}else
			cout << "Não existe caminho\n";

		for(i=0; i<MAX_NODO; i++)
			path[i] = -1;
		pesoPath = 0;
	}
	return 0;
}