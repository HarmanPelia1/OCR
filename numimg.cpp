#include "digitblob.h"
#include "numimg.h"
#include "bmplib.h"
#include <algorithm> // for std::sort
#include <deque>
#include <iomanip>
#include <iostream>

using namespace std;

// TO DO: Complete this function
NumImg::NumImg(const char* bmp_filename)
{
    //  Note: readGSBMP dynamically allocates a 2D array 
    //    (i.e. array of pointers (1 per row/height) where each  
    //    point to an array of unsigned char (uint8_t) pixels)

    // TO DO:
    // call readGSBMP to initialize img_, h_, and w_;
    
    h_ = 0;
    w_ = 0;
    img_ = NULL;
    img_ = readGSBMP(bmp_filename, h_, w_);



    // Leave this check
    if(img_ == NULL) {
        throw std::logic_error("Could not read input file");
    }
    
    // Convert to Black and White using a fixed threshold 
    for(int i =0; i < h_; i++){
        for(int j = 0; j < w_; j++){
            if(img_[i][j] > 150){
                img_[i][j] = 255;
            }
            else {
                img_[i][j] = 0;
            }
        }
    }
    // Perform any other initialization you need
}

// TO DO: Complete this function
NumImg::~NumImg()
{
    // Add code here if necessary
for (int i = 0; i < h_; i++){
    delete [] img_[i];
}
    delete [] img_;
}

// TO DO: Complete this function
size_t NumImg::findAndCreateDigitBlobs()
{
    bool** checked = visits(); //just want an all false 2D bool array
    DigitBlob blob1;//need to create and find the blob
        for(int i = 0; i < h_; i++){
            for(int j = 0; j < w_; j++){
                if(img_[i][j] == 0 && !checked[i][j]){//if black and not checked **LOGIC MISTAKE??**
                  blob1 = createDigitBlob(checked, i, j);
                  blobs_.push_back(blob1);
                }
            }
            sortDigitBlobs();
        }

    for (int i = 0; i < h_; i++) {
      delete [] checked[i];
    }
    delete [] checked; 
    return numDigitBlobs();
}

// Complete - Do not alter
std::string NumImg::classify(bool withDebug)
{
    std::string res;
    for(size_t i = 0; i < blobs_.size(); i++){
        blobs_[i].classify();
        if(withDebug){
            blobs_[i].printClassificationResults();
        }
        char c = blobs_[i].getClassification();
        res += c;
    }
    return res;
}

// Complete - Do not alter
void NumImg::printBoundingBoxes() const
{
    cout << setw(2) << "i" << setw(6) << "ULRow" << setw(6) << "ULCol" << setw(4) << "Ht." << setw(4) << "Wi." << endl;
    for(size_t i = 0; i < blobs_.size(); i++){
        const DigitBlob& b = blobs_[i];
        cout << setw(2) << i << setw(6) << b.getUpperLeft().row << setw(6) << b.getUpperLeft().col 
        << setw(4) << b.getHeight() << setw(4) << b.getWidth()  << endl;
        // cout << "Blob " << i << " ul=(" << b.getUpperLeft().row << "," << b.getUpperLeft().col 
        //     << ") h=" << b.getHeight() << " w=" << b.getWidth() << endl;
    }

}

// Complete - Do not alter
const DigitBlob& NumImg::getDigitBlob(size_t i) const
{
    if(i >= blobs_.size()){
        throw std::out_of_range("Index to getDigitBlob is out of range");
    }
    return blobs_[i];
}

// Complete - Do not alter
size_t NumImg::numDigitBlobs() const
{
    return blobs_.size();
}

// Complete - Do not alter
void NumImg::sortDigitBlobs()
{
    std::sort(blobs_.begin(), blobs_.end());
}

// Complete - Do not alter
void NumImg::drawBoundingBoxesAndSave(const char* filename)
{
    for(size_t i=0; i < blobs_.size(); i++){
        Location ul = blobs_[i].getUpperLeft();
        int h = blobs_[i].getHeight();
        int w = blobs_[i].getWidth();
        for(int i = ul.row-1; i < ul.row + h + 1; i++){
            img_[i][ul.col-1] = 128;
            img_[i][ul.col+w] = 128;
        }
        for(int j = ul.col-1; j < ul.col + w + 1; j++){
            img_[ul.row-1][j] = 128;
            img_[ul.row+h][j] = 128;
        }
    }
    writeGSBMP(filename, img_, h_, w_);
}

// TO DO:
// Add other (helper) function definitions here
bool** NumImg::visits() const{ 
    bool** visit = new bool*[h_];
for(int i = 0; i < h_; i++){
    visit[i] = new bool[w_];
}

for(int i = 0; i < h_; i++){
    for(int j = 0; j < w_; j++){
        visit[i][j] = false;
    }
}

    return visit;
}



DigitBlob NumImg::createDigitBlob(bool** explored, int pr, int pc)//go to tutor
{
    // Arrays to help produce neighbors easily in a loop
    // by encoding the **change** to the current location.
    // Goes in order N, NW, W, SW, S, SE, E, NE
    int neighbor_row[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int neighbor_col[8] = {0, -1, -1, -1, 0, 1, 1, 1};

    // Add your code here
vector<Location> loc_list;

loc_list.push_back(Location(pr, pc));
explored[pr][pc] = true;

Location top_left = Location(pr, pc);
Location bottom_right = Location(pr, pc);

Location current;
for(int i = 0; i < loc_list.size(); i++){
  current = loc_list[i];

for(int i = 0; i < 8; i++){
    BFS(neighbor_row[i], neighbor_col[i], current, top_left, bottom_right, loc_list, explored);
    }
}
  int blob_height = bottom_right.row - top_left.row + 1; 
  int blob_width = bottom_right.col - top_left.col + 1;

  return DigitBlob(img_, top_left, blob_height, blob_width);
}



void NumImg::BFS(int neighbor_r, int neighbor_c, Location& current, 
Location& top_left, Location& bottom_right,
vector<Location>& loc_list, bool** visit)
{
    int next_r = current.row + neighbor_r;
    int next_c = current.col + neighbor_c;

    if( (next_r >= 0) && (next_r < h_) && (next_c >= 0) && (next_c < w_) &&
    (img_[next_r][next_c] == 0) && (!visit[next_r][next_c]) ){

        loc_list.push_back(Location(next_r, next_c));//putting to be checked
        
        visit[next_r][next_c] = true;//making it checked

        if(top_left.row > next_r){
            top_left.row = next_r;
        }
        if(top_left.col > next_c){
            top_left.col = next_c;/////////////looking through them all
        }
        if(bottom_right.row < next_r){
            bottom_right.row = next_r;
        }        
        if(bottom_right.col < next_c){
            bottom_right.col = next_c;
        }
    }
}
