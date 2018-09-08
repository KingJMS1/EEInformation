#include <stat/stats.hpp>
#include "Reg.h"

#define STATS_GO_INLINE

using namespace std;

using Eigen::MatrixXd;
using Eigen::VectorXd;

// Each x should be centered with respect to itself.

void Regresser::generateSubsample(vector<int> &subsample, int num, int m)
{
	for (int i = 0; i < num; i++)
	{
		subsample.push_back(i);
	}

	for (int i = 0; i < m; i++)
	{
		int index = (rand() % (subsample.size() - i)) + i;
		int temp = subsample.at(i);
		subsample.at(i) = subsample.at(index);
		subsample.at(index) = subsample.at(i);
	}

	subsample.resize(m);
}

void Regresser::fastEval(MatrixXd &model, vector<int> indices, MatrixXd &xs, VectorXd &ys, int currX, VectorXd &residuals, double &rmse, vector<int> &subsample, stack<double> &ws, double &wi, double deltaw, int &f, double &alpha, MatrixXd &results, vector<int> &whichVars)
{
	//model, xs, ys, currX, residuals, rmse, subsample
	VectorXd subCurrX(indices.size());
	double gammahat = residuals.dot(xs.col(currX)) / (xs.col(currX).norm());
	
	for (int i = 0; i < indices.size(); i++)
	{
		int index = indices.at(i);
		subCurrX(i) = xs(index, currX);
	}
	
	

	MatrixXd a = (subCurrX.transpose() * model) * (model.transpose() * model).inverse() * (model.transpose() * subCurrX);
	double rsquared = a(0, 0) / subCurrX.squaredNorm();
	double t = gammahat / (rmse * sqrt(1 - rsquared));

	double cdfval = 2 * stats::pnorm(-abs(t), 0, 1);
	
	if (cdfval < alpha)
	{
		model.conservativeResize(model.rows(), model.cols() + 1);
		model.col(model.cols() - 1) = subCurrX;
		results.conservativeResize(results.rows(), results.cols() + 1);
		results.col(results.cols() - 1) = xs.col(currX);

		whichVars.push_back(currX);

		residuals = ys - (((results * (results.transpose() * results).inverse()) * results.transpose())* ys);
		rmse = residuals.norm() / (sqrt(xs.rows() - 1 - model.cols()));
		ws.push(wi + deltaw);
		f = currX;
		
	}
	else
	{
		ws.push((wi - alpha) / (1 - alpha));
	}
}

void Regresser::findResiduals(VectorXd &residuals, VectorXd &ys)
{
	double mean = ys.mean();
	residuals = ys - VectorXd::Constant(ys.size(), mean);
}

double Regresser::StdDev(VectorXd &ys)
{ //FINISHED
	double sum = 0;

	double mean = ys.mean();

	for (int i = 0; i < ys.size(); i++)
	{
		double num = ys(i) - mean;
		sum += num * num;
	}

	return sqrt((sum / (ys.size() - 1)));
}

void Regresser::center(MatrixXd &toCenter)
{
	for (int j = 0; j < toCenter.cols(); j++)
	{
		double mean = toCenter.col(j).mean();
		for (int i = 0; i < toCenter.rows(); i++)
		{
			toCenter(i, j) = toCenter(i, j) - mean;
		}
	}
}

//EACH VARIABLE (COLUMN) MUST BE CENTERED, OBSERVATIONS ARE ROWS, RESULTS NEEDS A COLUMN OF ONES
void Regresser::vifSelect(int m, MatrixXd &xs, VectorXd &ys, MatrixXd &blank, vector<int> &whichVars)
{
	MatrixXd results(xs.rows(), 1);
	results.col(0) = VectorXd::Constant(xs.rows(), 1);
	center(xs);
	double wzero = 0.50;
	double deltaw = 0.05;
	stack<double> ws;
	ws.push(wzero);

	vector<int> subsample;
	subsample.reserve(m);						//subsample contains random indices (row values) to index into an x vector
	generateSubsample(subsample, xs.rows(), m); //IMPLEMENTED

	int f = 0;

	VectorXd residuals(ys.size());
	double rmse = StdDev(ys); //IMPLEMENTED

	findResiduals(residuals, ys); //IMPLEMENTED

	MatrixXd model(m, 1);
	model.col(0) = VectorXd::Constant(m, 1);

	for (int i = 0; i < xs.cols(); i++)
	{
		double wi = ws.top();
		ws.pop();
		double a = wi / (1 + i - f);
		fastEval(model, subsample, xs, ys, i, residuals, rmse, subsample, ws, wi, deltaw, f, a, results, whichVars); //IMPLEMENTED?
	}

	blank = (results.transpose() * results).inverse() * results.transpose() * ys;
}


int main()
{
	MatrixXd useme(4000, 20);
	VectorXd ys(useme.rows());
	MatrixXd blank;
	MatrixXd results(useme.rows(), 1);
	int m = 220;
	
	for (int i = 0; i < useme.rows(); i++)
	{
		int rigit = rand() % 3000;
		useme(i, 0) = rigit + (rand() % 2);
		for (int j = 1; j < useme.cols(); j++)
		{
			useme(i, j) = (rand() % 8000000) / 5.0;
		}
		useme(i, 4) = rigit/2;
		ys(i) = rigit + (rand() % 2);
	}
	vector<int> a;
	Regresser::vifSelect(m, useme, ys,  blank, a);
	

	return 0;
}
