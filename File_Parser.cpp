/* Write a program to interpret the language of the file passed (for example : Ruby, PHP, Java) */
#include <iostream>
#include <fstream>
#include <string>
#include <boost/regex.hpp>
using namespace std;

class FileParser
{
    public: 
        string file_name;
        string language_used;
    /* Get a file from User */	
    void getFile()
    {
        cout<<"\t\t\t<----Interpret the Language of the file passed---->\n";
        cout<<"Enter the name of an existing  file: ";
        cin>>file_name;
    }
    /* Parsing a file Line by Line*/
    void fileRead()
    {
        ifstream file(file_name);//File Input Stream
        if (file.is_open())//Open a specified file if not return false  
        {
            for(string line; getline( file, line ); ) //Reading Line By Line
            {
    			
                findPattern(line);
            }			
            file.close();
        }
        else
        {
            cout<<"ERROR: Unable to open a file(File Not Exist or Permission Denied)\n";
        }
    }
    //Match Regular Expressions with line passed.
    void findPattern(string file_line)
    {
        //Regular Expression to find classes of java and php.
        const char* java_php_class = "^(public|private|protected)*[[:space:]]*" 
                                     "(class)[[:space:]]*"
                                     "(\\w*)[[:space:]]*"
                                     "(\\{)"; 

        //Regular Expression to find classess in ruby language.  
        const char* ruby_class = "(class)[[:space:]]*"
                                 "(\\w*)[[:space:]]*"; 	

        //Regular Expression to find ruby methods. 
        const char* ruby_def = "^[[:space:]]*"
                               "(def)[[:space:]]*"
                               "(\\w*)[[:space:]]*"
                               "(\\()*";

        //Regular Expression to find variables in ruby language.
        const char* ruby_var = "^[[:space:]]*"
                               "(@@)(\\w)[[:space:]]"
                               "(\\w*)[[:space:]]*";
         
        //Regular Expression to find methods in java.
        const char* java_method_var ="^[[:space:]]*"
                                     "(public|private|protected)[[:space:]]*"
                                     "(String|Integer|Float|void|Void)[[:space:]]*"
                                     "(\\w*)[[:space:]]*"
                                     "(\\()*"; 

        //Regular Expression to find <?php tag.
        const char* php_tag = "^[[:space:]]*<\\?php";

        //Regular Expression to find variables in PHP. 
        const char* php_var = "^[[:space:]]*"
                              "(var|public)[[:space:]]*(\\$)\\w[[:space:]]*"
                              "(\\w*)[[:space:]]*"; 

        //Regular Expression to find functions/methods in php.
        const char* php_function = "^[[:space:]]*"
                                   "(public|private|protected)*[[:space:]]*"
                                   "(function)[[:space:]]*" 
                                   "(\\w*)[[:space:]]*"
                                   "(\\()";

        //Regular Expression to find single line comments //.
        const char* single_line_comments = "^[[:space:]]*"
                                           "//";
        //Converting string to regular expressions
        boost::regex reg_class(java_php_class);    			
        boost::regex reg_ruby_class (ruby_class);
        boost::regex reg_ruby_def (ruby_def);
        boost::regex reg_ruby_var (ruby_var);
        boost::regex reg_php_tag (php_tag);
        boost::regex reg_php_var(php_var); 
        boost::regex reg_php_function (php_function);
        boost::regex reg_java_method_var(java_method_var);
        boost::regex reg_comment (single_line_comments);
      
        //Regular Expression matching for java and php classes
        if (regex_match (file_line,reg_class))
        {
            cout << file_line<<"\n";              
        }
        if (regex_search (file_line,reg_java_method_var))
        {
            cout << file_line<<"\n"; 
            language_used="Java Language Used.\t";             
        }
    			
        if (regex_match (file_line,reg_ruby_class))
        {
             cout << file_line<<"\n";              
        }
        //Method/def found then its ruby language
        if (regex_match (file_line,reg_ruby_def))
        {
            cout << file_line<<"\n";
            language_used = "Ruby Language Used.\t";
        }    				  

        if (regex_search (file_line,reg_ruby_var))
        {
            cout << file_line<<"\n";
        }
        //<?php found then its PHP language
        if (regex_search (file_line,reg_php_tag))
        {
            cout << file_line<<"\n";
            language_used = "PHP Language Used.\t";
        }
        if (regex_search (file_line,reg_php_var))
        {
            cout <<file_line<<"\n";
        }

        if (regex_search (file_line,reg_php_function))
        {
            cout <<file_line<<"\n";
            language_used = "PHP Language Used.\t";
        }
        if (regex_search (file_line,reg_comment))
        {
            cout << file_line<<"\n";
        }               
    }

};
int main()
{
    FileParser file_obj;
    file_obj.getFile();
    file_obj.fileRead();
    if(file_obj.language_used != "")
        cout<<"\n\n"<<file_obj.language_used<<"\n";
    file_obj.language_used="";
    return 0;
}
