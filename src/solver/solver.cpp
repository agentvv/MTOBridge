#include "solver.hpp"
#include "util/data_types.hpp"

namespace mtobridge {
	//Initialise default values of force response type and solver type
	ForceType Solver::force = ForceType(POSITIVE_MOMENT);
	SolverType Solver::solver = SolverType(CONCERNED);

	//Getter for the currently configured force response, returns a string for general use
	std::string Solver::getForceType() {
		if (Solver::force == ForceType(POSITIVE_MOMENT)) {
			return("Positive Moment");
		}
		else if (Solver::force == ForceType(NEGATIVE_MOMENT)) {
			return("Negative Moment");
		}
		else if (Solver::force == ForceType(SHEAR)) {
			return("Shear");
		}
		return NULL;
	}

	//Getter for the currently configured solver type, returns a string for general use
	std::string Solver::getSolverType() {
		if (Solver::solver == SolverType(CONCERNED)) {
			return("Concerned Section");
		}
		else if (Solver::solver == SolverType(CRITICAL)) {
			return("Critical Section");
		}
		return NULL;
	}

	//Setter to change the currently configured force response, takes in a string representing the desired force response
	void Solver::updateForceType(std::string forceStr) {
		if (forceStr == "Positive Moment") {
			Solver::force = ForceType(POSITIVE_MOMENT);
		}
		else if (forceStr == "Negative Moment") {
			Solver::force = ForceType(NEGATIVE_MOMENT);
		}
		else if (forceStr == "Shear") {
			Solver::force = ForceType(SHEAR);
		}
		else {
			throw invalidConfigurationValue();
		}
	}

	//Setter to change the currently configured solver type, takes in a string representing the desired solver
	void Solver::updateSolverType(std::string solverStr) {
		if (solverStr == "Concerned Section") {
			Solver::solver = SolverType(CONCERNED);
		}
		else if (solverStr == "Critical Section") {
			Solver::solver = SolverType(CRITICAL);
		}
		else {
			throw invalidConfigurationValue();
		}
	}
};  // namespace mtobridge