#include <iostream>
#include <vector>
#include<string>

using namespace std;

        struct Number
{
    int horizontal_index = 0;
    int vertical_index = 0;
    int data = 0;    
};

class Matrix {

public:

    int horizontal_size_;
    int vertical_size_;
    
    void Add_Matrix_Data (int horisontal_index, int vertical_index, int data) {
        matrix_data_.push_back({horisontal_index, vertical_index, data});
    }
    
    vector <Number> GetIndexVector () {
        vector <Number> result;
       result = matrix_data_;      
    return result;
    }
    
    void PushIndexVector(const vector <Number>& index_vector)  {
        matrix_data_ = index_vector;
    }
    
    void PrintMatrix () {
        int count=0;
        vector <int> data_vector = IndexVectorToDataVector();
        for (int i=0; i < vertical_size_; i++) {
            for (int j = 0; j < horizontal_size_; j++) {
                cout << data_vector[count] << " "s;
                count++;
            }
            cout << endl;
        }
    }
    
  vector <Number> Sum (const vector <Number>& index_vector_a, const vector <Number>& index_vector_b) {
    vector <Number> result;
    for (const auto& x : index_vector_a) {
        for (const auto& y : index_vector_b) {
            if (!IsAddingNumbersPossible(x,y)) {continue;}
            else {
        Number result_number = NumberPlusNumber (x, y);
        result.push_back(result_number);
    }
        }
    }
      return result;
  }
    
    int GetNumberData (int x, int y, const vector <Number>& index_vector) {
        int result = 0;
        for (const auto& number : index_vector) {
            if (number.horizontal_index == x && number.vertical_index == y) {
                result = number.data;
            }
        }
        
        return result;    
    }

private:


    
 vector <Number> matrix_data_;
 
  bool IsAddingNumbersPossible (const Number& a, const Number& b) {
     return (a.horizontal_index == b.horizontal_index && a.vertical_index == b.vertical_index);
 }   
 
  bool IsMultiplicationNumbersPossible (const Number& a, const Number& b) {
     return (a.vertical_index == b.horizontal_index);
 } 
    
 Number NumberPlusNumber (const Number& a, const Number& b) {
     Number c;
     if(IsAddingNumbersPossible(a,b)) {
         c.horizontal_index = a.horizontal_index;
         c.vertical_index = a.vertical_index;
         c.data = a.data + b.data;
     }
 return c;
 }
  
  Number NumberMulltiplyNumber (const Number& a, const Number& b) {
     Number c;
     if(IsAddingNumbersPossible(a,b)) {
         c.horizontal_index = a.horizontal_index;
         c.vertical_index = b.vertical_index;
         c.data = a.data * b.data;
     }
 return c;
 }   

    
 vector <int> IndexVectorToDataVector () {
        vector <int> result;
     for (const auto& x : matrix_data_) {
         result.push_back(x.data);
     }
     return result;
    }
    


};

Matrix CreateMatrix() {
        Matrix result;
        cout << "Enter horizontal_size"s << endl;
        cin >> result.horizontal_size_;       
        cout << "Enter vertical_size"s << endl;
        cin >> result.vertical_size_;
        for (int i=0; i < result.vertical_size_; i++) {
            for (int j=0; j<result.horizontal_size_; j++) {
             int data;
             cout << "Enter number"s << endl;  
             cin >> data;  
             result.Add_Matrix_Data(j, i, data);
            }
        }
    return result;
     }

Matrix SumMatrix (Matrix a, Matrix b) {
    Matrix result;
    result.horizontal_size_ = a.horizontal_size_;
    result.vertical_size_ = a.vertical_size_;
    result.PushIndexVector(result.Sum(a.GetIndexVector(), b.GetIndexVector()));
    return result;
    
}

Matrix MultiplyMatrix (Matrix a, Matrix b){
    Matrix result;
    result.horizontal_size_ = b.horizontal_size_;
    result.vertical_size_ = a.vertical_size_;
    vector <Number> result_vector;
     for (int i=0; i < result.vertical_size_; i++) {
            for (int j=0; j<result.horizontal_size_; j++) {              
              Number c;
              c.horizontal_index = j;
              c.vertical_index = i;  
                for (int m =0; m < b.vertical_size_; m++) {
                  c.data += a.GetNumberData (m, i, a.GetIndexVector()) * b.GetNumberData(j, m, (b.GetIndexVector()));    
                }
                                            
              result_vector.push_back(c);      
            }
     }
 result.PushIndexVector(result_vector);
    return result;
}





int main() { 
    cout << "Enter Matrix 1"s <<endl;
    Matrix a = CreateMatrix();
    cout << "Enter Matrix 2"s <<endl;
    Matrix b = CreateMatrix(); 
    cout << "choose operation + or *"s <<endl;
    string word;
    cin >> word;
    if (word == "+"s) {
        if (a.horizontal_size_ == b.horizontal_size_ && a.vertical_size_ == b.vertical_size_) {
            a.PrintMatrix();
            cout << "+"s << endl;
            b.PrintMatrix();
            cout << "="s << endl;
            SumMatrix(a,b).PrintMatrix();
        }
        else {
            cout << "These Matrixes cannot be summed"s <<endl;
        }
    }
    if (word == "*"s) {
        if (a.horizontal_size_ == b.vertical_size_) {
            a.PrintMatrix();
            cout << "*"s << endl;
            b.PrintMatrix();
            cout << "="s << endl;
            MultiplyMatrix(a,b).PrintMatrix();
        }
         else {
            cout << "These Matrixes cannot be multiplied"s <<endl;
        }
        
    }
    else {
        cout << "Invalid Operation"s <<endl;
    }
    }