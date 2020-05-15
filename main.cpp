#include "Stack.h"
#include "Queue.h"
#include "ShuntingYard.h"
using namespace std;
int main()
{
    std::string kek = "2 + 3 * 3 - 4 ";
    ShuntingYard* yard = new ShuntingYard(kek);
    yard->tokenization();
    yard->parse();
    cout << yard->calculate();
}
