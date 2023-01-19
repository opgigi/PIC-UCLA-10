#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <fstream>
#include <utility>

#ifndef COMPARE_H
#define COMPARE_H

/**
    @class CompareFiles

    this class is designed to store all the possible file path exist in the directory that user specify.  once the all the file paths are collected, then this class will find all the possible pairwise comparison path and then once it is done collecting all the pairwise path, then it will collect all the information and convert it into the single line char vector for the comparison.

    once two char vectors are ready then it will generate the boolean matrix based on how many letters are overlaps, and then it will create the matched_matrix to track how many letters are matched from those two char vectors.

    then the backtracking function will collect all the letters are overlaps and then will print out the part which part is overlapped.
    and let the user know how many characters are overlapped.

*/
class CompareFiles
{
private:

    // this is the file path variable that is set to be a root directory.
    // when the user is asked what directory that needed to be searched, then this root_dir will be passed through the constructor.
    std::filesystem::path root_directory;

    // this is the vector variable stores file paths. this vector is designed to store all the possible file path located in the directory for the pairing process.
    std::vector<std::filesystem::path> all_filepath_for_comparison;


public:


    std::vector<std::vector<bool>> current_boolean_table;

    /**
     this is the constructor, and designed for passing file path, which initializes root directory that user wants to search.

     @param root_directory : is the file path variable stores the directory path where the user wants to reach out to.
     */
    CompareFiles(std::filesystem::path root_directory);

    /**
     this function is designed to start from the root directory and using std::filesystem::recursive_directory_iterator, which enables to advance recursively through the entries of the directory and its child directory.

     then, using is_regular_file() to see that if there is a file in the subdirectory, will store every single file path into the file path vector all_filepath_for_comparison so we can create the pairwise file path vector for the comparison.
    */
    void find_all_filepath();

    /**
    this function is designed to pass the file path to open the file and the get all the char values from the file and store that into the single line char vector.
    once the insertion process is done, then it will close the file and clear and return the 1d char vector.

    @param target_file is the file path variable we are targeting to scan all the information it contains
    @return we are returning the 1d char vector.
    */
    std::vector<char> convert_into_singleline_txt(const std::filesystem::path target_file);

    /**
    this function is designed to compare two char vector and letter by letter and create the boolean matrix refers that which character is overlaps.


    @param char_vec_1 is the first char vector for creating matching boolean table by comparison
    @param char_vec_2 is the second char vector for creating matching boolean table by comparison
    @return this function returns 2d boolean vectors to store all the informations what letter matches and the one does not.
    */
    std::vector<std::vector<bool>> matches_boolean_table(const std::vector<char>* char_vec_1, const std::vector<char>* char_vec_2);

    /**
    this function is designed to create the matrix that based on the boolean table, which tracks the longest subsequences of char vector based on the given those two char vectors.

    @param char_vec_1 is the first char vector for creating matching table by comparison
    @param char_vec_2 is the second char vector for creating matching table by comparison
    @return it will return the 2d int vector tracks how many matched letters are there in the matrix.
    */
    std::vector<std::vector<int>> create_matching_table(const std::vector<char>* char_vec_1, const std::vector<char>* char_vec_2);


    /**
    this function is designed to compare two char vectors the figure out which char vec has more length compared to the other.

    @param char_vec_1 is the char vector to be compared for this function.
    @param char_vec_2 is the char vector to be compared for this function.
    @return this function will return the char vector has more larger size compared to the other char vector.
    */
    const std::vector<char>* vector_larger_size_comparison(const std::vector<char>* char_vec_1, const std::vector<char>* char_vec_2);

    /**
    this function is designed to compare two char vectors the figure out which char vec has less length compared to the other.

     @param char_vec_1 is the char vector to be compared for this function.
     @param char_vec_2 is the char vector to be compared for this function.
     @return this function will return the char vector has more smaller size compared to the other char vector.
    */
    const std::vector<char>* vector_smaller_size_comparison(const std::vector<char>* char_vec_1, const std::vector<char>* char_vec_2);

    /**
    this function is designed to read through the match matrix to find the longest subsequences using the backtracking method.
    backtracking method can be conducted by we set the index starts from the bottom right corner of the match matrix and checking that if the boolean table is true
    in that current index, store the word information and then move it to the diagonal, otherwise if left is smaller than its upper space, else move it to the left.

    @param matched_table is the match matrix that is generated from the match_making_matrix
    @param longest_possible_word is the longer char vector from the comparision between two char vecs after the function convert the file into the 1d char vecs.
    */
    void backtracking(std::vector<std::vector<int>>* matched_table, const std::vector<char>* longest_possible_word);

    /**
     this function is designed to find all the possible pairwise file path to compare between two files from two different directories.
     this function will calls the function find_all_filepath() to collect all the possible file path stores in the submission directory and store that into the all_filepath_for_comparison
     this function will create the vector stores the pairwise file path and then store every possible pairwise scenario into the variable.

     @return this function returns the vector stores the every possible scenario can be paired up.
     */
    std::vector<std::pair<std::filesystem::path, std::filesystem::path>> all_possible_pairing();

    /**
    this function that actually controls everything in the comparing process.
    this function will call the pairing function to find all the possible scenario that can files can be compared in the user-specified directory.

    then print out the directory path that shows which files are currently compared.

    then open those two files and store all the information into the 1d char vector for the comparison process.

    comparison function to run in three stages: call a function to generate the boolean matrix, then call a function to compute the longest common subsequence length from that matrix and set a matrix of path lengths, and then call a function to use the backtracking to compute the longest common subsequence from the boolean and length matrices.

    after all these process is completed then it will print out the common subsequence length and which part is overlapped between those two files.
    */
    void comparison_function();

};

#endif
