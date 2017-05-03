//Inputs in terminal

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "eigen/Eigen/Dense"

using namespace std;

int main(int argc, char* argv[]) {
	
//cout<<"Have"<<argc<<"arguments"<<endl;

//string name_file;
//cout<<"Enter the name of the file"<<endl;
//cin>>name_file;


float current_state1 = atof( argv[1] );
float current_state2 = atof( argv[2] );
float current_state3 = atof( argv[3] );
float current_state4 = atof( argv[4] );
string name_file = argv[5];
string time_pred = argv[6];					//Option for prediction: "Y"


float dat[100];

string file = name_file;            
ifstream openFile;
openFile.open(file.c_str());
float input;
for(int i=0; i<100; i++){
     openFile>>input;
     dat[i] = input;
     //cout<<dat[i]<<endl;
}

//initialise updated state
Eigen::MatrixXd xhatf(3,1);
xhatf << current_state1, current_state2, current_state3;	
//cout << xhatf << endl;

//Create process noise matrix
Eigen::MatrixXd sigmaf(3,3);
sigmaf << current_state4, 0, 0,
   0, current_state4, 0,
   0, 0, current_state4;

//Create F matrix
Eigen::MatrixXd F(3,3);
F << 1, 0, 0,
   0, 1, 1,
   0, 0, 1;
  
//initialise predicted state
Eigen::MatrixXd xhat(3,1);
xhat << 38000, 0, 0;
  
//Predicted sigma
Eigen::MatrixXd sigma(3,3);
sigma << 0.0, 0.0, 0.0,
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0;

//Create pertubations/observation noise matrix
Eigen::MatrixXd Q(3,3);
Q << 250000, 0, 0,
   0, 0.000025, 0,
   0, 0, 0.000025;
 
//Create the known matrix for linear evolution of obs z, H identity 2*3 matrix
Eigen::MatrixXd H(2,3);
H << 1.0, 0.0, 0.0,
   0.0, 1.0, 0.0;

//Create the measurement noise R matrix
Eigen::MatrixXd R(2,2);
R << 4000000, 0.0,
   0.0, 0.0009;

//Kalman gain matrix
Eigen::MatrixXd K(3,2);
K << 0.0, 0.0, 0.0,
   0.0, 0.0, 0.0;

//Measurement noise matrix
Eigen::MatrixXd z(2,1);
z << 0.0, 0.0;

///////////////////////////////Beginning of loop///////////////////////////////
for (int i = 0; i<50 ; i++){

xhat = F * xhatf;

//Variance - Covarianc matrix, assign initialise value if == 1
sigma = F * sigmaf * F.transpose() + Q; 

////////////////////////Update////////////////////////
//Kalgman gain matrix
K = sigma * H.transpose() * (H * sigma * H.transpose() + R).inverse();

//Read in z
//int i = 0;
z << dat[2 * i], dat[2 * i + 1];

//state variable
xhatf = xhat + K * (z - H * xhat);

//cov
sigmaf = sigma - K * H * sigma ;

//Print out state vector and cov matrix-->Print out in a line
  cout <<"Run "<<i+1<<": "<<xhatf(0,0)<<" "<<xhatf(1,0)<<" "<<xhatf(2,0)<<" ";
  cout <<sigmaf(0,0)<<" "<<sigmaf(0,1)<<" "<<sigmaf(0,2)<<" "<<sigmaf(1,0)<<" "<<sigmaf(1,1)<<" "<<sigmaf(1,2)<<" "<<sigmaf(2,0)<<" "<<sigmaf(2,1)<<" "<<sigmaf(2,2)<<endl;

}

//For prediction part of question
if(time_pred == "Y"){

	for(int i = 50; i<56; i++){
		
	xhat = F * xhatf;
	
	//Variance - Covarianc matrix, assign initialise value if == 1
	sigma = F * sigmaf * F.transpose() + Q; 
	
	////////////////////////Update////////////////////////
	//Kalgman gain matrix
	K = sigma * H.transpose() * (H * sigma * H.transpose() + R).inverse();
	

	//state variable
	xhatf = xhat + K * (H * xhat - H * xhat);
	
	//cov
	sigmaf = sigma - K * H * sigma ;
	
	//Print out state vector and cov matrix-->Print out in a line
	  cout <<"Run "<<i+1<<": "<<xhatf(0,0)<<" "<<xhatf(1,0)<<" "<<xhatf(2,0)<<" ";
	  cout <<sigmaf(0,0)<<" "<<sigmaf(0,1)<<" "<<sigmaf(0,2)<<" "<<sigmaf(1,0)<<" "<<sigmaf(1,1)<<" "<<sigmaf(1,2)<<" "<<sigmaf(2,0)<<" "<<sigmaf(2,1)<<" "<<sigmaf(2,2)<<endl;
	
	}//End of for loop
}//End of if loop

}//End of main loop

