//
//  SmartPointer.hpp
//  openGLTest
//
//  Created by xt on 17/8/29.
//  Copyright © 2017年 xt. All rights reserved.
//

#ifndef SmartPointer_hpp
#define SmartPointer_hpp

#include <stdio.h>

template <class T>
class RefPointer
{
    T * _pt;

    void                SaveNew() {if(_pt != 0)  _pt->NewRef();}
    void                SaveDel() {if(_pt != 0) _pt->DelRef();}

public:
    RefPointer(T* pt = 0):_pt(pt) {SaveNew();}
    RefPointer(const RefPointer<T>&mp):_pt(mp._pt){SaveNew();}
    RefPointer(){SaveDel();}

    operator            T*()const{return _pt;}
    T&operator          *()const {return *_pt;}
    T*operator          ->()const {return _pt;}

    T*                  Addr(){return _pt;}

    RefPointer<T>&    operator=(RefPointer<T>&sp)
    {
    return operator=(sp._pt);
    }

    RefPointer<T>&    operator=(T*p)
    {
    if(_pt != p)
        {
        SaveDel();
        _pt = p;
        SaveNew();
        }
    return (*this);
    }

    bool                operator==(T*)const;
    bool                operator!=(T*)const;
    bool                operator==(const RefPointer<T>&)const;
    bool                operator!=(const RefPointer<T>&)const;



};

template<class T>
inline bool RefPointer<T>::operator==(T *_pT) const
{
    return (_pt == _pT);
}

template<class T>
inline bool RefPointer<T>::operator!=(T *_pT) const
{
    return !operator==(_pT);
}

template<class T>
inline bool RefPointer<T>::operator==(const RefPointer& _pT) const
{
    return operator==(_pT._pt);
}

template<class T>
inline bool RefPointer<T>::operator!= (const RefPointer& _pT) const
{
    return !operator==(_pT);
}


#endif /* SmartPointer_hpp */
