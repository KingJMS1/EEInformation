#include <Python.h>
#include <vector>
#include "Cluster.h"


static PyObject *KClustering_cluster(PyObject *self, PyObject *args)    {
    PyObject *arr;
    int k;

    if (!PyArg_ParseTuple(args, "Oi", &arr, &k))    {
        return NULL;
    }
    Cluster::Clusterer a;
    return a.Clustered(arr, k);
}

static PyMethodDef KClusteringMethods[] = {
    {"cluster", KClustering_cluster, METH_VARARGS, "Does KClustering"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef KClustering_definition = {
    PyModuleDef_HEAD_INIT, 
    "KClustering",
    "A module to do KClustering",
    -1,
    KClusteringMethods
};

PyMODINIT_FUNC PyInit_KClustering(void) {
    Py_Initialize();
    return PyModule_Create(&KClustering_definition);
}