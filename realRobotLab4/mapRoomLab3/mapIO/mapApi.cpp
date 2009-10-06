  
#include "mapApi.h"
#include <string>
#include <sstream>


using namespace std;
using namespace PlayerCc;



	//int** gridTotals;
	//int** gridSummationTemp;
	//int resolutionPerMeter;
	

	void MapWorldApi::totalSummations(){
	}
	void MapWorldApi::addSensorReadingToMap(double x, double y){
		x += 8;
		y -= 8;
		x = (int) (x * 10);
		y = (int) abs(y * 10);
		
		
		//cout << "X: " << x << " Y: " << y << endl;
		
		gridTotals[(int)((y*columnCount) + x)] = 50;
	}
	//LaserProxy* laser;
	
	
 
	MapWorldApi::MapWorldApi(LaserProxy* newLaser, int newRowCount, int newColumnCount, int newResolutionPerMeter){
		resolutionPerMeter = newResolutionPerMeter;
		rowCount = newRowCount * resolutionPerMeter;
		columnCount = newColumnCount * resolutionPerMeter;
		gridTotals = new int[rowCount * columnCount];
		gridSummationTemp = new int[rowCount * columnCount];
		laser = newLaser;
		for(int index = 0; index < rowCount * columnCount; index++){
			gridTotals[index] = 0;
			gridSummationTemp[index] = 0;
		}
	}
		
	
	void MapWorldApi::ReadSensor(Pose & currentPose){
		for(unsigned int index = 0; index < (*laser).GetCount(); index++) {
			if((*laser)[index] < 7.5){
				Vector newVector((*laser)[index], (*laser).GetBearing(index)  + dtor(currentPose.getAngle()) , false);
				//newVector.debugIntensity(); cout << endl;
				addSensorReadingToMap((newVector.getXIntensity() + currentPose.getX()), (newVector.getYIntensity() + currentPose.getY()));
			}
		}
		DrawPicture();
	}	
	
	Vector MapWorldApi::NextUnknownMapLocations (int resolution){
		Vector nextLocation(0,0);
		return nextLocation;
	}
	
	void MapWorldApi::ReadMapIO(){
		ifstream fileIn;
		fileIn.open("2dGridMap.map");
		string line;
		int rowCountIndex = 0;

		if (fileIn.is_open())
  		{
  			
     			getline (fileIn,line);

   			int n;
			stringstream stream(stringstream::in | stringstream::out);
			stream << line;
   			stream >> n;
   			cout << n << endl;
			rowCount = n;
			stream >> n;
			cout << n << endl;
			columnCount = n;
			
			getline(fileIn, line);

  		  	while (! fileIn.eof() )
  		  	{
      				getline (fileIn,line);
				stringstream newStream(stringstream::in | stringstream::out);
				newStream << line;
      				for(int index = 0; index < columnCount; index ++) {
      					n = 0;
   					newStream >> n;
   					if(newStream){
	   					gridTotals[(rowCountIndex * columnCount) + index] = n;
					}
				}

    			}
    			fileIn.close();
  		}

	}
	void MapWorldApi::WriteMapIO(){
		ofstream fileOp;
		fileOp.open("2dGridMap.map.saved"); 	
		fileOp << rowCount << " " << columnCount << "\n";
		fileOp << "1 50" << "\n";
		for (int indexRow = 0; indexRow < rowCount; indexRow++){
			for(int indexColumn = 0; indexColumn < columnCount; indexColumn++){
				fileOp << gridTotals[(indexRow * columnCount) + indexColumn] << " ";
			}
			fileOp << "\n";
		}
		fileOp << "\n";
		
        	fileOp.close();
	}
	void MapWorldApi::DrawPicture(){
		ofstream fileOp;
		fileOp.open("2dGridMap.pgm"); 	
		fileOp << "P2"<< "\n";
		fileOp << "#seans test file." << "\n";
		fileOp << rowCount << " " << columnCount << "\n";
		fileOp << "50" << "\n";
		for (int indexRow = 0; indexRow < rowCount; indexRow++){
			for(int indexColumn = 0; indexColumn < columnCount; indexColumn++){
				fileOp << gridTotals[(indexRow * columnCount) + indexColumn] << " ";
			}
			fileOp << "\n";
		}
		fileOp << "\n";
		
        	fileOp.close();
	}
	void MapWorldApi::writeTestMapFile(){


		ofstream fileOp;
		fileOp.open("2dGridMap.map"); 	

	        fileOp << "16 16" << "\n";
		fileOp << "1 50" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 50 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
        	fileOp.close();

	}

	void MapWorldApi::writeTestImgFile(){
	
		ofstream fileOp;	
		fileOp.open("2dGridMap.pgm"); 

		fileOp << "P2"<< "\n";
		fileOp << "#seas test file." << "\n";
       		fileOp << "16 16" << "\n";
		fileOp << "50" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 50 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
		fileOp << "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" << "\n";
       		fileOp.close();
	}
	
