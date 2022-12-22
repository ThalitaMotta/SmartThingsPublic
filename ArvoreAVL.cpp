#include "ArvoreAVL.h"
#include<iostream>
#include<fstream>
#include<ostream>

using namespace std;

#pragma region Construtores
ArvoreAVL::ArvoreAVL() {
    quant = 0;
    root = NULL;
}

ArvoreAVL::ArvoreAVL(const ArvoreAVL &outro) {
    this->quant = outro.getQuant();
    this->root = outro.getRoot();
}

ArvoreAVL::~ArvoreAVL() {
    //será chamado quando o objeto for destruido
}
#pragma endregion Construtores

#pragma region Getters/Setters
void ArvoreAVL::setQuant(int quant) {
    this->quant = quant;
}

int ArvoreAVL::getQuant() const {
    return quant;
}

void ArvoreAVL::setRoot(No* root) {
    this->root = root;
}

No* ArvoreAVL::getRoot() const {
    return root;
}
#pragma endregion Getters/Setters

No* ArvoreAVL::buscar(No* subArvore, cliente &c) {
    if (subArvore != NULL) {
        cliente subCliente = subArvore->getCliente();
        if (c.getCpf() < subCliente.getCpf())
            return buscar(subArvore->getEsq(), c);
        else if (c.getCpf() > subCliente.getCpf())
            return buscar(subArvore->getDir(), c);
        else {
            return subArvore;
        }
    } else {
        cout << "\nElemento não encontrado!" << endl;
        return NULL;
    }
}

No* ArvoreAVL::localEntrada(No *subArvore, cliente &c){
    cliente subCliente = subArvore->getCliente();
    if(c.getCpf() < subCliente.getCpf()){
        if(subArvore->getEsq() != NULL)
            return localEntrada(subArvore->getEsq(), c);
    }else{
        if(subArvore->getDir() != NULL)
            return localEntrada(subArvore->getDir(), c);
    }
    return subArvore;
}

void ArvoreAVL::insert(cliente &c){
    No *novo = new No(c);

    if(root == NULL){
        root = new No();
        root->setCliente(c);
        quant ++;
    }else{
        No *pai = localEntrada(root, c);
        cliente cPai = pai->getCliente();

        if(c.getCpf() < cPai.getCpf()){
            pai->setEsq(novo);
            novo->setPai(pai);
            quant ++;
        }else if(c.getCpf() > cPai.getCpf()){
            pai->setDir(novo);
            novo->setPai(pai);
            quant ++;
        }else{
            cout << "\nElemento ja existe!" << endl;
        }
    }
}

#pragma region Remoção
void ArvoreAVL::remove(cliente &c){
    No *sair = buscar(root, c);

    if (sair != NULL)
    {
        int numFilhos = sair->getQuantFilhos();
        if (numFilhos == 0)
        {
            this->removeZeroF(sair);
        }
        else if (numFilhos == 1)
        {
            this->removeUmF(sair);
        }
        else
        {
            this->removeNF(sair);
        }
    }
    No *p2 = this->getP(sair);
    
    if (p2 != NULL)
    {
        cout << "Desbalanceou: ";
        p2->getCliente().imprimeDados();
        cout << endl;
        executaBalanceamento(sair);
    }
}

void ArvoreAVL::removeZeroF(No *sair){
    No *pai = sair->getPai();
    if (pai == NULL) { //estamos removendo o root
        root = NULL;
    }else {
        cliente cPai = pai->getCliente();
        cliente cSair = sair->getCliente();

        if (cSair.getCpf() < cPai.getCpf())
            pai->setEsq(NULL);
        else
            pai->setDir(NULL);
    }
}

void ArvoreAVL::removeUmF(No *sair){
    No *pai = sair->getPai();
    No *filho = sair->getFilhoUnico();

    if(pai == NULL){ //se não possui pai, logo sair = root
        root = filho;
    }else{
        if (filho != NULL)
        {
            filho->setPai(pai);
            if (filho->getCliente().getCpf() > pai->getCliente().getCpf())
                pai->setDir(filho);
            else
                pai->setEsq(filho);
        }
    }
}

void ArvoreAVL::removeNF(No *sair){
    No *antecessor = this->getAntecessor(sair);
    cliente c = antecessor->getCliente();
    this->remove(c);
    sair->setCliente(c);
}
#pragma endregion Remoção

No* ArvoreAVL::menorDescendente(No *no){
    if(no != NULL){
        if (no->getEsq() == NULL)
        {
            return no;
        }else
        {
            return menorDescendente(no->getEsq());
        }
        return NULL;
    }
}

No* ArvoreAVL::getSucessor(No *no){
    if (no != NULL){
        return menorDescendente(no->getDir());
    }
    else{
        cout << "Esse nó não possui antecessor";
        return NULL;
    }
}

No* ArvoreAVL::maiorDescendente(No *no){
    if (no != NULL) {
        if (no->getDir() == NULL)
            return no;
        else
            return maiorDescendente(no->getDir());
    }
    return NULL;
}

No* ArvoreAVL::getAntecessor(No *no){
    if (no != NULL){
        return maiorDescendente(no->getEsq());
    }
    else{
        cout << "Esse nó não possui antecessor";
        return NULL;
    }
}

#pragma region emOdem, preOrdem, posOrdem
void ArvoreAVL::emOrdem(No *no) {
    if (no != NULL) {
        emOrdem(no->getEsq());
        cout << "(" << no->getCliente().getCpf() << "," << no->getCliente().getNome() <<
                "," << getFatorBalanceamento(no) << "), ";
        emOrdem(no->getDir());
    }
}

void ArvoreAVL::preOrdem(No *no) {
    if (no != NULL) {
        cout << "(" << no->getCliente().getCpf() << "," << no->getCliente().getNome() << "), ";
        preOrdem(no->getEsq());
        preOrdem(no->getDir());
    }
}

void ArvoreAVL::posOrdem(No *no) {
    if (no != NULL) {
        posOrdem(no->getEsq());
        posOrdem(no->getDir());
        cout << "(" << no->getCliente().getCpf() << "," << no->getCliente().getNome() << "), ";
    }
}
#pragma endregion emOrdem, preOrdem, posOrdem

#pragma region Balanceamento
void ArvoreAVL::executaBalanceamento(No* entrou){
    No *p = getP(entrou);

    if(p != NULL){ //está desbalanceado
        No *q = getQ(p);

        if (p->getFator() > 0 && q->getFator() >= 0) //++, uma rotação
        {
            rotacaoUnica_DirDir(p, q);
        }else if (p->getFator() < 0 && q->getFator() <= 0) //--, uma rotação
        {
            rotacaoUnica_EsqEsq(p, q);
        }else if (p->getFator() > 0 && q->getFator() < 0) //+-, duas rotações
        {
            No *r = getP(q); //realizar as duas rotações R->Q e R->P
            rotacaoDupla_DirEsq(p, q, r);
        }
        else if (p->getFator() < 0 && q->getFator() > 0) //-+, duas rotações
        {
            No *r = getP(q); //realizar as duas rotações R->Q e R->P
            rotacaoDupla_EsqDir(p, q, r);
        }else
        {
            cout << "\nNão foi encontrado desbalanceamento." << endl;
        }
    }
}

void ArvoreAVL::rotacaoUnica_EsqEsq(No *P, No* Q) {
    No* paiP = P->getPai();
    No* A = Q->getDir();
    
    Q->setDir(P);
    P->setEsq(A);

    Q->setPai(paiP);
    if (Q->getCliente().getCpf() > paiP->getCliente().getCpf())
        paiP->setDir(Q);
    else
        paiP->setEsq(Q);
}

void ArvoreAVL::rotacaoUnica_DirDir(No *P, No* Q) {
    No* paiP = P->getPai();
    No* A = Q->getEsq();
    
    Q->setEsq(P);
    P->setDir(A);

    Q->setPai(paiP);
    if (Q->getCliente().getCpf() > paiP->getCliente().getCpf())
        paiP->setDir(Q);
    else
        paiP->setEsq(Q);
}

void ArvoreAVL::rotacaoDupla_DirEsq(No *p, No *q, No *r){
    if (r != NULL)
    {   //primeira rotação R->Q
        No *qPai = q->getPai();
        q->setPai(r); //r passa para cima de q
        r->setPai(qPai); // pai do r deixa de ser q e passa a ser qPai
        qPai->setDir(r); // como é do tipo +-, logo r está na subArvora a direita de qPai

        if(r->getDir() != NULL){ //caso o elemento tenha entrado a direita
            q->setEsq(r->getDir()); //para que r nao fique com 2 filhos a direta
            q->getEsq().setPai(q); //esqueci desta linha no vídeo
        }else{
            q->setEsq(NULL);
        }
        r->setDir(q); //q passou a ser filho de r

        //segunda rotação R->P, similar a rotacao DirDir
        No *pPai = p->getPai();
        p->setPai(r);
        r->setPai(pPai);
        if (r->getCliente().getCpf() > pPai->getCliente().getCpf())
            pPai->setDir(r);
        else
            pPai->setEsq(r);
        
        if(r->getEsq() != NULL){ //caso o elemento tenha entrado a esquerda
            p->setDir(r->getEsq());
            p->getDir().setPai(p); //esqueci desta parte no vídeo
        }else{
            p->setDir(NULL); //p deixa de apontar para r que agora é seu pai
        }
        r->setEsq(p);
    }
}

void ArvoreAVL::rotacaoDupla_EsqDir(No *p, No *q, No *r){
    if (r != NULL)
    {   //primeira rotação R->Q
        No *qPai = q->getPai();
        q->setPai(r);
        r->setPai(qPai);
        qPai->setEsq(r); //troquei dir por esq

        if(r->getEsq() != NULL){ //troquei dir por esq
            q->setDir(r->getEsq()); //inverte dir e esq
            q->getDir().setPai(q);
        }else{
            q->setDir(NULL);
        }
        r->setEsq(q); //troquei dir por esq

        //segunda rotação R->P, similar a rotacao EsqEsq
        No *pPai = p->getPai();
        p->setPai(r);
        r->setPai(pPai);
        if (r->getCliente().getCpf() > pPai->getCliente().getCpf())
            pPai->setDir(r);
        else
            pPai->setEsq(r);
        
        if(r->getDir() != NULL){ //troquei esq por dir
            p->setEsq(r->getDir()); //inverte dir e esq
            p->getEsq().setPai(p);
        }else{
            p->setEsq(NULL);
        }
        r->setDir(p); //troquei esq por dir
    }
}

No* ArvoreAVL::getP(No *entrou) {
    No *pai = entrou->getPai();
    while (pai != NULL) {
        int fator = getFatorBalanceamento(pai);
        if (abs(fator) >= 2) {
            return pai;
        }
        pai = pai->getPai();
    }
    return NULL;
}

No* ArvoreAVL::getQ(No *P) {
    if (P->getFator() > 0)
        return P->getDir(); //item entrou na subArvore direita
    else
        return P->getEsq(); //item entrou na subArvore esquerda
}

int ArvoreAVL::getFatorBalanceamento(No *no) {
    int h_esq = 0;
    int h_dir = 0;
    No* subEsq = no->getEsq();
    No* subDir = no->getDir();

    if (subEsq != NULL)
        h_esq = getAltura(subEsq);

    if (subDir != NULL)
        h_dir = getAltura(subDir);

    int fator = h_dir - h_esq;
    no->setFator(fator);
    return fator;
}

int ArvoreAVL::getAltura(No *no) {
    if (no == NULL) {
        return 0;
    } else {
        int h_esq = getAltura(no->getEsq());
        int h_dir = getAltura(no->getDir());

        if (h_esq > h_dir)
            return h_esq + 1;
        else
            return h_dir + 1;
    }
}
#pragma endregion Balanceamento
