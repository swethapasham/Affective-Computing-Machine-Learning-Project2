
#ifndef PREPROCESS_HPP_INCLUDED
#define PREPROCESS_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>
#include <typeinfo>
#include <math.h>
using namespace std;
struct Newone
{
float x;
float y;
float z;
};
Newone check;
int value=0;
int auvalue=0;
int extravalue=0;
vector<string> className;
vector<Newone> featuresVector;
vector<Newone> newone;
vector<float> leftRIghtEuclidean;
vector<float> leftNoseEuclidean;
vector<float> rightNoseEuclidean;
vector<float> averageEuclidean;
vector<int> actionUnits;
vector<float> extraUnits;
string attributes="";
string arffFile="";
class PreProcess
{
    public: PreProcess(std::string inputFile){
         // Turn the string into a stream.
        arffFile = inputFile;
        check.x=0.0;
        check.y=0.0;
        check.z=0.0;
        actionUnits.push_back(0);
        extraUnits.push_back(0);
        newone.push_back(check);
        ifstream myfile (inputFile);
        string line;
        if (myfile.is_open()){
        while (!myfile.eof()){
        getline (myfile,line);
        if(strstr(line.c_str(),"@data")){
            attributes += line+"\n"+"\n";
                break;
          }
          attributes += line+"\n";
        }
        }
        //cout << attributes;
        myfile.close();
        /* std::ifstream ifs;
        ifs.open(inputFile);
        string content;
        int note=0;
        while(ifs >> content) {

                if(note == 1){
                  cout << content<<endl<<endl;
                    split(content, ',');
                }
                if(content.compare("@data") == 0){
                    note = 1;
                }
        }
        ifs.close();*/
        int note=0;
        ifstream in("Project3.arff");
        char str[5000];
        while(in) {
          in.getline(str, 5000);  // delim defaults to '\n'
          string content(str);
          if(in) {
            if(note == 1){
                    split(content, ',');
                }
            if(content.find("@data")==0){
              note = 1;
            }
        }
      }

      in.close();
    }

  void split(string str, char delimiter){
  //vector<string> internal;
  value=0;
  auvalue=0;
  extravalue=0;
  stringstream ss(str);
  string tok;
        int i =1;
        int j=1;
  while(getline(ss, tok, delimiter)) { 
    if(!strstr(tok.c_str(),"T")){
        if(j <= 249){
          value++;
          switch(i){
              case 1 :
                          check.x = stof(tok);
                          //cout << stof(tok)<< endl;
                          i++;
                          break;
              case 2 :    check.y = stof(tok);
                          //cout << stof(tok)<< endl;
                          i++;
                          break;
              case 3 :    check.z = stof(tok);
                          //cout << stof(tok)<< endl;
                          newone.push_back(check);
                          i=1;
                          break;
          }
        }
        else if(j > 249 && j <= 284) {
                auvalue++;
                actionUnits.push_back(stoi(tok));
          }else{
            extravalue++;
            extraUnits.push_back(stof(tok));
          }
        j++;
      }else{
        className.push_back(tok);
      }
    }
  }
     void Translate(std::string translateType){
         float r1=0,r2=0,r3=0;
         float addx=0.0,addy=0.0,addz=0.0,avgx=0.0,avgy=0.0,avgz=0.0;
         if(translateType =="origin"){
          for(int i=1;i<newone.size();i++){
                addx += (newone[i].x);
                addy += (newone[i].y);
                addz += (newone[i].z);
            if(i%((value/3)) == 0 && i!=0){
              avgx=addx/(value/3);
              avgy=addy/(value/3);
              avgz=addz/(value/3);
              addx=addy=addz=0.0;
              for(int k=i;k>i-(value/3);k--){
                newone[k].x=newone[k].x-avgx;
                newone[k].y=newone[k].y-avgy;
                newone[k].z=newone[k].z-avgz;
              }
            }
          }
         }else{
          r1= rand() % 100+1;
          r2= rand() % 100+1;
          r3= rand() % 100+1;
          for(int k=1;k<newone.size();k++){
                newone[k].x=newone[k].x+r1;
                newone[k].y=newone[k].y+r2;
                newone[k].z=newone[k].z+r3;
            if(k%((value/3)) == 0 && k!=0){
                r1= rand() % 100+1;
                r2= rand() % 100+1;
                r3= rand() % 100+1;
            }
          }
         }
       }


     void WriteOutput(std::string outputFile){
      
      if(leftRIghtEuclidean.size() > 0){
          string temp="";
          attributes = "@relation ‘expression’\n";
          attributes += "@attribute faceAverageX numeric\n@attribute faceAverageY numeric\n@attribute faceAverageZ numeric\n";
          attributes += "@attribute leftEyeAverageX numeric\n@attribute leftEyeAverageY numeric\n@attribute leftEyeAverageZ numeric\n";
          attributes += "@attribute rightEyeAverageX numeric\n@attribute rightEyeAverageY numeric\n@attribute rightEyeAverageZ numeric\n";
          attributes += "@attribute leftEyebrowAverageX numeric\n@attribute leftEyebrowAverageY numeric\n@attribute leftEyebrowAverageZ numeric\n";
          attributes += "@attribute rightEyebrowAverageX numeric\n@attribute rightEyebrowAverageY numeric\n@attribute rightEyebrowAverageZ numeric\n";
          attributes += "@attribute noseAverageX numeric\n@attribute noseAverageY numeric\n@attribute noseAverageZ numeric\n";
          attributes += "@attribute mouthAverageX numeric\n@attribute mouthAverageY numeric\n@attribute mouthAverageZ numeric\n";
          attributes += "@attribute leftEyeRightEyeEuclidean numeric\n@attribute leftEyeMouthEuclidean numeric\n@attribute rightEyeMouthEuclidean numeric\n@attribute faceEuclidean numeric\n";

        ifstream myfile (arffFile);
        string line;
        int h = 0;
        if (myfile.is_open()){
        while (!myfile.eof()){
        getline (myfile,line);
        cout << line<<endl;
        if(strstr(line.c_str(),"@data")){
            attributes += "\n"+line+"\n"+"\n";
                break;
          }
          if(strstr(line.c_str(),"@attribute AU1 numeric")){
            h=1;
          }
          if(h==1){
                attributes+=line+"\n";
            }
          }
        }
        cout << attributes;
        myfile.close();

          std::ofstream ofs;
          ofs.open (outputFile, std::ofstream::app);
          ofs << attributes;
          ofs.close();
          attributes="";
          for(int j=0;j<className.size();j++){
            for(int i=1;i<=7;i++){
              temp += to_string(newone[i].x)+","+to_string(newone[i].y)+","+to_string(newone[i].z)+",";
            }
            temp += to_string(leftRIghtEuclidean[j])+",";
                    temp += to_string(leftNoseEuclidean[j])+",";
                            temp += to_string(rightNoseEuclidean[j])+",";
                              temp += to_string(averageEuclidean[j])+",";
                              //cout << temp<<endl;
           for(int i=1;i<=auvalue;i++){
            temp+= to_string(actionUnits[i])+",";
          }
          //cout << temp<< endl;
          for(int i=1;i<=extravalue;i++){
           temp+= to_string(extraUnits[i])+",";
          }
            ofs.open (outputFile, std::ofstream::app);
            ofs << temp<<className[j]<<endl;
            ofs.close();
            temp="";
            newone.erase(newone.begin()+1, newone.begin()+7+1);
            actionUnits.erase(actionUnits.begin()+1, actionUnits.begin()+(auvalue)+1);
            extraUnits.erase(extraUnits.begin()+1, extraUnits.begin()+(extravalue)+1);
        }
      }else{
        string temp="";
        std::ofstream ofs;
        ofs.open (outputFile, std::ofstream::app);
        ofs << attributes;
        ofs.close();
        attributes="";
        cout << value<< endl;
        for(int j=0;j<className.size();j++){
        for(int i=1;i<=value/3;i++){
          temp += to_string(newone[i].x)+","+to_string(newone[i].y)+","+to_string(newone[i].z)+",";
        }
        //cout << temp<< endl;
        for(int i=1;i<=auvalue;i++){
          temp+= to_string(actionUnits[i])+",";
        }
        //cout << temp<< endl;
        for(int i=1;i<=extravalue;i++){
          temp+= to_string(extraUnits[i])+",";
        }
        //cout << temp<< endl;
        ofs.open (outputFile, std::ofstream::app);
        ofs << temp<<className[j]<<endl;
        ofs.close();
        temp="";
        newone.erase(newone.begin()+1, newone.begin()+(value/3)+1);
        actionUnits.erase(actionUnits.begin()+1, actionUnits.begin()+(auvalue)+1);
        extraUnits.erase(extraUnits.begin()+1, extraUnits.begin()+(extravalue)+1);
      }
    }
   }

   void Rotate(std::string rotateAxis){
       double cospi=-1.0;
       double sinpi=0;
       double x=0.0;
       double y=0.0;
       double z=0.0;
       if(rotateAxis == "x"){
        for(int i=1;i<newone.size();i++){
          x = newone[i].x;
          y= (newone[i].y*cospi)+(newone[i].z*sinpi);
          z= (newone[i].y*(-1)*sinpi)+(newone[i].z*cospi);
          newone[i].x = x;
          newone[i].y = y;
          newone[i].z = z;
        }
       }
       else if(rotateAxis == "y"){
         for(int i=1;i<newone.size();i++){
            x = (newone[i].x*cospi)+ (newone[i].z*(-1)*sinpi);
            y = newone[i].y;
            z= (newone[i].x*sinpi)+(newone[i].z*cospi);
            newone[i].x = x;
            newone[i].y = y;
            newone[i].z = z;
       }
     }
       else if(rotateAxis == "z"){
        for(int i=1;i<newone.size();i++){
          x = (newone[i].x*cospi)+ (newone[i].y*sinpi);
          y = newone[i].y= (newone[i].x*(-1)*sinpi) + (newone[i].y*cospi);
          z = newone[i].z= newone[i].z;
          newone[i].x = x;
          newone[i].y = y;
          newone[i].z = z;
        }

       }

   }

   void scale(){
      for(int k=1;k<newone.size();k++){
          newone[k].x=newone[k].x*0.25;
          newone[k].y=newone[k].y*0.25;
          newone[k].z=newone[k].z*0.25 ;
        }
   }

   void CalculateFeatures(){
    Newone features;
    vector<float> averageEuclideanValue;
    float averageSum=0.0;
    float addx=0.0,addy=0.0,addz=0.0,avgx=0.0,avgy=0.0,avgz=0.0,x=0,y=0,z=0;
    float leftAddX=0,leftAddY=0,leftAddZ=0;
    float rightAddX=0,rightAddY=0,rightAddZ=0;
    float leftBrowAddX=0,leftBrowAddY=0,leftBrowAddZ=0;
    float rightBrowAddX=0,rightBrowAddY=0,rightBrowAddZ=0;
    float noseX=0,noseY=0,noseZ=0;
    float mouthX=0,mouthY=0,mouthZ=0;
      for(int i=1,j=1;i<newone.size();i++,j++){
          addx += (newone[i].x);
          addy += (newone[i].y);
          addz += (newone[i].z);

          if(i%((value/3)) != 0){
            averageEuclideanValue.push_back(distanceCalculate(newone[i].x,newone[i+1].x,newone[i].y, newone[i+1].y,newone[i].z, newone[i+1].z));
          }

          if(j >= 21 && j <= 28){
            leftAddX += (newone[i].x);
            leftAddY += (newone[i].y);
            leftAddZ += (newone[i].z);
          }
          else if(j >= 29 && j<=36){
            rightAddX += (newone[i].x);
            rightAddY += (newone[i].y);
            rightAddZ += (newone[i].z);
          }
          else if(j >= 1 && j<=10){
            leftBrowAddX += (newone[i].x);
            leftBrowAddY += (newone[i].y);
            leftBrowAddZ += (newone[i].z);
          }
          else if(j >= 11 && j<=20){
            rightBrowAddX += (newone[i].x);
            rightBrowAddY += (newone[i].y);
            rightBrowAddZ += (newone[i].z);
          }
          else if(j >= 37 && j<=48){
            noseX += (newone[i].x);
            noseY += (newone[i].y);
            noseZ += (newone[i].z);
          }
          else if(j >= 49 && j<=68){
            mouthX += (newone[i].x);
            mouthY += (newone[i].y);
            mouthZ += (newone[i].z);
          }
          if(i%((value/3)) == 0){
            features.x=addx/(value/3);
            features.y=addy/(value/3);
            features.z=addz/(value/3);
            featuresVector.push_back(features);
            features.x = leftAddX/8;
            features.y = leftAddY/8;
            features.z = leftAddZ/8;
            featuresVector.push_back(features);
            features.x = rightAddX/8;
            features.y = rightAddY/8;
            features.z = rightAddZ/8;
            featuresVector.push_back(features);
            features.x = leftBrowAddX/10;
            features.y = leftBrowAddY/10;
            features.z = leftBrowAddZ/10;
            featuresVector.push_back(features);
            features.x = rightBrowAddX/10;
            features.y = rightBrowAddY/10;
            features.z = rightBrowAddZ/10;
            featuresVector.push_back(features);
            features.x = noseX/12;
            features.y = noseY/12;
            features.z = noseZ/12;
            featuresVector.push_back(features);
            features.x = mouthX/20;
            features.y = mouthY/20;
            features.z = mouthZ/20;
            featuresVector.push_back(features);

            leftRIghtEuclidean.push_back(distanceCalculate(leftAddX/8, rightAddX/8, leftAddY/8, rightAddY/8, leftAddZ/10, rightAddZ/8));
            
            leftNoseEuclidean.push_back(distanceCalculate(leftAddX/8, noseX/12, leftAddY/8, noseY/12, leftAddZ/8, noseZ/12));
            
            rightNoseEuclidean.push_back(distanceCalculate(rightAddX/8, noseX/12, rightAddY/8, noseY/12, rightAddZ/8, noseZ/12));

            averageSum=0.0;

            for(int t=0;t<averageEuclideanValue.size();t++){
              averageSum+=averageEuclideanValue[t];
            }
            
            averageEuclidean.push_back(averageSum/averageEuclideanValue.size());

            averageEuclideanValue.clear();

            addx=addy=addz=leftAddX=leftAddY=leftAddZ=rightAddX=rightAddY=rightAddZ=0.0;
            leftBrowAddX=leftBrowAddY=leftBrowAddZ=rightBrowAddX=rightBrowAddY=rightBrowAddZ=noseX=noseY=noseZ=0.0;
            mouthX=mouthY=mouthZ=0.0;
            j=1;
            }
          }    
   }

   float distanceCalculate(float x1, float y1, float x2, float y2, float z1, float z2)
{
  float x = x1 - x2; //calculating number to square in next step
  float y = y1 - y2;
  float z = z1 - z2;
  float dist;

  dist = pow(x, 2) + pow(y, 2) + pow(z,2);       //calculating Euclidean distance
  dist = sqrt(dist);                  

  return dist;
}


};








#endif // PREPROCESS_HPP_INCLUDED
