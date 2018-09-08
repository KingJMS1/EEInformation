#include <Python.h>
#include "Reg.h"

static PyObject *VifRegression_regress(PyObject *self, PyObject *args)    {
    PyObject *xs;
    PyObject *ys;
    int m;
    
    MatrixXd finalVals;
    vector<int> finalVars;

    if (!PyArg_ParseTuple(args, "iOO", &m, &xs, &ys))    {
        return NULL;
    }
    if(!(PyList_Check(xs) && PyList_Check(ys)))    {
        printf("YOU MUST PASS TWO LISTS INTO THIS FUNCTION.");
        return NULL;
    }

    MatrixXd xMatrix(PyList_Size(xs), PyList_Size(PyList_GetItem(xs, 0)));
    VectorXd yMatrix(PyList_Size(ys));

    Regresser a;

    for(int i = 0; i < PyList_Size(xs); i++)    {
        PyObject *row = PyList_GetItem(xs, i);
        for(int j = 0; j < PyList_Size(row); j++) {
            xMatrix(i, j) = PyFloat_AsDouble(PyList_GetItem(row, j));
        }
        yMatrix(i) = PyFloat_AsDouble(PyList_GetItem(ys, i));
    }
    a.vifSelect(m, xMatrix, yMatrix, finalVals, finalVars);

    PyObject *toRet = PyTuple_New(2);
    PyObject *valList = PyList_New(finalVals.size());
    PyObject *indexList = PyList_New(finalVars.size());
    for(int i = 0; i < finalVals.size(); i++)   {
        PyList_SetItem(valList, i, PyFloat_FromDouble(finalVals(i)));
        if(i >= 1)   {
            PyList_SetItem(indexList, i-1, PyFloat_FromDouble(finalVars.at(i-1)));
        }
    }
    PyTuple_SetItem(toRet, 0, valList);
    PyTuple_SetItem(toRet, 1, indexList);
    return toRet;
}

static PyMethodDef VifRegressionMethods[] = {
    {"regress", VifRegression_regress, METH_VARARGS, "Does a Vif Regression, takes int m, 2dlist xs, 1dlist ys"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef VifRegression_definition = {
    PyModuleDef_HEAD_INIT, 
    "VifRegression",
    "A module to do a Vif Regression",
    -1,
    VifRegressionMethods
};

PyMODINIT_FUNC PyInit_VifRegression(void) {
    Py_Initialize();
    return PyModule_Create(&VifRegression_definition);
}