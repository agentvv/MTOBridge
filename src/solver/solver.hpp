#pragma once

#include <QtCharts>
#include <QtWidgets>

namespace mtobridge {
//enums for use in representing the force response types and solver types
enum ForceType {POSITIVE_MOMENT, NEGATIVE_MOMENT, SHEAR};
enum SolverType {CONCERNED, CRITICAL};

class Solver {
public:
	//Getter for the currently configured force response, returns a string for general use
	static std::string getForceType();

	//Getter for the currently configured solver type, returns a string for general use
	static std::string getSolverType();

	//Setter to change the currently configured force response, takes in a string representing the desired force response
	static void updateForceType(std::string forceStr);

	//Setter to change the currently configured solver type, takes in a string representing the desired solver
	static void updateSolverType(std::string solverStr);

private:
	static ForceType force;			//Variable to save currently selected force response
	static SolverType solver;		//Variable to save currently selected solver type
};
};  // namespace mtobridge
