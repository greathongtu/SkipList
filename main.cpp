#include "SkipList.h"

using namespace std;

int main() {

    SkipList<int,string> skipList;
    skipList.insert( 12,"fdf");
    skipList.insert(3, "etdf");
    skipList.insert(7, "dfsf");
    skipList.insert(8, "324sdf");
    skipList.insert(9, "we");
    skipList.insert(19, "e5yfdg");
    skipList.insert(19, "qwed");


    skipList.search(3);
    skipList.remove(3);
    skipList.remove(3);
    skipList.display_list();
}
