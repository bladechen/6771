#pragma once

#include <cassert>
#include <cmath>
#include <cstdint>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

// I make double pass by const reference, because double takes 12bytes to store in x86.
namespace evec
{

    class EuclideanVector
    {
        public:
            // constructor
            EuclideanVector();
            EuclideanVector(const EuclideanVector &v);
            EuclideanVector(EuclideanVector &&v);
            EuclideanVector(uint32_t dimension);
            EuclideanVector(uint32_t dimension, const double& value);
            // use list/vector/etc. iterator to construct EuclideanVector
            // template<typename Type> EuclideanVector(const Type::iterator & begin, const Type::iterator& end)
            template< typename Iterator, typename U = typename std::iterator_traits<Iterator>::difference_type>
            EuclideanVector(const Iterator& begin, const Iterator& end)
            {
                _dimension = std::distance(begin, end);
                _array = new double[_dimension];
                std::copy(begin, end, _array);
                // const auto& tmp = std::vector<double>(begin, end);
                // _array = new double[tmp.size()];
                // _dimension = tmp.size();
                // std::copy(tmp.begin(), tmp.end(), _array);
            }

            EuclideanVector(const std::initializer_list<double>& value_list);

            virtual ~EuclideanVector();

            EuclideanVector& operator=(const EuclideanVector& rhs);
            EuclideanVector& operator=(EuclideanVector&& rhs);
            EuclideanVector& operator+=(const EuclideanVector &rhs);
            EuclideanVector& operator-=(const EuclideanVector &rhs);
            EuclideanVector& operator*=(const double& rhs);
            EuclideanVector& operator/=(const double& rhs);

            double& operator[](int index);
            double  operator[](int index) const;
            operator std::vector<double>() const;
            operator std::list<double>() const;


            uint32_t getNumDimensions() const
            {
                return _dimension;
            };
            double   get(uint32_t index) const
            {
                assert(_valid_index(static_cast<int>(index)));
                return (*this)[static_cast<int>(index)];
            };
            double   getEuclideanNorm() const;
            EuclideanVector createUnitVector() const;

        private:
            void _invalid_cache()
            {
                _cache_flag = false;
            };
            void _free();
            void _deep_copy(const EuclideanVector& v);
            void _shallow_copy(const EuclideanVector& v);
            void _shallow_free(EuclideanVector& v);
            bool _valid_index(int index) const;

            uint32_t _dimension{0};
            double*  _array{nullptr};

            mutable double   _cache_norm{0};
            mutable bool     _cache_flag{false};
    };

    std::ostream& operator<<(std::ostream &os, const EuclideanVector &v);
    bool operator==(const EuclideanVector& lhs, const EuclideanVector& rhs);
    bool operator!=(const EuclideanVector& lhs, const EuclideanVector& rhs);
    EuclideanVector operator+(const EuclideanVector&lhs, const EuclideanVector& rhs);
    EuclideanVector operator-(const EuclideanVector&lhs, const EuclideanVector& rhs);
    double operator*(const EuclideanVector&lhs, const EuclideanVector& rhs);
    EuclideanVector operator*(const EuclideanVector&lhs, const double& rhs);
    EuclideanVector operator*(const double& lhs, const EuclideanVector& rhs);
    EuclideanVector operator/(const EuclideanVector&lhs, const double& rhs);

}
