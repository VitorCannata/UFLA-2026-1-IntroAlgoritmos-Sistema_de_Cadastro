/* NOMES: Nycollas Richard Pereira dos Santos, Luís Fellipe Dias Teodoro, Vitor Cannata de Carvalho
 * TURMA: 10A
 * TEMA: Games
*/

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Registro para informações do CSV
struct Jogo{
	int identificador; 
	int ano_lancamento;
	string nome; 
	string plataforma;
	string descricao;
};

// Redimensionamento de vetor
void redimensionaVetor(Jogo*& jogos, int& capacidade_vetor){ // o Jogo*& serve para que o parâmetro ocupe o mesmo espaço de memória do vetor original
	Jogo *temp = new Jogo[capacidade_vetor+5]; // cria um vetor temporário com a nova capacidade
	for (int i=0; i<capacidade_vetor; i++){
		temp[i] = jogos[i];
	}
	delete[] jogos;
	jogos = temp;
	capacidade_vetor += 5;
}

// Leitura de arquivo CSV
void lerArquivo_CSV(Jogo*& jogos, int& capacidade, int& num_registros){ // o Jogo*& serve para que o parâmetro ocupe o mesmo espaço de memória do vetor original
	ifstream entrada("dados.csv");
	
	if (entrada){
		string linha;
		getline(entrada, linha); // ignora a primeira linha
		int numRegistrosCSV;
		entrada >> numRegistrosCSV;
		num_registros = numRegistrosCSV;
		int capacidade_vetor = capacidade;
		getline(entrada, linha); // ler o enter
		jogos = new Jogo[capacidade_vetor];

		for (int i = 0; i < numRegistrosCSV; i++){
			if ((i == capacidade_vetor-1) and (numRegistrosCSV > capacidade_vetor)){
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
	}
	
	else {
		cout << "Arquivo não encontrado.";
	}
}

// Impressão de jogos com cout
void imprimirJogos(Jogo jogos[], int posicao){
	if (jogos[posicao].identificador != -1){ 	// A condição é para não imprimir jogos com deleção lógica
		cout << endl 
		<< jogos[posicao].identificador << ": " 
		<< jogos[posicao].nome << ", " 
		<< jogos[posicao].ano_lancamento << ", " 
		<< jogos[posicao].plataforma << ", " 
		<< jogos[posicao].descricao << endl;
	}
}

// Menu para impressão de jogos em cout
void menu_impressao(Jogo vet_Jogos[], int num_registros){
	int inicio_impressao_partes, final_impressao_partes;
	cout << endl << "Deseja o arquivo inteiro ou somente um trecho?" << endl
	<< "1 - Inteiro" << endl << "2 - Trecho" << endl;
	int opcao_menu;
	cin >> opcao_menu;
			
	if (opcao_menu == 1){
		for (int i = 0; i < num_registros; i++){
			imprimirJogos(vet_Jogos, i);
		}
	}
	else if (opcao_menu == 2){
		cout << endl << "Digite o trecho" << endl;
		cin >> inicio_impressao_partes >> final_impressao_partes;
				
		if ((inicio_impressao_partes < 1) or (final_impressao_partes > num_registros) or (inicio_impressao_partes > final_impressao_partes)){
			// Condição para o usuário colocar números dentro do trecho correto (1 até o final dos dados)
			cout << "ERRO! Trecho inválido." << endl;
			menu_impressao(vet_Jogos, num_registros);
		}
		else {
			for (int i = 0; i < num_registros; i++){
				if ((i+1 >= inicio_impressao_partes) and (i+1 <= final_impressao_partes)){
					// Condição para chamar o subprograma somente quando i+1 estiver dentro do trecho digitado
					imprimirJogos(vet_Jogos, i);
				}
			}
		}
		
	}
	else {
		cout << "ERRO! Opção inválida." << endl;
		menu_impressao(vet_Jogos, num_registros);
	}
}

// Pesquisa de jogos
void pesquisarJogos(Jogo vet_Jogos[], int num_registros){
	cout << "Gostaria de pesquisar por qual categoria?" << endl
	<< "1 - Nome" << endl << "2 - Plataforma" <<
	endl << "3 - Ano de lançamento" << endl;
	int opcao_pesquisa;
	cin >> opcao_pesquisa;
	string texto_pesquisa;
	int ano_pesquisa;
	int achou=0;
	
	switch (opcao_pesquisa){
		case 1:{
			cout << "Digite o nome: " << endl;
			cin.ignore(); // Limpa o buffer de entrada
			getline(cin, texto_pesquisa);
			for (int i=0; i<num_registros; i++){
				if (texto_pesquisa == vet_Jogos[i].nome){
					imprimirJogos(vet_Jogos, i);
					achou++;
				}
			}
			
			if (achou == 0){
				cout << endl << "Não foi possível encontrar." << endl;
			}
			break;
		}
		case 2:{
			cout << "Digite a plataforma: " << endl;
			cin.ignore();
			getline(cin, texto_pesquisa);
			for (int i=0; i<num_registros; i++){
				if (texto_pesquisa == vet_Jogos[i].plataforma){
					imprimirJogos(vet_Jogos, i);
					achou++;
				}
			}
			
			if (achou == 0){
				cout << endl << "Não foi possível encontrar." << endl;
			}
			break;
		}
		case 3:{
			cout << "Digite o ano: " << endl;
			cin >> ano_pesquisa;
			for (int i=0; i<num_registros; i++){
				if (ano_pesquisa == vet_Jogos[i].ano_lancamento){
					imprimirJogos(vet_Jogos, i);
					achou++;
				}
			}
			
			if (achou == 0){
				cout << endl << "Não foi possível encontrar." << endl;
			}
			break;
		}
		default:
			cout << "ERRO! Opção inválida" << endl;
			return pesquisarJogos(vet_Jogos, num_registros);		
	}
}

// Menu para o usuário inserir jogos
void inserirJogos(Jogo*& vet_Jogos, int& capacidade, int& num_registros){
	int opcao_insercao=1;
	while (opcao_insercao == 1){
		if (num_registros == capacidade){
			redimensionaVetor(vet_Jogos, capacidade);
		}
		int identificador_novo = num_registros;
		vet_Jogos[num_registros].identificador = identificador_novo;
		cout << "Digite o nome: ";
		cin.ignore();
		getline(cin, vet_Jogos[num_registros].nome);
		cout << "Digite o ano de lancamento: ";
		cin >> vet_Jogos[num_registros].ano_lancamento;
		cout << "Digite a plataforma: ";
		cin.ignore();
		getline(cin, vet_Jogos[num_registros].plataforma);
		cout << "Digite a descrição: ";
		getline(cin, vet_Jogos[num_registros].descricao);
		num_registros++;

		cout << "Deseja adicionar outro? Digite 1 para 'sim'." << endl;
		cin >> opcao_insercao;
	}
}

// Menu para deleção de algum jogo
void delecao(Jogo*& vet_Jogos, int& num_registros){
	cout << endl << "Deseja apagar por plataforma, ano de lançamento ou nome?" << endl
	<< "1 - Nome" << endl << "2 - Plataforma" << endl << "3 - Ano de lançamento" << endl;
	int opcao_delecao;
	cin >> opcao_delecao;
	
	while ((opcao_delecao == 1) or (opcao_delecao == 2) or (opcao_delecao == 3)){
		switch(opcao_delecao){
			case 1: {
				cout << "Digite o nome do jogo:" << endl;
				string nome_delecao;
				cin.ignore();
				getline(cin, nome_delecao);
				
				for (int i=0; i< num_registros; i++){
					if (vet_Jogos[i].nome == nome_delecao and vet_Jogos[i].identificador != -1){
						vet_Jogos[i].identificador = -1; // O jogo não é deletado, mas sim marcado
					}
				}
				
				break;
			}
			case 2: {
				cout << "Digite o nome da plataforma:" << endl;
				string plat_delecao;
				cin.ignore();
				getline(cin, plat_delecao);
				
				for (int i=0; i< num_registros; i++){
					if (vet_Jogos[i].plataforma == plat_delecao and vet_Jogos[i].identificador != -1){ // o campo identificador != -1 é necessário para que jogos já deletados não sejam considerados para deleção novamente, o que poderia causar a contagem de registros no arquivo CSV ficar incorreta
						vet_Jogos[i].identificador = -1;
					}
				}
				
				break;
			}
			case 3: {
				cout << "Digite o ano de lançamento:" << endl;
				int ano_delecao;
				cin >> ano_delecao;
				
				for (int i=0; i< num_registros; i++){
					if (vet_Jogos[i].ano_lancamento == ano_delecao and vet_Jogos[i].identificador != -1){
						vet_Jogos[i].identificador = -1;
					}
				}
				
				break;
			}
			default: {
				cout << "ERRO! Opção inválida." << endl;
				return delecao(vet_Jogos, num_registros);
			}
		}
			
		cout << endl << "Concluído. Deseja apagar por plataforma, ano de lançamento ou nome?" << endl
		<< "1 - Nome" << endl << "2 - Plataforma" << endl << "3 - Ano de lançamento" << endl << "4 - Não apagar mais" << endl;
		cin >> opcao_delecao;
	}
}

// Ordenação de jogos
void ordenar(Jogo vet_Jogos[], int num_registros){
	cout << "Como gostaria de ordenar?" << endl <<
	"1 - Nome" << endl << "2 - Ano de lançamento" << endl;
	int opcao_ordenar;
	cin >> opcao_ordenar;
	
	switch (opcao_ordenar){
		case 1:{
			// Insertion sort
			for (int i=1; i<num_registros; i++){
					Jogo pivo = vet_Jogos[i];
					int j = i-1;
					
					while(j >= 0 and pivo.nome < vet_Jogos[j].nome){
						vet_Jogos[j + 1] = vet_Jogos[j];
						j--;
					}

					vet_Jogos[j + 1] = pivo;
			}
			cout << "Ordenação concluída." << endl;
			break;
		}
		case 2:{
			// Shell sort
			int gap[9] = {1,4,10,23,57,132,301,701,1750};
			int coluna_gap;
			for (int i=0; i<9; i++){
				if (gap[i] >= num_registros){
					coluna_gap = i-1;
					i = 8;
				}
			}
			
			while (coluna_gap >= 0) {
				int h = gap[coluna_gap];
				for (int i = h; i < num_registros; i++) {
					Jogo temp = vet_Jogos[i];
					int j = i;
	
					while (j >= h and vet_Jogos[j - h].ano_lancamento > temp.ano_lancamento){
						vet_Jogos[j] = vet_Jogos[j - h];
						j -= h;
					}
					vet_Jogos[j] = temp;
				}

				coluna_gap--;
			}
			cout << "Ordenação concluída." << endl;
			break;
		}	
		default:{
			cout << "ERRO! Opção inválida." << endl;
			return ordenar(vet_Jogos, num_registros);
		}
	}
}

// Salvar as alterações (arquivos com -1 não são salvos)
void salvar(Jogo vet_Jogos[], int opcao_salvar, int num_registros, int num_registos_noCSV) {
	int identificador_final=1;
	
	if (opcao_salvar == 1){
		ofstream saidaDadosCSV("dados.csv", ios::trunc); // trunc apaga o conteúdo do arquivo antes de reescrever
		saidaDadosCSV << "identificador" << ";" << "nome" << ";" << "ano_lancamento" << ";" << "plataforma" << ";" << "descricao" << endl;
		saidaDadosCSV << num_registos_noCSV << endl;
		
		for (int i=0; i<num_registros; i++){
			if (vet_Jogos[i].identificador != -1){
				saidaDadosCSV << identificador_final << ";\"" 
				<< vet_Jogos[i].nome << "\";" 
				<< vet_Jogos[i].ano_lancamento << ";\"" 
				<< vet_Jogos[i].plataforma << "\";\"" 
				<< vet_Jogos[i].descricao << "\"" << endl;
				identificador_final++;
			}
		}

	}
	
	else {
		cout << "Digite um nome para um novo arquivo" << endl;
		string nome_novo;
		string lixo;
		getline(cin, lixo); // para limpar o buffer de entrada
		getline(cin, nome_novo);
		
		ofstream saidaNova(nome_novo);
		saidaNova << "identificador" << ";" << "nome" << ";" << "ano_lancamento" << ";" << "plataforma" << ";" << "descricao" << endl;
		saidaNova << num_registos_noCSV << endl;
		
		for (int i=0; i<num_registros; i++){
			if (vet_Jogos[i].identificador != -1){
				saidaNova << identificador_final << ";\"" 
				<< vet_Jogos[i].nome << "\";" 
				<< vet_Jogos[i].ano_lancamento << ";\"" 
				<< vet_Jogos[i].plataforma << "\";\"" 
				<< vet_Jogos[i].descricao << "\"" << endl;
				identificador_final++;
			}
		}
	}
}

// Menu para escolher como salvar
void opcao_salvar(Jogo vet_Jogos[], int num_registros){
	cout << "Como gostaria de salvar?" << endl
	<< "1 - Substituir" << endl <<
	"2 - Criar outro arquivo" << endl;
	int opcao_salvar;
	cin >> opcao_salvar;
			
	int contNum_registros = 0;
	for (int i=0;i<num_registros;i++){
		if (vet_Jogos[i].identificador != -1){
			contNum_registros++;
		}
	}
			
	if ((opcao_salvar == 1) or (opcao_salvar == 2)){
		salvar(vet_Jogos, opcao_salvar, num_registros, contNum_registros);
	}
	else {
		cout << "ERRO! Opção inválida." << endl;
	}
}

// Menu principal
int main(){
	int capacidade = 40;
	int num_registros = 0;
	Jogo* vet_Jogos = nullptr; /* inicializa o ponteiro do vetor de jogos como nulo, para que a função lerArquivo_CSV possa alocar a memória necessária
	para o vetor e atribuir o endereço ao ponteiro vet_Jogos. Dessa forma, o vetor de jogos estará disponível para uso em todo o programa,
	incluindo as funções de inserção, deleção e impressão. */
	
	lerArquivo_CSV(vet_Jogos, capacidade, num_registros);
	cout << endl;
	int opcao_menu=-1;

	while (opcao_menu != 0){
		cout << "===========================================" << endl;
		cout << "                 GAMES                     " << endl;
		cout << "===========================================" << endl;
		cout << "1 - IMPRIMIR GAMES" << endl;
		cout << "2 - PESQUISAR GAMES" << endl;
		cout << "3 - INSERIR GAMES" << endl;
		cout << "4 - DELETAR GAMES" << endl;
		cout << "5 - ORDENAR GAMES" << endl;
		cout << "6 - SALVAR ALTERAÇÕES" << endl;
		cout << "0 - SAIR" << endl;

		cin >> opcao_menu;
		switch (opcao_menu){
			case 1:
				menu_impressao(vet_Jogos, num_registros);
				break;
			case 2:
				pesquisarJogos(vet_Jogos, num_registros);
				break;
			case 3:
				inserirJogos(vet_Jogos, capacidade, num_registros);
				break;
			case 4:
				delecao(vet_Jogos, num_registros);
				break;
			case 5:
				ordenar(vet_Jogos, num_registros);
				break;
			case 6:
				opcao_salvar(vet_Jogos, num_registros);
				break;
			case 0:
				cout << "Saindo do programa..." << endl;
				break;
			default:
				cout << "Opção inválida. Tente novamente." << endl;
		}
	}

	delete[] vet_Jogos; // Desalocar o vetor alocado dinamicamente
	return 0;
}
