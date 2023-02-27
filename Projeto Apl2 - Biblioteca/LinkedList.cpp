#include "LinkedList.h"

LinkedList *Create(){
  LinkedList *lista = new LinkedList;
  lista -> count = 0;
  lista -> head = lista -> tail = nullptr;
  return lista;
}

bool IsEmpty(const LinkedList *lista){
  if ((lista -> head == nullptr) && (lista -> tail == nullptr)) return true;
  return false;
}

void Insert(LinkedList *lista,std::string isbn,std::string titulo,std::string autor,std::string cidade,std::string editora,std::string disciplina,int edicao, int ano, char bibliobasica){
  Node *nodo = new Node;
  nodo -> isbn = isbn;
  nodo -> titulo  = titulo;
  nodo -> autor  = autor;
  nodo -> cidade  = cidade;
  nodo -> editora  = editora;
  nodo -> disciplina  = disciplina;
  nodo -> edicao  = edicao;
  nodo -> ano  = ano;
  nodo -> bibliobasica = bibliobasica;
  if (IsEmpty(lista) == true){
    lista -> head = nodo;
    lista -> tail = nodo;
  }
  lista -> head -> previous = nodo;
  nodo -> next = lista -> head;
  lista -> head = nodo;
  lista -> count++;
  lista -> head -> previous = lista -> tail;
  lista -> tail -> next = lista -> head;
}

void Append(LinkedList *lista,std::string isbn,std::string titulo,std::string autor,std::string cidade,std::string editora,std::string disciplina,int edicao, int ano, char bibliobasica){
  Node *nodo = new Node;
  nodo -> isbn = isbn;
  nodo -> titulo  = titulo;
  nodo -> autor  = autor;
  nodo -> cidade  = cidade;
  nodo -> editora  = editora;
  nodo -> disciplina  = disciplina;
  nodo -> edicao  = edicao;
  nodo -> ano  = ano;
  nodo -> bibliobasica = bibliobasica;
  if (IsEmpty(lista) == true){
    lista -> head = nodo;
    lista -> tail = nodo;
  }
  lista -> tail -> next = nodo;
  nodo -> previous = lista -> tail;
  lista -> tail = nodo;
  lista -> count++;
  lista -> head -> previous = lista -> tail;
  lista -> tail -> next = lista -> head;
}

Node *RemoveNode(LinkedList *lista,std::string isbn,std::string titulo){
  Node *toRemove;
  int i = lista -> count;
  toRemove = lista -> head;
  while((toRemove -> titulo != titulo) && (toRemove -> isbn != isbn)){
    toRemove = toRemove -> next;
    i--;
    if (i == 0) break;
  }
  if (toRemove -> isbn == isbn){
    toRemove -> previous -> next = toRemove -> next;
    toRemove -> next -> previous = toRemove -> previous;
    toRemove -> next = nullptr;
    toRemove -> previous = nullptr;
    lista -> count--;
    return toRemove;
    }
  else if (toRemove -> titulo == titulo){
    toRemove -> previous -> next = toRemove -> next;
    toRemove -> next -> previous = toRemove -> previous;
    toRemove -> next = nullptr;
    toRemove -> previous = nullptr;
    lista -> count--;
    return toRemove;
  }
  else{
    return nullptr;
  }
}

void Clear(LinkedList *lista){
  Node *aux;
  while (lista -> count != 0){
    aux = lista -> head;
    lista -> head = lista -> head -> next;
    delete aux;
    lista -> count--;
  }
  lista -> tail = nullptr;
  lista -> head = nullptr;
}

void Destroy(LinkedList *lista){
  Clear(lista);
  delete lista;
}

int Count(LinkedList *lista){
  return lista -> count;
}