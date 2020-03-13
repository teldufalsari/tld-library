#ifndef CORE_AVL_YGGDRASIL_H
#define CORE_AVL_YGGDRASIL_H

//
// Created by iduna on 3/5/2020.
//

namespace tld
{
	
	template <typename T>
	class avl_tree
	{
	public:
		struct tree_node
		{
			T _n_value;
			unsigned char height{};
			tree_node* left;
			tree_node* parent;
			tree_node* right;
			
			tree_node();
			
			tree_node(const tree_node& that);
			
			~tree_node();
		};
	
	public:
		tree_node* root_;
	
	private:
		void InOrderTraverse(void (avl_tree<T>::*p_function)(tree_node*), tree_node* p_node);
		
		void PreOrderTraverse(void (avl_tree<T>::*p_function)(tree_node*), tree_node* p_node);
		
		void PostOrderTraverse(void (avl_tree<T>::*p_function)(tree_node*), tree_node* p_node);
		
		tree_node* Insert(tree_node** node, const T& new_value);
		
		void NodeDestroy(tree_node* p_node);
		
		tree_node* Find(tree_node* p_node, const T& key);
		
		void FindAndRemove(tree_node* p_node, const T& key);
		
		void Remove(tree_node* p_node);
		
		tree_node* Max(tree_node* p_node);
		
		void Copy(tree_node** p_dst, const tree_node& src);
		
		void RotateLeft(tree_node* old_root);
		
		void RotateRight(tree_node* old_root);
		
		void Balance(tree_node* p_tree);
		
		inline unsigned char Height(tree_node* p_node);
		
		char Diff(tree_node* p_node);
		
		void SetHeight(tree_node* p_node);
	
	
	public:
		avl_tree();
		
		avl_tree(const avl_tree& that);
		
		~avl_tree();
		
		avl_tree& operator =(const avl_tree& that);
		
		tree_node* Insert(const T& new_value);
		
		void Destroy();
		
		void FindAndRemove(const T& key);
		//void Dump();
		//void PrintNode(tree_node* p_node);
	};
	
	//TREE_NODE
	template <typename T>
	avl_tree<T>::tree_node::tree_node(): _n_value(), height(1), left(nullptr), parent(nullptr), right(nullptr)
	{}
	
	template <typename T>
	avl_tree<T>::tree_node::tree_node(const avl_tree::tree_node& that)
	{
		this->_n_value = that._n_value;
		this->height = that.height;
		this->left = nullptr;
		this->parent = nullptr;
		this->right = nullptr;
	}
	
	template <typename T>
	avl_tree<T>::tree_node::~tree_node() = default;
	
	
	//AVL_TREE
	template <typename T>
	avl_tree<T>::avl_tree() : root_(nullptr)
	{}
	
	template <typename T>
	avl_tree<T>::avl_tree(const avl_tree& that)
	{
		this->root_ = nullptr;
		
		if (that.root_)
			Copy(&(this->root_), *(that.root_));
	}
	
	template <typename T>
	avl_tree<T>::~avl_tree()
	{
		if (root_)
			this->Destroy();
	}
	
	template <typename T>
	void avl_tree<T>::InOrderTraverse(void (avl_tree<T>::*p_function)(tree_node*), tree_node* p_node)
	{
		if (p_node == nullptr)
			return;
		
		if (p_node->left != nullptr)
			InOrderTraverse(p_function, p_node->left);
		
		(this->*p_function)(p_node);
		
		if (p_node->right != nullptr)
			InOrderTraverse(p_function, p_node->right);
	}
	
	template <typename T>
	void avl_tree<T>::PreOrderTraverse(void (avl_tree<T>::*p_function)(tree_node*), tree_node* p_node)
	{
		if (p_node == nullptr)
			return;
		
		(this->*p_function)(p_node);
		
		if (p_node->left != nullptr)
			PreOrderTraverse(p_function, p_node->left);
		
		if (p_node->right != nullptr)
			PreOrderTraverse(p_function, p_node->right);
	}
	
	template <typename T>
	void avl_tree<T>::PostOrderTraverse(void (avl_tree<T>::*p_function)(tree_node*), tree_node* p_node)
	{
		if (p_node == nullptr)
			return;
		
		if (p_node->left != nullptr)
			PostOrderTraverse(p_function, p_node->left);
		
		if (p_node->right != nullptr)
			PostOrderTraverse(p_function, p_node->right);
		
		(this->*p_function)(p_node);
	}
	
	template <typename T>
	void avl_tree<T>::Destroy()
	{
		PostOrderTraverse(&avl_tree::NodeDestroy, root_);
		root_ = nullptr;
	}
	
	template <typename T>
	void avl_tree<T>::NodeDestroy(avl_tree::tree_node* p_node)
	{
		delete p_node;
	}
	
	template <typename T>
	void avl_tree<T>::RotateLeft(avl_tree::tree_node* old_root)
	{
		tree_node* new_root = old_root->right;
		
		old_root->right = new_root->left;
		if (old_root->right)
			old_root->right->parent = old_root;
		
		if (old_root->parent)
		{
			if (old_root->parent->right == old_root)
				old_root->parent->right = new_root;
			else
				old_root->parent->left = new_root;
		} else
			this->root_ = new_root;
		
		new_root->parent = old_root->parent;
		
		new_root->left = old_root;
		old_root->parent = new_root;
		
		SetHeight(old_root);
		SetHeight(new_root);
	}
	
	template <typename T>
	void avl_tree<T>::RotateRight(avl_tree::tree_node* old_root)
	{
		tree_node* new_root = old_root->left;
		
		old_root->left = new_root->right;
		if (old_root->left)
			old_root->left->parent = old_root;
		
		if (old_root->parent)
		{
			if (old_root->parent->right == old_root)
				old_root->parent->right = new_root;
			else
				old_root->parent->left = new_root;
		} else
			this->root_ = new_root;
		
		new_root->parent = old_root->parent;
		
		new_root->right = old_root;
		old_root->parent = new_root;
		
		SetHeight(old_root);
		SetHeight(new_root);
	}
	
	template <typename T>
	void avl_tree<T>::Balance(avl_tree::tree_node* p_tree)
	{
		SetHeight(p_tree);
		
		if (Diff(p_tree) == 2)
		{
			if (Diff(p_tree->right) < 0)
				RotateRight(p_tree->right);
			
			RotateLeft(p_tree);
		}
		
		if (Diff(p_tree) == -2)
		{
			if (Diff(p_tree->left) > 0)
				RotateLeft(p_tree->left);
			
			RotateRight(p_tree);
		}
	}
	
	template <typename T>
	unsigned char avl_tree<T>::Height(avl_tree::tree_node* p_node)
	{
		return (p_node ? p_node->height : 0);
	}
	
	template <typename T>
	char avl_tree<T>::Diff(avl_tree::tree_node* p_node)
	{
		return (Height(p_node->right) - Height(p_node->left));
	}
	
	template <typename T>
	void avl_tree<T>::SetHeight(avl_tree::tree_node* p_node)
	{
		unsigned char hl = Height(p_node->left);
		unsigned char hr = Height(p_node->right);
		
		p_node->height = (hl > hr ? hl : hr) + 1;
	}
	
	template <typename T>
	typename avl_tree<T>::tree_node* avl_tree<T>::Insert(avl_tree::tree_node** node, const T& new_value)
	{
		if (!(*node))
		{
			*node = new tree_node;
			(*node)->_n_value = new_value;
			
			return *node;
		}
		if (new_value == (*node)->_n_value)
		{
			return *node;
		}
		if (new_value < (*node)->_n_value)
		{
			tree_node* new_node = Insert(&((*node)->left), new_value);
			
			if ((*node)->left->parent == 0)
				(*node)->left->parent = *node;
			
			Balance(*node);
			return new_node;
		}
		tree_node* new_node = Insert(&((*node)->right), new_value);
		
		if ((*node)->right->parent == 0)
			(*node)->right->parent = *node;
		
		Balance(*node);
		return new_node;
		
	}
	
	template <typename T>
	typename avl_tree<T>::tree_node* avl_tree<T>::Insert(const T& new_value)
	{
		return Insert(&root_, new_value);
	}
	
	template <typename T>
	void avl_tree<T>::FindAndRemove(avl_tree::tree_node* p_node, const T& key)
	{
		if (!p_node)
			return;
		
		if (key > p_node->_n_value)
		{
			FindAndRemove(p_node->right, key);
			Balance(p_node);
		} else if (key < p_node->_n_value)
		{
			FindAndRemove(p_node->left, key);
			Balance(p_node);
		} else
			Remove(p_node);
	}
	
	template <typename T>
	void avl_tree<T>::Remove(avl_tree::tree_node* p_node)
	{
		if (p_node == nullptr)
			return;
		
		if ((p_node->right == nullptr) && (p_node->left == nullptr))
		{
			if (p_node->parent->right == p_node)
				p_node->parent->right = nullptr;
			else
				p_node->parent->left = nullptr;
			
			delete (p_node);
		} else if (p_node->right == nullptr)
		{
			if (p_node->parent->right == p_node)
				p_node->parent->right = p_node->left;
			else
				p_node->parent->left = p_node->left;
			
			p_node->left->parent = p_node->parent;
			delete (p_node);
		} else if (p_node->left == nullptr)
		{
			if (p_node->parent->right == p_node)
				p_node->parent->right = p_node->right;
			else
				p_node->parent->left = p_node->right;
			
			p_node->right->parent = p_node->parent;
			delete (p_node);
		} else
		{
			p_node->_n_value = Max(p_node->left)->_n_value;
			FindAndRemove(p_node->left, (Max(p_node->left)->_n_value));
		}
	}
	
	template <typename T>
	typename avl_tree<T>::tree_node* avl_tree<T>::Find(avl_tree::tree_node* p_node, const T& key)
	{
		if (key == p_node->_n_value)
			return p_node;
		else
		{
			if ((key < p_node->_n_value) && (p_node->left != nullptr))
				return Find(p_node->left, key);
			else if (p_node->right != nullptr)
				return Find(p_node->right, key);
		}
		return nullptr;
	}
	
	template <typename T>
	void avl_tree<T>::FindAndRemove(const T& key)
	{
		FindAndRemove(root_, key);
	}
	
	
	template <typename T>
	typename avl_tree<T>::tree_node* avl_tree<T>::Max(avl_tree::tree_node* p_node)
	{
		if (p_node == nullptr)
			return p_node;
		
		while (p_node->right != nullptr)
			p_node = p_node->right;
		
		return p_node;
	}
	
	template <typename T>
	void avl_tree<T>::Copy(avl_tree::tree_node** p_dst, const avl_tree::tree_node& src)
	{
		if (*p_dst)
			return;
		
		
		(*p_dst) = new tree_node;
		tree_node* dst = *p_dst;
		dst->_n_value = src._n_value;
		
		if (src.left)
		{
			Copy(&(dst->left), *(src.left));
			dst->left->parent = dst;
		}
		
		if (src.right)
		{
			Copy(&(dst->right), *(src.right));
			dst->right->parent = dst;
		}
	}
	
	template <typename T>
	avl_tree<T>& avl_tree<T>::operator =(const avl_tree& that)
	{
		if (this == &that)
			return *this;
		
		this->Destroy();
		
		if (that.root_)
			Copy(&(this->root_), *(that.root_));
		
		return *this;
	}
	
	template <typename T>
	inline bool operator ==(const avl_tree<T>& lht, const avl_tree<T>& rht)
	{
		return (lht.root_ == rht.root_);
	}
	
} //namespace tld
#endif //CORE_AVL_YGGDRASIL_H
