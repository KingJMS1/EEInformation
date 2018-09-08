#ifndef __MYCLASS_H__
#define __MYCLASS_H__
#endif

using namespace std;
namespace Cluster
{
class Clusterer
{
  public:
	static int assocWithClosest(vector<vector<vector<double>>> &result, vector<vector<double>> &means, vector<double> &vec);

	static void update(vector<vector<vector<double>>> &result, vector<vector<double>> &means);

	static void listToVector(PyObject *list, vector<double> &vec);

	static PyObject *vectorToList(vector<double> vec);

	static PyObject *Clustered(PyObject *list, int k);
};
} // namespace Cluster
//IF YOU CAN'T FIGURE OUT HOW TO USE THE LIBRARIES, JUST COPY CLUSTER.CPP INTO CLUSTER.H AND CHANGE THE NAMESPACE STUFF AND YOU'LL BE FINE.