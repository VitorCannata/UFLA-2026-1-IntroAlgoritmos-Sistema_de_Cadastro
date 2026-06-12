#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct jogo{
	int identificador; 
	int ano_lancamento;
	string nome; 
	string plataforma;
	string descricao;
};

int main(){
	string nome_entrada;
	getline(cin, nome_entrada);
	
	ifstream entrada(nome_entrada);
	
	if(entrada){
		string linha;
		getline(entrada, linha); // ignora a primeira linha
		int num_registros;
		entrada >> num_registros;
		int capacidade_vetor=40;
		getline(entrada, linha); // ler o enter
		jogo *vet_jogos = new jogo[capacidade_vetor];
		
		cout << "Deseja que os dados do arquivo sejam impressos?" << endl
		<< "0 - Não" << endl << "1 - Sim" << endl;
		int opção_impressão=0;
		cin >> opção_impressão;
		int início_impressão_partes, final_impressão_partes;
		
		if ((opção_impressão != 0) and (opção_impressão != 1)){
			cout << "ERRO! Tente novamente." << endl;
			return 1;
		}
		if (opção_impressão == 1){
			cout << endl << "Deseja o arquivo inteiro ou somente um trecho?" << endl
			<< "2 - Inteiro" << endl << "3 - Trecho" << endl;
			cin >> opção_impressão;
			if (opção_impressão == 3){
				cout << endl << "Digite o trecho" << endl;
				cin >> início_impressão_partes >> final_impressão_partes;
			}
		}
			
			for(int i = 0; i < num_registros; i++){
				entrada >> vet_jogos[i].identificador;
				entrada.ignore(2); // ignora ; e abre aspas
				getline(entrada, vet_jogos[i].nome, '"');
				entrada.ignore(1);
				entrada >> vet_jogos[i].ano_lancamento; // ta pegando errado
				entrada.ignore(2);
				getline(entrada, vet_jogos[i].plataforma, '"');
				entrada.ignore(2);
				getline(entrada, vet_jogos[i].descricao, '"');
				getline(entrada, linha); // ler o enter
				
				if (opção_impressão == 2){
					cout << endl << vet_jogos[i].identificador << " " << vet_jogos[i].nome << " " << vet_jogos[i].ano_lancamento << " " 
					<< vet_jogos[i].plataforma << " " << vet_jogos[i].descricao << endl;
				}
				if ((opção_impressão == 3) and ((i+1 >= início_impressão_partes) and (i+1 <= final_impressão_partes))){
					cout << endl << vet_jogos[i].identificador << " " << vet_jogos[i].nome << " " << vet_jogos[i].ano_lancamento << " " 
					<< vet_jogos[i].plataforma << " " << vet_jogos[i].descricao << endl;
				}
					
				if ((i == capacidade_vetor-1) and (num_registros > capacidade_vetor)){
					jogo *temp = new jogo[capacidade_vetor+5];
					for (int i=0; i<capacidade_vetor; i++){
						temp[i] = vet_jogos[i];
					}
					delete[] vet_jogos;
					vet_jogos = temp;
					capacidade_vetor += 5;
				}					
		}
		
		cout << endl << "Capacidade final: " << capacidade_vetor << endl;
		delete[] vet_jogos;
	}
	else {
		cout << "Arquivo não encontrado";
	}
	return 0;
}
