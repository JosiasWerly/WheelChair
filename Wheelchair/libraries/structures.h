namespace DataStructures
{
	template<typename rType>
	class dFunctor;
	template<typename objType, typename rType>
	class dMemberFnx;

	class dBase
	{
	private:
		dBase *dxPad;
	public:
		virtual void unbind()
		{
			delete dxPad;
			dxPad = nullptr;
		}
		virtual void operator()()
		{
			dxPad->operator()();
		}

		template<typename rType>
		void bind(rType(*fnx)())
		{
			dxPad = new dFunctor<rType>(fnx);
		}
		template<typename rType, typename objType>
		void bind(rType(objType::*fnx)(), objType& obj)
		{
			dxPad = new dMemberFnx<objType, rType>(fnx, obj);
		}

		template<typename rType>
		dBase(rType(*fnx)())
		{
			this->bind(fnx);
		}
		template<typename rType, typename objType>
		dBase(rType(objType::*fnx)(), objType& obj)
		{
			this->bind(fnx, obj)
		}
	};
	template<typename rType>
	class dFunctor : public dBase
	{
	public:
		rType(*Fnx)();

		dFunctor()
		{}
		dFunctor(rType(*fnx) ()) : Fnx(fnx)
		{}

		rType operator()()
		{
			return Fnx();
		}
	};
	template<typename objType, typename rType>
	class dMemberFnx : public dBase
	{
	private:
		typedef rType(objType::*fnx)();
	public:
		objType& Obj;
		fnx Fnx;

		dMemberFnx()
		{}
		dMemberFnx(fnx fnx, objType& obj)
			: Fnx(fnx), Obj(obj)
		{}
		rType operator()()
		{
			return (Obj.*Fnx)();
		}
	};

	//template<class T> class X { typename T::Y;
	class Serializable
	{
	public:
		Serializable()
		{}
		virtual char* serialize() = 0;
		virtual int unSerialize(char* Value) = 0;
	};
	template <typename Type>
	class Iterator
	{
	public:
		Type Value;
		Iterator *Next, *Preview;

		Iterator()
		{
			Next = nullptr;
			Preview = nullptr;
		}
		Iterator(Type _value)
		{
			this->Value = _value;
			this->Next = nullptr;
			Preview = nullptr;
		}
		~Iterator()
		{
			Next = nullptr;
			Preview = nullptr;
		}
		Type* operator++()
		{
			return Next;
		}
		Type* operator--()
		{
			return Preview;
		}
	};
	template<typename Key, typename Value>
	class Pair : public Serializable
	{
	private:
		typedef typename Key TKey;
		typedef typename Value TValue;
	public:
		Key key;
		Value value;

		Pair()
		{
		}
		Pair(Key key)
		{
			this->key = key;
		}
		Pair(Key key, Value value)
		{
			this->key = key;
			this->value = value;
		}
		~Pair()
		{
		}

		char* serialize()
		{
			/*string *_key = nullptr, *_value = nullptr;
			string Result = "";

			_key = dynamic_cast<string*>(&key);
			_value = dynamic_cast<string*>(&value);
			if (_key && _value)
			{
				Result = string(*_key + ":" + *_value);
				_key = nullptr;	_value = nullptr;
				delete _key, _value;
			}
			return Result;*/
			return "";
		}
		int unSerialize(char* data)
		{
			/*Key *_key = nullptr;
			Value *_value = nullptr;
			int KeyEnd = 0;
			for (size_t i = 0; i < data.length(); i++)
				if (data[i] == ':')
				{
					KeyEnd = i;
					break;
				}
			string
				__key = data.substr(0, KeyEnd),
				__value = data.substr(KeyEnd + 1);
			try
			{
				<Key*>(&__key);
				_value = dynamic_cast<Value*>(&__value);
				if (_key && _value)
					this->operator[](*_key) = *_value;
				_value = _key = nullptr;
			}
			catch (const std::exception&)
			{
				throw;
			}
			return KeyEnd;*/
			return 1;
		}

		Value &operator[](Key key)
		{
			this->key = key;
			return value;
		}
		void operator=(Pair<Key, Value> Other)
		{
			key = Other.key;
			value = Other.value;
		}
		void operator=(const Value &value)
		{
			this->value = value;
		}
		bool operator==(Pair<Key, Value> Other)
		{
			return
				key == Other.key &&
				value == Other.value;
		}
		bool operator==(const Key &key)
		{
			return this->key == key;
		}
	};
	template <typename Type>
	class List : public Serializable
	{
	public:
		typedef typename Iterator<Type> Iterator;
		typedef typename Iterator* PIterator;
	protected:
		Iterator *First, *Last;
		unsigned int list_size;
	public:
		List()
		{
			First = nullptr;
			Last = nullptr;
			list_size = 0;
		}
		~List()
		{
			PIterator _it = nullptr;
			for (;list_size > 0; list_size--)
			{
				_it = First;
				First = First->Next;
				delete _it;
				_it = nullptr;
			}
		}
		void clear()
		{
			Iterator *it = First, *_t;
			for (int i = 0; i < list_size; i++)
			{
				_t = it->Next;
				delete it;
				it = NULL;
				it = _t;
			}
			Last = NULL;
			First = NULL;
			list_size = 0;
		}
		PIterator emplaceBack(Type _value)
		{
			list_size++;
			if (!First)
				Last = First = new Iterator(_value);
			else
			{
				Iterator *t = Last;
				Last = new Iterator(_value);
				t->Next = Last;
				Last->Preview = t;
			}
			return Last;
		}
		PIterator emplace(Type _value, unsigned int Position)
		{
			PIterator	Next = NULL,
				Actual = NULL;
			Actual = at(Position);
			if (!Actual)
				return emplaceBack(_value);
			else
			{
				if (Actual->Next)
				{
					Next = Actual->Next;
					Actual->Next = new Iterator(_value, Next);
					Actual->Next->Preview = Actual;
					Next->Preview = Actual->Next;
					return Actual->Next;
				}
				else
					return emplaceBack(_value);
			}
		}
		bool erase(unsigned int Index)
		{
			if (Index < list_size)
			{
				PIterator _internal = this->at(Index);
				if (_internal->Preview)
					if (_internal->Next)
						_internal->Preview->Next = _internal->Next;
				if (_internal->Next)
					if (_internal->Preview)
						_internal->Next->Preview = _internal->Preview;
				delete _internal;
				_internal = nullptr;
				list_size--;
				return true;
			}
			return false;
		}
		bool erase(Type Value)
		{
			unsigned int found = false;
			PIterator t = First;
			for (unsigned int i = 0; i < list_size; i++)
				if (t->Value == Value)
				{
					found = i;
					break;
				}
				else
					t = t->Next;
			if (found != false)
				return delete(found);
			return false;
		}
		unsigned int size()
		{
			return list_size;
		}
		virtual List<Type> &operator=(const List<Type> *Other)
		{
			*this = Other;
			return *this;
		}
		virtual List<Type> &operator=(const List<Type> &Other)
		{
			this->clear();
			PIterator t = Other.First;
			for (unsigned int i = 0; i < Other.list_size; i++)
			{
				if (t)
				{
					this->emplaceBack(t->Value);
					t = t->Next;
				}
			}
			return *this;
		}
		virtual Type &operator[](unsigned int Index)
		{
			PIterator t = First;
			for (unsigned int i = 0; i < Index; i++)
				t = t->Next;
			return t->Value;
		}
		PIterator find(Type Value)
		{
			PIterator t = First;
			for (unsigned int i = 0; i < list_size; i++)
				if (t->Value == Value)
					return t;
				else
					t = t->Next;
			return NULL;
		}
		PIterator at(unsigned int Index)
		{
			if (Index >= list_size)
				return nullptr;
			PIterator t = First;
			for (unsigned int i = 0; i < Index; i++)
				t = t->Next;
			return t;
		}
		PIterator begin()
		{
			return First;
		}
		PIterator end()
		{
			return Last;
		}

		char* serialize()
		{
			return "NotDone";
		}
		virtual int unSerialize(char* data)
		{
			return -1;
		}
	};
	template <typename Key, typename Value>
	class Map : public List<Pair<Key, Value>>
	{
	public:
		typedef typename Pair<Key, Value> PairType;
		typedef typename List<Pair<Key, Value>>::Iterator Iterator;
		typedef typename Iterator* PIterator;
		Map()
		{
		}
		~Map()
		{
		}
		PairType &operator[](Key key)
		{
			PIterator t = List<Pair<Key, Value>>::First;
			for (unsigned int i = 0; i < List<Pair<Key, Value>>::size(); i++)
				if (t->Value == key)
					break;
				else
					t = t->Next;
			if (!t)
				t = emplaceBack(PairType(key));
			return t->Value;
		}
		virtual PairType &operator[](unsigned int Index)
		{
			PIterator t = List<Pair<Key, Value>>::First;
			for (unsigned int i = 0; i < Index; i++)
			{
				t = t->Next;
			}
			return t->Value;
		}
		char* serialize()
		{
			/*string _internal = "";
			for (PIterator it = First; it; it = it->Next)
				_internal += it->Value.serialize() + '\n';
			return _internal;*/
			return "";
		}
		int unSerialize(char* data)
		{
			/*Pair<string, string> _internal;
			unsigned int lastPost = 0;
			for (unsigned int i = 0; i < Data.length(); i++)
			{
				if (Data[i] == '\n')
				{
					_internal.unSerialize(Data.substr(lastPost, i - lastPost));
					this->operator[](_internal.key) = _internal.value;
					lastPost = i + 1;
				}
			}*/
			return 0;
		}
	};
	template<typename Type>
	class Node
	{
		typedef typename Node* tKey;
		typedef typename float tValue;
		typedef typename Pair<tKey, tValue> TLink;
		typedef typename List<TLink> TEdge;
	public:
		Type value;
		TEdge edges;


		Node(Type value) : value(value)
		{}
		Node()
		{}
		Node* link(Node<Type> *node, tValue value = 1)
		{
			node->edges.emplaceBack(TLink(this, value));
			edges.emplaceBack(TLink(node, value));
			return node;
		}
		unsigned int linkCounts()
		{
			return
		}

	};
};