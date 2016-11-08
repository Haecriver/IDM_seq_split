#ifndef __pi_HPP__
#define __pi_HPP__

#include <ctime>
#include <cmath>

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include <sys/wait.h>

#include "../../CLHEP/Random/MTwistEngine.h"

#include "seq_splitting.hpp"

const bool DEBUG_MC = 0;

class Pi : public SeqSplit{
	private:
		unsigned long		_nb_tirages;

	public:
		Pi(unsigned int pNb_exp, std::string pStatePath, 
					std::string pStateName, std::string pStateExt, std::string pResPath, 
					std::string pResName, unsigned long pnb_tirages,
					 bool pmode_seq_split);
				
		~Pi();

		void do_computing(std::fstream& fs, CLHEP::MTwistEngine* mt);
		std::vector<float> monte_carlo ();
};

#endif
