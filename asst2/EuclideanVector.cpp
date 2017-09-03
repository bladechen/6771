// use assert instead of exception, because for the assignment, what happen an exception
// caught(invalid input) but i can not do any thing with it but simply call exit(-1)?
// therefore when asst spec tells me the error msg need to output, then it is the case
// to use exception rather than assert.
// refer to https://www.cse.unsw.edu.au/~cs6771/16s2/postscript/html/week06.html#Exceptions versus assertions
//
#include "EuclideanVector.h"

namespace evec
{

    EuclideanVector::EuclideanVector():EuclideanVector(1, 0.0){}

    EuclideanVector::EuclideanVector(const EuclideanVector &v)
    {
        _deep_copy(v);
    }

    EuclideanVector::EuclideanVector(EuclideanVector &&v)
    {
        _shallow_copy(v);
        _shallow_free(v);
    }


    EuclideanVector::EuclideanVector(uint32_t dimension):EuclideanVector(dimension, 0.0){}

    EuclideanVector::EuclideanVector(uint32_t dimension, double value)
    {
        _array = new double[dimension];
        _dimension = dimension;
        for (auto i = 0U; i < _dimension; ++ i)
        {
            _array[i] = value;
        }
        assert(_array != nullptr);
    }

    EuclideanVector::EuclideanVector(const std::initializer_list<double>& value_list) : EuclideanVector(value_list.begin(), value_list.end()){}

    EuclideanVector::~EuclideanVector()
    {
        _free();
    }

    EuclideanVector& EuclideanVector::operator=(const EuclideanVector& rhs)
    {
        if (this != &rhs)
        {
            _deep_copy(rhs);
            _invalid_cache();
        }
        return *this;
    }

    EuclideanVector& EuclideanVector::operator=(EuclideanVector&& rhs)
    {
        if (this != &rhs)
        {
            _shallow_copy(rhs);
            _shallow_free(rhs);
            _invalid_cache();
        }
        return *this;
    }

    // the format would be [1 2 3]
    std::ostream& operator<<(std::ostream &os, const EuclideanVector &v)
    {
        os << "[";
        for (auto i = 0U; i < v.getNumDimensions(); ++ i)
        {
            if (i == 0)
                os << v[i];
            else
                os << " " << v[i];
        }
        os << "]";
        return os;
    }

    double& EuclideanVector::operator[](int index)
    {
        assert(_valid_index(index));
        _invalid_cache();
        return _array[index];
    }

    double EuclideanVector::operator[](int index) const
    {
        assert(_valid_index(index));
        return _array[index];
    }


    EuclideanVector& EuclideanVector::operator+=(const EuclideanVector &rhs)
    {
        assert(_dimension == rhs._dimension);
        for (auto i = 0U; i < _dimension; ++ i)
        {
            _array[i] += rhs._array[i];
        }
        _invalid_cache();
        return *this;
    }

    EuclideanVector& EuclideanVector::operator-=(const EuclideanVector &rhs)
    {
        assert(_dimension == rhs._dimension);
        for (auto i = 0U; i < _dimension; ++ i)
        {
            _array[i] -= rhs._array[i];
        }
        _invalid_cache();
        return *this;
    }

    EuclideanVector& EuclideanVector::operator*=(const double& rhs)
    {
        for (auto i = 0U; i < _dimension; ++ i)
        {
            _array[i] *= rhs;
        }
        _invalid_cache();
        return *this;
    }

    EuclideanVector& EuclideanVector::operator/=(const double& rhs)
    {
        for (auto i = 0U; i < _dimension; ++ i)
        {
            _array[i] /= rhs;
        }
        _invalid_cache();
        return *this;
    }

    EuclideanVector::operator std::vector<double>() const
    {
        if (_array == nullptr)
        {
            return std::vector<double>();
        }
        return std::vector<double>(_array, _array + _dimension);
    }

    EuclideanVector::operator std::list<double>() const
    {
        if (_array == nullptr)
        {
            return std::list<double>();
        }
        return std::list<double>(_array, _array + _dimension);
    }

    EuclideanVector operator+(const EuclideanVector&lhs, const EuclideanVector& rhs)
    {
        assert(lhs.getNumDimensions() == rhs.getNumDimensions());
        EuclideanVector ret(lhs);
        ret += rhs;
        return ret;
    }

    EuclideanVector operator-(const EuclideanVector&lhs, const EuclideanVector& rhs)
    {
        assert(lhs.getNumDimensions() == rhs.getNumDimensions());
        EuclideanVector ret(lhs);
        ret -= rhs;
        return ret;
    }

    bool operator==(const EuclideanVector& lhs, const EuclideanVector& rhs)
    {
        if (lhs.getNumDimensions() != rhs.getNumDimensions())
        {
            return false;
        }
        uint32_t len = lhs.getNumDimensions();
        for (auto i = 0U; i < len; ++ i)
        {
            if (lhs[i] != rhs[i])
            {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const EuclideanVector& lhs, const EuclideanVector& rhs)
    {
        return !(lhs == rhs);
    }
    // dot-product multiplication.
    double operator*(const EuclideanVector& lhs, const EuclideanVector& rhs)
    {
        assert(lhs.getNumDimensions() == rhs.getNumDimensions());
        double result = 0;
        for (auto i = 0U; i < lhs.getNumDimensions(); ++ i)
        {
            result += lhs[i] * rhs[i];
        }
        return result;
    }

    // perform scalar multiplication.
    EuclideanVector operator*(const EuclideanVector&lhs, double rhs)
    {
        EuclideanVector ret(lhs);
        ret *= rhs;
        return ret;
    }

    // perform scalar multiplication.
    EuclideanVector operator*(double lhs, const EuclideanVector& rhs)
    {
        EuclideanVector ret(rhs);
        ret *= lhs;
        return ret;
    }

    EuclideanVector operator/(const EuclideanVector& lhs, double rhs)
    {
        EuclideanVector ret(lhs);
        ret /= rhs;
        return ret;
    }

    double EuclideanVector::getEuclideanNorm() const
    {
        if (_cache_flag)
        {
            return _cache_norm;
        }
        double result = 0;
        for (auto i = 0U; i < _dimension; ++ i)
        {
            result += _array[i] * _array[i];
        }
        _cache_flag = true;
        _cache_norm = ::sqrt(result);
        return _cache_norm;
    }

    EuclideanVector EuclideanVector::createUnitVector() const
    {
        return EuclideanVector(*this) /= getEuclideanNorm();
    }

    void EuclideanVector::_free()
    {
        if (_array != nullptr)
        {
            delete[] _array;
            _array = nullptr;
        }
        _dimension = 0;
        _invalid_cache();
    }

    // the caller of copy should make sure they are not the same.
    // one function for one responsibility!
    void EuclideanVector::_shallow_copy(const EuclideanVector& v)
    {
        assert(this != &v);
        _free();
        _dimension = v._dimension;
        _array = v._array;
    }

    void EuclideanVector::_deep_copy(const EuclideanVector& v)
    {
        assert(this != &v);
        _free();
        _dimension = v._dimension;
        _array = new double[_dimension];
        for (auto i = 0U; i < _dimension; i ++)
        {
            _array[i] = v[i];
        }
    }

    void EuclideanVector::_shallow_free(EuclideanVector& v)
    {
        v._dimension = 0;
        v._array = nullptr;
        _invalid_cache();
    }

    bool EuclideanVector::_valid_index(int index) const
    {
        return (index >= 0 && index < static_cast<int>(_dimension));
    }

}
