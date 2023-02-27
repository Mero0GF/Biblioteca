// Lucas Goulart de Farias Meres - 42127459
// Thiago Leandro Liporace - 42128481

//Referências: Trabalho Lista Circular Duplamente Encadeada, PDFs disponibilizados no moodle, alphacodingskills.com e StackOverflow para aprender como ler arquivos em C++.

#include "LinkedList.h"

using namespace std;

void Print(const LinkedList* lista)
{
  cout << "----------------------------------------------------------------------\n";
  cout << "A sua biblioteca possui atualmente " << lista -> count << " livros, sendo estes:\n";
  Node *aux = lista -> head;
  for (int i = 0;i < lista -> count;i++){
    cout << "\n------------/ " << "LIVRO " << i+1 << " /------------\n"; 
    cout <<"Titulo: " << aux -> titulo << "\n";
    cout <<"ISBN: " << aux -> isbn << "\n";
    cout <<"Autor: " << aux -> autor << "\n";
    cout <<"Cidade: " << aux -> cidade << "\n";
    cout <<"Editora: " << aux -> editora << "\n";
    cout <<"Disciplina: " << aux -> disciplina << "\n";
    cout <<"Edicao: " << aux -> edicao << "\n";
    cout <<"Ano de sua publicacao: " << aux -> ano << "\n";
    cout <<"Bibliografia basica: " << aux -> bibliobasica << "\n";
    aux = aux -> next;
  }
}

Node *RemoverLivro(LinkedList *lista,std::string isbn,std::string titulo){
  int opcao;
  cout << "Quer remover um livro pelo ISBN(1) ou pelo Titulo(2)? Digite o numero correspondente.\n";
  cin >> opcao;
  cin.ignore();
  Node *livro;
  if (opcao == 1){
    titulo = "";
    cout << "Digite o ISBN do livro que deseja remover:";
    getline(cin,isbn);
    livro = RemoveNode(lista,isbn,titulo);
  }
  if(opcao == 2){
    isbn = "";
    cout << "Digite o Titulo do livro que deseja remover:";
    getline(cin,titulo);
    livro = RemoveNode(lista,isbn,titulo);
  }
  return livro;
}

void SalvarLivros(LinkedList *lista){
  std::fstream file;
  file.open("bibliografia.csv");
  Node *aux = lista -> head;
  file << "Disciplina;ISBN;T�tulo;Autor;Edi�o;Cidade;Editora;Ano;Bibliografia b�sica\n";
  for (int i = 0;i < lista -> count;i++){
    file << aux -> disciplina << ';' << aux -> isbn << ';' << aux -> titulo << ';' << aux -> autor << ';' << aux -> edicao << ';' << aux -> cidade << ';' << aux -> editora << ';' << aux -> ano << ';' << aux -> bibliobasica << '\n';
    aux = aux -> next;
  }
  file.close();
}

void InserirLivro(LinkedList* lista,std::string isbn,std::string titulo,std::string autor,std::string cidade,std::string editora,std::string disciplina,int edicao,int ano, char bibliobasica){
  cout << "\nDigite o ISBN deste livro: ";
  getline(cin,isbn);
  cout << "\nDigite o titulo do livro que deseja inserir: ";
  getline(cin,titulo);
  cout << "\nDigite o autor deste livro: ";
  getline(cin,autor);
  cout << "\nDigite a cidade em que este livro foi publicado: ";
  getline(cin,cidade);
  cout << "\nDigite a editora que publicou este livro: ";
  getline(cin,editora);
  cout << "\nDigite a disciplina que o livro aborda: ";
  getline(cin,disciplina);
  cout << "\nDigite a edicao deste livro(1,2,3,4,etc): ";
  cin >> edicao;
  cout << "\nDigite o ano que este livro foi publicado: ";
  cin >> ano;
  cout << "\nDigite S ou N dependendo se o livro possui bibliografia basica ou nao: ";
  cin >> bibliobasica;
  Append(lista,isbn,titulo,autor,cidade,editora,disciplina,edicao,ano,bibliobasica);
}

void AnaliseA(const LinkedList* lista){
  string estrangeiras[16] = {"Elsevier","Pearson","McGraw-Hill","The MIT Press","Addison-Wesley","Dover","Wiley","Cengage Learning","Campus","Brooks Cole","Academic Press","Springer","Packt Publishing","Chapman & Hall","Princeton University Press","CRC Press"}; 
  string brasileiras[3] = {"LTC","Bookman","Ibpex"}; 
  Node *aux;
  aux = lista -> head;
  float count_estrangeira = 0,count_br = 0;
  for (int i = 0;i < lista -> count;i++){
    for (int j = 0;j < 16;j++){
      if (aux -> editora == estrangeiras[j]) count_estrangeira++;
    }
    aux = aux -> next;
  }
  aux = lista -> head;
  for (int i = 0;i < lista -> count;i++){
    for (int j = 0;j < 3;j++){
      if (aux -> editora == brasileiras[j]) count_br++;
    }
    aux = aux -> next;
  }
  aux = nullptr;
  float result = (count_br/(count_br+count_estrangeira))*100;
  cout << "----------------------------------------------------------------------\n";
  cout << "A quantidade total de livros publicados por editoras brasileiras eh: " << count_br << "\nE a quantidade total de livros publicados por editoras estrangeiras eh: " << count_estrangeira;
  cout << "\n----------------------------------------------------------------------\n";
  cout << "A porcentagem de livros publicados por editoras brasileiras e: " << result << "%\n" << "A porcentagem de livros publicados por editoras estrangeiras e: " << (100-result) << "%\n";
}

void AnaliseB(const LinkedList *lista){
  Node *aux;
  aux = lista -> head;
  float count = 0;
  int entry;
  cout << "Esta analise ira apresentar todos os livros lancados a partir do ano selecionado." << '\n' <<  "Digite o ano desejado para esta busca: ";
  cin >> entry;
  cout << "\n------------/ " << "LIVROS PUBLICADOS A PARTIR DE " << entry << " /------------\n";
  for (int i = 0;i < lista -> count;i++){
    if (aux -> ano >= entry) {
      cout << "\n------------/ " << "LIVRO " << i << " DA LISTA " << "/------------\n";
      cout << "Titulo: " << aux -> titulo << "\n";
      cout << "ISBN: " << aux -> isbn << "\n";
      cout << "Ano: " << aux -> ano << "\n";
      count++;
      }
    aux = aux -> next;
  }
  aux = nullptr;
  float result = (count/lista->count)*100;
  cout << "A porcentagem de livros publicados a partir de " << entry << " na lista eh: " << result << "%\n";
}

void AnaliseC(const LinkedList *lista){
  Node *aux;
  Node *mais_antigo;
  int count = 0;
  mais_antigo = lista -> head;
  aux = lista -> head;
  for (int i = 0;i < lista -> count;i++){
    if (aux -> ano < mais_antigo -> ano) mais_antigo = aux;
    aux = aux -> next;
  }
  cout << "\n------------/ " << "LIVRO MAIS ANTIGO DA SUA BIBLIOTECA " << "/------------\n";
  cout << "Titulo: " << mais_antigo -> titulo << "\n";
  cout << "ISBN: " << mais_antigo -> isbn << "\n";
  cout << "Ano: " << mais_antigo -> ano << "\n";
  aux = lista -> head;
  for (int i = 0;i < lista -> count;i++){
    if ((mais_antigo -> ano == aux -> ano) && (mais_antigo -> titulo != aux -> titulo)){
      cout << "\n------------/ " << "LIVROS DESTE MESMO ANO " << "/------------\n";
      cout << "Titulo: " << aux -> titulo << "\n";
      cout << "ISBN: " << aux -> isbn << "\n";
      cout << "Ano: " << aux -> ano << "\n";
    }
    aux = aux -> next;
  }
}

int main() {
  int entry;
  int flag2 = 0;
  bool flag = true;
  std::string str;
  std::fstream file;
  std::string data;
  int edicao,ano;
  std::string isbn,titulo,autor,cidade,editora,disciplina;
  char bibliobasica;
  LinkedList *lista = Create();
  while(flag == true){
    cout << "\n----------------------- BIBLIOTECA DE LIVROS ------------------------\n";
    cout << "1. Ler dados\n2. Exibir dados\n3. Salvar dados\n4. Inserir livro\n5. Remover livro\n6. Análise de dados A\n7. Análise de dados B\n8. Análise de dados C\n9. Encerrar\n";
    cout << "Digite o numero da opcao desejada: ";
    cin >> entry;
    cin.ignore();
    switch(entry){
      case 1:{
      file.open("bibliografia.csv");
  		if (file.is_open())
  		  {
  			std::getline(file, str);
  		  }
  	  else{
        cout << "Nao foi possivel abrir o arquivo.";
        break;
      }
      flag2 = 1;
      while(true)
      {
        if (file.eof()) break;
        std::getline(file, str);
        std::istringstream texto(str);
        int i = 0;
        while(std::getline(texto,data,';')){
          if (i == 0){
            disciplina = data;
          }
          else if (i == 1){
            isbn = data;
          }
          else if (i == 2){
            titulo = data;
          }
          else if (i == 3){
            autor = data;
          }
          else if (i == 4){
            edicao = stoi(data);
          }
          else if (i == 5){
            cidade = data;
          }
          else if (i == 6){
            editora = data;
          }
          else if (i == 7){
            ano = stoi(data);
          }
          else if (i == 8){
            const char *c = data.c_str();
            bibliobasica = *c;
          }
          i++;
        }
        if (i == 0) break;
        Append(lista,isbn,titulo,autor,cidade,editora,disciplina,edicao,ano,bibliobasica);
      }
      break;
      }
      case 2:
      if (flag2 == 0){
        cout << "\nEh necessario a leitura de dados antes que esse comando seja executado.\n";
        break;
      }
      Print(lista);
      break;
      case 3:
      if (flag2 == 0){
        cout << "\nEh necessario a leitura de dados antes que esse comando seja executado.\n";
        break;
      }
        SalvarLivros(lista);
      break;
      case 4:
        if (flag2 == 0){
        cout << "\nEh necessario a leitura de dados antes que esse comando seja executado.\n";
        break;
      }
        InserirLivro(lista,isbn,titulo,autor,cidade,editora,disciplina,edicao,ano,bibliobasica);
      break;
      case 5:{
        if (flag2 == 0){
        cout << "\nEh necessario a leitura de dados antes que esse comando seja executado.\n";
        break;
      }
        Node* temp = RemoverLivro(lista,isbn,titulo);
        if (temp == nullptr){
          cout << "Nao existe nenhum livro com este titulo.\n";
          break;
        }
        cout << "\n------------/ " << "LIVRO REMOVIDO " << "/------------\n";
        cout << "Titulo: " << temp -> titulo << "\n";
        cout << "ISBN: " << temp -> isbn << "\n";
        delete temp;
        break;
        }
      
      case 6:
      if (flag2 == 0){
        cout << "\nEh necessario a leitura de dados antes que esse comando seja executado.\n";
        break;
      }
      AnaliseA(lista);
      break;
      
      case 7:
      if (flag2 == 0){
        cout << "\nEh necessario a leitura de dados antes que esse comando seja executado.\n";
        break;
      }
      AnaliseB(lista);
      break;
      
      case 8:
      if (flag2 == 0){
        cout << "\nEh necessario a leitura de dados antes que esse comando seja executado.\n";
        break;
      }
      AnaliseC(lista);
      break;
      
      case 9:
      Destroy(lista);
      cout << "Fechando terminal...\n";
      flag = false;
      break;
    }
  }
}