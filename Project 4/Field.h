
#ifndef Field_h
#define Field_h
using namespace std;

class Field {
public:

    // copy vector into field_array
    Field(const vector<vector<int>> & rhs){
        
        field_array = rhs;
        weight_array = rhs;
        
        
        y_range = (int) field_array.size();
        x_range = (int) field_array[0].size();
        
        
        // assign weights based on bottom right corner
        
        // pre-process the matrix for weight functionality
        
        for (int i = 1; i < x_range;i++){
            weight_array[0][i] = field_array[0][i] + weight_array[0][i - 1];
        }
        for (int j = 1; j < y_range;j++){
            weight_array[j][0] = field_array[j][0] + weight_array[j-1][0];
        }
        
        for (int x = 1; x < y_range; x++){
            for(int y = 1; y < x_range; y++){
            weight_array[x][y] = field_array[x][y] + weight_array[x - 1][y] + weight_array[x][y - 1] - weight_array[x - 1][y - 1];
     
            }
           // cout << endl;
        }
        
        /*
        // COMPILER OUTPUT FOR DEV
        cout << "x_range: "<< x_range << endl;
        cout << "y_range: "<<y_range << endl;
     
        cout << "ARRAY" << endl;
        cout << "----------------"<< endl;
        for (int x = 0; x < y_range; x++){
            for(int y = 0; y < x_range; y++){
            cout << field_array[x][y] << " ";
            }
           cout << endl;
        }
        
        cout << "WEIGHT ARRAY" << endl;
               cout << "----------------"<< endl;
               for (int x = 0; x < y_range; x++){
                   for(int y = 0; y < x_range; y++){
                       cout << weight_array[x][y] << " ";
                   }
                   cout << endl;
               }
        
        */
    };
    
    // move vector into field_array
    Field(vector<vector<int>> && rhs){
        
        field_array = rhs;
        weight_array = rhs;
        
        
        y_range = (int) field_array.size();
        x_range = (int) field_array[0].size();
        
        
        // assign weights based on bottom right corner
        
        // pre-process the matrix for weight functionality
        
        for (int i = 1; i < x_range;i++){
            weight_array[0][i] = field_array[0][i] + weight_array[0][i - 1];
        }
        
        for (int j = 1; j < y_range;j++){
            weight_array[j][0] = field_array[j][0] + weight_array[j-1][0];
        }
        
        for (int x = 1; x < y_range; x++){
            for(int y = 1; y < x_range; y++){
                weight_array[x][y] =  field_array[x][y] +
                                                    weight_array[x][y - 1] -
                                                    weight_array[x - 1][y - 1] +
                                                    weight_array[x - 1][y];
     
            }
           // cout << endl;
        }
        
        
        // COMPILER OUTPUT FOR DEV
        /*
        cout << "x_range: "<< x_range << endl;
        cout << "y_range: "<<y_range << endl;
       
        cout << "ARRAY" << endl;
        cout << "----------------"<< endl;
        for (int x = 0; x < y_range; x++){
            for(int y = 0; y < x_range; y++){
                cout << field_array[x][y] << " ";
            }
            cout << endl;
        }
        
        cout << "WEIGHT ARRAY" << endl;
               cout << "----------------"<< endl;
               for (int x = 0; x < y_range; x++){
                   for(int y = 0; y < x_range; y++){
                       cout << weight_array[x][y] << " ";
                   }
                   cout << endl;
               }
         */
        
        
    };
    
    int Weight(int x1, int y1, int x2, int y2){
        // if coordinates out of range, throw exception
        
        if (x1 >= x_range || x2 >= x_range || y1 >= y_range || y2 >= y_range || x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0  ){
            
            // throw exception
            throw out_of_range ("OUT OF RANGE");
            
        }
        
        else{
            
            
            int rc_x,rc_y,lc_x,lc_y;
            
            // establish bottom right and top left corner
            if (x2 > x1){
                rc_x = x2;
                lc_x = x1;
            }
            else{
                rc_x = x1;
                lc_x = x2;
            }
            
            if (y2 > y1){
                rc_y = y2;
                lc_y = y1;
            }
            else{
                rc_y = y1;
                lc_y = y2;
            }
   
            //cout << lc_x << " " << lc_y << endl;
             //cout << rc_x << " " << rc_y << endl;
                
           // use the right lower corner and upper left corner to find area
            int total =  0;
            
            if (lc_y - 1 >= 0){
                if(lc_x - 1 >= 0){
                   total += weight_array[lc_y - 1][lc_x - 1];
                }
            }
            
            if (lc_x - 1 >= 0){
                   total -= weight_array[rc_y][lc_x - 1];
            }
            
            if (lc_y - 1 >= 0){
                   total -= weight_array[lc_y - 1][rc_x];
            }
            
            
            
            total += weight_array[rc_y][rc_x];
            return total;
        }
      
        
    };
    
    
    
    int PathCost() {
        
        if(x_range == 0){
            return 0;
        }
        
        for(int x=1;x <y_range; x++) {
            field_array[x][0]+=field_array[x-1][0];
        }
        
        for(int y=1;y<x_range;y++) {
            field_array[0][y]+=field_array[0][y-1];
        }
        
        for(int x=1;x<y_range;x++) {
            for(int y=1;y<x_range;y++) {
                if (field_array[x][y-1] < field_array[x-1][y] ){
                    field_array[x][y]+=field_array[x][y-1];
                }
                else{
                    field_array[x][y]+= field_array[x-1][y];
                }
            }
        }
        return field_array[y_range-1][x_range-1];
    }
    
    
    

    
private:
    
    vector <vector<int>> field_array;
    vector<vector<int>> weight_array;
    int x_range;
    int y_range;
    
    
    
    
};


#endif /* Field_h */
