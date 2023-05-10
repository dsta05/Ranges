//
//  main.cpp
//  02. Ranges
//
//  Created by Dimitar Stamboliev on 10.05.23.
//

/*
 
 2. Ranges
 A range is a pair of integer numbers – let’s say that from and to form the range [from, to].
 If an integer number x is such that from <= x <= to, then we say that x is inside the range [from, to], or that
 the range [from, to] contains x.
 You are given a set of ranges, in which no two ranges intersect. That means that no range contains the from or to
 of another range.
 You are also given a sequence of integer numbers – let’s call them to check numbers.
 For each of the check numbers, print "in" if the number is inside any range, and "out" otherwise (i.e. if no range contains the number).
 NOTE: there will be a large number of ranges and an even larger number of integer numbers.
 Input
 The input will be separated into two parts.
 The first part will contain the ranges, each described as two integer numbers on a separate line of the standard
 input (the from and to of the range), until a line containing only the symbol '.' (dot) is reached.
 After that, each line of the standard input will contain exactly one check number, until a line containing only the
 symbol '.' (dot) is reached. Output
 For each check number in the input, print "in" if that number is contained in any range, or "out" if no range contains that number.
 
 */

#include <iostream>
#include <map>
#include <sstream>

using namespace std;

class Range{
  
private:
    int from;
    int to;
    
public:
    Range() {};
    
    Range(int from_, int to_) : from(from_), to(to_) {}
    
    int getFrom() { return this->from; }
    
    int getTo() { return this->to; }
    
    bool isOnRange(int value) {
        return this->from <= value && value <= this->to;
    }
    
};

bool inARange(int value, const map<int, shared_ptr<Range> > & rangesByFrom, const map<int, shared_ptr<Range> > & rangesByTo){
 
    auto fromIt = rangesByFrom.upper_bound(value);
    if (fromIt == rangesByFrom.begin()) {
        return false;
    }
    
    fromIt--;
    
    auto toIt = rangesByTo.lower_bound(value);
    if (toIt == rangesByTo.end()) {
        return false;
    }
    
    return fromIt->second == toIt->second;
}

int main(int argc, const char * argv[]) {

    map<int, shared_ptr<Range> > rangesByFrom;
    map<int, shared_ptr<Range> > rangesByTo;
    
    string lineIn;
    
    while (getline(cin, lineIn) && lineIn != ".") {
        
        istringstream lineRange(lineIn);
        
        int from;
        int to;
        
        lineRange >> from >> to;
        shared_ptr<Range> r = make_shared<Range>(from, to);
        rangesByFrom[from] = r;
        rangesByTo[to] = r;
        
    }
    
    ostringstream output;
    
    while (getline(cin, lineIn) && lineIn != ".") {
        
        istringstream lineValue(lineIn);
        
        int value;
        
        lineValue >> value;
        
        if (inARange(value, rangesByFrom, rangesByTo)) {
            output << "in";
        } else {
            output << "out";
        }
        
        output << endl;
        
    }
    
    cout << output.str() << endl;
    
    return 0;
}


/*
 
1 3
5 10
20 20
.
0
2
3
4
5
7
19
20
.
 
 */
