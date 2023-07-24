#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <utility>
#include <string>
#include <set>
#include <map>


// defined in performance.cpp
void usage();
template <class T>
void bst_sort(std::map<T, int> &mp, std::ostream &ostr, int &output_count) {
  // use the map sort algorithm
  output_count = mp.size();
  //again, using const itertaors for maps
  typename std::map<T, int>::const_iterator iter1;
  for (iter1 = mp.begin(); iter1 != mp.end(); iter1++) {
    for(int i = 0; i<iter1->second;i++){
      ostr << iter1->first << "\n";
    }
  }
}
template <class T>
void bst_remove_duplicates(std::map<T, int> &mp, std::ostream &ostr, int &output_count, std::istream &istr, int &input_count) { 
  // don't reorder the elements, just do all pairwise comparisons
  //sets a T variable
  T x;
  //while searching though the input stream
  while(istr >> x){
    //if you reach the end of the map and found the element in the map,
    // it means there are no other duplicate values in the map
    if(mp.find(x)==mp.end()){
      //so, insert the unique pair into the map
      mp.insert(std::make_pair(x, 1));
      //print the unique value
      ostr << x << std::endl;
    }
    //else, keep going through the inputs
    input_count++;
  }
  //and set the output count to the map's size
  output_count = mp.size();
}
// based off: https://stackoverflow.com/questions/9370945/finding-the-max-value-in-a-map 
template <class T>
void bst_mode(std::map<T, int> &mp, std::ostream &ostr, int &output_count) {
  //using the max element function to find the maximum value in the map
  typename std::map<T, int>::iterator iter1 = std::max_element(mp.begin(), mp.end(), [] 
  (const std::pair<T, int> & x, const std::pair<T, int> & y)->bool {
      return x.second < y.second;
  });
  //prints the max value
  output_count = 1;
  ostr << iter1->first << std::endl;
}

void bst_closest_pair(std::map<int, int> &mp, std::ostream &ostr, int &output_count) {
  //asserting
 assert (mp.size() >= 2);
  output_count = 2;
  int best;
  // the two elements with closest value must be next to each other in sorted order
  //exactly the same as list_closest_pair, except changing iterators
  //to be map iterators
  typename std::map<int, int>::iterator iter1;
  typename std::map<int, int>::iterator iter2;
  for (iter1 = mp.begin(); iter1 != mp.end(); iter1++) {
    int first = iter1->first;
    iter1++;
    if(iter1 == mp.end()){
      break;
    }
    int second = iter1->first;
    iter1--;
    int diff = second-first;
    if (iter1 == mp.begin() || diff < best) {
      best = diff;
      iter2 = iter1;
    }
  }
  // print the two elements
  output_count = 2;
  ostr << iter2->first << "\n";
  iter2++;
  ostr << iter2->first << "\n";
}
template <class T>
void bst_first_sorted(std::map<T, int> &mp, std::ostream &ostr, int &output_count, int optional_arg) {
  //assertions
  assert (optional_arg >= 1);
  assert ((int)mp.size() >= optional_arg);
  //similar to other first sorted functions
  output_count = optional_arg;
  //counter variable
  int c = 0;
  //creates a map iterator
  typename std::map<T, int>::iterator iter1 = mp.begin();
  //looping through the output count
  for (int i = 0; i < output_count;i++, iter1++) {
    //loops through the duplicates
    for(int j = 0; j<iter1->second; j++){
      //checks if the counter is less than the output count
      if(c < output_count){
        //the prints every duplicate possible
         ostr << iter1->first << "\n";
         //counter to keep track of how many elements we go through
         c++;
      }
    }
  }
}
void bst_longest_substring(std::map<std::string, int> &mp, std::ostream &ostr, int &output_count) {
  //similar to longest substring in previous data types
  std::string str = "";
  //creates iterators
    typename std::map<std::string, int>::iterator iter1;
    typename std::map<std::string, int>::iterator iter2 = ++mp.begin();
    for (iter1 = mp.begin(); iter1 != --(mp.end()); iter1++){
        for (iter2 = mp.begin(); iter2 != mp.end(); iter2++ ){
          //now pointing to the element values (first, the strings)
            for (unsigned int ind1 = 0; ind1 < iter1->first.size(); ind1++){
              //also points the map to its first element (the strings)
                for (unsigned int ind2 = str.size()+1; ind2 <= iter1->first.size() - ind1; ind2++ ){
                  //also pointing to the strings tc create a substring based on the string 
                  //stored in the map
                    std::string sub1 = (iter1->first).substr(ind1, ind2);
                    if (iter2->first.find(sub1) != std::string::npos && iter1 != iter2){
                        if (str.length() < sub1.length()){
                            str = sub1;
                        }
                    }
                }
            }
        }
    }
    output_count = 1;
    ostr << str << std::endl;
}

void bst_test(const std::string &operation, const std::string &type,
              std::istream &istr, std::ostream &ostr,
              int &input_count, int &output_count, int optional_arg) {
  if (type == "string") {
    // load the data into a map of strings
    std::map<std::string, int> mp;
    //since maps are sorted, you need to prioritize remove duplictes because when you put it into the map
    //it automatically sorts it, so you need to remove them first before sorting
    if (operation == "remove_duplicates") { bst_remove_duplicates (mp,ostr,output_count, istr, input_count); }
    else{
      //else, continue with the other commands
      std::string s;
    input_count = 0;
    while (istr >> s) {
      mp[s]++;
      input_count++;
    }
       if      (operation == "sort")             { bst_sort              (mp,ostr,output_count); }
    else if (operation == "mode")              { bst_mode              (mp,ostr,output_count); }
    // "closest_pair" not available for strings
    else if (operation == "first_sorted")      { bst_first_sorted      (mp,ostr,output_count,optional_arg); }
    else if (operation == "longest_substring") { bst_longest_substring (mp,ostr,output_count); }
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }
  }
  //same for the integer types
  else {
    assert (type == "integer");
    // load the data into a map of integers
    std::map<int, int> mp;
    if (operation == "remove_duplicates") { bst_remove_duplicates (mp,ostr,output_count, istr, input_count); }
    else{
      int v;
    input_count = 0;
    while (istr >> v) {
      mp[v]++;
      input_count++;
    }
      if      (operation == "sort")              { bst_sort              (mp,ostr,output_count); }
    else if (operation == "mode")              { bst_mode              (mp,ostr,output_count); }
    else if (operation == "closest_pair")      { bst_closest_pair      (mp,ostr,output_count); }
    else if (operation == "first_sorted")      { bst_first_sorted      (mp,ostr,output_count,optional_arg); }
    // "longest_substring" not available for integers
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }
  }
}
