/**
 * Definition of a class that implements a list based on array.
 * This is a template class, where we need to specify the type
 * of key (unique) and the type of information we need to store
 * in the list.
 *
 * Author: Selan Santos
 * Date: March 25th, 2015
 * */

#ifndef _ARRAY_LIST_H_
#define _ARRAY_LIST_H_

#include <iostream>
#include <stdexcept>
#include <functional>

using std::cout;
using std::cerr;
using std::endl;
using std::string;


template < typename Key, typename Data, typename KeyComparator = std::less<Key>> //Prover próprio functor
class ArrayList
{
    protected:
        struct NodeAL {    // Estrutura do noh de um lista seq.
            Key id;       // A chave eh um inteiro nesta TAD.
            Data info;// A informacao tambem eh inteiro.
        };

        static const int SIZE=50;   // Tamanho maximo da lista.
        int mi_Length;              // Comprimento atual da lista.
        int mi_Capacity;            // Capacidade maxima de armazenamento.
        NodeAL *mpt_Data;          // Area de armazenamento: vetor regular.

        int _search( Key _x ) const; // Metodo de busca auxiliar.

    public:
        ArrayList ( int _iMaxSz = SIZE );
        virtual ~ArrayList () { delete [] mpt_Data; }
        bool remove( Key _x, Data & );     // Remove da lista.
        bool search( Key _x, Data & _sdata, KeyComparator compare) const;         // busca publica.
        bool insert( Key _novaId, Data _novaInfo );

        //! Sobrecarga do operador <<, que faz com que seja impresso o conteudo da lista.
        /*! @param _os Output stream, normalmente o <CODE>cout</code>.
         *  @param _oList A lista a ser impressa.
         *  @return A pr&oacute;pria <CODE>os</code> recebida como par&acirc;metros (para permitir encadeamento).
         */
        inline friend std::ostream &operator<< (std::ostream& _os, const ArrayList& _oList )
        {
            _os << "[ ";
            for( int i(0) ; i < _oList.mi_Length ; ++i )
                _os << "{id: " << _oList.mpt_Data[i].id << ", info: " << _oList.mpt_Data[i].info << "}  ";
            _os << "]";
            return _os;
        }
};

template <typename Key, typename Data, typename KeyComparator>
class SortedArrayList : public ArrayList<Key, Data, KeyComparator>
{
private:
	int _search (Key _x) const; //Método de busca auxiliar, difere da buscaAux do pai por ser busca binária
public:
	SortedArrayList(int _iMaxSz) : ArrayList < Key, Data, KeyComparator > ( _iMaxSz ){};
	bool remove (Key _x, Data &);
	bool insert (Key _novaId, Data _novaInfo );
};

#include "arraylist.inl"

#endif
