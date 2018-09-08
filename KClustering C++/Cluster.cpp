#include <Python.h>
#include <vector>
#include "Cluster.h"

using namespace std;

namespace Cluster
{
int Clusterer::assocWithClosest(vector<vector<vector<double>>> &result, vector<vector<double>> &means, vector<double> &vec)
{
	
	double dist = INT_MAX;
	int index = -1;

	for (int i = 0; i < means.size(); i++)
	{
		double thisdist = 0;
		for (int j = 0; j < vec.size(); j++)
		{
			double a = (means.at(i).at(j) - vec.at(j));
			thisdist += a * a;
		}
		if (thisdist < dist)
		{
			dist = thisdist;
			index = i;
		}
	}
	result.at(index).push_back(vec);
	return index;
}

void Clusterer::update(vector<vector<vector<double>>> &result, vector<vector<double>> &means)
{

	for (int i = 0; i < result.size(); i++)
	{
		for (int k = 0; k < means.at(0).size(); k++)
		{
			double dimsum = 0;
			for (int j = 0; j < result.at(i).size(); j++)
			{
				dimsum += result.at(i).at(j).at(k);
			}
			dimsum /= result.at(i).size();
			means.at(i).at(k) = dimsum;
		}
	}
}

void Clusterer::listToVector(PyObject *list, vector<double> &vec)
{
	if (!PyList_Check(list))
	{
		return;
	}

	vec.reserve(PyList_Size(list));
	for (Py_ssize_t i = 0; i < PyList_Size(list); i++)
	{
		PyObject *val = PyList_GetItem(list, i);
		vec.push_back(PyFloat_AsDouble(val));
	}
	return;
}

PyObject *Clusterer::vectorToList(vector<double> vec)
{
	PyObject *list = PyList_New(vec.size());

	for (int i = 0; i < vec.size(); i++)
	{
		PyList_SetItem(list, i, PyFloat_FromDouble((double)vec.at(i)));
	}

	return list;
}

PyObject *Clusterer::Clustered(PyObject *list, int k)
{

	vector<vector<double>> means;
	means.reserve(k);
	vector<vector<vector<double>>> result;
	result.reserve(k);

	for (int i = 0; i < k; i++)
	{
		vector<vector<double>> lol;
		result.push_back(lol);
	}

	if (!PyList_Check(list))
	{
		return NULL;
	}

	for (int i = 0; i < k; i++)
	{
		int index = (rand() % (((int)PyList_Size(list)) - i)) + i; //Don't want to choose the same thing twice.
		PyObject *pyinitmean = PyList_GetItem(PyList_GetSlice(list, 0, PyList_Size(list)), index);
		vector<double> initmean;
		listToVector(pyinitmean, initmean); //We swap so that we don't add the same data value into the set multiple times. /See <why>
		means.push_back(initmean);
		result[i].push_back(initmean);
		PyList_SetItem(list, index, PyList_GetItem(list, i));
		PyList_SetItem(list, i, pyinitmean);
	}
	//First run

	for (int i = k; i < ((int)PyList_Size(list)); i++)
	{ // <why>
		vector<double> vec;
		PyObject *smallList = PyList_GetItem(list, i);
		listToVector(smallList, vec);
		assocWithClosest(result, means, vec);
	}
	update(result, means);

	bool aChangeOccurred = true;
	while (aChangeOccurred)
	{
		vector<vector<vector<double>>> newsult;
		newsult.reserve(result.size());
		vector<vector<double>> lol;
		newsult.assign(result.size(), lol);
		aChangeOccurred = false;
		for (int i = 0; i < (int)result.size(); i++)
		{
			for (int j = 0; j < (int)result.at(i).size(); j++)
			{
				if (i != assocWithClosest(newsult, means, result.at(i).at(j)))
				{
					aChangeOccurred = true;
				}
			}
		}
		result = newsult;
		update(result, means);
	}

	PyObject *retlist = PyList_New(result.size());

	for (int i = 0; i < (int)result.size(); i++)
	{
		PyObject *futureList = PyList_New(result.at(i).size());
		for (int j = 0; j < (int)result.at(i).size(); j++)
		{
			PyList_SetItem(futureList, j, vectorToList(result.at(i).at(j)));
		}
		PyList_SetItem(retlist, i, futureList);
	}
	return retlist;
}
} // namespace Cluster