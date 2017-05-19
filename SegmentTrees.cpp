#include <math.h>
#include <iostream>
using namespace std;

/*
 * Class representing a Segment Tree data structure.
 */
class SegmentTree {

private:
	int* st;
	int len;

	void printSegmentTreeUtil(int ss, int se, int si) {

		cout<<st[si]<<" ";
		if (ss == se) {
			return;
		}
		int mid = ss + ((se-ss)/2);
		printSegmentTreeUtil(ss, mid, 2*si+1);
		printSegmentTreeUtil(mid+1, se, 2*si+2);
	}

	void createSegmentTree(int* inputArr) {

		if (len == 0) {
			return;
		}
		int height = (int)ceil(log2(len));
		st = new int[(int)(2*pow(2,height)-1)];
		createSegmentTreeUtil(inputArr, 0, len-1, 0);
	}

	int createSegmentTreeUtil(int* arr, int ss, int se, int si) {
		if (ss == se) {
			st[si] = arr[ss];
			return arr[ss];
		}

		int mid = ss + (se-ss)/2;
		st[si] = createSegmentTreeUtil(arr, ss, mid, 2*si+1) +
				createSegmentTreeUtil(arr, mid+1, se, 2*si+2);
		return st[si];
	}

	int findSumUtil(int ss, int se, int qs, int qe, int si) {

		// If the query index covers completely the current start and end index, then return the value at that node.
		if (qs <= ss && qe >= se) {
			return st[si];
		}

		// If the query index is out of bound of the given index then return 0
		if (qs > se || qe < ss) {
			return 0;
		}

		if (ss != se) {
			int mid = ss + ((se-ss)/2);
			return findSumUtil(ss, mid, qs, qe, 2*si+1) + findSumUtil(mid+1, se, qs, qe, 2*si+2);
		}
	}

	void updateUtil(int ss, int se, int i, int val, int si) {

		if (i < ss || i > se) {
			return;
		}

		st[si] = st[si] + val;
		if (ss != se) {
			int mid = ss + (se-ss)/2;
			updateUtil(ss, mid, i, val, 2*si+1);
			updateUtil(mid+1, se, i, val, 2*si+2);
		}
	}

public:
	/*
	 * Constructor
	 */
	SegmentTree(int* inputArr, int len) {
		this->len = len;
		this->st = 0;
		createSegmentTree(inputArr);
	}

	/**
	 * Prints segment tree in pre-order format. 
	 */
	void printSegmentTree() {
		printSegmentTreeUtil(0, len-1, 0);
		cout<<"\n";
	}

	/**
	 * Returns the sum of elements in the given range.
	 */
	int findSum(int l, int r) {
		if (l < 0 || r > len-1) {
			return -1;
		}

		return findSumUtil(0, len-1, l, r, 0);
	}

	/*
	 * Updates the element of the input array at the particular index and still maintains the Sum property.
	 */
	void updateItem(int index, int value) {

		if (index < 0 || index > len-1) {
			return;
		}
		updateUtil(0, len-1, index, value, 0);

	}

	/**
	 * Returns pointer to segment tree.
	 */
	int* getSt() const
	{
		return st;
	}
};
