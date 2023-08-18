/*
 * File: main.cpp
 * --------------
 * Blank C++ project configured to use Stanford cslib and Qt
 */

#include "console.h"
#include "simpio.h"
#include "testing/SimpleTest.h"
#include "vector.h"
#include "queue.h"
using namespace std;

int fewestCoinsFor(Vector<int> coins, int target) {
    //Inspired by the "I can’t believe that I can prove that it can sort" algorithm although more efficient sorting algorithms are possible
    for(int i=coins.size()-1; i>-1; i--){
        for(int j=coins.size()-1; j>-1; j--){
            if(coins.get(i)<coins.get(j)){
                int temp=coins.get(i);
                coins.set(i, coins.get(j));
                coins.set(j, temp);
            }
        }
    }
    if(target<coins.get(0)){
        return -1;
    }
    Vector<int>store;
    store.add(0);
    for(int i=1; i<=target;i++){
        store.add(INT_MAX);
    }
    for(int i = 1; i<=target ; i++){
        for(int j=0; j<coins.size();j++){
            if(coins.get(j)<= i){
                int temp = store.get(i-coins.get(j));
                if(((temp+1)<store.get(i))&&temp!=INT_MAX){
                    store.set(i,temp+1);
                }
            }
        }
    }
    if(INT_MAX ==store.get(target)){
        cout<<"No combination of coins can make the given value"<<endl;
        return -1;
    }
    Queue<int> num;
    for(int i=0; i<coins.size();i++){
        while( target>=coins.get(i)){
            target-= coins.get(i);
            num.enqueue(coins.get(i));
        }
    }
    int size= num.size();
    cout<<"To make the given value, the following coins are necessary:"<<endl;
    for(int i=0; i<size; i++){
        cout<<"one "<<num.dequeue()<<" cent coin."<<endl;
    }
    return size;
}

int main(){
    /*
    if (runSimpleTests(SELECTED_TESTS)) {
        return 0;
    }
*/
    Vector<int> coins={ 9, 6, 5, 1};
    int target=13;
    int result=fewestCoinsFor(coins,target);
    cout <<"The minimum number of coins necessary to make the targeted value is: "<< result << endl;
    return 0;
}

PROVIDED_TEST("Simple Test") {
    Vector<int> coins={1, 10, 25};
    int target=27;
    EXPECT_EQUAL(fewestCoinsFor(coins, target), 3);
}
PROVIDED_TEST("Imossible Test (Inspired by numberFile)") {
    Vector<int> coins={6, 9, 20};
    int target=43;
    EXPECT_EQUAL(fewestCoinsFor(coins, target), -1);
}
