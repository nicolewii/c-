#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <queue>


// defined in performance.cpp
void usage();
template <class T>
void priority_queue_sort(std::priority_queue<T,std::vector<T>, std::greater<T> > &pq, std::ostream &ostr, int &output_count) {
  output_count = pq.size();
  //checking that the priority queue isnt empty
  while(!pq.empty()){
    //prints the top element
    ostr << pq.top() << std::endl;
    //then removes it
    pq.pop();
  }
}
template <class T>
void priority_queue_remove_duplicates(std::priority_queue<T,std::vector<T>, std::greater<T> > &pq, std::ostream &ostr, int &output_count) { 
  //priority queue can have duplicates, but you don't really need to remove them to navigate through the priority queue
  (void)pq; //voids priority queue
  //prints nothing
  ostr << std::endl;
  //sets output count to 0
  output_count = 0;
}
template <class T>
void priority_queue_mode(std::priority_queue<T,std::vector<T>, std::greater<T> > &pq, std::ostream &ostr, int &output_count) {
  //sets a variable to the top value
  T x = pq.top();
  //then removes that value
  pq.pop();
  //sets another empty variable to hold the mode
  T m;
  //sets variables to keep track of the first and second
  int first =0, second = 0;
  //while the priority queue isnt empty
  while(!pq.empty()){
    //if the top value isn't the current top value
    if(x != pq.top()){
      //then the first is 0
      first = 0;
    //else increment first
    }else{
      first++;
      //if the first is greater than the second
      if(first > second){
        //set the second to the first (to be able to check the rest)
        second = first;
        //and set the current mode to the x's value
        m = x;
      }
    }
    //reset x to the new top
    x = pq.top();
    //then remove it
    pq.pop();
  }
  //then print the mode
  output_count = 1;
  ostr << m << std::endl;
  
}

template <class T>
void priority_queue_first_sorted(std::priority_queue<T,std::vector<T>, std::greater<T> > &pq, std::ostream &ostr, int &output_count, int optional_arg) {
  //assertions
  assert (optional_arg >= 1);
  assert ((int)pq.size() >= optional_arg);
  output_count = optional_arg;
  //loops through the output count
  for (int i = 0; i < output_count; i++) {
    //prints what the top value is
    ostr << pq.top() << "\n";
    //then removes it
    pq.pop();
  }
}
template <class T>
void priority_queue_closest_pair(std::priority_queue<T,std::vector<T>, std::greater<T> > &pq, std::ostream &ostr, int &output_count) {
  //assertion
  assert (pq.size() >= 2);
  output_count = 2;
  //holds variables for the best, first, second, and their elements
  int best;
  int first, second, ind1, ind2;
  //sets the first element to the top value
  ind1 = pq.top();
  //remove it
  pq.pop();
  //counter variable to keep track of how many times
  //we get a closest pair
  int start = 0;
  //checks the queue isnt empty
  while(!pq.empty()){
    //sets the second element to the next top
    ind2 = pq.top();
    //get the difference between those values
    int diff = ind2-ind1;
    //if the start is 0 (meaning this is our first time looping)
    //or id the difference is less than the best
    if(start == 0||diff<best){
      //set the best fo the difference
      best = diff;
      //set the first to the first element
      first = ind1;
      //set the second to the second element
      second = ind2;
      //increment start
      start++;
    }
    //then update the first element's top again
    ind1=pq.top();
    //and remove it again
    pq.pop();
  }
  //then print the closest pair
  output_count = 2;
  ostr << first << "\n";
  ostr << second << "\n";
}
template <class T>
void priority_queue_longest_substring(std::priority_queue<T,std::vector<T>, std::greater<T> > &pq, std::ostream &ostr, int &output_count) {
  //priority queue doesn't need to use longest substring because priority queues can find the greatest value on their own
  (void)pq; //voids priority queue
  //print a blank line
  ostr << std::endl;
  //sets the output count to 0
  output_count = 0;
}

void priority_queue_test(const std::string &operation, const std::string &type,
                         std::istream &istr, std::ostream &ostr,
                         int &input_count, int &output_count, int optional_arg) {
  if (type == "string") {
    // load the data into a map of strings
     std::priority_queue<std::string,std::vector<std::string>, std::greater<std::string> > pq ;
     //copied from hash tabla and bst, doesn't really matter because priority queues
     //dont use this function
    if (operation == "remove_duplicates") { priority_queue_remove_duplicates (pq,ostr,output_count); }
    else{
      std::string s;
    input_count = 0;
    while (istr >> s) {
      pq.push(s);
      input_count++;
    }
       if      (operation == "sort")             { priority_queue_sort              (pq,ostr,output_count); }
    else if (operation == "mode")              { priority_queue_mode              (pq,ostr,output_count); }
    // "closest_pair" not available for strings
    else if (operation == "first_sorted")      { priority_queue_first_sorted      (pq,ostr,output_count,optional_arg); }
    else if (operation == "longest_substring") { priority_queue_longest_substring (pq,ostr,output_count); }
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }
  }
  //same for integer values
  else {
    assert (type == "integer");
    // load the data into a map of integers
     std::priority_queue<int,std::vector<int>, std::greater<int> > pq;
    if (operation == "remove_duplicates") { priority_queue_remove_duplicates (pq,ostr,output_count); }
    else{
      int v;
    input_count = 0;
    while (istr >> v) {
      pq.push(v);
      input_count++;
    }
      if      (operation == "sort")              { priority_queue_sort              (pq,ostr,output_count); }
    else if (operation == "mode")              { priority_queue_mode              (pq,ostr,output_count); }
    else if (operation == "closest_pair")      { priority_queue_closest_pair      (pq,ostr,output_count); }
    else if (operation == "first_sorted")      { priority_queue_first_sorted      (pq,ostr,output_count,optional_arg); }
    // "longest_substring" not available for integers
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }
  }

}
