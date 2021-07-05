#include <stdio.h>
typedef unsigned int uint;
typedef unsigned int byte;

void abort()
{
    byte zero;
    volatile auto exception = 1/zero;
}
template<class T, size_t SIZE>
class CheckedArray
{
    T space[SIZE];
public:
   T& operator[] (size_t i)
   {
       if(i>=SIZE)
       {
           abort();
       }
       return space[i];
   }
};

template<class T, size_t ROWS, size_t COLS>
class CheckedMatrix
{
    typedef CheckedArray<T, COLS> RowType;
    RowType space[ROWS];
public:
    RowType& operator[] (size_t r)
    {
       if(r>=ROWS)
       {
           abort();
       }
       return space[r];
    } 
};

uint T; //number of testcases
uint& noOfTestCases = T;
constexpr byte digitCount = 9;
constexpr byte fieldsCount = digitCount * digitCount;
CheckedMatrix<byte, digitCount, digitCount> sudoku;

inline bool isFree(byte r, byte c)
{
    return sudoku[r][c] ==0;
}
bool isOkInRow(byte digit, byte row, byte col)
{
    for(byte c=col+1; c<digitCount;c++)
    {
        if(sudoku[row][c] == digit)
        {
            return false;    
        }
    }
    for(byte c=0; c<col; c++)
    {
        if(sudoku[row][c] == digit)
        {
            return false;    
        }
    }
    return true;
}
bool isOkInCol(byte digit, byte row, byte col)
{
    for(byte r=row+1; r<digitCount;r++)
    {
        if(sudoku[r][col] == digit)
        {
            return false;    
        }
    }
    for(byte r=0; r<row; r++)
    {
        if(sudoku[r][col] == digit)
        {
            return false;    
        }
    }
    return true;
}
bool isOkInSquare(byte digit, byte row, byte col)
{
    byte rFrom=3*(row/3);
    byte rTo=rFrom+3;
    byte cFrom=3*(col/3);
    byte cTo=cFrom+3;

   for(byte r=rFrom; r<rTo; r++)
       for(byte c=cFrom; c<cTo; c++)
       {
           if(r==row && c==col)
           {
               continue;
           }
           if(sudoku[r][c]==digit)
           {
               return false;
           }
       }
       return true;
}

bool isOk(byte d, byte r, byte c)
{
    return isOkInRow(d, r, c) && isOkInCol(d, r, c) && isOkInSquare(d, r, c);
}

bool solve()
{
    bool solved = true; 
    for(byte r=0; r<digitCount; r++)
    {
        for(byte c=0; c<digitCount; c++)
        {
            if(isFree(r, c))
            {
                for(byte d=1; d<= digitCount; d++)
                {
                    if(isOk(d, r, c))
                    {
                        sudoku[r][c] = d;
                        if(solve())
                        {
                            return true;
                        }
                        sudoku[r][c] = 0;
                    }
                }
                return false;
            }
        }
    }
    return solved; 
}
int main()
{
//    freopen("in/1.in", "r", stdin);
    scanf("%u", &noOfTestCases);
    for(uint t=1; t<=noOfTestCases; t++)
    {
        for(byte r=0; r<digitCount; r++)
        {
            for(byte c=0; c<digitCount; c++)
            {
                scanf("%u",&(sudoku[r][c]));
            }
        }
        if(!solve())
        {
            printf("Can't solve test: %u\n",t);
        }
        else
        {
            for(byte r=0; r<digitCount; r++)
            {
                printf("%u",sudoku[r][0]);
                for(byte c=1; c<digitCount; c++)
                {
                    printf(" %u",sudoku[r][c]);
                }
                printf("\n");
            }
        }
    }
}