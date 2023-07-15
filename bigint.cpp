// Copy in your bigint.cpp (overwrite this file)
//  and then add the appropriate code
#include <iostream>
#include "bigint.h"

using namespace std;

// Write your implementation below
// convert string to BigInt
BigInt::BigInt(string s, int base){
  new_base = base;

  for (int i = s.size() - 1; i >= 0; i--){
    char c = s[i];
    int num = static_cast<int>(c);
    if (num >= 48 && num <=57 ){
      num = static_cast<int>(c) - '0'; 
  }
  else if (num >= 65 && num <= 90){
      num = 10 + static_cast<int>(c) - 'A';
    }
    numbers.push_back(num);
  }
  
  removeLeadingZeroes();
} 


// get string representation
string BigInt::to_string() const{
  string strNumber = "" ;
    for(int i = numbers.size() -1; i >= 0; i--){
      int num = numbers[i];
      if (num >= 0 && num <= 9){
        strNumber += static_cast<char>(num) + '0';
      }
      else if(num >= 10 && num <= 35){
        strNumber += static_cast<char>(num) - 10 + 'A';
      }
    }

return strNumber;
} 

 // add another BigInt to this one
void BigInt::add(BigInt b){
int row_add;
bool extra = false;

int B_size = b.numbers.size();
int A_size = numbers.size();

int bigsize = A_size;
if(B_size > A_size){
  for(int i = 0; i < B_size - A_size; i++){
    numbers.push_back(0);
    bigsize = B_size;
  }
}

else if(A_size > B_size){
  for(int i= 0; i < A_size - B_size; i++){
    b.numbers.push_back(0);
    bigsize = A_size;
  }
}

for(int i = 0; i < bigsize; i++){
  row_add = numbers[i] + b.numbers[i];
  
    if(extra == true){
      row_add +=1;
    extra = false;
  }
  if(row_add > new_base - 1){
    numbers[i] = row_add - new_base;
    extra = true;
  }
  else{
    numbers[i] = row_add;
  }
}

 if (extra == true){
   numbers.push_back(1);
   extra = false;
 }
}

void BigInt::removeLeadingZeroes(){
  int num_size = numbers.size();
  for(int i = num_size - 1; i > 0; i-- ){
    if(numbers[i] != 0){
      return;
    } 
    numbers.pop_back();
  } 
}

// BigInt BigInt::operator+(const BigInt& rhs) const{
//   return BigInt("hehe");
// }

BigInt BigInt::operator-(const BigInt& rhs) const {

  if (*this < rhs) return rhs.operator-(*this); //recursion to check if it needs to subtract

  vector<int> subtract;
  vector<int> rhs3;
  int sum;
  int carry = 0;

  int rhs_size = rhs.numbers.size();
  int lhs_size = numbers.size();
  int bigsize = 0;
        
        for(int i =0; i< lhs_size; i++){
      subtract.push_back(numbers[i]);
    }
    for(int i= 0; i< rhs_size; i++){
      rhs3.push_back(rhs.numbers[i]);
    }

    if(lhs_size > rhs_size){
      bigsize = lhs_size;
    }
    else{
      bigsize = rhs_size;
    }
    
    if(rhs_size > lhs_size){
  for(int i = 0; i < rhs_size - lhs_size; i++){
    subtract.push_back(0);
    bigsize = rhs_size;
  }
}

else if(lhs_size > rhs_size){
  for(int i= 0; i < lhs_size - rhs_size; i++){
    rhs3.push_back(0);
    bigsize = lhs_size;
  }
}


//fix
int i = 0;

while(i < rhs_size && i < lhs_size){
  sum = subtract[i] - rhs.numbers[i] - carry;

    carry = 0 > sum;
    sum = carry ? new_base + sum : sum; 

  subtract[i] = sum;
  i++;
}

  while (carry == 1 && i < lhs_size) {
    sum = subtract[i] - carry;

    carry = 0 > sum;
    sum = carry ? new_base + sum : sum;
    
    subtract[i] = sum;
    i++;
  }

string finally = "";

    for(int k = bigsize - 1; k >= 0; k--){
      int num = subtract[k];
      if (num >= 0 && num <= 9){
        finally += static_cast<char>(num) + '0';
      }
      else if(num >= 10 && num <= 35){
        finally += static_cast<char>(num) - 10 + 'A';
      }
    }

 return BigInt(finally, new_base);
}

bool BigInt::operator<(const BigInt& rhs) const {
  int sizer = numbers.size();

  if(numbers.size() == rhs.numbers.size() ){

    for(int i = sizer -1; i >= 0; i--){

      if ( numbers[i] != rhs.numbers[i] ){

        return ( numbers[i] < rhs.numbers[i] );
      }
    }
  }

  else{
    return ( numbers.size() < rhs.numbers.size() );
  }
  return false; 
}


BigInt BigInt::operator+(const BigInt& rhs) const {
  vector<int> sum;
  vector<int> rhs2;
  int row_add;
  bool extra = false;

  int rhs_size = rhs.numbers.size();
  int lhs_size = numbers.size();
  int bigsize = 0;
    
    for(int i =0; i< lhs_size; i++){
      sum.push_back(numbers[i]);
    }
    for(int i= 0; i< rhs_size; i++){
      rhs2.push_back(rhs.numbers[i]);
    }

    if(lhs_size > rhs_size){
      bigsize = lhs_size;
    }
    else{
      bigsize = rhs_size;
    }
  
if(rhs_size > lhs_size){
  for(int i = 0; i < rhs_size - lhs_size; i++){
    sum.push_back(0);
    bigsize = rhs_size;
  }
}

else if(lhs_size > rhs_size){
  for(int i= 0; i < lhs_size - rhs_size; i++){
    rhs2.push_back(0);
    bigsize = lhs_size;
  }
}

for(int i = 0; i < bigsize; i++){
  row_add = sum[i] + rhs2[i];
  
    if(extra == true){
      row_add +=1;
    extra = false;
  }
  if(row_add > new_base - 1){
    sum[i] = row_add - new_base;
    extra = true;
  }
  else{
    sum[i] = row_add;
  }
}

 if (extra == true){
   sum.push_back(1);
   extra = false;
 }

string final = "";

    for(int i = bigsize - 1; i >= 0; i--){
      int num = sum[i];
      if (num >= 0 && num <= 9){
        final += static_cast<char>(num) + '0';
      }
      else if(num >= 10 && num <= 35){
        final += static_cast<char>(num) - 10 + 'A';
      }
    }

 return BigInt(final, new_base);
}




// int main() {

//   BigInt n1("90239020932032");
//   BigInt n2("2032039201083103919041");

//   BigInt n3 = n1 + n2;
//   cout << n3.to_string() << endl;

//   n1.add(n2);

//   cout << n1.to_string() << endl;
// }
