#ifndef __seq_splitting_HPP__
#define __seq_splitting_HPP__

#include <unistd.h>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <stdlib.h> 

#include <sys/wait.h>

#include "../../CLHEP/Random/MTwistEngine.h"

class SeqSplit{
	protected:
		CLHEP::MTwistEngine* 			_mt;
		unsigned 						_nb_exp;
		std::vector<int> 				_children;
		
		std::string 					_statePath;
		std::string 					_stateName;
		std::string 					_stateExt;
		
		std::string 					_resPath;
		std::string 					_resName;
		
		bool							_mode_seq_split;
	
		float get_genrand(CLHEP::MTwistEngine* mt);
		
	public:
		SeqSplit(unsigned int pNb_exp, std::string pStatePath, 
					std::string pStateName, std::string pStateExt, std::string pResPath, 
					std::string pResName, bool pmode_seq_split);
							
		virtual ~SeqSplit();
	
		// Calcul les res dans des fichiers
		int compute_res();
		virtual void do_computing(std::fstream& fs, CLHEP::MTwistEngine* mt)=0;
};


#endif
