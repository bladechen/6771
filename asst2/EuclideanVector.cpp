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


EuclideanVector::EuclideanVector(uint32_t dimension):EuclideanVector(dimension, 0.0)
{

}

EuclideanVector::EuclideanVector(uint32_t dimension, double value)
{
    _array = new double[dimension];
    _dimension = dimension;
    for (uint32_t i = 0; i < _dimension; ++ i)
    {
        _array[i] = value;
    }
    assert(_array != nullptr);
}

EuclideanVector::EuclideanVector(const std::initializer_list<double>& value_list) : EuclideanVector(value_list.begin(), value_list.end())
{

}

EuclideanVector::~EuclideanVector()
{
    _free();
}


EuclideanVector& EuclideanVector::operator=(const EuclideanVector& rhs)
{
    if (this != &rhs)
    {
        _deep_copy(rhs);
    }
    return *this;

}

EuclideanVector& EuclideanVector::operator=(EuclideanVector&& rhs)
{
    if (this != &rhs)
    {
        _shallow_copy(rhs);
        _shallow_free(rhs);
    }
    return *this;

}

std::ostream& operator<<(std::ostream &os, const EuclideanVector &v)
{
    os << "[";
    for (uint32_t i = 0; i < v._dimension; ++ i)
    {
        if (i == 0) os << v[i];
        else os << " " << v[i];
    }
    os << "]";
    return os;
}

double& EuclideanVector::operator[] (int index)
{
    assert(_valid_index(index));
    return _array[index];
}

double  EuclideanVector::operator[] (int index)  const
{
    assert(index < static_cast<int>(_dimension) && index >= 0);
    return _array[index];
}


EuclideanVector& EuclideanVector::operator+=(const EuclideanVector &rhs)
{

    assert(_dimension == rhs._dimension);
    for (uint32_t i = 0; i < _dimension; ++ i)
    {
        _array[i] += rhs._array[i];

    }
    return *this;


}

EuclideanVector& EuclideanVector::operator-=(const EuclideanVector &rhs)
{
    assert(_dimension == rhs._dimension);
    for (uint32_t i = 0; i < _dimension; ++ i)
    {
        _array[i] -= rhs._array[i];

    }
    return *this;
}

EuclideanVector& EuclideanVector::operator*=(const double& rhs)
{
    for (uint32_t i = 0; i < _dimension; ++ i)
    {
        _array[i] *= rhs;

    }
    return *this;
}

EuclideanVector& EuclideanVector::operator/=(const double& rhs)
{
    for (uint32_t i = 0; i < _dimension; ++ i)
    {
        _array[i] /= rhs;

    }
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


bool operator==(const EuclideanVector& lhs, const EuclideanVector& rhs)
{
    if (lhs.getNumDimensions() != rhs.getNumDimensions())
    {
        return false;
    }
    uint32_t len = lhs.getNumDimensions();
    for (uint32_t i = 0; i < len; ++ i)
    {
        if (lhs[i] != rhs[i]) return false;
    }
    return true;
}

bool operator!=(const EuclideanVector& lhs, const EuclideanVector& rhs)
{
    return !(lhs == rhs);
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

double operator*(const EuclideanVector& lhs, const EuclideanVector& rhs)
{

    assert(lhs.getNumDimensions() == rhs.getNumDimensions());
    double result = 0;
    for (uint32_t i = 0; i < lhs.getNumDimensions(); ++ i)
    {
        result += lhs[i] * rhs[i];
    }
    return result;
}

EuclideanVector operator*(const EuclideanVector&lhs, double rhs)
{
    EuclideanVector ret(lhs);
    ret *= rhs;
    return ret;

}

EuclideanVector operator*(double lhs, const EuclideanVector& rhs)

{
    EuclideanVector ret(rhs);
    ret *= lhs;
    return ret;

}


EuclideanVector operator/(const EuclideanVector&lhs, double rhs)
{
    EuclideanVector ret(lhs);
    ret /= rhs;
    return ret;
}

double EuclideanVector::getEuclideanNorm() const
{
    double result = 0;
    for (uint32_t i = 0; i < _dimension; ++ i)
    {
        result += _array[i] * _array[i];
    }
    return ::sqrt(result);

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
}

void EuclideanVector::_shallow_copy(const EuclideanVector& v)
{
    if (this == &v)
    {
        return;
    }
    _free();
    _dimension = v._dimension;
    _array = v._array;
}

void EuclideanVector::_deep_copy(const EuclideanVector& v)
{
    if (this == &v)
    {
        return;
    }
    _free();
    _dimension = v._dimension;
    _array = new double[_dimension];
    for (uint32_t i = 0; i < _dimension; i ++)
    {
        _array[i] = v[i];
    }
}


void EuclideanVector::_shallow_free(EuclideanVector& v)
{
    v._dimension = 0;
    v._array = nullptr;
}


bool EuclideanVector::_valid_index(int index) const
{
    return (index >= 0 && index < static_cast<int>(_dimension));
}

}
