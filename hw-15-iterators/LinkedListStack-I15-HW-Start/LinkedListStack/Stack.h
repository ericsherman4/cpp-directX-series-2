#pragma once

#include <iostream>


class Stack
{
private:
	class Element
	{
		
	public: // element public
		Element( int val,Element* pNext )
			:
			val( val ),
			pNext( pNext )
		{}
		Element( const Element& src )
			:
			val( src.val )
		{
			if( src.pNext != nullptr )
			{
				pNext = new Element( *src.pNext );
			}
		}
		Element& operator=( const Element& ) = delete;
		int GetVal() const
		{
			return val;
		}
		Element* Disconnect()
		{
			auto pTemp = pNext;
			pNext = nullptr;
			return pTemp;
		}
		int CountElements() const
		{
			if( pNext != nullptr )
			{
				return pNext->CountElements() + 1;
			}
			else
			{
				return 1;
			}
		}
		~Element()
		{
			delete pNext;
			pNext = nullptr;
		}

		// dont make this private cause of the silly way all these classes are nested
		int val;
		Element* pNext = nullptr;
	};

public: // stack public
	class ConstIterator
	{
	public:
		ConstIterator() = default;
		ConstIterator(Element* ptr)
			: iter(ptr)
		{
		}
		ConstIterator& operator++() // prefix operator doesnt take any param
		{
			iter = iter->pNext;
			return *this;
		}
		bool operator!=(const ConstIterator& rhs) const
		{
			return iter != rhs.iter;
		}
		// dereference operator, not multiplication!
		// multiplication would take parameters
		// you need this for the for loop to make happy because n is dereferenced
		// and this way you also dont need the overloaded << operator

		// i guess its better to return a const int & than an int becuase youll get an error modiyfing it,
		// verses modying a copy and realizing what youre doing.
		const int& operator*() const
		{
			return iter->val;
		}
		//friend std::ostream& operator<<(std::ostream& stream, Iterator& rhs)
		//{
		//	stream << rhs.iter->val;
		//	return stream;
		//}
	private:
		Element* iter = nullptr;
	};

	class Iterator
	{
	public:
		Iterator() = default;
		Iterator(Element* ptr)
			: iter (ptr)
		{
		}
		Iterator& operator++() // prefix operator doesnt take any param
		{
			iter = iter->pNext;
			return *this;
		}
		bool operator!=(const Iterator & rhs) const
		{
			return iter != rhs.iter;
		}
		// dereference operator, not multiplication!
		// multiplication would take parameters
		// you need this for the for loop to make happy because n is dereferenced
		// and this way you also dont need the overloaded << operator
		int& operator*()
		{
			return iter->val;
		}
		//friend std::ostream& operator<<(std::ostream& stream, Iterator& rhs)
		//{
		//	stream << rhs.iter->val;
		//	return stream;
		//}
	private:
		Element* iter = nullptr;
	};

	Stack() = default;
	Stack( const Stack& src )
	{
		*this = src;
	}
	Stack& operator=( const Stack& src )
	{
		if( &src != this )
		{
			if( !Empty() )
			{
				delete pTop;
				pTop = nullptr;
			}

			if( !src.Empty() )
			{
				pTop = new Element( *src.pTop );
			}
		}
		return *this;
	}
	~Stack()
	{
		delete pTop;
		pTop = nullptr;
	}
	void Push( int val )
	{
		pTop = new Element( val,pTop );
	}
	int Pop()
	{
		if( !Empty() )
		{
			const int tempVal = pTop->GetVal();
			auto pOldTop = pTop;
			pTop = pTop->Disconnect();
			delete pOldTop;
			return tempVal;
		}
		else
		{
			return -1;
		}
	}
	int Size() const
	{
		if( !Empty() )
		{
			return pTop->CountElements();
		}
		else
		{
			return 0;
		}
	}
	bool Empty() const
	{
		return pTop == nullptr;
	}

	Iterator begin()
	{
		//return Iterator(pTop);
		return { pTop };
	}

	Iterator end()
	{
		return {};
	}

	ConstIterator begin() const
	{
		//return Iterator(pTop);
		return { pTop };
	}

	ConstIterator end() const
	{
		return {};
	}



	
private:
	Element* pTop = nullptr;
};
