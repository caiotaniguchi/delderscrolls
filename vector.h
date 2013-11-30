/*
 *    ************************************************************
 *                             Vectors
 *    ************************************************************
 *
 *    class vector2d
 *       A two dimensional vector.
 *       Constants:
 *          x2d, y2d
 *             Vectors (1, 0) and (0, 1). These values cannot be
 *             changed, but can be used in operations normally.
 *       Operators:
 *          vector2d operator =(vector2d)
 *          vector2d operator +(vector2d)
 *          vector2d operator +=(vector2d)
 *          vector2d operator -(vector2d)
 *          vector2d operator -=(vector2d)
 *          vector2d operator *(double)
 *          vector2d operator *=(double)
 *          vector2d operator /(double)
 *          vector2d operator /=(double)
 *          vector2d operator -(void)
 *          bool operator ==(vector2d)
 *          bool operator !=(vector2d)
 *          bool operator >(vector2d)
 *          bool operator >=(vector2d)
 *          bool operator <(vector2d)
 *          bool operator <=(vector2d)
 *          double operator *(vector2d)
 *             Dot product.
 *          operator string()
 *       Methods:
 *          vector2d()
 *             Constructor. X and Y are set to 0.
 *          vector2d(double newX, double newY)
 *             Constructor. X is set to newX and y is set to newY.
 *          vector2d(vector2d v)
 *             Constructor. X and Y are copied from v.
 *          double getX()
 *          setX(double)
 *          double getY()
 *          setY(double)
 *          double getR()
 *          setR(double)
 *             Length.
 *          double getA()
 *          setA(double)
 *             Angle.
 *          double dot(vector2d)
 *             Dot product.
 *          double cross(vector2d)
 *             Cross product. The result is the Z component of the
 *             resulting 3d vector.
 *          void rotate(double angle)
 *             Rotates the vector counter-clockwise.
 *          void transform(double **matrix)
 *             Performs a linear transformatrix. matrix must be
 *             2 by 2.
 *
 *    class vector3d
 *       A three dimensional vector.
 *       Constants:
 *          x3d, y3d, z3d
 *             Vectors (1, 0, 0), (0, 1, 0) and (0, 0, 1). These
 *             values cannot be changed, but can be used in
 *             operations normally.
 *       Operators:
 *          vector3d operator =(vector3d)
 *          vector3d operator +(vector3d)
 *          vector3d operator +=(vector3d)
 *          vector3d operator -(vector3d)
 *          vector3d operator -=(vector3d)
 *          vector3d operator *(double)
 *          vector3d operator *=(double)
 *          vector3d operator /(double)
 *          vector3d operator /=(double)
 *          vector3d operator -(void)
 *          bool operator ==(vector3d)
 *          bool operator !=(vector3d)
 *          bool operator >(vector3d)
 *          bool operator >=(vector3d)
 *          bool operator <(vector3d)
 *          bool operator <=(vector3d)
 *          double operator *(vector3d)
 *             Dot product.
 *          operator string()
 *       Methods:
 *          vector3d()
 *             Constructor. X, y and z are set to 0.
 *          vector3d(double newX, double newY, double newZ)
 *             Constructor. X is set to newX, y is set to newY and
 *             z is set to newZ.
 *          vector3d(vector3d v)
 *             Constructor. X, y and z are copied from v.
 *          double getX()
 *          setX(double)
 *          double getY()
 *          setY(double)
 *          double getZ()
 *          setZ(double)
 *          double getR()
 *          setR(double)
 *             Length.
 *          double getA1()
 *          setA1(double)
 *             Angle with the Z axis.
 *          double getA2()
 *          setA2(double)
 *             Angle between the X axis and the projection of the
 *             vector on the XY plane.
 *          double dot(vector3d)
 *             Dot product.
 *          vector3d cross(vector3d)
 *             Cross product.
 *          void rotate(double angle, double dirX, double dirY, double dirZ)
 *             Rotates the vector counter-clockwise around the
 *             direction dirX, dirY, dirZ.
 *          void rotate(double angle, vector3d v)
 *             Rotates the vector counter-clockwise around the
 *             v vector.
 *          void transform(double **matrix)
 *             Performs a linear transformatrix. matrix must be
 *             3 by 3.
 *
 */

#ifndef VECTOR_H
#define VECTOR_H "vector.h"

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdarg>

/*****************************************************************
                            Vectors
*****************************************************************/

class vector2d{
   private:
      double x, y;
   public:
      vector2d(){}
      vector2d(double newX, double newY):x(newX),y(newY){}
      vector2d(const vector2d &v):x(v.x),y(v.y){}
      double getX() const;
      void setX(double newX);
      double getY() const;
      void setY(double newY);
      double getR() const;
      void setR(double newR);
      double getA() const;
      void setA(double newA);
      double dot(const vector2d &v) const;
      double cross(const vector2d &v) const;
      void rotate(double angle);
      void transform(double **matrix);
      const vector2d &operator =(const vector2d &v);
      const vector2d operator +(const vector2d &v) const;
      const vector2d &operator +=(const vector2d &v);
      const vector2d operator -(const vector2d &v) const;
      const vector2d &operator -=(const vector2d &v);
      const vector2d operator *(double d) const;
      friend const vector2d operator *(double d, const vector2d &v);
      const vector2d &operator *=(double d);
      const vector2d operator /(double d) const;
      const vector2d &operator /=(double d);
      const vector2d operator -(void) const;
      bool operator ==(const vector2d &v) const;
      bool operator !=(const vector2d &v) const;
      bool operator >(const vector2d &v) const;
      bool operator >=(const vector2d &v) const;
      bool operator <(const vector2d &v) const;
      bool operator <=(const vector2d &v) const;
      double operator *(const vector2d &v) const;
      operator std::string() const;
};

extern const vector2d x2d, y2d;

class vector3d{
   private:
      double x, y, z;
   public:
      vector3d(){}
      vector3d(double newX, double newY, double newZ):x(newX),y(newY),z(newZ){}
      vector3d(const vector3d &v):x(v.x),y(v.y),z(v.z){}
      double getX() const;
      void setX(double newX);
      double getY() const;
      void setY(double newY);
      double getZ() const;
      void setZ(double newZ);
      double getR() const;
      void setR(double newR);
      double getA1() const;
      void setA1(double newA1);
      double getA2() const;
      void setA2(double newA2);
      double dot(const vector3d &v) const;
      const vector3d cross(const vector3d &v) const;
      void rotate(double angle, double dirX, double dirY, double dirZ);
      void rotate(double angle, const vector3d &v);
      void transform(double **matrix);
      const vector3d &operator =(const vector3d &v);
      const vector3d operator +(const vector3d &v) const;
      const vector3d &operator +=(const vector3d &v);
      const vector3d operator -(const vector3d &v) const;
      const vector3d &operator -=(const vector3d &v);
      const vector3d operator *(double d) const;
      friend const vector3d operator *(double d, const vector3d &v);
      const vector3d &operator *=(double d);
      const vector3d operator /(double d) const;
      const vector3d &operator /=(double d);
      const vector3d operator -(void) const;
      bool operator ==(const vector3d &v) const;
      bool operator !=(const vector3d &v) const;
      bool operator >(const vector3d &v) const;
      bool operator >=(const vector3d &v) const;
      bool operator <(const vector3d &v) const;
      bool operator <=(const vector3d &v) const;
      double operator *(const vector3d &v) const;
      operator std::string() const;
};

extern const vector3d x3d, y3d, z3d;

/*****************************************************************
                        Implementation
*****************************************************************/

template <class T>
T fromStr(std::string s){
   std::istringstream st(s);
   T result;
   st >> result;
   return result;
}

template <class T>
std::string toStr(T v){
   std::ostringstream st;
   st << v;
   return st.str();
}

template <class T>
const typename varManager<T>::varType &varManager<T>::varType::operator=(const varType &v){
   name = v.name;
   value = v.value;
   return *this;
}

template <class T>
bool varManager<T>::varType::operator<(const varType &v) const{
   return name.compare(v.name)<0;
}

template <class T>
void varManager<T>::write(const std::string &id, const T &val){
   varType newVar(id, val);
   typename std::vector<varType>::iterator it;
   it = std::lower_bound(varList.begin(), varList.end(), newVar);
   if (std::binary_search(varList.begin(), varList.end(), newVar)){
      *it = newVar;
      return;
   }
   varList.insert(it, newVar);
}

template <class T>
bool varManager<T>::read(const std::string &id, T &val){
   varType newVar(id);
   if (std::binary_search(varList.begin(), varList.end(), newVar)){
      typename std::vector<varType>::iterator it;
      it = std::lower_bound(varList.begin(), varList.end(), newVar);
      val = (*it).value;
      return true;
   }
   return false;
}

#endif
