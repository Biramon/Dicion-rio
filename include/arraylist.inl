/**
 * ArrayList class implementation.
 *
 */

#include "arraylist.h"

/**
 * ---------------------------------------------------------------------------
 * Common methods
 * ---------------------------------------------------------------------------
 */

// Construtor inicializa TAD.
template < typename Key, typename Data, typename KeyComparator >
ArrayList<Key,Data, KeyComparator>::ArrayList ( int _iMaxSz ) :
    mi_Length( 0 ),         // Tamanho logico.
    mi_Capacity( _iMaxSz ), // Guardar capacidade atual.
    mpt_Data( nullptr )
{
    if ( _iMaxSz < 0 )          // Nao aceitamos lista com tamanho negativo.
        throw std::invalid_argument( "[ArrayList()]: Tamanho de lista invalido!" );
    this->mpt_Data = new NodeAL[ _iMaxSz ]; // Tamanho maximo.
}


//Busca púlica
template < typename Key, typename Data, typename KeyComparator >
bool ArrayList<Key,Data, KeyComparator>::search (Key _x, Data & _sdata, KeyComparator compare) const
{
	bool result;
	auto procurado = _search(_x);

	if (procurado == this->mi_Length) result = false;
	else {
		//Verificar se de fato o indice retornado corresponde a chave informada
		if (compare(this->mpt_Data[procurado].id, _x) == 0 ) {
			_sdata = this->mpt_Data[procurado].info;
			result = true;
		}
		else {
			result = false;
		}
	}
	return result;
}

/**
 * ---------------------------------------------------------------------------
 * Methods from ArrayList.
 * ---------------------------------------------------------------------------
 */

//Busca privada
template < typename Key, typename Data, typename KeyComparator >
int ArrayList<Key,Data, KeyComparator>:: _search (Key _x) const {
	auto i(0);
	KeyComparator compare;
    for (/*Empty*/; i < this->mi_Length && compare (_x, this->mpt_Data[i].id) != 0; ++i) {}
	return i;
}

//Inserção em lista não ordenada. Θ(1)
template < typename Key, typename Data, typename KeyComparator >
bool ArrayList<Key,Data, KeyComparator>::insert(Key _novaID, Data _novaInfo) 
{
	if (this->mi_Length == mi_Capacity) {
		throw std::invalid_argument("[ArrayList::insert]: Lista cheia (Overflow)\n");
		return false;
	} else {
		if(this->mi_Length == 0){
        	this->mpt_Data[0].id = _novaID;
            this->mpt_Data[0].info = _novaInfo;
            this->mi_Length++;
            return true;
        }
        auto procurado(0);
		procurado = ArrayList::_search(_novaID);
		if (procurado == _novaID) {
			cerr << "[ArrayList::insert]: Chaves repetidas!\n";
			return false;
		} else {
			this->mpt_Data[procurado].id = _novaID;
			this->mpt_Data[procurado].info = _novaInfo;
			this->mi_Length++;
		}
	}
    return true;
}

//Remoção em lista não ordenada. Inserindo último elemento no local do removido. Θ(1)
template < typename Key, typename Data, typename KeyComparator >
bool ArrayList<Key,Data, KeyComparator>::remove(Key _x, Data & _recovData)
{
	if (this->mi_Length == 0) {
		throw std::invalid_argument("[ArrayList::remove]: Lista vazia (Underflow)\n");
		return false;
    } else {
		auto procurado(0);
		procurado = ArrayList::_search(_x);
		if (procurado == mi_Length) {
			cerr << "[ArrayList::remove]: Elemento a ser removido não foi encontrado\n";
			return false;
        } else {
			_recovData = this->mpt_Data[procurado].info;
			this->mpt_Data[procurado].id = this->mpt_Data[this->mi_Length-1].id;
			this->mpt_Data[procurado].info = this->mpt_Data[this->mi_Length-1].info;
			this->mi_Length--;
			return true;
		}
	}
}
/**
 * ---------------------------------------------------------------------------
 * Methods from SortedArrayList.
 * ---------------------------------------------------------------------------
 */

//Busca privada (filho)
template < typename Key, typename Data, typename KeyComparator >
int SortedArrayList<Key, Data, KeyComparator>::_search(Key _x) const
{
	int inf = 0;
	int sup = this->mi_Length - 1;
	int procurado = this->mi_Length;
	int meio;
	KeyComparator compare;

	while (inf <= sup) {
		meio = (sup + inf) / 2;
		if (compare (_x, this->mpt_Data[meio].id) == 1) {
			inf = meio + 1;
		} else
		if (compare (_x, this->mpt_Data[meio].id ) == 0) {
			return meio;
		} else {
			procurado = meio;
			sup = meio - 1;
		}
	}
	return procurado;
}

//Inserção em lista ordenada. O(n)
template < typename Key, typename Data, typename KeyComparator >
bool SortedArrayList<Key, Data, KeyComparator>::insert(Key _novaId, Data _novaInfo) {
    if (this->mi_Length == this->mi_Capacity) {
        throw std::invalid_argument("[SortedArrayList::insert]: Lista cheia (Overflow)\n");
        return false;
    } else {
        auto procurado = SortedArrayList::_search(_novaId);
        if(this->mi_Length == 0){
        	this->mpt_Data[0].id = _novaId;
            this->mpt_Data[0].info = _novaInfo;
            this->mi_Length++;
            return true;
        }

        if (procurado == _novaId) {
            cerr << "[SortedArrayList::insert]: Chaves repetidas!\n";
            return false;
        } else {
            this->mi_Length++;
            for (int i = this->mi_Length; i > procurado; i--) { //Movimentar os elementos a partir do 'buraco' que foi aberto
                this->mpt_Data[i] = this->mpt_Data[i-1];
            }
            this->mpt_Data[procurado].id = _novaId;
            this->mpt_Data[procurado].info = _novaInfo;
        }
    }
    return true;
}

//Remoção em uma lista ordenada. O(n)
template < typename Key, typename Data, typename KeyComparator >
bool SortedArrayList<Key, Data, KeyComparator>::remove(Key _x, Data & _recovData) {
    if (this->mi_Length == 0) {
        throw std::invalid_argument("[SortedArrayList::remove]: Lista vazia (Underflow)\n");
        return false;
    } else {
        auto procurado(0);
        procurado = SortedArrayList::_search(_x);
        if (procurado == this->mi_Length) {
            cerr << "[SortedArrayList::remove]: Elemento a ser removido não foi encontrado\n";
            return false;
        } else {
            _recovData = this->mpt_Data[procurado].info;
            for (int i = procurado; i < this->mi_Length; i++) //Movimentar os elementos para os 'buracos' que foram abertos
                this->mpt_Data[i] = this->mpt_Data[i+1];
            
            this->mi_Length--;
        }
    }
    return true;
}
