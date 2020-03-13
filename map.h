//
// Created by iduna on 3/13/2020.
//

#ifndef TLD_MAP_H
#define TLD_MAP_H

namespace tld
{
	//
// Created by iduna on 2/27/2020.
//


#include "core/avl_yggdrasil.h"
	
	template <typename KeyT, typename ValT>
	struct pair_t
	{
		KeyT _p_key;
		ValT _p_value;
		
		pair_t();
		
		explicit
		pair_t(KeyT nkey);
		
		pair_t(KeyT nkey, ValT nvalue);
		
		~pair_t();
		
		pair_t(const pair_t&);
	};

//template <typename KeyT, typename ValT>
//inline bool operator>(const pair_t<KeyT, ValT>& lht, const pair_t<KeyT, ValT>& rht);
	
	template <typename KeyT, typename ValT>
	inline bool operator <(const pair_t<KeyT, ValT>& lht, const pair_t<KeyT, ValT>& rht);
	
	template <typename KeyT, typename ValT>
	inline bool operator ==(const pair_t<KeyT, ValT>& lht, const pair_t<KeyT, ValT>& rht);
	
	template <typename KeyT, typename ValT>
	class map_t
	{
	public:
		typedef typename tld::avl_tree<pair_t<KeyT, ValT> >::tree_node node_t;
	
	private:
		tld::avl_tree<pair_t<KeyT, ValT> > m_tree_;
		
		node_t* Find(const KeyT& key, node_t* p_node);
	
	
	public:
		map_t();
		
		map_t(const map_t& that);
		
		~map_t();
		
		void Insert(const pair_t<KeyT, ValT>& _x);
		
		void Erase(const KeyT& key);
		
		ValT& Find(const KeyT& key);
		
		void Clear();
		
		bool Empty();
		
		ValT& operator [](const KeyT& key);
		
		map_t& operator =(const map_t& that);
	};
	
	template <typename KeyT, typename ValT>
	pair_t<KeyT, ValT>::pair_t() : _p_key(), _p_value()
	{}
	
	template <typename KeyT, typename ValT>
	pair_t<KeyT, ValT>::pair_t(KeyT nkey) : _p_key(nkey), _p_value()
	{}
	
	template <typename KeyT, typename ValT>
	pair_t<KeyT, ValT>::pair_t(KeyT nkey, ValT nvalue) : _p_key(nkey), _p_value(nvalue)
	{}
	
	template <typename KeyT, typename ValT>
	pair_t<KeyT, ValT>::pair_t(const pair_t& that)
	{
		this->_p_key = that._p_key;
		this->_p_value = that._p_value;
	}
	
	
	template <typename KeyT, typename ValT>
	pair_t<KeyT, ValT>::~pair_t() = default;
	
	template <typename KeyT, typename ValT>
	map_t<KeyT, ValT>::~map_t() = default;
	
	template <typename KeyT, typename ValT>
	map_t<KeyT, ValT>::map_t() = default;
	
	template <typename KeyT, typename ValT>
	ValT& map_t<KeyT, ValT>::Find(const KeyT& key)
	{
		node_t* res_node = Find(key, m_tree_.root_);
		
		if (res_node)
			return res_node->_n_value._p_value;
		
		pair_t<KeyT, ValT> n_node(key);
		return (m_tree_.Insert(n_node))->_n_value._p_value;
	}
	
	template <typename KeyT, typename ValT>
	typename map_t<KeyT, ValT>::node_t* map_t<KeyT, ValT>::Find(const KeyT& key, map_t::node_t* p_node)
	{
		if (p_node == nullptr)
			return nullptr;
		
		if (key == p_node->_n_value._p_key)
			return p_node;
		
		if (key < p_node->_n_value._p_key)
			return Find(key, p_node->left);
		
		return Find(key, p_node->right);
	}
	
	template <typename KeyT, typename ValT>
	ValT& map_t<KeyT, ValT>::operator [](const KeyT& key)
	{
		node_t* res_node = Find(key, m_tree_.root_);
		
		if (res_node)
			return res_node->_n_value._p_value;
		
		pair_t<KeyT, ValT> n_node(key);
		return (m_tree_.Insert(n_node))->_n_value._p_value;
	}
	
	template <typename KeyT, typename ValT>
	map_t<KeyT, ValT>& map_t<KeyT, ValT>::operator =(const map_t& that)
	{
		if (this != &that)
		{
			this->m_tree_ = that.m_tree_;
		}
		return *this;
	}
	
	template <typename KeyT, typename ValT>
	map_t<KeyT, ValT>::map_t(const map_t& that)
	{
		this->m_tree_ = that.m_tree_;
	}
	
	template <typename KeyT, typename ValT>
	void map_t<KeyT, ValT>::Erase(const KeyT& key)
	{
		m_tree_.FindAndRemove(key);
	}
	
	template <typename KeyT, typename ValT>
	void map_t<KeyT, ValT>::Clear()
	{
		m_tree_.Destroy();
	}
	
	template <typename KeyT, typename ValT>
	bool map_t<KeyT, ValT>::Empty()
	{
		return (m_tree_.root_ == nullptr);
	}
	
	template <typename KeyT, typename ValT>
	void map_t<KeyT, ValT>::Insert(const pair_t<KeyT, ValT>& _x)
	{
		m_tree_.Insert(_x);
	}

/*template <typename KeyT, typename ValT>
inline bool operator>(const pair_t<KeyT, ValT>& lht, const pair_t<KeyT, ValT>& rht)
{
    return (lht.key > rht.key);
}*/
	
	template <typename KeyT, typename ValT>
	inline bool operator <(const pair_t<KeyT, ValT>& lht, const pair_t<KeyT, ValT>& rht)
	{
		return (lht._p_key < rht._p_key);
	}
	
	template <typename KeyT, typename ValT>
	inline bool operator ==(const pair_t<KeyT, ValT>& lht, const pair_t<KeyT, ValT>& rht)
	{
		return (lht._p_key == rht._p_key);
	}
	
	template <typename KeyT, typename ValT>
	inline bool operator ==(const map_t<KeyT, ValT>& lht, const map_t<KeyT, ValT>& rht)
	{
		return (lht.m_tree_ == rht.m_tree_);
	}
	
}// namespace tld

#endif //TLD_MAP_H
