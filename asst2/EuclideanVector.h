#ifndef _EuclideanVector_H_
#define _EuclideanVector_H_

// FIXME
#include <cassert>
#include <cmath>
#include <cstdint>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>
namespace evec
{

class EuclideanVector
{
    public:
        EuclideanVector();
        EuclideanVector(const EuclideanVector &v);
        EuclideanVector(EuclideanVector &&v);
        EuclideanVector(uint32_t dimension);
        EuclideanVector(uint32_t dimension, double value);
        template<typename Type> EuclideanVector(const Type& begin, const Type& end)
        {
            std::vector<double> tmp = std::vector<double>(begin, end);
            _array = new double[tmp.size()];
            _dimension = 0;
            for (const auto& i: tmp)
            {
                _array[_dimension ++] = i;
            }
            _dimension = tmp.size();
        }

        EuclideanVector(const std::initializer_list<double>& value_list);

        virtual ~EuclideanVector();

        EuclideanVector& operator= (const EuclideanVector& rhs);
        EuclideanVector& operator= (EuclideanVector&& rhs);
        EuclideanVector& operator+=(const EuclideanVector &rhs);
        EuclideanVector& operator-=(const EuclideanVector &rhs);
        EuclideanVector& operator*=(const double& rhs);
        EuclideanVector& operator/=(const double& rhs);
        double& operator[] (int index);
        double  operator[] (int index) const ;


        operator std::vector<double>() const ;
        operator std::list<double>() const;




        friend std::ostream& operator<<(std::ostream &os, const EuclideanVector &v);
        friend bool operator==(const EuclideanVector& lhs, const EuclideanVector& rhs);
        friend bool operator!=(const EuclideanVector& lhs, const EuclideanVector& rhs);
        friend EuclideanVector operator+(const EuclideanVector&lhs, const EuclideanVector& rhs);
        friend EuclideanVector operator-(const EuclideanVector&lhs, const EuclideanVector& rhs);
        friend double operator*(const EuclideanVector&lhs, const EuclideanVector& rhs);
        friend EuclideanVector operator*(const EuclideanVector&lhs, double rhs);
        friend EuclideanVector operator*(double lhs, const EuclideanVector& rhs);
        friend EuclideanVector operator/(const EuclideanVector&lhs, double rhs);



        uint32_t getNumDimensions() const {return _dimension;};
        double   get(uint32_t index) const
        {
            assert(_valid_index(static_cast<int>(index)));
            return (*this)[static_cast<int>(index)];
        };
        double   getEuclideanNorm() const;
        EuclideanVector createUnitVector() const;


    private:

        void _free();
        void _deep_copy(const EuclideanVector& v);
        void _shallow_copy(const EuclideanVector& v);
        void _shallow_free(EuclideanVector& v);
        bool _valid_index(int index) const;


        uint32_t _dimension{0};
        double*  _array{nullptr};

        // double   _cache_norm{0};
        // bool     _cache_flag{0};
};
}

#endif
