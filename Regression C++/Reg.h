#ifndef REG_H
#define REG_H

#include <vector>
#include <stack>
#include <Eigen/Eigen/Dense>
#include <Eigen/Eigen/Core>

using namespace std;

using Eigen::MatrixXd;
using Eigen::VectorXd;

class Regresser {
    public:
        static void generateSubsample(vector<int> &subsample, int num, int m);
        static void fastEval(MatrixXd &model, vector<int> indices, MatrixXd &xs, VectorXd &ys, int currX, VectorXd &residuals, double &rmse, vector<int> &subsample, stack<double> &ws, double &wi, double deltaw, int &f, double &alpha, MatrixXd &results, vector<int> &whichVars);
        static void findResiduals(VectorXd &residuals, VectorXd &ys);
        static double StdDev(VectorXd &ys);
        static void center(MatrixXd &toCenter);
        static void vifSelect(int m, MatrixXd &xs, VectorXd &ys, MatrixXd &blank, vector<int> &whichVars);
};
#endif