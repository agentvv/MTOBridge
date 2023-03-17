#include "solver.hpp"
#include "util/data_types.hpp"

namespace mtobridge {
	ForceType Solver::force = ForceType(POSITIVE_MOMENT);
	SolverType Solver::solver = SolverType(CONCERNED);

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

	std::string Solver::getSolverType() {
		if (Solver::solver == SolverType(CONCERNED)) {
			return("Concerned Section");
		}
		else if (Solver::solver == SolverType(CRITICAL)) {
			return("Critical Section");
		}
		return NULL;
	}

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