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
	Jogo *temp = new Jogo[capacidade_vetor+5]; // cria um vetor temporário com a nova capacidade
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

			if ((i == capacidade_vetor-1) && (numRegistrosCSV > capacidade_vetor)){
				redimensionaVetor(jogos, capacidade_vetor);
			}	

			entrada >> jogos[i].identificador;
			entrada.ignore(2); // ignora ; e abre aspas
			getline(entrada, jogos[i].nome, '"');
			entrada.ignore(1);
			entrada >> jogos[i].ano_lancamento; 
			entrada.ignore(2);
			getline(entrada, jogos[i].plataforma, '"');
			entrada.ignore(2);
			getline(entrada, jogos[i].descricao, '"');
			getline(entrada, linha); // ler o enter
			
							
		}
		capacidade = capacidade_vetor;
	} else {
		cout << "Arquivo nao encontrado";
	}
}

void imprimirJogos(Jogo jogos[], int posicao){
	if(jogos[posicao].identificador != -1){
		cout << endl 
		<< jogos[posicao].identificador << " " 
		<< jogos[posicao].nome << " " 
		<< jogos[posicao].ano_lancamento << " " 

		<< jogos[posicao].plataforma << " " 
		<< jogos[posicao].descricao << endl;
	}
}

void menu_impressao(Jogo vet_Jogos[], int num_registros){
	cout << endl << "Deseja que os dados do arquivo sejam impressos?" << endl
	<< "0 - Não" << endl << "1 - Sim" << endl;
		int opcao_impressao=0;
		cin >> opcao_impressao;
		int inicio_impressao_partes, final_impressao_partes;
		if ((opcao_impressao != 0) && (opcao_impressao != 1)){
			cout << "ERRO! Tente novamente." << endl;
		}
		if (opcao_impressao == 1){
			cout << endl << "Deseja o arquivo inteiro ou somente um trecho?" << endl
			<< "1 - Inteiro" << endl << "2 - Trecho" << endl;
			int opcao_menu;
			cin >> opcao_menu;
			if (opcao_menu != 1 && opcao_menu != 2){
				cout << "ERRO! Tente novamente." << endl;
			}
			else if (opcao_menu == 1){
				for (int i = 0; i < num_registros; i++){
					imprimirJogos(vet_Jogos, i);
				}
			}
			else if (opcao_menu == 2){
				cout << endl << "Digite o trecho" << endl;
				cin >> inicio_impressao_partes >> final_impressao_partes;
				if (inicio_impressao_partes < 1 || final_impressao_partes > num_registros || inicio_impressao_partes > final_impressao_partes){
					cout << "ERRO! Tente novamente." << endl;
				}
				else {
					for(int i = 0; i < num_registros; i++){
						if ((i+1 >= inicio_impressao_partes) && (i+1 <= final_impressao_partes)){
							imprimirJogos(vet_Jogos, i);
						}
					}
				}
			}
		}
}


void salvar(Jogo vet_Jogos[], int opcao_salvar, int num_registros, int num_registos_noCSV);
// o campo num_registos_noCSV é necessário para que o número de registros seja atualizado corretamente no arquivo CSV, já que o campo num_registros pode conter jogos deletados (com identificador -1) e não deve ser considerado para a contagem de registros no arquivo CSV

void inserirJogos(Jogo*& vet_Jogos, int& capacidade, int& num_registros){
	/*if (num_registros == capacidade){
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
	
	cout << "Deseja adicionar outro? Digite 1 para 'sim'." << endl;
	int opcao_repeticao;
	cin >> opcao_repeticao;
	if (opcao_repeticao == 1){
		inserirJogos(vet_Jogos, capacidade, num_registros);
	}
	else {
		cout << "Deseja salvar as alterações?" << endl
		<< "0 - Não" << endl << "1- Sim (substituir)" << endl <<
		"2 - Sim (criar outro arquivo)" << endl;
		int opcao_salvar;
		cin >> opcao_salvar;
		
		if ((opcao_salvar == 1) || (opcao_salvar == 2)){
			salvar(vet_Jogos, opcao_salvar, num_registros);			
		}
	}*/

	cout << "Deseja adicionar um jogo?" << endl;
	cout << "0 - Não" << endl << "1 - Sim" << endl;
	int opcao_insercao;
	cin >> opcao_insercao;
	while (opcao_insercao == 1){
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

		cout << "Deseja adicionar outro? Digite 1 para 'sim'." << endl;
		cin >> opcao_insercao;
	}

		cout << "Deseja salvar as alterações?" << endl
		<< "0 - Não" << endl << "1- Sim (substituir)" << endl <<
		"2 - Sim (criar outro arquivo)" << endl;
		int opcao_salvar;
		cin >> opcao_salvar;
		
		if ((opcao_salvar == 1) || (opcao_salvar == 2)){
			salvar(vet_Jogos, opcao_salvar, num_registros, num_registros);
			//aqui o campo num_registos_noCSV é igual ao campo num_registros, já que nesse ponto do código não houve deleção de jogos, ou seja, o número de registros no vetor é igual ao número de registros no arquivo CSV			
		}
}


void delecao(Jogo*& vet_Jogos, int& num_registros){
	cout << endl << "Deseja apagar por plataforma, ano de lançamento ou nome?" << endl
	<< "0 - Plataforma" << endl << "1 - Ano de lançamento" << endl << "2 - Nome" << endl;
	int opcao_delecao;
	cin >> opcao_delecao;
	

	while(opcao_delecao == 0 || opcao_delecao == 1 || opcao_delecao == 2){
		switch(opcao_delecao){
			case 0: {
				cout << "Digite o nome da plataforma:" << endl;
				string plat_delecao;
				cin.ignore();
				getline(cin, plat_delecao);
				
				
				for (int i=0; i< num_registros; i++){
					if (vet_Jogos[i].plataforma == plat_delecao && vet_Jogos[i].identificador != -1){ // o campo identificador != -1 é necessário para que jogos já deletados não sejam considerados para deleção novamente, o que poderia causar a contagem de registros no arquivo CSV ficar incorreta
						vet_Jogos[i].identificador = -1;
					}
				}
				break;
			}
			case 1: {
				cout << "Digite o ano de lançamento:" << endl;
				int ano_delecao;
				cin >> ano_delecao;
				for (int i=0; i< num_registros; i++){
					if (vet_Jogos[i].ano_lancamento == ano_delecao && vet_Jogos[i].identificador != -1){
						vet_Jogos[i].identificador = -1;
					}
				}
				break;
			}
			case 2: {
				cout << "Digite o nome do jogo:" << endl;
				string nome_delecao;
				cin.ignore();
				getline(cin, nome_delecao);
				for (int i=0; i< num_registros; i++){
					if (vet_Jogos[i].nome == nome_delecao && vet_Jogos[i].identificador != -1){
						vet_Jogos[i].identificador = -1;
					}
				}
				break;
			}
			default: {
				cout << "ERRO! Tente novamente" << endl;
				return delecao(vet_Jogos, num_registros);
			}
		}

			int contNum_registros = 0;

			for(int i=0;i<num_registros;i++){
				if(vet_Jogos[i].identificador != -1){
					contNum_registros++;
				}
			}

			cout << "Deseja salvar as alterações?" << endl
			<< "0 - Não" << endl << "1- Sim (substituir)" << endl <<
			"2 - Sim (criar outro arquivo)" << endl;
			int opcao_salvar;
			cin >> opcao_salvar;
			
			if ((opcao_salvar == 1) || (opcao_salvar == 2)){
				salvar(vet_Jogos, opcao_salvar, num_registros, contNum_registros);
			}



			cout << endl << "Deseja apagar por plataforma, ano de lançamento ou nome?" << endl
			<< "0 - Plataforma" << endl << "1 - Ano de lançamento" << endl << "2 - Nome" << endl << "3 - Não apagar mais" << endl;
			cin >> opcao_delecao;
	}
	
		/*cout << "Processo concluído. Digite 1 para fazer outra deleção." << endl;
		int opcao_repeticao;
		cin >> opcao_repeticao;
		if (opcao_repeticao == 1){
			delecao(vet_Jogos, num_registros);
		} */
		
		
		
}


void salvar(Jogo vet_Jogos[], int opcao_salvar, int num_registros, int num_registos_noCSV) {

	if (opcao_salvar == 1){
		ofstream saidaDadosCSV("dados.csv", ios::trunc); // trunc apaga o conteúdo do arquivo antes de reescrever
		saidaDadosCSV << "identificador" << ";" << "nome" << ";" << "ano_lancamento" << ";" << "plataforma" << ";" << "descricao" << endl;
		saidaDadosCSV << num_registos_noCSV << endl;
		for(int i=0; i<num_registros; i++){
			if (vet_Jogos[i].identificador != -1){
				saidaDadosCSV << vet_Jogos[i].identificador << ";\"" 
				<< vet_Jogos[i].nome << "\";" 
				<< vet_Jogos[i].ano_lancamento << ";\"" 
				<< vet_Jogos[i].plataforma << "\";\"" 
				<< vet_Jogos[i].descricao << "\"" << endl;
			}
		}

	}
		if (opcao_salvar == 2){
			cout << "Digite um nome para um novo arquivo" << endl;
			string nome_novo;
			string lixo;
			getline(cin, lixo); // para limpar o buffer de entrada
			getline(cin, nome_novo);
			ofstream saidaNova(nome_novo);
			saidaNova << "identificador" << ";" << "nome" << ";" << "ano_lancamento" << ";" << "plataforma" << ";" << "descricao" << endl;
			saidaNova << num_registos_noCSV << endl;
			for(int i=0; i<num_registros; i++){
				if (vet_Jogos[i].identificador != -1){
					saidaNova << vet_Jogos[i].identificador << ";\"" 
					<< vet_Jogos[i].nome << "\";" 
					<< vet_Jogos[i].ano_lancamento << ";\"" 
					<< vet_Jogos[i].plataforma << "\";\"" 
					<< vet_Jogos[i].descricao << "\"" << endl;
				}
			}
		}
}

int main(){
	int capacidade = 40;
	int num_registros = 0;
	Jogo* vet_Jogos = nullptr; // inicializa o ponteiro do vetor de jogos como nulo, para que a função lerArquivo_CSV possa alocar a memória necessária para o vetor e atribuir o endereço ao ponteiro vet_Jogos. Dessa forma, o vetor de jogos estará disponível para uso em todo o programa, incluindo as funções de inserção, deleção e impressão.
	/*cout << "Digite o nome do arquivo: " << endl;
	string nome_arquivo;
	cin.ignore();
	getline(cin, nome_arquivo);*/
	lerArquivo_CSV(vet_Jogos, capacidade, num_registros);
	cout << endl;
	int opcao_menu=-1;

	while(opcao_menu != 0){
		

		cout << "===========================================" << endl;
		cout << "                 GAMES                     " << endl;
		cout << "===========================================" << endl;
		cout << "1 - IMPRIMIR GAMES" << endl;
		cout << "2 - INSERIR GAMES" << endl;
		cout << "3 - DELETAR GAMES" << endl;
		cout << "0 - SAIR" << endl;

		cin >> opcao_menu;

		switch(opcao_menu){
			case 1:
				menu_impressao(vet_Jogos, num_registros);
				break;
			case 2:
				inserirJogos(vet_Jogos, capacidade, num_registros);
				break;
			case 3:
				delecao(vet_Jogos, num_registros);
				break;
			case 0:
				cout << "Saindo do programa..." << endl;
				break;
			default:
				cout << "Opção inválida. Tente novamente." << endl;
		}
		}

	delete[] vet_Jogos;
		
	return 0;

}
