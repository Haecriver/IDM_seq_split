#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
#include <unistd.h> 

#include <string>
#include <iostream>
#include <sstream>

#include "../../CLHEP/Random/MTwistEngine.h"

int main (int argc, char** argv)
{
	CLHEP::MTwistEngine * mt = NULL;
	int nbStates, sizeStates;
	std::stringstream ss;
	const char* name;
	
	if(argc<3){
		std::cout << "Usage: ./stateGenerator <numberOfStates> <sizeOfStates>" << std::endl;
	}else{
		ss << argv[1] << " " << argv[2];
		ss >> nbStates >> sizeStates;	
		ss.str(std::string());
		ss.clear();
		
		mt = new CLHEP::MTwistEngine();

		for(int i = 0; i < nbStates; i++)
		{
			ss << "state" << i << ".state";
			name = ss.str().c_str();
			std::cout << ss.str();
			
			for(int j = 0; j<sizeStates; j++){
				mt->flat();
			}
			mt->saveStatus(name);
			
			ss.str(std::string());
			ss.clear();
		}
	
	}
	
	
	delete mt;
	return 0;
}
