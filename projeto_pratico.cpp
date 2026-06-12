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
		getline(entrada, linha); // ler o enter
		jogo *vet_jogos = new jogo[num_registros];
			for(int i = 0; i < num_registros; i++){
				entrada >> vet_jogos[i].identificador;
				entrada.ignore(2); // ignora ; e abre aspas
				getline(entrada, vet_jogos[i].nome, '"');
				entrada.ignore(1);
				entrada >> vet_jogos[i].ano_lancamento; // Corrigido
				entrada.ignore(2);
				getline(entrada, vet_jogos[i].plataforma, '"');
				entrada.ignore(2);
				getline(entrada, vet_jogos[i].descricao, '"');
				getline(entrada, linha); // ler o enter
				
				cout << endl << vet_jogos[i].identificador << " " << vet_jogos[i].nome << " " << vet_jogos[i].ano_lancamento << " " 
					<< vet_jogos[i].plataforma << " " << vet_jogos[i].descricao << endl;
		}
		delete[] vet_jogos;
	}
	else cout << "Arquivo não encontrado";

}
