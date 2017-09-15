#include <iostream>
#include "DataReceiver.h"
#include "FilterDataReceiver.h"
#include <vector>

using namespace std;
int main()
{
    //UNIT TEST DataReceiver
    FilterDataReceiver ft;
    ft.find_all_devs();
    vector<string> res;
    ft.get_all_devs(res);

    for(auto i:res)
        cout << i << endl;
    printf("hello");

    ft.read_adapter(1);

    ft.check_datalink();

    ft.set_compile();

    ft.set_filter();

    ft.start_listen();


    return 0;
}