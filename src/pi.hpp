#ifndef __pi_HPP__
#define __pi_HPP__
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <sstream>
#include <fstream>
#include <vector>

#include <sys/wait.h>

#include "../../CLHEP/Random/MTwistEngine.h"

#include "seq_splitting.hpp"

#define DEBUG_MC 0
#define CHARGEMENT 0

#define M_PI 3.14159265358979323846

class Pi : public SeqSplit{
	public:
		Pi(unsigned int pNb_exp, unsigned long pNb_tirage,
						std::string pStatePath, std::string pStateName, std::string pStateExt, 
						std::string pResPath, std::string pResName);
				
		~Pi();

		void do_computing(std::fstream& fs, CLHEP::MTwistEngine* mt);
		std::vector<float> monte_carlo ();
};

#endif
