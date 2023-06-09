#include <iostream>

template<typename T, unsigned char N, unsigned char M> //using template to allow matrixes of any data type

class Matrix {

private:

    T m_arr[N][M];

public:

    template <typename T, unsigned char N, unsigned char M>
    friend void setElement(Matrix<T, N, M>& matrix, unsigned char n, unsigned char m, T element);

    template <typename T, unsigned char N, unsigned char M>
    friend std::ostream& operator << (std::ostream& out, const Matrix<T, N, M>& matrix);

    template <typename T, unsigned char N, unsigned char M>
    friend std::istream& operator >> (std::istream& in, Matrix<T, N, M>& matrix);

    Matrix()
    {
        std::fill((T*)m_arr, (T*)m_arr + N * M, 0);     //fill matrix with zeros
        std::cout << "Default constructor" << std::endl;
    }

    ~Matrix()
    {
        std::cout << "Destructor" << std::endl;
    };

    Matrix(const Matrix<T, N, M>& matrix)       //copy constructor
    {
        std::copy(matrix.m_arr[0], matrix.m_arr[0] + N * M, m_arr[0]);
        std::cout << "Copy constructor" << std::endl;
    }

    Matrix<T, N, M>& operator = (const Matrix<T, N, M>& other)      //copy assignment operator
    {
        std::copy(other.m_arr[0], other.m_arr[0] + N * M, m_arr[0]);
        std::cout << "Copy asignment operator" << std::endl;
        return *this;
    }

    double determinant()
    {
        if (N == 1 && M == 1)
        {
            return (double)m_arr[0][0];
        }
        if (N == 2 && M == 2)
        {
            return ((double)(m_arr[0][0] * m_arr[1][1]) - (double)(m_arr[1][0] * m_arr[0][1]));
        }

        if (N == 3 && M == 3)   //rule of triangle
        {
            return ((double)(m_arr[0][0] * m_arr[1][1] * m_arr[2][2]) + ((double)m_arr[0][1] * m_arr[1][2] * m_arr[2][0]) +
                ((double)m_arr[1][0] * m_arr[2][1] * m_arr[0][2]) - ((double)m_arr[0][2] * m_arr[1][1] * m_arr[2][0]) -
                ((double)m_arr[1][2] * m_arr[2][1] * m_arr[0][0]) - ((double)m_arr[1][0] * m_arr[0][1] * m_arr[2][2]));
        }

        throw std::exception();     //if det = 0

    }

    Matrix& operator ++ ()      //prefix
    {
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < M; j++) {
                this->m_arr[i][j] += 1;
            }
        }
        return *this;
    }

    Matrix operator ++ (int)		//postfix
    {
        Matrix temp = *this;

        for (int i = 0; i < this->N; i++)
        {
            for (int j = 0; j < this->M; j++)
            {
                ++(this->m_arr[i][j]);
            }
        }

        return temp;
    }

    T at(unsigned char n, unsigned char m)      //returns the element
    {
        return this->m_arr[n][m];
    }
};

template <typename T, unsigned char N, unsigned char M>
void setElement(Matrix<T, N, M>& matrix, unsigned char n, unsigned char m, T element) {
    matrix.m_arr[n][m] = element;
}

template <typename T, unsigned char N, unsigned char M>
std::ostream& operator << (std::ostream& out, const Matrix<T, N, M>& matrix)
{
    for (size_t i = 0; i < N; i++)
    {
        out << "   ( ";
        for (size_t j = 0; j < M; j++)
        {
            out << matrix.m_arr[i][j] << ' ';
        }
        out << ')' << std::endl;
    }
    return out;
}


template <typename T, unsigned char N, unsigned char M>
std::istream& operator >> (std::istream& in, Matrix<T, N, M>& matrix)
{
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < M; j++)
        {
            in >> matrix.m_arr[i][j];
        }
    }
    return in;
}




int main()
{
    try {

        Matrix<int, 3, 3> a;

        std::cin >> a;
        std::cout << a;
        std::cout << "Determinant: " << a.determinant() << std::endl;
        std::cout << ++a << std::endl;

        Matrix<int, 3, 3> b = a;

        Matrix<int, 3, 3> c;

        c = b = a;
        std::cout << "Element: " << c.at(1, 1);
        //std::cout << c << std::endl;
        //setElement(c, 1, 1, 10);
        //std::cout << c << std::endl;
    }
    catch (...) {
        std::cout << "Determinant doesn't exist!";
    }
}