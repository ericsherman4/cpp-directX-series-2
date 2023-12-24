#pragma once

#include <iostream>


class Stack
{
private:
	class Element
	{
	public:
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
		void operator*=(int mul)
		{
			val *= mul;
		}
		Element* operator++()
		{
			Element* fun = this->pNext;
			return this->pNext;
		}
		friend std::ostream& operator<<(std::ostream& stream, Element ele)
		{
			stream << ele.GetVal();
			return stream;
		}

		~Element()
		{
			delete pNext;
			pNext = nullptr;
		}
	private:
		int val;
		Element* pNext = nullptr;
	};

public:
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

	Element* begin()
	{
		return pTop;
	}

	Element* end()
	{
		return nullptr;
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
private:
	Element* pTop = nullptr;
};
