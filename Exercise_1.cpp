// Time Complexity: O(n) where n is the total number of integers in the nested list
// Space Complexity: O(d) for the stack used 
// Were you able to solve the problem on Leetcode?: Yes
// Did you face any challenges while solving the problem? The logic of adding stack elements using native iterators was tricky

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

class NestedIterator {
public:

    stack<vector<NestedInteger>::const_iterator> begins, ends;

    NestedIterator(vector<NestedInteger> &nestedList) {
        begins.push(nestedList.begin());
        ends.push(nestedList.end());
        
    }
    
    int next() {
        // return the integer at the current iterator position
        // and move the iterator to the next position
        return (begins.top()++)->getInteger();
    }
    
    bool hasNext() {
        while(!begins.empty() ){
            // if current list has been processed and reaches end of list, pop the stack to get rid of the nested list element
            if (begins.top() == ends.top()) {
                
                begins.pop();
                ends.pop();

            }
            else {
                // get the top most element on the stack and move iterator to next element
                
                auto nextElement = begins.top();
                if (nextElement->isInteger()) {
                    // if the next element is an integer, return true
                    return true;
                }
                else{
                    // if the next element is a nested list, push its begin and end iterators onto the stack
                    // and move the iterator to the next element in the current list
                    // this effectively flattens the nested structure and makes sure that integers are always placed to top of the stack
                    begins.top()++;
                    const vector<NestedInteger>& currList = nextElement->getList();
                    begins.push(currList.begin());
                    ends.push(currList.end());
                }


            }
        }

        return false;
        
    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */