#ifndef _OPENGL_OBJECT_H
#define _OPENGL_OBJECT_H

class Base
{

private:
    unsigned int                _cRefs;

public:
    Base() :            _cRefs(0) { }
    virtual ~Base() { }
    void                NewRef() { ++_cRefs; }

    void                DelRef()
    {
        if (--_cRefs == 0) {
            delete this;
        }
    }
    
    unsigned int getRefCount() const { return _cRefs; }
};



#endif