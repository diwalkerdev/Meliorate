#ifndef MONO_PTR_H
#define MONO_PTR_H

///////////////////////////////////////////////////////////////////////////////

template <typename T>
class mono_ptr {
public:
	T* operator ->() {
		return instance();
	}

    T& operator *() {
        return *instance();
    }

private:
    T* instance() {
        static T t;
        return &t;
    }
};

#endif  /* MONO_PTR_H */
