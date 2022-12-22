#pragma once
#include "No.h"

class ArvoreAVL
{
    private:
        int quant;
        No *root;

        void removeZeroF(No *sair);
        void removeUmF(No *sair);
        void removeNF(No *sair);

        No* localEntrada(No *subArvore, cliente &c);
        No* menorDescendente(No *no);
        No* maiorDescendente(No *no);
    public:
        //construtores
        ArvoreAVL(/* args */);
        ArvoreAVL(const ArvoreAVL &outro);
        virtual ~ArvoreAVL();

        //métodos
        void insert(cliente &c);
        void remove(cliente &c);
        No* buscar(No *subArvore, cliente &outro);

        No* getSucessor(No *no);
        No* getAntecessor(No *no);

        void emOrdem(No *no);
        void posOrdem(No *no);
        void preOrdem(No *no);
        void preOrdemArquivo(No *no);

        int getAltura(No *no);
        int getFatorBalanceamento(No *no);
        void executaBalanceamento(No *entrou);
        No* getP(No *);
        No* getQ(No *P);
        void rotacaoUnica_EsqEsq(No *P, No *Q);
        void rotacaoUnica_DirDir(No *P, No *Q);
        void rotacaoDupla_DirEsq(No *p, No *q, No *r);
        void rotacaoDupla_EsqDir(No *p, No *q, No *r);

        void loadProdutos();
        void saveProdutosArquivo();
        
        //getters e setters
        void setQuant(int quant);
        int getQuant() const;
        void setRoot(No* root);
        No* getRoot() const;
};
