#pragma once


#include <QtCharts>
#include <QtWidgets>

namespace mtobridge {
enum ForceType {POSITIVE_MOMENT, NEGATIVE_MOMENT, SHEAR};
enum SolverType {CONCERNED, CRITICAL};

class Solver {
public:
	//Solver();
	//~Solver();

	static std::string getForceType();
	static std::string getSolverType();
	static void updateForceType(std::string forceStr);
	static void updateSolverType(std::string solverStr);

private:
	static ForceType force;
	static SolverType solver;
};
};  // namespace mtobridge
