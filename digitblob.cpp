#include "digitblob.h"
#include <iostream>
// Add more includes if necessary
#include <vector>

using namespace std;

// TO DO - Complete this function
bool Location::operator<(const Location& other) const
{
    if(col != other.col){
        return (col < other.col);
    }
    else{
        return (row < other.row);
    }
}

// TO DO - Complete this function
DigitBlob::DigitBlob()
{
    img_ = NULL;
    digit_ = '!'; // dummy value
    bq0_ = bq1_ = bq2_ = bq3_ = bq4_ = bqd_ = 0;
    euler_ = -2;

    // ul_'s Location default constructor already initializes it to -1,-1

    // Initilaize h_ and w_ and any other data members


}

// TO DO - Complete this function
DigitBlob::DigitBlob(uint8_t** img, Location upperleft, int height, int width)
{
    img_ = img;
    digit_ = '!'; // dummy value

    bq0_ = bq1_ = bq2_ = bq3_ = bq4_ = bqd_ = 0;
    euler_ = -2;

    // Initilaize ul_, h_ and w_ and any other data members
    ul_ = upperleft;
    h_ = height;
    w_ = width;

    row = ul_.row;
    col = ul_.col;

    bottom_row = row + height -1;
    bottom_col = col + width -1;

    X_Sym = 0;
    Y_Sym = 0;

    CM_ofX = 0;
    CM_ofY = 0; 
}

// TO DO - Complete this function if necessary
DigitBlob::~DigitBlob()
{
    // Add code if it is necessary
    //I dont think it is necessary since I didn't dynamically allocate anything
    //but I will set the img back to NULL
    
    // img_ = NULL;
    // digit_ = '!';

    // bq0_ = bq1_ = bq2_ = bq3_ = bq4_ = bqd_ = 0;
    // euler_ = -2;  

    // h_ = 0;
    // w_ = 0;       
    // row = 0;
    // col =0;
    // bottom_row = 0;
    // bottom_col = 0;
}

// TO DO - Complete this function
void DigitBlob::classify()
{
    calc_bit_quads();
    calc_euler_number();
    // Call helper functions to calculate features

    calc_centers_of_mass(); 
    calc_symmetry();

    // TO DO: use the results of helper functions to calculate features
    //    We suggest starting with the Euler number but you are free to
    //    change our structure
    if (euler_ == -1){
      digit_ = '8';
    }
    //digit 0
    else if (euler_ == 0){
      if(Y_Sym > .89 ){
        digit_ = '0';
      }
      //digit 6
      else if(X_Sym > .47 && X_Sym < .68 && CM_ofY > .44 && CM_ofY < .51 && CM_ofX > 0.52 && CM_ofX < 0.57){
        digit_ = '6';
      }
      //digit 9
      else if(CM_ofX > .43 && CM_ofX < .48 && CM_ofY < .57 && CM_ofY > .49 && Y_Sym < .7){
        digit_ = '9';
      }
      else{
        digit_ = '4';
      }
    
    
    
    }
    else if(euler_ == 1){

      if(CM_ofX < .39){
        digit_ = '7';
      }

      //
      else if( Y_Sym > .73 && CM_ofY > .44 && CM_ofY < .51){
        digit_ = '1';
      }

      else if( 0.53 < CM_ofX && CM_ofX < 0.56 && X_Sym > 0.5 && X_Sym < 0.65) {
        digit_ = '2';
      }

      else if ( Y_Sym > 0.72) {
        digit_ = '3';
      }
      else {
        digit_ = '5';
      }


    }

        // printClassificationResults(); 


}

// Complete - Do not alter
char DigitBlob::getClassification() const
{
    return digit_;
}

// TO DO - Complete this function
void DigitBlob::printClassificationResults() const
{
    cout << "Digit blob at " << ul_.row << "," << ul_.col << " h=" << h_ << " w=" << w_ << endl;
    cout << "Bit quads: 1, 2, D, 3, 4:";
    cout << " " << bq1_ << " " << bq2_ << " " << bqd_;
    cout << " " << bq3_ << " " << bq4_ << endl;
    cout << "Euler number is " << euler_ << endl;
    // TO DO: Add any other couts to print classification test data

cout << "Center of Mass of x is " << CM_ofX << endl;
cout << "Center of Mass of y is " << CM_ofY << endl;

cout << "vert symmetry of y is " << Y_Sym << endl;
cout << "horizontal symmetry of x is " << X_Sym << endl;

    cout << "****Classified as: " << digit_ << "\n\n" << endl;

}

// Complete - Do not alter
const Location& DigitBlob::getUpperLeft() const
{
    return ul_;
}

// Complete - Do not alter
int DigitBlob::getHeight() const
{
    return h_;
}

// Complete - Do not alter
int DigitBlob::getWidth() const
{
    return w_;
}

// Complete - Do not alter
bool DigitBlob::operator<(const DigitBlob& other)
{
    // Use Location's operator< for DigitBlob operator<
    return ul_ < other.ul_;
}

// Complete - Do not alter
void DigitBlob::calc_euler_number()
{
    euler_ = (bq1_ - bq3_ - 2*bqd_) / 4;
}

// TO DO - Complete this function to set bq1_, bq2_, etc.
void DigitBlob::calc_bit_quads(){
  for (int i = ul_.row-1; i < ul_.row + h_; i++){
    for (int j = ul_.col-1; j < ul_.col + w_; j++ ){
      int total = img_[i][j] + img_[i+1][j+1] + img_[i][j+1] + img_[i+1][j];
    if(total == 0){
      bq4_++;
    }//checking if they are black or something else then making the blobs off of that
    else if(total == 255){
      bq3_++;
    }
    else if(total == 255*2){

      if(( img_[i][j] == 0 && img_[i+1][j+1] == 0) || (img_[i+1][j] == 0 && img_[i][j+1] == 0 )){
        bqd_++;
      }

      else{
        bq2_++;
      }
    }

    else if(total == 255*3){
      bq1_++;
    }

    else if(total == 255*4){
      bq0_++;
    }

    }
  }
}

// Add more private helper function implementations below

void DigitBlob::calc_centers_of_mass(){

   CM_ofX = CM_X();
   CM_ofY = CM_Y();

}

double DigitBlob::CM_X(){ //black pixels in x / total black pixels
  int blkpxlcnt = 0;
  int weightedcnt = 0;
  for (int i = 0; i < h_; i++){
    for (int j = 0; j < w_; j++){
      if (img_[row+i][col+j] == 0){
        weightedcnt += i; //LOGIC CHECKKKKKK
        blkpxlcnt++;
      }
    }
  }
  double centerized = (1.0 * weightedcnt) /blkpxlcnt;
  return centerized/(h_ - 1);
}

double DigitBlob::CM_Y(){ // black pixels in Y / total black pixels
  int blkpxlcnt = 0;
  int weightedcnt = 0;
  for (int i = 0; i < h_; i++){
    for (int j = 0; j < w_; j++){
      if (img_[row+i][col+j] == 0){
        weightedcnt += j; //LOGIC CHECKKKKKK
        blkpxlcnt++;
      }
    }
  }
  double centerized = (weightedcnt * 1.0 )/ blkpxlcnt;
  return centerized/(w_ - 1);
}




void DigitBlob::calc_symmetry(){
  int totaly = 0;
  int totalx = 0;
  double symmery = 0;
  double symmerx = 0;

  // Symm y 
  for(int i = ul_.row; i < ul_.row + (h_/2); i++ ){
    for(int j = ul_.col; j < bottom_col; j++ ){//symmetrical by checking the top half vs the bottom
      totaly++;

      if(img_[i][j] == img_[bottom_row - (i - ul_.row)][j]){
        symmery++;
      }
    }
  }

  Y_Sym = symmery / totaly;

  for(int i = ul_.row; i < ul_.row + h_; i++ ){
    for(int j = ul_.col; j < ul_.col + (w_/2) ; j++ ){//right sidevs left
      totalx++;

      if(img_[i][j] == img_[i][bottom_col - (j - ul_.col)] ){
        symmerx++;
      }
    }
  }
  X_Sym = symmery/totalx;
}
