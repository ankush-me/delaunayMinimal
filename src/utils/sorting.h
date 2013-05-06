#ifndef __SORTING_H__
#define __SORTING_H__

#include <Eigen/Dense>
#include <Eigen/AlignedVector>
#include <vector>
#include <iostream>
#include <algorithm>
#include "misc.h"
#include <boost/shared_ptr.hpp>

/** Compare points::Ptr based on i_th coordinate.
 *   - Ties broken using subsequent coordinates. */
struct PtrCoordinateComparatorEQ : std::binary_function
<boost::shared_ptr<Eigen::Vector2d>, boost::shared_ptr<Eigen::Vector2d>, bool> {
	// dimensions of the vector
	const int d;
	// the coordinate index based on which two points should be compared
	const int i;
	PtrCoordinateComparatorEQ(int _d, int _i);

	bool operator() (const boost::shared_ptr<Eigen::Vector2d> &v1,
			const boost::shared_ptr<Eigen::Vector2d> &v2) const ;
};


/** Compare points::Ptr based on i_th coordinate.
 *   - Ties broken using subsequent coordinates. */
struct PtrCoordinateComparator : std::binary_function
<boost::shared_ptr<Eigen::Vector2d>, boost::shared_ptr<Eigen::Vector2d>, bool> {
	// dimensions of the vector
	const int d;
	// the coordinate index based on which two points should be compared
	const int i;
	PtrCoordinateComparator(int _d, int _i);

	bool operator() (const boost::shared_ptr<Eigen::Vector2d> &v1,
			const boost::shared_ptr<Eigen::Vector2d> &v2) const ;
};


/** Templatized comparator for lexicographic less-than test.
 *  The comparisons are made of the indices based on the points stores in PTS.*/
struct IndexedComparator : std::binary_function <int, int, bool> {
private:

public:
	int d; // dimensions of the vector
	const std::vector<boost::shared_ptr<Eigen::Vector2d> > * pts;
	int N;

	// the coordinate index based on which two points should be compared
	const int i;


	IndexedComparator(int _d, int _i, const std::vector<boost::shared_ptr<Eigen::Vector2d> > *_pts);
	bool operator() (const int &idx1, const int &idx2) const;
};


// compare points based on i_th coordinate. Ties broken using subsequent coordinates.
struct CoordinateComparator : std::binary_function <Eigen::VectorXd, Eigen::VectorXd, bool> {
	// dimensions of the vector
	const int d;

	// the coordinate index based on which two points should be compared
	const int i;
	CoordinateComparator(int _d, int _i);

	bool operator() (const Eigen::VectorXd &v1, const Eigen::VectorXd &v2) const;
};


// compare points lexico-graphically
struct Comparator : std::binary_function <Eigen::VectorXd, Eigen::VectorXd, bool> {
	int d; // dimensions of the vector
	Comparator(int _d);

	bool operator() (const Eigen::VectorXd &v1, const Eigen::VectorXd &v2) const ;
};

struct EqComparator : std::binary_function <Eigen::VectorXd, Eigen::VectorXd, bool> {
	int d; // dimensions of the vector
	EqComparator(int _d);

	bool operator() (const Eigen::VectorXd &v1, const Eigen::VectorXd &v2) const;
};


/* Sorts the pts b/w [start, end] (inclusive) indices,
 * based on COMP_I coordinate of the points, breaking ties
 * by circularly subsequent coordinates. */
void lexicoSort(std::vector<int> & pts,
		const std::vector<boost::shared_ptr<Eigen::Vector2d> > *ptrs,
		int start, int end,  int comp_coord=0);

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
		int start, int end, int comp_coord=0);

#endif
