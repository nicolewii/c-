// Program:  hw1.cpp
// Purpose:  To compute morphological image processing for the specified command from the user.
#include <iostream> // input output stream
#include <fstream> // file stream
#include <string> //string header file
#include <vector> //vector header file
using namespace std; //creates proper scope

//replace function takes in the vector of strings, character of the old char to replace with new char
void replacestr(std::vector<string>& vect, char old, char rep){ 
    for(unsigned long i = 0; i<vect.size();i++){  // iterates through the vector
        for(unsigned long j = 0;j < vect[i].size(); j++){ //interates through the strings in the vector
            if (vect[i][j] == old){ //if the character is equal to the old character
                vect[i][j] = rep; //replaces the old character with the new character
            }
        } 

    }
}
//dilation function that takes in the vector of strings and dilation character
void dilation(std::vector<string>& vect, char dil){
    std::vector<string> newv; //creates a new vector of strings
    newv = vect; //makes the current vector the new vector
    for(unsigned long i = 0; i<vect.size();i++){  //iterates through the vector
        for(unsigned long j = 0;j < vect[i].size(); j++){ //iterates through the strings in the vector
            if (vect[i][j] == dil) { // if the character in the string contains the dilation character
                //dilates the function if its out of bounds 
                if (i > 0) { //if the vector index is greater than 0 then its not at the border
                        newv[i-1][j] = dil; //replaces the whtie space character with the dilation character
                                            // and stores it in the new vector to prevent the new 
                                            // dilation characters from being dilated again
                    }
                if (j > 0) { //if the string index is greater than 0 then its not at the border
                    newv[i][j-1] = dil;//replaces the whtie space character with the dilation character
                                        // and stores it in the new vector to prevent the new 
                                        // dilation characters from being dilated again
                }
                if (i +1<vect.size()) { //if the vector index plus one (prevents from replacing at the border) 
                                        //is less than the size of the vector
                    newv[i+1][j] = dil; //replaces the whtie space character with the dilation character
                                        // and stores it in the new vector to prevent the new 
                                        // dilation characters from being dilated again
                }
                if (j+1<vect[i].size()) {//if the vector index plus one (prevents from replacing at the border) 
                                        //is less than the size of the vector
                    newv[i][j+1] = dil;  //replaces the whtie space character with the dilation character
                                        // and stores it in the new vector to prevent the new 
                                        // dilation characters from being dilated again
                if (i == 0 || j == 0 || i == vect.size()||j == vect.size()){
                    if (i == 0 && j == 0){// if its at 0,0 it only dilates up and right
                        newv[i][j+1] = dil;
                        newv[i+1][j] = dil;
                    }
                    if (i == 0 && j != 0 && j < vect.size()){ //if it it on the top boarder, dilates left right and down
                        newv[i][j+1] = dil;
                        newv[i+1][j] = dil;
                        newv[i][j-1] = dil;
                    }
                    if (i != 0 && j == 0 && i < vect.size()){ //if on left boarder, dilates, up, right, and down
                        newv[i-1][j] = dil;
                        newv[i][j+1] = dil;
                        newv[i+1][j] = dil;
                    }
                    if (i == 0 && j == vect.size()){ // if on the top right corner, dilates down and left
                        newv[i+1][j] = dil;
                        newv[i][j-1] = dil;
                    if (i != 0 && j ==  vect.size() && i < vect.size()){ //if on the right border, dilates up, down and left
                        newv[i-1][j] = dil;
                        newv[i][j-1] = dil;
                        newv[i+1][j] = dil;
                    }
                    if (i == vect.size() && j == vect.size()){//if on the bottom right corner only dilates up and left
                        newv[i-1][j] = dil;
                        newv[i][j-1] = dil;
                    }
                    if (i == vect.size() && j != vect.size() && j > 0){ //if on the bottom border, dilates up, right and left
                        newv[i-1][j] = dil;
                        newv[i][j-1] = dil;
                        newv[i][j+1] = dil;
                    }
                    if (i == vect.size() && j == 0){ // if on the bottom left corner, it only dilates up and right
                        newv[i-1][j] = dil;
                        newv[i][j+1] = dil;
                    }
                }
                    
                }

            }
        }
    }
    vect = newv; //sets the vector to the new vector so that the new dilated vector is outputed
}
}
//erosion function that takes in the vector of strings, erosion character, and background (whitespeace) character
void erosion(std::vector<string>& vect, char erod, char back)
{
    std::vector<string> newv; //creates a new vector of strings
    newv = vect; //makes the current vector the new vector
    for(unsigned long i = 0; i<vect.size();i++){ //iterates through the vector
        for(unsigned long j = 0;j < vect[i].size(); j++){ //iterates through the strings in the vector
            //if the character is the erosion character:
            if (vect[i][j] == erod) { 
                 //if it has a whitespace on the right or left, it removes the character
                if(vect[i][j+1] == back &&vect[i][j-1] == back){
                    newv[i][j] = back;
                }
                //if it has a whitespace above or below it removes the character
                if (vect[i-1][j] == back || vect[i+1][j] == back){
                    newv[i][j] = back;
                }//if there is a whitespace on the right but has more than 4 erosion characters it removes the character
                if (vect[i][j+1] == back && vect[i][j-4] == erod){
                    newv[i][j] = back;
                }
                //if there is a whitespace on right or below it removes the character
                if (vect[i][j-1] == back || vect[i+1][j] == back){
                    newv[i][j] = back;
                }
                //if it has an erosion character on its right and left, and whitespace 2 spaces right or left
                // it removes the characters on the right and left
                if (vect[i][j+1] == erod && vect[i][j-1] == erod && (vect[i][j-2] == back && vect[i][j+2] == back)){
                    newv[i][j+1] = back;
                    newv[i][j-1] = back;
                }
                if (i == 0 || j == 0 || i == vect.size()||j == vect.size()){
                //removes the character if its at a border
                if(i == 0 && j == 0){
                    newv[i][j] = back;
                }
                if(i == 0 && j == vect.size()){
                    newv[i][j] = back;
                }
                if(i == vect.size() && j == 0){
                    newv[i][j] = back;
                }
                if(i == vect.size() && j == vect.size()){
                    newv[i][j] = back;
                }

                if (i == 0 && j != 0 && j < vect.size()){
                    if (vect[i+1][j] == erod){
                        vect[i+1][j] = back;
                    }
                    if (vect[i][j+1] == erod){
                        vect[i][j+1] = back;
                    }
                    if (vect[i][j-1] == erod){
                        vect[i][j-1] = back;
                    }

                }

                if (i != 0 && j == 0 && j < vect.size()){
                    if (vect[i+1][j] == erod){
                        vect[i+1][j] = back;
                    }
                    if (vect[i-1][j] == erod){
                        vect[i-1][j] = back;
                    }
                    if (vect[i][j+1] == erod){
                        vect[i][j+1] = back;
                    }

                }


                if (i == vect.size() && j != 0 && j < vect.size()){
                    if (vect[i-1][j] == erod){
                        vect[i-1][j] = back;
                    }
                    if (vect[i][j+1] == erod){
                        vect[i][j+1] = back;
                    }
                    if (vect[i][j-1] == erod){
                        vect[i][j-1] = back;
                    }

                }

                if (i != 0 && j == vect.size() && i < vect.size()){
                    if (vect[i-1][j] == erod){
                        vect[i-1][j] = back;
                    }
                    if (vect[i+1][j] == erod){
                        vect[i+1][j] = back;
                    }
                    if (vect[i][j-1] == erod){
                        vect[i][j-1] = back;
                    }
                }
                
                }
            }

        }
    }
    vect = newv; //sets the vector to the new vector so that the new eroded vector is outputed
}

    


//intakes the command argument from the user, sets int argc and char** arv
int main(int argc, char** argv) 
{

    std::string line; //creates string line to input a line from the file
    std::ifstream infile(argv[1]); //takes the input file as the 2 item in the command
    std::ofstream outfile(argv[2]); //takes the output file as the 3rd item in the command
    //if there is no file found
    if (!infile){
        std::cerr << "Could not find input file."; //prints error
    //if the input file can't be opened
    }else if(!infile.is_open()){
        std::cerr << "Could not open input file."; // prints error
    }else if(!outfile.is_open()){
        std::cerr << "Could not open output file."; // prints error
    }else if(!infile.is_open() && !outfile.is_open()){
        std::cerr << "Could not open input and output file."; // prints error
    }else{ //if the file is valid and is opened, 

        std::vector<string> filev; // creates empty string vector

        while(getline(infile, line)){ //adds the vectors line by line through a while loop
            filev.push_back(line);
        } 
        infile.close(); //closes the file after reading and adding it to a vector
        std::string comm = argv[3]; //sets argument 3 to a string so it can be compared
        if (argc < 4){ //if there are less than 4 arguments in the command
           std::cerr << "Invalid number of arguments"; //prints error
        //if there are less than five arguments and the user is trying to use replace or erosion
        }else if(argc < 5 && (comm == "replace" || comm == "erosion")){
            std::cerr << "Invalid number of arguments to run replace or erosion"; //prints error
        }else{
        //if the command is replace, dilation, or erosion, it computes the proper command to the functions above
        if (comm == "replace" || comm == "dilation" || comm == "erosion"){
            if (comm == "replace"){ //if the command is replace
                replacestr(filev, argv[4][0], argv[5][0]); //calls the function
            }else if (comm == "dilation"){ //if the command is dilation
                dilation(filev, argv[4][0]); //calls the function
            }else if(comm == "erosion"){ //if the command is erosiion
                erosion(filev, argv[4][0], argv[5][0]);//calls the function
            }
            //inputs the new vector into the outfile 
            for(unsigned long i = 0; i<filev.size();i++){ //loops throught the vector
            outfile << filev[i]<< "\n"; //adds each string to the outfile with a new line
            }
        outfile.close(); //closes the file after adding each string
        }else{//if the user does not use any of the commands above
            std::cerr << "Please use commands such as: replace, dilation, or erosion."; //prints error
        }
    }
    return 0;
    }  
}