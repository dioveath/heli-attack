// Vector2D.h
//
// last-edit-by: <> 
//
// Description:
//
//////////////////////////////////////////////////////////////////////

#ifndef VECTOR2D_H
#define VECTOR2D_H 1


#include <math.h>
#include <iostream>


class Vector2D {

 public:
    Vector2D(float x, float y)
	: m_x(x), m_y(y) { }

    float getX() const { return m_x; }
    float getY() const { return m_y; }

    void setX(float x) { m_x = x; }
    void setY(float y) { m_y = y; }

    float length() { return sqrt(m_x*m_x + m_y*m_y); }

    Vector2D(const Vector2D& v) { m_x = v.m_x; m_y = v.m_y; }

    Vector2D operator + (const Vector2D& v2) const {
	return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
    }

    friend Vector2D& operator += (Vector2D& v1, Vector2D& v2){
	v1.m_x += v2.m_x;
	v1.m_y += v2.m_y;

	return v1;
    }

    Vector2D operator - (const Vector2D& v2) const {
	return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
    }

    friend Vector2D& operator -= (Vector2D& v1, Vector2D& v2){
	v1.m_x -= v2.m_x;
	v2.m_y -= v2.m_y;

	return v1;
    }

    Vector2D operator / (float scalar){
	return Vector2D(m_x / scalar, m_y / scalar);
    }

    Vector2D& operator /= (float scalar){
	m_x /= scalar;
	m_y /= scalar;

	return *this;
    }

    Vector2D operator * (float scalar){
	return Vector2D(m_x * scalar, m_y * scalar);
    }

    Vector2D& operator *= (float scalar){
	m_x *= scalar;
	m_y *= scalar;

	/* std::cout << *this << std::endl; */
	return *this;
    }

    void normalize(){
	float l = length();
	if(l > 0){
	    (*this) /= l;
	}
    }


    friend std::ostream& operator << (std::ostream& os, const Vector2D& v){
	os << "(x: " << v.getX();
	os << ",y: " << v.getY() << ")" << std::endl;
	return os;
    }
    

 private:
    float m_x, m_y;

};




#endif // VECTOR2D_H
//////////////////////////////////////////////////////////////////////
// $Log:$
//
