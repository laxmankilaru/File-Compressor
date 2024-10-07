#include "Huffman.h"
#include "frequencycounter.h"
#include <bits/stdc++.h>
#include <getopt.h>
using namespace std;

std::ifstream::pos_type filesize(const string filename)
{
    ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

int main(int argc,char** argv){
  int option_read;
  int m = 0;
  string inputfilename,outputfilename="output.txt";
  const option long_options[] =
    {
      /* These two options set a common flag to either 0 or 1. */
      
      
      /* These options don’t set a flag.
	 We distinguish them by their indices. */
      
      {"mode",     required_argument,       0, 'm'},
      {"input",  required_argument,       0, 'i'},
      {"output",  required_argument, 0, 'o'},
    };

  while (1)
    {
      /* getopt_long stores the option index here. */
      int option_index = 0;
      option_read = getopt_long (argc, argv, "m:i:o:",
                       long_options, &option_index);

      /* Detect the end of the options. */
      if (option_read == -1)
        break;

      switch (option_read)
        {
        case 'm':
            if(strcmp(optarg,"d")==0){
                m =1;
            }
            break;

        case 'i':
          inputfilename = optarg;
          break;

        case 'o':
    if (optarg == nullptr) {
        std::cerr << "Error: Missing argument for output filename." << std::endl;
        exit(EXIT_FAILURE); // or handle the error appropriately
    }
    outputfilename = optarg;
    break;


        case '?':
          /* getopt_long already printed an error message. */
          break;

        default:
          abort ();
        }
    }
    frequencycounter frequencyCounter ;
    Huffman huffman;
    if(m==0){
        clock_t tStart = clock();
        frequencyCounter.readfile(inputfilename);
        huffman.huffer(frequencyCounter.getfrequencymap());
        huffman.compresstofile(inputfilename,outputfilename);
        cout <<"Time taken: "<<(1.0*(clock() - tStart)/CLOCKS_PER_SEC)<<"sec"<<endl;
        cout << "Input File Size : "<<filesize(inputfilename)<<" bytes."<<endl;
        cout<< "Compressed File Size : "<<filesize(outputfilename)<<" bytes."<<endl;
        cout<< "Compression Ratio : "<<(1.0*filesize(outputfilename)/filesize(inputfilename))<<endl;  
    }
    else{
        clock_t tStart = clock();
        huffman.dehuffer(inputfilename,outputfilename);
        cout <<"Time taken: "<<(1.0*(clock() - tStart)/CLOCKS_PER_SEC)<<"sec"<<endl;
        cout << "Input File (Compressed) Size : "<<filesize(inputfilename)<<" bytes."<<endl;
        cout<< "DeCompressed File Size : "<<filesize(outputfilename)<<" bytes."<<endl;
    }
}
