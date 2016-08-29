#include<bits/stdc++.h>

using namespace std;

void splitter(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    splitter(s, delim, elems);
    return elems;
}

vector< vector<string> > Input; //The main Input dataset
vector< vector<int> > Dataset;  //The hashed dataset
vector<string> items;

int main()
{
  string temp,line,input,output;
  int i;
  vector<string> lines;
  float confidence,support,flag;
  ifstream myfile("config.csv");
  if(myfile.is_open())
  {
    i=0;
    while(getline(myfile, line))
    {
      temp = line.substr(line.find(",")+1,line.length()-1);
      if(i==0)
        input=temp;
      else if(i==1)
        output=temp;
      else if(i==2)
        support=std::atof(temp.c_str());
      else if(i==3)
        confidence=std::atof(temp.c_str());
      else if(i==4)
        flag=std::atof(temp.c_str());
      i++;
    }
    myfile.close();
    ifstream inputfile("input.csv");
    if(inputfile.is_open())
    {
      while(getline(inputfile, line))
      {
        lines = split(line, ',');
        Input.push_back(lines);
        for(int i=0;i<lines.size();i++)
        {
          if (find(items.begin(), items.end(), lines[i]) == items.end())
            items.push_back(lines[i]);
        }
        lines.clear();
      }
    }
    else
      cout << "Unable to open input file\n";
    for(int i=0;i<Input.size();i++)
    {
      vector<int> temp;
      Dataset.push_back(temp);
      for(int j=0;j<Input[i].size();j++)
      {
        Dataset[i].push_back(0);
        for(int k=0;k<items.size();k++)
        {
          if(Input[i][j]==items[k])
          {
              Dataset[i][j]+=k;
              break;
          }
        }
        cout << Dataset[i][j] << " ";
      }
      cout << "\n";
    }
    int count[items.size()+1]={0};
    for(int i=0;i<Dataset.size();i++)
    {
      for(int j=0;j<Dataset[i].size();j++)
      {
        count[Dataset[i][j]]++;
      }
    }
    cout << "support-->" << support*Dataset.size() << "\n";
    for(int i=0;i<items.size();i++)
    {
      //cout << count[i] << " ";
      if((float)count[i]>(float)support*Dataset.size())
        cout << i << " ";
    }
    cout << "\n";
  }
  else
    cout << "Unable to open config file\n";
  return 0;
}
