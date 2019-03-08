#include<iostream>
#include<string.h>
#include<conio.h>
using namespace std;
class HugeInteger
{
private:
    char* data;
    int size;
public:
    HugeInteger()
    {
        data=NULL;
        size=0;
    }
    HugeInteger(int x)
    {
        size=x;
        data=new char[x+1];
        data[x]='\0';
    }
    ~HugeInteger()
    {
        delete[] data;
        data=NULL;
        size=0;
    }
    HugeInteger(const HugeInteger &j)
    {
        data=new char[j.size+1];
        for(int a=0; a<j.size; a++)
        {
            data[a]=j.data[a];
        }
        data[j.size] = '\0';
        size=j.size;
    }
    friend istream &operator >> (istream &inp,HugeInteger &z)
	{
        char* tmp;
        int nsize=0;
        tmp=new char[z.size+1];
        inp.getline(z.data,z.size+1);
        strcpy_s(tmp,z.size+1,z.data);
        delete[] z.data;
        z.data=NULL;
        int check=0;
        for (int c = 0; tmp[c] != '\0'; c++)
        {
            if (tmp[c] != '0')
            {
                check = 0;
                break;
            }
            else
                check = 1;
        }
        if (check == 1)
        {
            z.data = new char [2];
            z.data[0] = '0';
            z.data[1] = '\0';
            z.size = 1;
            return inp;
        }
        for(int a=0; ; a++)
        {
            if(tmp[a]!='0')
            {
                for(int x=0; tmp[a]!='\0'; x++,a++)
                {
                    nsize++;
                }
            }
			if (tmp[a] == '\0')
				break;
        }
        z.data=new char[nsize+1];
        for(int a=0; ; a++)
        {
            if(tmp[a]!='0')
            {
                for(int x=0; tmp[a]!='\0'; x++,a++)
                {
                    z.data[x]=tmp[a];
                }
				break;
            }

        }
        z.data[nsize] = '\0';
        delete[] tmp;
        z.size = nsize;
        return inp;
    }
    friend ostream &operator << (ostream &out,HugeInteger &z)
    {
        out<<z.data;
        return out;
    }
    HugeInteger operator = (HugeInteger &x)
    {
        size = x.size;
        data = new char[size+1];
        for (int a = 0; a < size; a++)
        {
            data[a] = x.data[a];
        }
        data[size] = '\0';
        return x;
    }
    int* convertToNum(HugeInteger &x)
    {
        int* arr;
        arr = new int[x.size];
        for (int a = 0; x.data[a]!='\0'; a++)
        {
            switch (x.data[a])
            {
            case'0':
                arr[a] = 0;
                break;
            case'1':
                arr[a] = 1;
                break;
            case'2':
                arr[a] = 2;
                break;
            case'3':
                arr[a] = 3;
                break;
            case'4':
                arr[a] = 4;
                break;
            case'5':
                arr[a] = 5;
                break;
            case'6':
                arr[a] = 6;
                break;
            case'7':
                arr[a] = 7;
                break;
            case'8':
                arr[a] = 8;
                break;
            case'9':
                arr[a] = 9;
                break;
            }
        }
        return arr;
    }
    HugeInteger convertToChar(int carry, int* arr, int size)
    {
        HugeInteger m;
        int a = 0, count;
        if (carry == 0)
        {
            count = size + 1;
            m.data = new char[count];
        }
        else if (carry < 10 && carry > 0)
        {
            count = size + 2;
            m.data = new char[count];
            switch (carry)
            {
            case 1:
                m.data[a] = '1';
                break;
            case 2:
                m.data[a] = '2';
                break;
            case 3:
                m.data[a] = '3';
                break;
            case 4:
                m.data[a] = '4';
                break;
            case 5:
                m.data[a] = '5';
                break;
            case 6:
                m.data[a] = '6';
                break;
            case 7:
                m.data[a] = '7';
                break;
            case 8:
                m.data[a] = '8';
                break;
            case 9:
                m.data[a] = '9';
                break;
            case 0:
                m.data[a] = '0';
                break;
            }
            a++;
        }
        else if (carry == 11)
        {
            count = size + 2;
            m.data = new char[count];
            m.data[a] = '-';
            a++;
        }
        for (int x=0; a < count; a++,x++)
        {
            switch (arr[x])
            {
            case 1:
                m.data[a] = '1';
                break;
            case 2:
                m.data[a] = '2';
                break;
            case 3:
                m.data[a] = '3';
                break;
            case 4:
                m.data[a] = '4';
                break;
            case 5:
                m.data[a] = '5';
                break;
            case 6:
                m.data[a] = '6';
                break;
            case 7:
                m.data[a] = '7';
                break;
            case 8:
                m.data[a] = '8';
                break;
            case 9:
                m.data[a] = '9';
                break;
            case 0:
                m.data[a] = '0';
                break;
            }
        }
        m.data[count-1] = '\0';
        m.size = count-1;
        delete[] arr;
        return m;
    }
    HugeInteger operator + (HugeInteger &x)
    {
        //HugeInteger res;
        int* arr1;
        int* arr2;
        int A, B;
        if (size > x.size)
        {
            A = size;
            B = x.size;
            arr1 = convertToNum(*this);
            arr2 = convertToNum(x);
        }
        else
        {
            A = x.size;
            B = size;
            arr1 = convertToNum(x);
            arr2 = convertToNum(*this);
        }
        int carry = 0,tmp;
        int b = B - 1;
        int* sum = new int[A];
        for (int a = A - 1; a >= 0; a--)
        {
            for (; b >= 0; b--, a--)
            {
                tmp = arr1[a] + arr2[b] + carry;
                if (tmp > 9)
                {
                    carry = 1;
                    sum[a] = tmp - 10;
                }
                else
                {
                    carry = 0;
                    sum[a] = tmp;
                }
            }
            if (a >= 0)
            {
                tmp = arr1[a] + carry;
                if (tmp > 9)
                {
                    carry = 1;
                    sum[a] = tmp - 10;
                }
                else
                {
                    carry = 0;
                    sum[a] = tmp;
                }
            }
        }
        //for (int y = 0; y < A; y++)
        //cout << sum[y];
        return convertToChar(carry, sum, A);
    }
    bool operator < (HugeInteger &x)
    {
        if (size < x.size)
            return true;
        else if (size > x.size)
            return false;
        else
        {
            int*a = convertToNum(*this);
            int*b = convertToNum(x);
            for (int i = 0; i < size; i++)
            {
                if (a[i] < b[i])
                {
                    delete[] a;
                    delete[] b;
                    return true;
                }
                if (a[i] > b[i])
                {
                    delete[] a;
                    delete[] b;
                    return false;
                }
            }
        }
        return false;
    }
    bool operator > (HugeInteger &x)
    {
        if (x.data[0] == '-')
            return true;
        else if (data[0] == '-')
            return false;
        else if (size > x.size)
            return true;
        else if (size < x.size)
            return false;
        else
        {
            int*a = convertToNum(*this);
            int*b = convertToNum(x);
            for (int i = 0; i < size; i++)
            {
                if (a[i] > b[i])
                {
                    delete[] a;
                    delete[] b;
                    return true;
                }
                if (a[i] < b[i])
                {
                    delete[] a;
                    delete[] b;
                    return false;
                }
            }
            delete[] a;
            delete[] b;
        }
        return false;
    }
    bool operator != (HugeInteger &x)
    {
        if (size != x.size)
            return true;
        else
        {
            for (int a = 0; a < size; a++)
            {
                if (data[a] != x.data[a])
                    return true;
            }
            return false;
        }
    }
    bool operator == (HugeInteger &x)
    {
        if (size != x.size)
            return false;
        else
        {
            for (int a = 0; a < size; a++)
            {
                if (data[a] != x.data[a])
                    return false;
            }
            return true;
        }
    }
    bool operator <= (HugeInteger &x)
    {
        if (*this < x || *this == x)
            return true;
        else
            return false;
    }
    bool operator >= (HugeInteger &x)
    {
        if (*this > x || *this == x)
            return true;
        else
            return false;
    }
    HugeInteger operator - (HugeInteger &x)
    {
        int* arr1;
        int* arr2;
        int* eq = new int[1];
        eq[0] = 0;
        int A, B, minus, carry = 0;
        if (*this == x)
            return convertToChar(0, eq, 1);
        if (*this > x)
        {
            arr1 = convertToNum(*this);
            arr2 = convertToNum(x);
            A = size - 1;
            B = x.size - 1;
            minus = 0;
        }
        else
        {
            arr1 = convertToNum(x);
            arr2 = convertToNum(*this);
            A = x.size - 1;
            B = size - 1;
            minus = 11;
        }
        delete[] eq;
        int* d = new int[A + 1];
        //diff[0] = -1;
        int b = B, tmp,tmp2;
        for (int a = A; a >= 0; a--)
        {
            for (; b >= 0; b--, a--)
            {
                tmp = arr1[a] - carry;
                if (tmp >= arr2[b])
                {
                    //diff[c + 1] = diff[c];
                    d[a] = tmp - arr2[b];
                    //cout << d[a];
                    carry = 0;
                }
                else
                {
                    tmp = tmp + 10;
                    //diff[c + 1] = diff[c];
                    d[a] = tmp - arr2[b];
                    //if (d[a] < 0)
                    //_getch();
                    carry = 1;
                }
            }
            if (a >= 0)
            {
                tmp2 = arr1[a] - carry;
                if (tmp2 < 0)
                {
                    tmp2 = tmp2 + 10;
                    carry = 1;
                }
                else
                    carry = 0;
                d[a] = tmp2;
                //carry = 0;
            }
        }
        int count = 0;
        for (int z = 0; z <= A; z++)
        {
            if (d[z] != 0)
            {
                for (; z <= A; z++)
                    count++;
            }
        }
        int* res = new int[count];
        int r = 0;
        for (int z = 0; z <= A; z++)
        {
            if (d[z] != 0)
            {
                for (; z <= A; z++)
                {
                    res[r] = d[z];
                    //cout << res[r];
                    r++;
                }
            }
        }

        delete[] d;
        //for (int a = 0;a<4; a++)
        //cout << diff[a];
        return convertToChar(minus, res, count);
        //return result;
    }
    HugeInteger operator * (HugeInteger& x)
    {
        HugeInteger prod(1);
        prod.data[0] = '0';
        if (*this == prod || x == prod)
            return prod;
        int foo, carry = 0, num;
        int* arr1;
        int* arr2;
        int A, B;
        if (size > x.size)
        {
            A = size;
            B = x.size;
            arr1 = convertToNum(*this);
            arr2 = convertToNum(x);
        }
        else
        {
            A = x.size;
            B = size;
            arr1 = convertToNum(x);
            arr2 = convertToNum(*this);
        }
        int nsize, n = 0;
        int** mul = new int*[B];
        for (int b = B - 1; b >= 0; b--)
        {
            nsize = A + n;
            mul[b] = new int[nsize];
            int e = nsize - 1;
            for ( int a = 0; a < n; a++, e--)
            {
                mul[b][e] = 0;
            }
            n++;
            for (int a = e; a >= 0; a--)
            {
                //mul[b] = new int[A];
                foo = arr1[a] * arr2[b];
                num = foo + carry;
                if (num > 9)
                {
                    carry = num / 10;
                    num = num % 10;
                }
                else
                    carry = 0;
                mul[b][a] = num;
            }
            prod = convertToChar(carry, mul[b], nsize) + prod;
            carry = 0;
        }
        return prod;
    }
    HugeInteger operator / (HugeInteger &x)
    {
        HugeInteger div(size);
        int u = 0;
        HugeInteger check(1);
        check.data[0] = '0';
        HugeInteger p;
        HugeInteger dif;
        HugeInteger tmp(1);
        tmp.data[0] = '0';
        HugeInteger inc(1);
        inc.data[0] = '1';
        HugeInteger foo(x.size + 1);
        int c = 0, a = 0;
        for (; c < size;)
        {
            for (; a < x.size + 1; a++, c++)
            {
                foo.data[a] = data[c];
            }
            for (int v = 0; foo.data[v] != '\0'; v++)
            {
                foo.size = v + 1;
            }
            HugeInteger f(foo.size);
            int check2;
            for (int m = 0; m < foo.size; m++)
            {
                if (foo.data[m] != '0')
                {
                    check2 = 0;
                    int a = 0;
                    for (int s = m; s < foo.size; s++,a++)
                    {
                        f.data[a] = foo.data[s];
                    }
                    f.data[a] = '\0';
                    f.size = a;
                    break;
                }
                else
                    check2 = 1;
            }
            if (check2 == 1)
            {
                f.data[0] = '0';
                f.data[1] = '\0';
                f.size = 1;
            }
            a = 0;
            for (tmp = check;; tmp = tmp + inc)
            {
                p = x*tmp;
                if (p == f || p > f - x)
                {
                    for (int i = 0; i < tmp.size; i++)
                    {
                        div.data[u] = tmp.data[i];
                        u++;
                    }
                    dif = f - p;
                    //if (dif != check) {
                    for (int r = 0; r < dif.size; r++)
                    {
                        foo.data[r] = dif.data[r];
                        a = r + 1;
                        //}
                    }
                    break;
                }
            }
        }
        div.data[u] = '\0';
        div.size = u;
        return div;
    }
    HugeInteger sqrt()
    {
        HugeInteger compare(1);
        compare.data[0] = '1';
        compare.size = 1;
        HugeInteger max = *this;
        HugeInteger min(1);
        min.data[0] = '0';
        HugeInteger two(1);
        two.data[0] = '2';
        HugeInteger tmp;
        for (int i = 0; max-min!=compare; i++)
        {
            tmp = (max + min) / two;
            if (tmp*tmp == *this)
                return tmp;
            else if (tmp*tmp > *this)
                max = tmp;
            else
                min = tmp;
        }
        return min;
    }
};
int main()
{
    HugeInteger h(200);
    cin >> h;
    cout << h<<endl;
    HugeInteger h1(30);
    cin >> h1;
    cout << h1<<endl;

    cout << (h == h1) << "\n";
    cout << (h != h1) << endl;
    cout << (h < h1) << endl;
    cout << (h > h1) << endl;
    cout << (h <= h1) << endl;
    cout << (h >= h1) << endl;

    cout << "Sum of  two huge integers is : ";
    HugeInteger h2 = h1 + h;
    cout << h2<<endl;

    cout << "Difference of  two huge integers is : ";
    h2 = h - h1;
    cout << h2<<endl;

    cout << "Product of  two huge integers is : ";
    h2 = h1 * h;
    cout << h2<<endl;

    cout << "Division of  two huge integers is : ";
    HugeInteger h3 = h / h1;
    cout << h3<<endl;
    cout << "square root: ";
    cout << h.sqrt();
    _getch();
    return 0;
}
