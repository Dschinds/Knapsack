using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>





class ValueWeight
{

     unsigned int weight_;
     unsigned int value_;
public:
    ValueWeight(unsigned int weight = 0, unsigned int value = 0) :
    weight_(weight),
    value_(value)
    {
    }
    int getWeight(){
        return weight_;
    }
    int getValue(){
        return value_;
    }
    void setWeight(int weight){
        weight_ = weight;
    }
    void setValue(int value){
        value_ = value;
    }
};

unsigned long long knapsackUnlimited(std::vector<ValueWeight>& ValueWeight,
unsigned int weightCapacity)
{
    // calculate the maximum value that we can carry
    vector<long long> myvec(weightCapacity + 1);
    for(int i = 0; i < myvec.size();++i){
        for(int j = 0; j < ValueWeight.size();++j){
            int weight = ValueWeight[j].getWeight();
            int value = ValueWeight[j].getValue();
            if(weight == 0 && value != 0){
                throw range_error("Max value is infinity!");
            }
            if(weight <= i){
                myvec[i] = max(myvec[i],myvec[i - weight] + value);
            }
        }
    }
    
    return myvec[weightCapacity];
}
unsigned long long knapsackLimited(std::vector<ValueWeight>& ValueWeight,
unsigned int weightCapacity){
    vector<vector<long long>> myvec(ValueWeight.size() + 1,vector<long long>(weightCapacity + 1));
    int value = 0,weight = 0; //Initalize but will never be needed
    for(int i = 0; i <= ValueWeight.size(); ++i){
        for(int j = 0; j <= weightCapacity;++j){
            if(i > 0){
            weight =ValueWeight[i - 1].getWeight();
            value = ValueWeight[i - 1].getValue();
            }
            if(i == 0 || j == 0){
                myvec[i][j] = 0;
            }
            else if (weight <= j){
                myvec[i][j] = max(value + myvec[i - 1][j - weight], myvec[i - 1][j]);
            }
            else {
                myvec[i][j] = myvec[i - 1][j];
            }
        }
    }
    
    
    return myvec[ValueWeight.size()][weightCapacity];
}
void formatComparasion(std::vector<ValueWeight>& ValueWeight,

unsigned int weightCapacity){
    cout << "When we have a knapsack with unlimited items the total value will be " <<
    knapsackUnlimited(ValueWeight, weightCapacity) << endl <<
    "When we have a knapsack with one of each item we get a total value of " << knapsackLimited(ValueWeight, weightCapacity) << endl;
    
}


int main()
{
    vector<ValueWeight> vec;
    cout << "Enter Weights and Values and Weights When Promted when done enter -1 in Weight field" << endl;
    int value = 0;
     int weight = 0;
    unsigned int weightCapacity = 0;
    while(true){
        cout << "Input a weight" << endl;
        cin >> weight;
        if(weight < 0){
            break;
        }
        cout << "Input a value" << endl;
        cin >> value;
        ValueWeight vw(weight,value);
        vec.push_back(vw);
    }
    cout << "Enter the weight capacity for the function that is > 0" << endl ;
    cin >> weightCapacity;
    if(weightCapacity < 0){
        throw "Less then 0 weightCapacity";
    }
    formatComparasion(vec, weightCapacity);
    return 0;
    
}
