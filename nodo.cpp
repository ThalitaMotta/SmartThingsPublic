#include "No.h"

No::No() {
    this->pai = NULL;
    this->esq = NULL;
    this->dir = NULL;
    //this->c = NULL;
    this->fator = 0;
}

No::No(cliente& outro){
    this->pai = NULL;
    this->esq = NULL;
    this->c.copiar(outro);
    this->dir = NULL;
    this->fator = 1;
}

No::No(const No& orig) {
    this->pai = orig.getPai();
    this->c = orig.getCliente();
    this->esq = orig.getEsq();
    this->dir = orig.getDir();
    this->fator = orig.getFator();
            
}

No::~No() {}

int No::getQuantFilhos(){
    if(dir == NULL && esq == NULL)
        return 0;
    else if((dir == NULL && esq != NULL) ||(dir != NULL && esq == NULL))
        return 1;
    else
        return 2;
}

No* No::getFilhoUnico(){ //retorna null caso tenha mais de um filho
    if(this->getQuantFilhos() == 1){
        if(this->esq != NULL)
            return this->esq;
        else
            return this->dir;
    }else{
        return NULL;
    }
}

void No::setFator(int fator){
    this->fator = fator;
}

int No::getFator() const{
    return fator;
}

void No::setDir(No* dir){
    if(this != NULL)
        this->dir = dir;
}

No* No::getDir() const{
    return dir;
}

void No::setCliente(cliente c){
    this->c = c;
}

cliente No::getCliente() const{
    return c;
}

void No::setEsq(No* esq){
    this->esq = esq;
}

No* No::getEsq() const{
    return esq;
}

void No::setPai(No* pai){
    this->pai = pai;
}

No* No::getPai() const{
    return pai;
}
