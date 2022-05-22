#include "SkipList.h"

using namespace std;

int main() {

    SkipList<string,int> skipList;
    int length =1000;
    for(int i=1;i<length;i++){
        skipList.insert( to_string(i+3),i);
    }
    skipList.remove("11");
    skipList.display_list();
}
