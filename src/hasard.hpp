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


class Hasard: public SeqSplit{
	private:
		std::string		_mot_recherche;
	public:
		Hasard(unsigned int pNb_exp, std::string pStatePath, 
					std::string pStateName, std::string pStateExt, std::string pResPath, 
					std::string pResName, std::string pmot_recherche,
					bool pmode_seq_split);
				
		~Hasard();

		void do_computing(std::fstream& fs, CLHEP::MTwistEngine* mt);
		std::vector<float> mot_hasard();


};

#endif
