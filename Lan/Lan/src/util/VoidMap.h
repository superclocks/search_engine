#ifndef _Lan_util_VoidMap_
#define _Lan_util_VoidMap_
#include <hash_map>
#include <map>
namespace Lan
{namespace util{

template<typename _kt,typename _vt,
	typename _base,
	typename _KeyDeletor=Lan::util::Deletor::Dummy,
	typename _ValueDeletor=Lan::util::Deletor::Dummy>
class __CLMap:public _base
{
private:
	bool dk;
	bool dv;
	typedef _base base;
public:
	typedef typename _base::iterator iterator;
	typedef typename _base::const_iterator const_iterator;
	typedef std::pair<_kt,_vt> _pair;

	__CLMap():dk(true),dv(true) //__CLMap默认的构造函数
	{
	}

	~__CLMap()  //__CLMap析构函数
	{
		clear();
	}
	void setDeleteKey(bool val){dk = val;}
	void setDeleteValue(bool val){dv = val;}

	//检测某个key值是否存在
	//参数k为被检测的k值
	//如果k值存在返回true，否则返回false
	bool exists(_kt k) const
	{
		const_iterator itr=base::find(k);
		bool ret=itr!=base::end();
		return ret;
	}

	//将pair添加到map中，如果map中已经有元素，则清空map
	void put(_kt k,_vt v)
	{
		if(dk || dv)
		{
			remove(k);
		}
		base::insert(_pair(k,v));
	}
	//通过key获取value
	_vt get(_kt k) const
	{
		const_iterator itr=base::find(k);
		if(itr==base::end())
		{
			return NULL;
		}
		else
		{
			return itr->second;
		}
	}
	//通过key获取key值
	_kt getKey(_kt k) const
	{
		const_iterator itr=base::find(k);
		if(itr==base::end())
		{
			return NULL;
		}
		else
		{
			return itr->first;
		}
	}
	void removeitr(iterator itr,const bool dontDeleteKey =false,const bool dontDeleteValue = false)
	{
		_kt key = itr->first;
		_vt val = itr->second;
		base::erase(itr);
		//keys & vals need to be deleted after erase, because the hashvalue is still needed
		if(dk && !dontDeleteKey)
		{
			_KeyDeletor::doDelete(key);
		}
		if(dv && !dontDeleteValue)
		{
					_ValueDeletor::doDelete(val);
		}
	}
	//有选择的删除key和value
	void remove(_kt key, const bool dontDeleteKey = false, const bool dontDeleteValue = false)
	{
		iterator itr = base::find(key);
		if(itr != base::end())
		{
			removeitr(itr,dontDeleteKey,dontDeleteValue);
		}
	}
	//删除map中的所有key和value
	void clear()
	{
		if(dk || dv)
		{
			iterator itr = base::begin();
			while(itr != base::end())
			{
				if(dk)
				{
					_KeyDeletor::doDelete(itr->first);
				}
				if(dv)
				{
					_ValueDeletor::doDelete(itr->second);
				}
				++itr;
			}
		}
			base::clear();
		}
};

#define CLHashtable CLHashMap
//HashMap类与Hashtable类相同，但其没有同步特性
template<typename _kt, typename _vt,
	typename _Hasher,
	typename _Equals,
	typename _KeyDeletor=Lan::util::Deletor::Dummy,
	typename _ValueDeletor=Lan::util::Deletor::Dummy>
class CLHashMap:public __CLMap<_kt,_vt,
	stdext::hash_map<_kt,_vt, _Hasher>,
	_KeyDeletor,_ValueDeletor>
{
typedef __CLMap<_kt,_vt, stdext::hash_map<_kt,_vt, _Hasher>,
			_KeyDeletor,_ValueDeletor> _this;
public:
	CLHashMap ( const bool deleteKey=false, const bool deleteValue=false )
	{
		_this::setDeleteKey(deleteKey);
		_this::setDeleteValue(deleteValue);
	}
};
//
template<typename _kt, typename _vt, 
	typename _Compare,
	typename _KeyDeletor=Lan::util::Deletor::Dummy,
	typename _ValueDeletor=Lan::util::Deletor::Dummy>
class CLSet:public __CLMap<_kt,_vt,
	std::map<_kt,_vt, _Compare>,
	_KeyDeletor,_ValueDeletor>
{
	typedef typename std::map<_kt,_vt,_Compare> _base;
	typedef __CLMap<_kt, _vt, std::map<_kt,_vt, _Compare>,
		_KeyDeletor,_ValueDeletor> _this;
public:
	CLSet ( const bool deleteKey=false, const bool deleteValue=false )
	{
		_this::setDeleteKey(deleteKey);
		_this::setDeleteValue(deleteValue);
	}
};



}}
#endif