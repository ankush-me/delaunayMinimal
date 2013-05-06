#include "sorting.h"

PtrCoordinateComparatorEQ::PtrCoordinateComparatorEQ(int _d, int _i) : d(_d), i(mod(_i,d)) {}
bool PtrCoordinateComparatorEQ::operator() (const boost::shared_ptr<Eigen::Vector2d> &v1,
		const boost::shared_ptr<Eigen::Vector2d> &v2) const {

	using namespace std;

	cout << "  comparing : "<<(*v1).transpose()<<"|"<<v2->transpose()<<endl;
	bool ret;
	if ((*v1)[1] > (*v2)[1]) ret = false;
	else
		ret = (  ((*v1)[1] < (*v2)[1])? true : ((*v1)[0] > (*v2)[0]));
	cout << "     returning : "<<(ret?"true": "false")<<endl;
	return ret;

}


/** Compares two points given their indices.*/
IndexedComparator::IndexedComparator(int _d, int _i,
		const std::vector<boost::shared_ptr<Eigen::Vector2d> > *_pts) :
		d(_d), i(_i), pts(_pts), N(_pts->size()) {}

bool IndexedComparator::operator() (const int &idx1, const int &idx2) const {
	int c = i;
	do {
		if ( (*(pts->at(idx1)))[c] == (*(pts->at(idx2)))[c] )
			c = mod(c+1,d);
		else
			return ( (*(pts->at(idx1)))[c] < (*(pts->at(idx2)))[c]);
	} while (c != i);
	return false;
}


PtrCoordinateComparator::PtrCoordinateComparator(int _d, int _i) : d(_d), i(mod(_i,d)) {}
bool PtrCoordinateComparator::operator() (const boost::shared_ptr<Eigen::Vector2d> &v1,
		const boost::shared_ptr<Eigen::Vector2d> &v2) const {
	int c = i;
	do {
		if ((*v1)[c] == (*v2)[c])
			c = mod(c+1,d);
		else
			return ((*v1)[c] < (*v2)[c]);
	} while (c != i);
	return false;
}

CoordinateComparator::CoordinateComparator(int _d, int _i) : d(_d), i(mod(_i,d)) {}
bool CoordinateComparator::operator() (const Eigen::VectorXd &v1, const Eigen::VectorXd &v2) const {
	int c = i;
	do {
		if (v1[c] == v2[c])
			c = mod(c+1,d);
		else
			return (v1[c] < v2[c]);
	} while (c != i);
	return false;
}


Comparator::Comparator(int _d) : d(_d) {}
bool Comparator::operator() (const Eigen::VectorXd &v1, const Eigen::VectorXd &v2) const {
	int i = 0;
	while(i < d && v1[i] == v2[i]) {i++;}
	return (i==d)? false :  v1[i] < v2[i];
}


EqComparator::EqComparator(int _d) : d(_d) {}
bool EqComparator::operator() (const Eigen::VectorXd &v1, const Eigen::VectorXd &v2) const {
	int i = 0;
	while(i < d && v1[i] == v2[i]) {i++;}
	return (i==d);
}


/* Sorts the pts b/w [start, end] (inclusive) indices,
 * based on COMP_I coordinate of the points, breaking ties
 * by circularly subsequent coordinates. */
void lexicoSort(std::vector<int> & pts,
		const std::vector<boost::shared_ptr<Eigen::Vector2d> > *ptrs,
		int start, int end,  int comp_coord) {
	IndexedComparator comp(2, comp_coord, ptrs);
	int n = pts.size();
	if (n != 0)
		sort(pts.begin()+start, pts.begin()+end+1, comp);
}


/** Partially sorts an array of points in [start, end] (inclusive)
 *  such that [start,mid] < [mid,end].
 *   - E[O(end-start+1)] (linear) time.
 *   - Returns the index of the median element: mid \in [start, end].
 *   - comp_coord : index of the coordinate based on which the
 *                  comparisons should be done first.
 *   - Uses nth_element function of the standard library.
 *   - Mutates the vector b/w [start, end]. */
int median(std::vector<int> & pts,
		const std::vector<boost::shared_ptr<Eigen::Vector2d> > *ptrs,
		int start, int end, int comp_coord) {
	if (start > end) return -1;
	IndexedComparator comp(2, comp_coord, ptrs);
	const int mid = start + (end-start)/2;
	std::nth_element(pts.begin()+start, pts.begin()+mid, pts.begin()+end+1, comp);
	return mid;
}
