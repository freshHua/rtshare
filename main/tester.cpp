#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class cs
{
    public:
        cs(int i): i_(i)  { cout << "cs(" << i <<") constructor!" << endl; }
        ~cs() { cout << "cs destructor,i(" << i_ << ")" << endl; }

        cs& operator=(const cs& other)
        {
            i_ = other.i_;
            cout << "cs operator=()" << endl;
            return *this;
        }

        int get_i() const { return i_; }
        void change(int i)  { i_ = i; }

    private:
        int i_;
};

cs get_cs()
{
    static int i = 0;
    return cs(i++);
}

int main()
{

    vector<int> myvec{ 3, 2, 5, 7, 3, 2 };
    vector<int> lbvec(myvec);

    sort(lbvec.begin(), lbvec.end(), [](int a, int b) ->  bool { return a < b; });   // Lambda表达式
    cout << "lambda expression:" << endl;
    for (auto it : lbvec)
        cout << it << ' ';

    return 0;
}
