#ifndef __hasard_HPP__
#define __hasard_HPP__

#include <ctime>
#include <cmath>

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include <algorithm>

#include <sys/wait.h>

#include "../../CLHEP/Random/MTwistEngine.h"

#include "seq_splitting.hpp"


const bool DEBUG_MC = 0;


class Gattaca: public SeqSplit{
	private:
		unsigned		_nb_nucleotides;
	public:
		Gattaca(unsigned int pNb_exp, std::string pStatePath, 
				std::string pStateName, std::string pStateExt, std::string pResPath, 
				std::string pResName,int pnb_nucleotides,
				bool pmode_seq_split);
				
		~Gattaca();

		void do_computing(std::fstream& fs, CLHEP::MTwistEngine* mt);
		std::vector<float> mot_hasard();
};

#endif
