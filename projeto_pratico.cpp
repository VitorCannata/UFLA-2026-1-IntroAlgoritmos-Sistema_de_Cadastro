#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Jogo{
	int identificador; 
	int ano_lancamento;
	string nome; 
	string plataforma;
	string descricao;
};


void redimensionaVetor(Jogo*& jogos, int& capacidade_vetor){ // o Jogo*& serve para que o parâmetro ocupe o mesmo espaço de memória do vetor original
	Jogo *temp = new Jogo[capacidade_vetor+5];
	for (int i=0; i<capacidade_vetor; i++){
		temp[i] = jogos[i];
	}
	delete[] jogos;
	jogos = temp;
	capacidade_vetor += 5;
}


// Moudlarizar leitura
void lerArquivo_CSV(Jogo*& jogos, int& capacidade, int& num_registros){ // o Jogo*& serve para que o parâmetro ocupe o mesmo espaço de memória do vetor original 
	ifstream entrada("dados.csv");
	if(entrada){
		string linha;
		getline(entrada, linha); // ignora a primeira linha
		int numRegistrosCSV;
		entrada >> numRegistrosCSV;
		num_registros = numRegistrosCSV;
		int capacidade_vetor = capacidade;
		getline(entrada, linha); // ler o enter
		jogos = new Jogo[capacidade_vetor];

		for(int i = 0; i < numRegistrosCSV; i++){
			entrada >> jogos[i].identificador;
			entrada.ignore(2); // ignora ; e abre aspas
			getline(entrada, jogos[i].nome, '"');
			entrada.ignore(1);
			entrada >> jogos[i].ano_lancamento; // ta peg&&o errado
			entrada.ignore(2);
			getline(entrada, jogos[i].plataforma, '"');
			entrada.ignore(2);
			getline(entrada, jogos[i].descricao, '"');
			getline(entrada, linha); // ler o enter
			
			if ((i == capacidade_vetor-1) && (numRegistrosCSV > capacidade_vetor)){
				redimensionaVetor(jogos, capacidade_vetor);
			}					
		}
		capacidade = capacidade_vetor;
	} else {
		cout << "Arquivo nao encontrado";
	}
}

void imprimirJogos(Jogo jogos[], int posicao){
	cout << endl 
	<< jogos[posicao].identificador << " " 
	<< jogos[posicao].nome << " " 
	<< jogos[posicao].ano_lancamento << " " 
	<< jogos[posicao].plataforma << " " 
	<< jogos[posicao].descricao << endl;
}

void menu_impressao(Jogo vet_Jogos[], int num_registros){
	cout << endl << "Deseja que os dados do arquivo sejam impressos?" << endl
	<< "0 - Nao" << endl << "1 - Sim" << endl;
		int opcao_impressao=0;
		cin >> opcao_impressao;
		int inicio_impressao_partes, final_impressao_partes;
		if ((opcao_impressao != 0) && (opcao_impressao != 1)){
			cout << "ERRO! Tente novamente." << endl;
		}
		if (opcao_impressao == 1){
			cout << endl << "Deseja o arquivo inteiro ou somente um trecho?" << endl
			<< "2 - Inteiro" << endl << "3 - Trecho" << endl;
			cin >> opcao_impressao;
			if(opcao_impressao != 2 && opcao_impressao != 3)
				cout << "ERRO! Tente novamente." << endl;
				else if(opcao_impressao == 2)
					for(int i = 0; i < num_registros; i++){
						imprimirJogos(vet_Jogos, i);
					}
					else if (opcao_impressao == 3){
						cout << endl << "Digite o trecho" << endl;
						cin >> inicio_impressao_partes >> final_impressao_partes;
						if(inicio_impressao_partes < 1 || final_impressao_partes > num_registros || inicio_impressao_partes > final_impressao_partes)
							cout << "ERRO! Tente novamente." << endl;
						else
							for(int i = 0; i < num_registros; i++){
								if ((i+1 >= inicio_impressao_partes) && (i+1 <= final_impressao_partes)){
									imprimirJogos(vet_Jogos, i);
								}
							}
					}
		}
}

void inserirJogos(Jogo*& vet_Jogos, int& capacidade, int& num_registros){
	if (num_registros == capacidade){
		redimensionaVetor(vet_Jogos, capacidade);
	}
	cout << "Digite o identificador do jogo: ";
	cin >> vet_Jogos[num_registros].identificador;
	cin.ignore(); // Limpa o buffer de entrada
	cout << "Digite o nome do jogo: ";
	getline(cin, vet_Jogos[num_registros].nome);
	cout << "Digite o ano de lancamento do jogo: ";
	cin >> vet_Jogos[num_registros].ano_lancamento;
	cin.ignore(); // Limpa o buffer de entrada
	cout << "Digite a plataforma do jogo: ";
	getline(cin, vet_Jogos[num_registros].plataforma);
	cout << "Digite a descricao do jogo: ";
	getline(cin, vet_Jogos[num_registros].descricao);
	num_registros++;
}

int main(){
	int capacidade = 40;
	int num_registros = 0;
	Jogo* vet_Jogos = new Jogo[capacidade];
	lerArquivo_CSV(vet_Jogos, capacidade, num_registros);
	int opcao_menu=-1;

	while(opcao_menu != 0){
		cout << "===========================================" << endl;
	cout << "                 GAMES                     " << endl;
	cout << "===========================================" << endl;
	cout << "1 - IMPRIMIR GAMES" << endl;
	cout << "2 - INSERIR GAMES" << endl;

	cin >> opcao_menu;

	switch(opcao_menu){
		case 1:
			menu_impressao(vet_Jogos, num_registros);
			break;
		case 2:
			inserirJogos(vet_Jogos, capacidade, num_registros);
			break;
		case 0:
			cout << "Saindo do programa..." << endl;
			break;
		default:
			cout << "Opcao invalida. Tente novamente." << endl;
	}

	}
	
	return 0;

}
